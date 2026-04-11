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

INSERT INTO itens_pedidos (id_pedido, id_livro, quantidade, preco_unitario) VALUES
(1, 1, 2, 150.00),
(2, 2, 1, 200.00),
(3, 3, 3, 180.50);

-- UPDATEs para testar auditoria
UPDATE Livros SET preco = 300.00 WHERE id_livro = 1;
UPDATE Livros SET preco = 180.00 WHERE id_livro = 2;

-- DELETEs de teste
DELETE FROM Clientes WHERE id_clientes = 1;
DELETE FROM Clientes WHERE nome = 'Teste Sem Pedido';
DELETE FROM Clientes

-- SELECTs finais
SELECT * FROM Livros;
SELECT * FROM Clientes;
SELECT * FROM Pedidos;
SELECT * FROM itens_pedidos;
SELECT * FROM log_auditoria;