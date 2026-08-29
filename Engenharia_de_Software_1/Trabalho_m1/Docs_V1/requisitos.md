# Requisitos do Sistema — KGE System

## 3.1 Requisitos Funcionais (RF)

### RF01 — Cadastrar paciente
O sistema deve permitir o cadastro de pacientes com informações básicas (nome, documento e data de nascimento).

### RF02 — Atualizar dados do paciente
O sistema deve permitir a atualização dos dados cadastrais do paciente.

### RF03 — Registrar triagem
O sistema deve permitir o registro de informações clínicas iniciais do paciente (sintomas, sinais vitais e observações).

### RF04 — Classificar prioridade automaticamente
O sistema deve classificar automaticamente o paciente em um nível de prioridade com base nas informações da triagem.

### RF05 — Permitir ajuste manual de prioridade
O sistema deve permitir que um profissional de saúde autorizado altere manualmente a prioridade do paciente.

### RF06 — Inserir paciente na fila
O sistema deve inserir o paciente na fila de atendimento após a triagem.

### RF07 — Ordenar fila automaticamente
O sistema deve ordenar automaticamente a fila com base na prioridade dos pacientes.

### RF08 — Atualizar fila em tempo real
O sistema deve atualizar a ordem da fila automaticamente sempre que houver alteração de prioridade ou entrada de novos pacientes.

### RF09 — Exibir fila de atendimento
O sistema deve permitir que profissionais visualizem a lista de pacientes em espera, com suas respectivas prioridades.

### RF10 — Exibir tempo estimado de espera
O sistema deve calcular e exibir o tempo estimado de atendimento para cada paciente.

### RF11 — Chamar próximo paciente
O sistema deve permitir que o profissional chame o próximo paciente da fila.

### RF12 — Registrar atendimento
O sistema deve registrar quando um paciente inicia e finaliza o atendimento médico.

---

## 3.2 Requisitos Não Funcionais (RNF)

### RNF01 — Desempenho
O sistema deve responder às operações do usuário em até 2 segundos.

### RNF02 — Usabilidade
O sistema deve possuir interface simples e intuitiva, permitindo uso por profissionais com pouca experiência em tecnologia.

### RNF03 — Segurança
O sistema deve garantir a proteção dos dados dos pacientes, respeitando as diretrizes da LGPD.

### RNF04 — Disponibilidade
O sistema deve estar disponível para uso durante todo o horário de funcionamento da unidade de saúde (mínimo de 99% de disponibilidade).

### RNF05 — Compatibilidade
O sistema deve funcionar em computadores com configurações básicas utilizados em unidades públicas.

### RNF06 — Acessibilidade
O sistema deve oferecer recursos de acessibilidade, como contraste adequado e fontes legíveis.

---

## 3.3 Regras de Negócio (RN)

### RN01 — Classificação por risco
Os pacientes devem ser classificados em níveis de prioridade com base na gravidade do caso clínico.

### RN02 — Prioridade de casos graves
Pacientes classificados como casos graves devem ter prioridade máxima na fila de atendimento.

### RN03 — Ordenação da fila
A fila deve ser organizada priorizando pacientes de maior risco, independentemente da ordem de chegada.

### RN04 — Atualização dinâmica
A posição do paciente na fila deve ser atualizada automaticamente sempre que houver alteração de prioridade ou novos atendimentos.

### RN05 — Ajuste por profissional
Profissionais de saúde autorizados podem alterar a prioridade do paciente em casos específicos.

### RN06 — Atendimento de emergência
Pacientes em estado crítico devem ser atendidos imediatamente, sem necessidade de aguardar na fila.

### RN07 — Cálculo do tempo de espera
O tempo estimado de espera deve considerar a quantidade de pacientes na fila e o tempo médio de atendimento.

### RN08 — Registro obrigatório de triagem
Nenhum paciente pode ser inserido na fila sem passar pelo processo de triagem.

### RN09 — Controle de atendimento
Um paciente não pode ser atendido simultaneamente por mais de um profissional.

### RN10 — Ordem de chamada
O sistema deve sempre sugerir o próximo paciente com maior prioridade disponível.