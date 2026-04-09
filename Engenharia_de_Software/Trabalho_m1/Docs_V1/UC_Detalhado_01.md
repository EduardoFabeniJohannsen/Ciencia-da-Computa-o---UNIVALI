# UC01 — Gerenciar fila de atendimento

**Autor:**  
**Revisor:**  

## Ator primário
Profissional de saúde (enfermeiro ou médico)

---

## Objetivo
Permitir que o profissional visualize, organize e acompanhe a fila de pacientes, garantindo atendimento conforme prioridade clínica.

---

## Pré-condições
- Pacientes devem estar cadastrados no sistema  
- Pacientes devem ter passado pelo processo de triagem  
- Pacientes devem possuir uma classificação de prioridade  

---

## Pós-condições
- A fila de atendimento estará atualizada conforme prioridade  
- O próximo paciente elegível para atendimento estará definido  

---

## Fluxo principal

1. O profissional acessa a tela de gerenciamento de fila  
2. O sistema exibe a lista de pacientes em espera  
3. O sistema apresenta os pacientes ordenados por prioridade  
4. O sistema exibe informações relevantes (nome, prioridade e tempo estimado)  
5. O sistema atualiza automaticamente a fila em tempo real  
6. O profissional acompanha a ordem de atendimento  
7. O sistema mantém a fila organizada conforme regras de negócio  

---

## Fluxos alternativos

### FA01 — Alteração de prioridade
1. O profissional seleciona um paciente na fila  
2. O profissional altera a prioridade do paciente  
3. O sistema recalcula a ordem da fila  
4. O sistema atualiza a exibição da fila  

---

### FA02 — Entrada de novo paciente
1. Um novo paciente é inserido na fila após triagem  
2. O sistema recalcula automaticamente a posição do paciente  
3. O sistema atualiza a fila em tempo real  

---

## Exceção

### EX01 — Paciente sem triagem
1. O sistema identifica que o paciente não possui triagem registrada  
2. O sistema impede a inserção do paciente na fila  
3. O sistema exibe uma mensagem de erro ao profissional  

---

## Regras de negócio aplicáveis
- RN01 — Classificação por risco  
- RN02 — Prioridade de casos graves  
- RN03 — Ordenação da fila  
- RN04 — Atualização dinâmica  
- RN08 — Registro obrigatório de triagem  