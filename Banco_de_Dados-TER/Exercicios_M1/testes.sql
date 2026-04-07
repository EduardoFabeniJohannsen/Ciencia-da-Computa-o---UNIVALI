INSERT INTO Livros (titulo, autor, preco, quantidade_estoque) VALUES
('Redes de Computadores', 'Tanenbaum', 150.00, 6),
('Clean Code', 'Robert C. Martin', 200.00, 4),
('Engenharia de Software', 'Ian Sommerville', 180.50, 3);

INSERT INTO Clientes (nome, email) VALUES
('Joao Silva', 'joao@email.com'),
('Maria Oliveira', 'maria@email.com'),
('Carlos Pereira', 'carlos@email.com');

INSERT INTO Pedidos (id_cliente, data_pedido, stats) VALUES
(1, CURRENT_DATE, 'PENDENTE'),
(2, CURRENT_DATE, 'PAGO'),
(3, CURRENT_DATE, 'CANCELADO');

INSERT INTO itens_pedidos (id_pedido, id_livro, quantidade, preco_unitario) VALUES
(1, 1, 2, 150.00),
(2, 2, 1, 200.00),
(3, 3, 3, 180.50);

UPDATE Livros SET preco = 300.00 WHERE id_livro = 1;
UPDATE Livros SET preco = 180.00 WHERE id_livro = 2;

SELECT * FROM Livros;
SELECT * FROM Clientes;
SELECT * FROM Pedidos;
SELECT * FROM itens_pedidos;
SELECT * FROM log_auditoria;