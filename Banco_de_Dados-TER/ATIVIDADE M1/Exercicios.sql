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