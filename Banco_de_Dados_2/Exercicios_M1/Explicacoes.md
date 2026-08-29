Nível 1: Conceitos Básicos e Auditoria Simples

Exercício 1: Rastreando Alterações de Preços

Descrição: A gerência da livraria precisa de um histórico de todas as alterações de preços dos livros para
análise de precificação.

Descreva como você implementaria um trigger para auditar essas mudanças.
R: Eu implementaria um trigger que é acionado sempre que ocorre uma atualização na tabela de livros. Esse trigger chamaria uma função responsável por verificar se o preço foi alterado e, caso tenha sido, inserir um registro na tabela de log_auditoria contendo as informações da mudança.

Em qual tabela o trigger deve ser criado e a que evento(s) (INSERT, UPDATE, DELETE) ele deve responder?
Justifique sua escolha.
R: O trigger deve ser criado na tabela Livros e responder ao evento UPDATE. Isso porque o objetivo é monitorar alterações de preço, que só ocorrem em operações de atualização. O uso de INSERT não é necessário, pois não há alteração de valor inicial, e DELETE também não é relevante para esse caso, pois o registro seria removido.

Que informações seriam essenciais para armazenar na tabela log_auditoria sempre que o preço de um livro
for alterado?
R: As informações essenciais são: o nome da tabela afetada (livros), o ID do registro alterado (id_livro), o tipo da operação (UPDATE), o preço antigo, o preço novo e a data da alteração. Esses dados permitem identificar claramente qual livro sofreu alteração, quando ocorreu e quais foram os valores envolvidos.

Como você usaria as variáveis especiais OLD e NEW dentro da função do trigger para capturar o preço antigo
e o novo preço?
R: As variáveis OLD e NEW são utilizadas para acessar os valores antes e depois da atualização. O preço antigo é obtido com OLD.preco e o novo preço com NEW.preco. Dessa forma, é possível comparar os dois valores e registrar a alteração apenas quando houver diferença entre eles, garantindo um log mais preciso.

====================

Exercício 2: Garantindo a Consistência do E-mail do Cliente

Descrição:
Para evitar problemas de comunicação, a livraria quer garantir que todos os e-mails de clientes sejam armazenados em letras minúsculas.

Qual é o melhor momento para executar essa lógica: BEFORE ou AFTER a inserção ou atualização de um registro na tabela clientes?
Explique o porquê.
R: O melhor momento é BEFORE INSERT ou UPDATE, pois assim o valor do e-mail pode ser modificado antes de ser salvo no banco de dados. Isso garante que o dado já seja armazenado corretamente, evitando inconsistências e não sendo necessário corrigir depois.

Como você modificaria o valor do campo de e-mail antes que ele seja salvo no banco de dados, utilizando a estrutura de um trigger?
R: Utilizaria a variável NEW dentro da função do trigger para alterar diretamente o valor do campo antes da inserção ou atualização. Nesse caso, aplicaria a função LOWER no campo NEW.email, garantindo que o valor seja convertido para letras minúsculas antes de ser persistido no banco.

Desenvolva a função do trigger que converte o e-mail para minúsculas e associe-a à tabela clientes.
R:No código



==============================


Nível 2: Validação de Regras de Negócio

Exercício 3: Prevenindo Estoque Negativo

Descrição: É crucial para o sistema da livraria que a quantidade de um livro em estoque nunca se torne
negativa. Proponha uma solução usando triggers para impor essa regra de negócio.

Este trigger deve ser associado à tabela livros ou itens_pedido? A que evento(s) ele deve reagir? Justifique.
R: O trigger deve ser associado à tabela itens_pedido, pois é nela que ocorre a saída de estoque quando um item é adicionado a um pedido. Ele deve reagir ao evento BEFORE INSERT, pois assim é possível validar a quantidade antes da inserção e impedir a operação caso o estoque seja insuficiente.

Como você implementaria a lógica para verificar o estoque disponível antes de confirmar a inserção de um
novo item em um pedido?
R: A lógica consiste em consultar a quantidade disponível na tabela livros utilizando o id_livro do item que está sendo inserido. Em seguida, compara-se o valor com a quantidade solicitada (NEW.quantidade). Se o estoque disponível for menor que a quantidade solicitada, a operação deve ser bloqueada.

O que o trigger deveria fazer se a quantidade pedida for maior que o estoque disponível? (Dica: pense em
como interromper a operação e notificar o usuário).
R: O trigger deve interromper a operação utilizando RAISE EXCEPTION, exibindo uma mensagem de erro informando que o estoque é insuficiente. Isso impede que o registro seja inserido e mantém a consistência dos dados.

Crie a função e o trigger que realizam a baixa no estoque da tabela livros após a inserção de um novo
itens_pedido e que, ao mesmo tempo, valide se o estoque se tornaria negativo.
R: No código

=======

Exercício 4: Impedindo a Exclusão de Clientes com Pedidos

Descrição: Para manter a integridade do histórico de vendas, um cliente que já realizou um pedido não pode
ser excluído do sistema.

O trigger deve ser do tipo BEFORE ou AFTER DELETE na tabela clientes? Por quê?
R: O trigger deve ser do tipo BEFORE DELETE, pois é necessário validar a existência de pedidos antes que a exclusão ocorra. Dessa forma, é possível impedir a operação antes que o registro seja removido do banco de dados.

Como a função do trigger pode verificar se existem registros na tabela pedidos associados ao cliente que está
sendo excluído?
R: A função pode realizar uma consulta na tabela pedidos utilizando o id do cliente (OLD.id_clientes) para verificar se existem registros associados. Isso pode ser feito com um SELECT COUNT ou utilizando EXISTS para verificar a existência de pelo menos um pedido.

Qual ação o trigger deve tomar caso o cliente possua pedidos? Como ele pode impedir a exclusão?
R: Caso o cliente possua pedidos, o trigger deve interromper a operação utilizando RAISE EXCEPTION, exibindo uma mensagem de erro. Isso impede a exclusão do registro e garante a integridade dos dados.

Implemente a solução completa (função e trigger).
R: No código

=======

Exercício 5: Atualização Automática do Status do Pedido

Descrição: A livraria deseja automatizar a atualização do status de um pedido. Sempre que o último item de
um pedido for marcado como "enviado", o status do pedido na tabela pedidos deve ser atualizado para "Concluído".

O trigger deve monitorar qual tabela e qual evento para essa automação?
R: O trigger deve monitorar a tabela itens_pedidos e reagir ao evento UPDATE, pois a mudança de status ocorre nos itens do pedido. Sempre que um item for atualizado, é necessário verificar se todos os itens daquele pedido já foram enviados.

Dentro da função do trigger, como você verificaria se todos os outros itens do mesmo pedido também já foram
enviados?
R: A verificação pode ser feita com uma consulta na tabela itens_pedidos buscando itens do mesmo id_pedido cujo status_item seja diferente de "enviado". Se não existir nenhum registro nessas condições, significa que todos os itens já foram enviados. Isso pode ser feito utilizando NOT EXISTS.

Descreva os passos lógicos que a função do trigger executaria para, após uma atualização em itens_pedido,
decidir se deve ou não atualizar a tabela pedidos.
R: Primeiro, o trigger verifica se o status do item foi alterado para "enviado". Em seguida, consulta a tabela itens_pedidos para verificar se ainda existem itens do mesmo pedido que não foram enviados. Se não existir nenhum, a função atualiza o status do pedido na tabela pedidos para "Concluído". Caso contrário, nenhuma ação é realizada.

Escreva o código PL/pgSQL para esta funcionalidade
R:git