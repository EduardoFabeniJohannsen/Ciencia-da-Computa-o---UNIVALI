-- Creates basicos para começar a atividade
CREATE DATABASE aula_Emerson;

CREATE TABLE Aluno(
	id SERIAL PRIMARY KEY,
	nome TEXT NOT NULL	
);

CREATE TABLE LOG_Exclusoes(
	id SERIAL PRIMARY KEY,
	id_aluno INT FOREN KEY REFERENCES Aluno(id),
	nome TEXT NOT NULL,
	data_exclusao TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
)

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


-- Exercicio 1
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

CREATE TRIGGER Bloquear_Nome_Sem_Sobrenome
BEFORE INSERT OR UPDATE
ON Aluno
FOR EACH ROW
EXECUTE FUNCTION Validar_Nome_Com_Sobrenome();


-- Exercicio 2
CREATE OR REPLACE FUNCTION Converter_nome_para_maiusculo()
RETURNS TRIGGER AS $$
BEGIN 
	IF NEW.nome != UPPER(NEW.nome) THEN
		NEW.nome = UPPER(NEW.nome);
		RAISE NOTICE 'Nome alterado de % para %', OLD.nome, new.nome;
		RETURN NEW;
	END IF
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER Garantir_Nome_Maiusculo()
BEFORE INSERT OR UPDATE
ON Aluno
FOR EACH ROW
EXECUTE FUNCTION Converter_nome_para_maiusculo();

-- Exercicio 3
CREATE OR REPLACE FUNCTION Registrar_Exclusao_Aluno()
RETURNS TRIGGER AS $$
BEGIN
	INSERT INTO LOG_Exclusoes(id_aluno, nome)
	VALUES(OLD.id, OLD.nome);
	
	RAISE NOTICE 'Aluno "%" excluído e registrado no log', OLD.nome;
	RETURN OLD;
END
$$ LANGUAGE plpgsql;

CREATE TRIGGER Chamar_Registrar_Exclusao_Aluno()
BEFORE DELETE
ON Aluno
FOR EACH ROW
EXECUTE FUNCTION Registrar_Exclusao_Aluno();

-- Exercicio 4
CREATE OR REPLACE FUNCTION Avisar_Mudanva_Nome()
RETURNS TRIGGER AS $$
BEGIN
	RAISE NOTICE 'Aluno "%" alterado nome para %', OLD.nome,NEW.nome;
END
$$ LANGUAGE plpgsql;

CREATE TRIGGER Chamar_Avisar_Mudanva_Nome()
BEFORE UPDATE
ON Aluno
FOR EACH ROW
EXECUTE FUNCTION Chamar_Avisar_Mudanva_Nome();