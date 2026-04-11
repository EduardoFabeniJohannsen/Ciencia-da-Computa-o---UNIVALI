-- LIMPAR TODAS AS TABELAS (ordem correta por causa das FKs)
TRUNCATE TABLE itens_pedidos, pedidos, clientes, livros, log_auditoria RESTART IDENTITY CASCADE;

-- INSERTS
INSERT INTO Livros (titulo, autor, preco, quantidade_estoque) VALUES
('Redes de Computadores', 'Tanenbaum', 150.00, 6),
('Clean Code', 'Robert C. Martin', 200.00, 4),
('Engenharia de Software', 'Ian Sommerville', 180.50, 3);

INSERT INTO Clientes (nome, email) VALUES
('Joao Silva', 'joao@email.com'),
('Maria Oliveira', 'maria@email.com'),
('Carlos Pereira', 'carlos@email.com'),
('Teste Sem Pedido', 'teste@email.com');

INSERT INTO Pedidos (id_cliente, data_pedido, stats) VALUES
(1, CURRENT_DATE, 'PENDENTE'),
(2, CURRENT_DATE, 'PAGO'),
(3, CURRENT_DATE, 'CANCELADO');

INSERT INTO itens_pedidos (id_pedido, id_livro, quantidade, preco_unitario, status_item) VALUES
(1, 1, 2, 150.00, 'pendente'),
(1, 2, 1, 200.00, 'pendente'),
(2, 2, 1, 200.00, 'pendente'),
(3, 3, 3, 180.50, 'pendente');

-- UPDATEs para testar auditoria
UPDATE Livros SET preco = 300.00 WHERE id_livro = 1;
UPDATE Livros SET preco = 180.00 WHERE id_livro = 2;

-- UPDATEs para testar trigger de status

-- ainda não conclui
UPDATE itens_pedidos
SET status_item = 'enviado'
WHERE id_item = 1;

-- agora conclui pedido 1
UPDATE itens_pedidos
SET status_item = 'enviado'
WHERE id_pedido = 1;

-- DELETEs de teste

-- deve falhar
DELETE FROM Clientes WHERE id_clientes = 1;

-- deve funcionar
DELETE FROM Clientes WHERE nome = 'Teste Sem Pedido';

-- SELECTs finais
SELECT * FROM Livros;
SELECT * FROM Clientes;
SELECT * FROM Pedidos;
SELECT * FROM itens_pedidos;
SELECT * FROM log_auditoria;