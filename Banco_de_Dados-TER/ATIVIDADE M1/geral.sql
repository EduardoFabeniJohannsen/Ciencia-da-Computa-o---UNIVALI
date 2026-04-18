-- Inserindo pedidos
CALL registrar_pedido('Saldanha', 1500);
CALL registrar_pedido('Fulano', 1100);

-- Atualizando status
UPDATE pedidos SET status_pedido = 'Processado' WHERE id = 1;
UPDATE pedidos SET status_pedido = 'Cancelado' WHERE id = 2;

-- Tentando deletar (vai dar erro se não for Pendente)
DELETE FROM pedidos WHERE id = 1;

-- Inserir um pendente pra testar delete
CALL registrar_pedido('Teste', 500);

DELETE FROM pedidos WHERE cliente = 'Teste';

-- Ver logs
SELECT * FROM log_pedidos;

-- Teste relatório
CALL relatorios_vendas('2024-01-01', '2025-12-31');