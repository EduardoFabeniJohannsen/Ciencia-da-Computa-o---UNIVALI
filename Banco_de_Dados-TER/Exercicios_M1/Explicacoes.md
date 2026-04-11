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