CREATE TABLE IF NOT EXISTS public.produtos
(
    id_produto integer NOT NULL,
    nome_produto character varying(255) COLLATE pg_catalog."default" NOT NULL,
    preco_custo numeric(10,2),
    preco_venda numeric(10,2),
    saldo integer,
    CONSTRAINT produtos_pkey PRIMARY KEY (id_produto)
)

CREATE TABLE IF NOT EXISTS public.compras
(
    id_compra integer NOT NULL,
    id_produto integer NOT NULL,
    quantidade integer NOT NULL,
    data_compra date NOT NULL,
    preco_unitario numeric(10,2) NOT NULL,
    CONSTRAINT compras_pkey PRIMARY KEY (id_compra),
    CONSTRAINT compras_id_produto_fkey FOREIGN KEY (id_produto)
        REFERENCES public.produtos (id_produto) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
)


CREATE TABLE IF NOT EXISTS public.vendas
(
    id_venda integer NOT NULL,
    id_produto integer NOT NULL,
    quantidade integer NOT NULL,
    data_venda date NOT NULL,
    preco_unitario numeric(10,2) NOT NULL,
    CONSTRAINT vendas_pkey PRIMARY KEY (id_venda),
    CONSTRAINT vendas_id_produto_fkey FOREIGN KEY (id_produto)
        REFERENCES public.produtos (id_produto) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
)

SELECT * FROM vendas
SELECT * FROM compras
SELECT * FROM produtos

/*Soma das compras*/
SELECT id_produto,
	SUM(quantidade) AS quantidade_comprada
FROM compras
GROUP BY id_produto

/*Soma das Vendas*/
SELECT id_produto,
	SUM(quantidade) AS quantidade_vendida
FROM vendas
GROUP BY id_produto

/*Estoque Atual*/
SELECT 
    p.id_produto,
    nome_produto,

    (SELECT SUM(COMPRAS.quantidade) 
     FROM compras COMPRAS 
     WHERE COMPRAS.id_produto = p.id_produto)
    AS Total_de_Compras,

    (SELECT SUM(VENDAS.quantidade) 
     FROM vendas VENDAS 
     WHERE VENDAS.id_produto = p.id_produto)
    AS Total_de_Vendas,

    (
        (SELECT SUM(COMPRAS.quantidade) 
         FROM compras COMPRAS 
         WHERE COMPRAS.id_produto = p.id_produto)
        -
        (SELECT SUM(VENDAS.quantidade) 
         FROM vendas VENDAS 
         WHERE VENDAS.id_produto = p.id_produto)
    ) AS Saldo

FROM PRODUTOS p;

/*Compras e vendas, porem usando CTE*/
WITH cte_produtos AS (
    SELECT 
        id_produto,
        nome_produto
    FROM produtos
),

cte_compras AS (
    SELECT 
        c.id_produto,
        SUM(c.quantidade) AS total_compras
    FROM compras c
    GROUP BY c.id_produto
),

cte_vendas AS (
    SELECT 
        v.id_produto,
        SUM(v.quantidade) AS total_vendas
    FROM vendas v
    GROUP BY v.id_produto
)

SELECT 
    p.id_produto,
    p.nome_produto,
    COALESCE(c.total_compras, 0) AS total_compras,
    COALESCE(v.total_vendas, 0) AS total_vendas,
    COALESCE(c.total_compras, 0) - COALESCE(v.total_vendas, 0) AS saldo

FROM cte_produtos p
LEFT JOIN cte_compras c ON p.id_produto = c.id_produto
LEFT JOIN cte_vendas v ON p.id_produto = v.id_produto;



/*Procedimento pra mostrar a info de um produto pelo ID*/
CREATE OR REPLACE PROCEDURE Procedure_mostrando_dados(p_id integer)
LANGUAGE plpgsql
AS $$
DECLARE 
    v_nome TEXT;
    v_total_compras INT;
    v_total_vendas INT;
    v_saldo INT;
BEGIN
    -- Nome do produto
    SELECT nome_produto
    INTO v_nome
    FROM produtos
    WHERE id_produto = p_id;

    -- Total de compras
    SELECT COALESCE(SUM(quantidade), 0)
    INTO v_total_compras
    FROM compras
    WHERE id_produto = p_id;

    -- Total de vendas
    SELECT COALESCE(SUM(quantidade), 0)
    INTO v_total_vendas
    FROM vendas
    WHERE id_produto = p_id;

    -- Saldo
    v_saldo := v_total_compras - v_total_vendas;

    -- Saída
    RAISE NOTICE 'Produto: %', v_nome;
    RAISE NOTICE 'Total de Compras: %', v_total_compras;
    RAISE NOTICE 'Total de Vendas: %', v_total_vendas;
    RAISE NOTICE 'Saldo: %', v_saldo;

END;
$$;
call Procedure_mostrando_dados(1)



/*Procedimento pra mostrar os produtos*/
CREATE OR REPLACE PROCEDURE mostra_nome_produtos()
AS $$
DECLARE
    v_reg RECORD;
BEGIN
    FOR v_reg IN SELECT nome_produto FROM produtos	
	LOOP
      RAISE NOTICE 'O nome  é %', v_reg.nome_produto;
	END LOOP;
END;
$$ LANGUAGE plpgsql;

call mostra_nome_produtos()