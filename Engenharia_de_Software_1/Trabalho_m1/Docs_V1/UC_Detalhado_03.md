# UC03 — Classificar prioridade

**Autor:**  
**Revisor:**  

## Ator primário
Sistema

## Atores secundários
Enfermeiro (triagem)

---

## Objetivo
Classificar automaticamente o paciente em um nível de prioridade com base nas informações registradas na triagem.

---

## Pré-condições
- O paciente deve ter triagem registrada no sistema  
- As informações clínicas devem estar completas  

---

## Pós-condições
- O paciente terá uma prioridade definida  
- O paciente estará apto para inserção na fila de atendimento  

---

## Fluxo principal

1. O sistema recebe os dados da triagem do paciente  
2. O sistema analisa as informações clínicas (sintomas, sinais vitais e observações)  
3. O sistema aplica as regras de classificação de risco  
4. O sistema define automaticamente o nível de prioridade do paciente  
5. O sistema registra a prioridade atribuída  
6. O sistema disponibiliza o paciente para inserção na fila  

---

## Fluxos alternativos

### FA01 — Reclassificação manual
1. O enfermeiro analisa a prioridade definida pelo sistema  
2. O enfermeiro identifica necessidade de ajuste  
3. O enfermeiro altera manualmente a prioridade  
4. O sistema registra a nova prioridade  
5. O sistema atualiza os dados do paciente  

---

## Exceção

### EX01 — Dados insuficientes para classificação
1. O sistema identifica ausência ou inconsistência nos dados da triagem  
2. O sistema não realiza a classificação automática  
3. O sistema solicita revisão dos dados ao enfermeiro  
4. O paciente permanece sem prioridade definida até correção  

---

## Regras de negócio aplicáveis
- RN01 — Classificação por risco  
- RN02 — Prioridade de casos graves  
- RN05 — Ajuste por profissional  
- RN07 — Cálculo do tempo de espera  