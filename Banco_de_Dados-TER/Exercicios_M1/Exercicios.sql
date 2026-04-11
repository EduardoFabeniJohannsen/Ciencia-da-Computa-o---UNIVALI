

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