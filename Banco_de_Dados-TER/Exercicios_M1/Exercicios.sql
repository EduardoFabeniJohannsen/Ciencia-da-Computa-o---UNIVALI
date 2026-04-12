

-- Exercicio 1
CREATE OR REPLACE FUNCTION Auditar_Alteracao_Preco()
RETURNS TRIGGER AS $$
BEGIN

    -- Só registra se o preço realmente mudou
    IF OLD.preco <> NEW.preco THEN

        INSERT INTO log_auditoria (
            tabela_afetada,
            id_registro_afetado,
            operacao,
            preco_antigo,
            preco_novo,
            data_operacao
        )
        VALUES (
            'livros',
            OLD.id_livro,
            'UPDATE',
            OLD.preco,
            NEW.preco,
            CURRENT_TIMESTAMP
        );

    END IF;

    RETURN NEW;

END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER Trigger_Auditar_Preco
AFTER UPDATE
ON livros
FOR EACH ROW
EXECUTE FUNCTION Auditar_Alteracao_Preco();


-- Exercicio 2
CREATE OR REPLACE FUNCTION Converter_Email_Minusculo()
RETURNS TRIGGER AS $$
BEGIN
    NEW.email := LOWER(NEW.email);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER Trigger_Email_Minusculo
BEFORE INSERT OR UPDATE
ON Clientes
FOR EACH ROW
EXECUTE FUNCTION Converter_Email_Minusculo();

-- Exercicio 3
CREATE OR REPLACE FUNCTION Controlar_Estoque()
RETURNS TRIGGER AS $$
DECLARE
    estoque_atual INTEGER;
BEGIN
    -- Busca o estoque atual do livro
    SELECT quantidade_estoque
    INTO estoque_atual
    FROM Livros
    WHERE id_livro = NEW.id_livro;

    -- Verifica se há estoque suficiente
    IF estoque_atual < NEW.quantidade THEN
        RAISE EXCEPTION 'Erro: estoque insuficiente para o livro ID %', NEW.id_livro;
    END IF;

    -- Realiza a baixa no estoque
    UPDATE Livros
    SET quantidade_estoque = quantidade_estoque - NEW.quantidade
    WHERE id_livro = NEW.id_livro;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER Trigger_Controlar_Estoque
BEFORE INSERT
ON itens_pedidos
FOR EACH ROW
EXECUTE FUNCTION Controlar_Estoque();

-- Exercicio 4

CREATE OR REPLACE FUNCTION Impedir_Exclusao_Cliente()
RETURNS TRIGGER AS $$
BEGIN
    -- Verifica se o cliente possui pedidos
    IF EXISTS (
        SELECT 1
        FROM Pedidos
        WHERE id_cliente = OLD.id_clientes
    ) THEN
        RAISE EXCEPTION 'Erro: cliente possui pedidos e não pode ser excluído';
    END IF;

    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER Trigger_Impedir_Exclusao_Cliente
BEFORE DELETE
ON Clientes
FOR EACH ROW
EXECUTE FUNCTION Impedir_Exclusao_Cliente();


-- Exercicio 5

CREATE OR REPLACE FUNCTION Atualizar_Status_Pedido()
RETURNS TRIGGER AS $$
BEGIN
    -- Verifica se o item foi marcado como enviado
    IF NEW.status_item = 'enviado' THEN

        -- Verifica se ainda existe algum item não enviado
        IF NOT EXISTS (
            SELECT 1
            FROM itens_pedidos
            WHERE id_pedido = NEW.id_pedido
            AND status_item <> 'enviado'
        ) THEN

            -- Atualiza o status do pedido
            UPDATE Pedidos
            SET stats = 'Concluído'
            WHERE id_pedidos = NEW.id_pedido;

        END IF;

    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER Trigger_Atualizar_Status_Pedido
AFTER UPDATE
ON itens_pedidos
FOR EACH ROW
EXECUTE FUNCTION Atualizar_Status_Pedido();

-- Exercicio 6

CREATE OR REPLACE FUNCTION Relatorio_Vendas_Cliente(p_id_cliente INTEGER)
RETURNS TABLE (
    nome_cliente TEXT,
    total_pedidos INTEGER,
    valor_total NUMERIC(10,2)
) AS $$
BEGIN
    RETURN QUERY
    SELECT 
        c.nome,
        COUNT(DISTINCT p.id_pedidos)::INTEGER,
        COALESCE(SUM(ip.quantidade * ip.preco_unitario), 0)
    FROM Clientes c
    LEFT JOIN Pedidos p ON p.id_cliente = c.id_clientes
    LEFT JOIN itens_pedidos ip ON ip.id_pedido = p.id_pedidos
    WHERE c.id_clientes = p_id_cliente
    GROUP BY c.nome;
END;
$$ LANGUAGE plpgsql;



-- Exercicio 7
CREATE OR REPLACE FUNCTION Repor_Estoque(p_id_livro INTEGER, p_quantidade INTEGER)
RETURNS VOID AS $$
DECLARE
    estoque_antigo INTEGER;
BEGIN
    -- busca estoque atual
    SELECT quantidade_estoque
    INTO estoque_antigo
    FROM Livros
    WHERE id_livro = p_id_livro;

    -- valida existência
    IF estoque_antigo IS NULL THEN
        RAISE EXCEPTION 'Livro não encontrado';
    END IF;

    -- atualiza estoque
    UPDATE Livros
    SET quantidade_estoque = quantidade_estoque + p_quantidade
    WHERE id_livro = p_id_livro;

    -- registra log
    INSERT INTO log_auditoria (
        tabela_afetada,
        id_registro_afetado,
        operacao,
        preco_antigo,
        preco_novo,
        data_operacao
    )
    VALUES (
        'livros',
        p_id_livro,
        'REPOSICAO_ESTOQUE',
        estoque_antigo,
        estoque_antigo + p_quantidade,
        CURRENT_DATE
    );
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION Verificar_E_Repor_Estoque()
RETURNS TRIGGER AS $$
DECLARE
    estoque_atual INTEGER;
BEGIN
    -- pega estoque atual
    SELECT quantidade_estoque
    INTO estoque_atual
    FROM Livros
    WHERE id_livro = NEW.id_livro;

    -- verifica limite mínimo
    IF estoque_atual <= 5 THEN
        -- chama a procedure de reposição (ex: repor 10 unidades)
        PERFORM Repor_Estoque(NEW.id_livro, 10);
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;



CREATE TRIGGER Trigger_Repor_Estoque
AFTER INSERT
ON itens_pedidos
FOR EACH ROW
EXECUTE FUNCTION Verificar_E_Repor_Estoque();


-- Exercicio 8
CREATE OR REPLACE FUNCTION Cancelar_Pedido(p_id_pedido INTEGER)
RETURNS VOID AS $$
DECLARE
    item RECORD;
BEGIN
    -- Verifica se o pedido existe
    IF NOT EXISTS (
        SELECT 1 FROM Pedidos WHERE id_pedidos = p_id_pedido
    ) THEN
        RAISE EXCEPTION 'Pedido não encontrado';
    END IF;

    -- Devolve os itens ao estoque
    FOR item IN
        SELECT id_livro, quantidade
        FROM itens_pedidos
        WHERE id_pedido = p_id_pedido
    LOOP
        UPDATE Livros
        SET quantidade_estoque = quantidade_estoque + item.quantidade
        WHERE id_livro = item.id_livro;
    END LOOP;

    -- Atualiza status do pedido
    UPDATE Pedidos
    SET stats = 'Cancelado'
    WHERE id_pedidos = p_id_pedido;

    -- Registra log
    INSERT INTO log_auditoria (
        tabela_afetada,
        id_registro_afetado,
        operacao,
        data_operacao
    )
    VALUES (
        'pedidos',
        p_id_pedido,
        'CANCELAMENTO_PEDIDO',
        CURRENT_DATE
    );

END;
$$ LANGUAGE plpgsql;

-- Exercicio 9
CREATE OR REPLACE FUNCTION Ranking_Livros_Mais_Vendidos(p_mes INTEGER, p_ano INTEGER)
RETURNS TABLE (
    titulo TEXT,
    autor TEXT,
    total_vendido INTEGER
) AS $$
BEGIN
    RETURN QUERY
    SELECT 
        l.titulo,
        l.autor,
        SUM(ip.quantidade)::INTEGER
    FROM itens_pedidos ip
    JOIN pedidos p ON p.id_pedidos = ip.id_pedido
    JOIN livros l ON l.id_livro = ip.id_livro
    WHERE EXTRACT(MONTH FROM p.data_pedido) = p_mes
      AND EXTRACT(YEAR FROM p.data_pedido) = p_ano
    GROUP BY l.titulo, l.autor
    ORDER BY total_vendido DESC
    LIMIT 5;
END;
$$ LANGUAGE plpgsql;