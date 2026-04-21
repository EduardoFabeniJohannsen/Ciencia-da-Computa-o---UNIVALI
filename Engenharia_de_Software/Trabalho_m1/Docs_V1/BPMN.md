# BPMN — Processo de Atendimento Proposto

## Descrição do Processo

O processo de atendimento inicia com a chegada do paciente na unidade de saúde. O paciente é atendido pela recepção, onde seus dados são cadastrados no sistema.

Após o cadastro, o paciente é encaminhado para a triagem, realizada por um enfermeiro, que registra informações clínicas como sintomas, sinais vitais e observações.

Com base nesses dados, o sistema realiza automaticamente a classificação de prioridade do paciente, podendo ser ajustada manualmente pelo profissional de saúde, se necessário.

Após a definição da prioridade, o paciente é inserido na fila de atendimento, que é organizada dinamicamente conforme o nível de risco.

O sistema mantém a fila atualizada em tempo real, recalculando a ordem e o tempo estimado de espera sempre que necessário.

Quando disponível, o médico chama o próximo paciente da fila, respeitando a prioridade definida, e realiza o atendimento.

Ao final, o atendimento é registrado no sistema, encerrando o processo.

---

## Etapas do Processo

1. Paciente chega à unidade de saúde  
2. Recepcionista realiza cadastro  
3. Enfermeiro realiza triagem  
4. Sistema classifica prioridade automaticamente  
5. (Opcional) Profissional ajusta prioridade  
6. Sistema insere paciente na fila  
7. Sistema organiza fila dinamicamente  
8. Médico chama próximo paciente  
9. Médico realiza atendimento  
10. Sistema registra atendimento  

---

## Observações

- O processo prioriza pacientes com maior gravidade  
- A fila não segue apenas ordem de chegada  
- O sistema atua ativamente na organização da fila  
- O tempo estimado é atualizado dinamicamente  

---

## Diagrama BPMN

📌 O diagrama está disponível em:  
`/diagramas/bpmn.png`