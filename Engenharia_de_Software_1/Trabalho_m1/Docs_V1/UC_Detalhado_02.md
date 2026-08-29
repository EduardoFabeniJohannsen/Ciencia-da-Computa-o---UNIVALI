# UC02 — Registrar triagem

**Autor:**  
**Revisor:**  

## Ator primário
Enfermeiro (triagem)

---

## Objetivo
Permitir o registro das informações clínicas iniciais do paciente para definição de prioridade no atendimento.

---

## Pré-condições
- O paciente deve estar previamente cadastrado no sistema  

---

## Pós-condições
- As informações de triagem do paciente estarão registradas  
- O paciente estará apto para classificação de prioridade  

---

## Fluxo principal

1. O enfermeiro acessa a tela de triagem  
2. O enfermeiro seleciona o paciente cadastrado  
3. O sistema exibe os dados do paciente  
4. O enfermeiro insere informações clínicas (sintomas, sinais vitais e observações)  
5. O enfermeiro confirma o registro da triagem  
6. O sistema armazena as informações inseridas  
7. O sistema disponibiliza os dados para classificação de prioridade  

---

## Fluxos alternativos

### FA01 — Atualização de triagem
1. O enfermeiro acessa uma triagem já registrada  
2. O enfermeiro altera os dados clínicos  
3. O sistema atualiza as informações  
4. O sistema sinaliza a necessidade de reclassificação de prioridade  

---

## Exceção

### EX01 — Dados obrigatórios não preenchidos
1. O enfermeiro tenta confirmar a triagem sem preencher todos os campos obrigatórios  
2. O sistema identifica a ausência de informações essenciais  
3. O sistema impede o registro da triagem  
4. O sistema exibe mensagem solicitando o preenchimento dos campos obrigatórios  

---

## Regras de negócio aplicáveis
- RN01 — Classificação por risco  
- RN05 — Ajuste por profissional  
- RN08 — Registro obrigatório de triagem  