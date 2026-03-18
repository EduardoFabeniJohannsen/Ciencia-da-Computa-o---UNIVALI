-- Creates basicos para começar a atividade
CREATE DATABASE aula_Emerson;
CREATE TABLE Aluno(
	id SERIAL PRIMARY KEY,
	nome TEXT NOT NULL	
);

-- COMEÇO -> Comando para inserir/apagar/ver os dados e testar
INSERT INTO Aluno
VALUES(1,'teste A'),
	  (2,' teste B'),
	  (3,'teste C ');

-- Ver o que foi feito nos dados
SELECT * FROM Aluno;

-- remover triggers antigas
DROP TRIGGER IF EXISTS Corrigir_Espacos_Nome ON Aluno;
DROP TRIGGER IF EXISTS Bloquear_Nome_Sem_Sobrenome ON Aluno;

-- Derrubar tudo do 0
TRUNCATE TABLE Aluno;
-- FIM -> Comando para inserir/apagar/ver os dados e testar


CREATE OR REPLACE FUNCTION Bloquar_nome_com_espacos_no_comecoEfim()
RETURNS TRIGGER AS $$
BEGIN
	NEW.nome := TRIM(regexp_replace(NEW.nome, ' +', ' ', 'g'));
    RETURN NEW;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION Validar_Nome_Com_Sobrenome()
RETURNS TRIGGER AS $$
BEGIN
    IF SPLIT_PART(TRIM(NEW.nome), ' ', 2) = '' THEN
        RAISE EXCEPTION 'Erro! É necessário sobrenome';
    END IF;
	RAISE NOTICE 'Aluno "%" inserido com sucesso', new.nome;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;



-- criar primeiro a de correção
CREATE TRIGGER Corrigir_Espacos_Nome
BEFORE INSERT OR UPDATE
ON Aluno
FOR EACH ROW
EXECUTE FUNCTION Bloquar_nome_com_espacos_no_comecoEfim();

-- depois a de validação
CREATE TRIGGER Bloquear_Nome_Sem_Sobrenome
BEFORE INSERT OR UPDATE
ON Aluno
FOR EACH ROW
EXECUTE FUNCTION Validar_Nome_Com_Sobrenome();


