# Casos de Uso — KGE System

## 4.1 Atores do Sistema

### Paciente
Pessoa que busca atendimento na unidade de saúde.

### Recepcionista
Responsável por realizar o cadastro do paciente no sistema.

### Enfermeiro (Triagem)
Responsável por registrar os dados clínicos e, se necessário, ajustar a prioridade do paciente.

### Médico
Responsável por visualizar a fila, chamar pacientes e realizar atendimentos.

### Gestor da Unidade
Responsável por gerenciar regras de prioridade e gerar relatórios de atendimento.

---

## 4.2 Lista de Casos de Uso

### UC01 — Cadastrar paciente
Permite que o recepcionista registre os dados do paciente no sistema.

### UC02 — Registrar triagem
Permite que o enfermeiro registre dados clínicos do paciente.

### UC03 — Classificar prioridade automaticamente
Permite que o sistema classifique o paciente com base nos dados da triagem.

### UC04 — Ajustar prioridade
Permite que o enfermeiro altere manualmente a prioridade do paciente.

### UC05 — Inserir paciente na fila
Permite que o sistema adicione o paciente à fila de atendimento.

### UC06 — Organizar fila
Permite que o sistema ordene a fila com base nas regras de prioridade.

### UC07 — Visualizar fila de atendimento
Permite que o médico visualize os pacientes em espera.

### UC08 — Chamar próximo paciente
Permite que o médico selecione o próximo paciente para atendimento.

### UC09 — Realizar atendimento
Permite que o médico realize o atendimento do paciente.

### UC10 — Registrar atendimento
Permite que o sistema registre o atendimento realizado.

### UC11 — Atualizar fila e tempo de espera
Permite que o sistema atualize a ordem da fila e o tempo estimado.

### UC12 — Exibir tempo estimado de espera
Permite que o sistema informe o tempo de espera ao paciente ou profissional.

### UC13 — Gerenciar regras de prioridade
Permite que o gestor configure regras de prioridade do sistema.

### UC14 — Gerar relatórios
Permite que o gestor visualize relatórios de atendimento.

---

## 4.3 Relacionamento Geral dos Casos de Uso

O processo inicia com o cadastro do paciente (UC01), realizado pela recepção. Em seguida, o paciente passa pela triagem (UC02), onde são coletadas informações clínicas.

Com base nesses dados, o sistema realiza a classificação automática da prioridade (UC03), podendo ser ajustada manualmente pelo enfermeiro (UC04).

Após a definição da prioridade, o paciente é inserido na fila (UC05), que é organizada dinamicamente (UC06).

O médico pode visualizar a fila (UC07), chamar o próximo paciente (UC08) e realizar o atendimento (UC09). O sistema registra o atendimento (UC10) e atualiza a fila e o tempo de espera (UC11), exibindo essas informações (UC12).

Além disso, o gestor da unidade pode gerenciar regras de prioridade (UC13) e gerar relatórios (UC14).

---

## 4.4 Diagrama de Casos de Uso

O diagrama de casos de uso representa a interação entre os atores e o sistema, demonstrando as funcionalidades principais.
