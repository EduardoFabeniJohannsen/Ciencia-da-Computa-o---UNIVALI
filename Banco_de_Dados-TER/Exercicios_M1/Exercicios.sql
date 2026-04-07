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