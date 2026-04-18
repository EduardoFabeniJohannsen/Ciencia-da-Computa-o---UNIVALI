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