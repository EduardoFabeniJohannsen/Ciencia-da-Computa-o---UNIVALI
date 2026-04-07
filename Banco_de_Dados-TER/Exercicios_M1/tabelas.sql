CREATE TABLE Livros (
	id_livro SERIAL PRIMARY KEY,
	titulo TEXT NOT NULL,
	autor TEXT NOT NULL,
	preco NUMERIC(10,2) NOT NULL,
	quantidade_estoque INTEGER NOT NULL
);

CREATE TABLE Clientes (
	id_clientes SERIAL PRIMARY KEY,
	nome TEXT NOT NULL,
	email TEXT UNIQUE NOT NULL
);

CREATE TABLE Pedidos (
	id_pedidos SERIAL PRIMARY KEY,
	id_cliente INTEGER NOT NULL,
	data_pedido DATE NOT NULL,
	stats TEXT NOT NULL,

    CONSTRAINT fk_cliente
        FOREIGN KEY (id_cliente)
        REFERENCES clientes(id_clientes)
        ON DELETE CASCADE
);

CREATE TABLE itens_pedidos (
	id_item SERIAL PRIMARY KEY,
	id_pedido INTEGER NOT NULL,
	id_livro INTEGER NOT NULL,
	quantidade INTEGER NOT NULL,
	preco_unitario NUMERIC(10,2) NOT NULL,

		CONSTRAINT fk_pedido
		FOREIGN KEY(id_pedido)
		REFERENCES Pedidos(id_pedidos)
		ON DELETE CASCADE,

		CONSTRAINT fk_livro
		FOREIGN KEY(id_livro)
		REFERENCES Livros(id_livro)
		ON DELETE CASCADE
);

CREATE TABLE log_auditoria(
	id_log SERIAL PRIMARY KEY,
	tabela_afetada TEXT NOT NULL,
	id_registro_afetado INTEGER,
	operacao TEXT NOT NULL,
	preco_antigo NUMERIC(10,2),
	preco_anovo NUMERIC(10,2)
);

