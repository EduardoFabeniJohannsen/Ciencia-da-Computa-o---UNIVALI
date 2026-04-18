CREATE TABLE pedidos (
    id SERIAL PRIMARY KEY,
    cliente VARCHAR(100) NOT NULL,
    data_pedido TIMESTAMP,
    valor NUMERIC(10,2),
    status_pedido VARCHAR(20)
);

CREATE TABLE log_pedidos (
    id SERIAL PRIMARY KEY,
    pedido_id INT,
    operacao VARCHAR(50),
    data_log TIMESTAMP
);