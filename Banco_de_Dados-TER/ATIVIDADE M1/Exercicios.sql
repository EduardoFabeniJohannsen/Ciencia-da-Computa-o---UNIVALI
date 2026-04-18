-- QUESTÃO 1
CREATE OR REPLACE PROCEDURE registrar_pedido(
    p_cliente VARCHAR,
    p_valor NUMERIC
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_id INT;
BEGIN
    INSERT INTO pedidos(cliente, data_pedido, valor, status_pedido)
    VALUES (p_cliente, NOW(), p_valor, 'Pendente')
    RETURNING id INTO v_id;

    RAISE NOTICE 'Pedido criado com ID: %', v_id;
END;
$$;


-- QUESTÃO 2
CREATE OR REPLACE PROCEDURE relatorios_vendas(
    p_data_inicio TIMESTAMP,
    p_data_fim TIMESTAMP
)
LANGUAGE plpgsql
AS $$
BEGIN
    SELECT 
        cliente,
        TO_CHAR(data_pedido, 'Month/YYYY') AS mes_ano,
        SUM(valor) AS total_vendas
    FROM pedidos
    WHERE data_pedido BETWEEN p_data_inicio AND p_data_fim
      AND status_pedido NOT IN ('Cancelado', 'Pendente')
    GROUP BY cliente, mes_ano
    ORDER BY total_vendas DESC;
END;
$$;

-- QUESTÃO 3    
-- INSERT
CREATE OR REPLACE FUNCTION trg_insert_pedido()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO log_pedidos(pedido_id, operacao, data_log)
    VALUES (NEW.id, 'INSERT', NOW());

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_insert_pedido
AFTER INSERT ON pedidos
FOR EACH ROW
EXECUTE FUNCTION trg_insert_pedido();

-- UPDATE
CREATE OR REPLACE FUNCTION trg_update_pedido()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.status_pedido IN ('Processado', 'Cancelado') THEN
        INSERT INTO log_pedidos(pedido_id, operacao, data_log)
        VALUES (NEW.id, 'UPDATE - ' || NEW.status_pedido, NOW());
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_pedido
AFTER UPDATE ON pedidos
FOR EACH ROW
EXECUTE FUNCTION trg_update_pedido();

-- DELETE
CREATE OR REPLACE FUNCTION trg_delete_pedido()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.status_pedido <> 'Pendente' THEN
        RAISE EXCEPTION 'Só é possível deletar pedidos com status Pendente!';
    END IF;

    INSERT INTO log_pedidos(pedido_id, operacao, data_log)
    VALUES (OLD.id, 'DELETE', NOW());

    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_delete_pedido
BEFORE DELETE ON pedidos
FOR EACH ROW
EXECUTE FUNCTION trg_delete_pedido();

-- QUESTÃO 4
CREATE OR REPLACE FUNCTION trg_monitor_pedidos()
RETURNS TRIGGER AS $$
BEGIN

    -- INSERT
    IF TG_OP = 'INSERT' THEN
        INSERT INTO log_pedidos(pedido_id, operacao, data_log)
        VALUES (NEW.id, 'INSERT', NOW());
        RETURN NEW;
    END IF;

    -- UPDATE
    IF TG_OP = 'UPDATE' THEN
        IF NEW.status_pedido IN ('Processado', 'Cancelado') THEN
            INSERT INTO log_pedidos(pedido_id, operacao, data_log)
            VALUES (NEW.id, 'UPDATE - ' || NEW.status_pedido, NOW());
        END IF;
        RETURN NEW;
    END IF;

    -- DELETE
    IF TG_OP = 'DELETE' THEN
        IF OLD.status_pedido <> 'Pendente' THEN
            RAISE EXCEPTION 'Só é possível deletar pedidos Pendente!';
        END IF;

        INSERT INTO log_pedidos(pedido_id, operacao, data_log)
        VALUES (OLD.id, 'DELETE', NOW());

        RETURN OLD;
    END IF;

END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_monitor_pedidos
AFTER INSERT OR UPDATE OR DELETE ON pedidos
FOR EACH ROW
EXECUTE FUNCTION trg_monitor_pedidos();