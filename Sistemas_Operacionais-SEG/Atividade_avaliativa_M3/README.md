# MiniFileSystem
Mini Sistema de Arquivos desenvolvido em C++ para a disciplina de Sistemas Operacionais da Universidade do Vale do Itajaí (UNIVALI).

## Descrição
O objetivo deste projeto é simular o funcionamento de um sistema de arquivos inspirado em ambientes Linux, implementando conceitos fundamentais estudados na disciplina de Sistemas Operacionais.

O sistema será executado em modo texto e permitirá ao usuário realizar operações semelhantes às encontradas em sistemas Unix, incluindo gerenciamento de diretórios, arquivos, permissões, usuários e alocação de blocos.

---

## Tecnologias Utilizadas
* C++
* GCC/G++
* WSL (Windows Subsystem for Linux)
* Visual Studio Code
* Git e GitHub

---

## Estrutura do Projeto
```text
MiniFileSystem/

│── main.cpp

│── SistemaArquivos.h
│── SistemaArquivos.cpp

│── Diretorio.h
│── Diretorio.cpp

│── Arquivo.h
│── Arquivo.cpp

│── FCB.h

│── Usuario.h
│── Usuario.cpp

│── Disco.h
│── Disco.cpp

│── Permissao.h

│── README.md
```

---

## Funcionalidades Implementadas

### Diretórios
* Criação de diretórios.
* Navegação entre diretórios.
* Retorno ao diretório pai.
* Listagem dos diretórios existentes.
* Estrutura hierárquica em árvore.

### Interface
* Menu numérico interativo.
* Navegação por opções.
* Tratamento básico de opções inválidas.

---

## Funcionalidades em Desenvolvimento

### Arquivos
* Criar arquivos.
* Ler arquivos.
* Escrever conteúdo.
* Copiar arquivos.
* Renomear arquivos.
* Excluir arquivos.

### Controle de Acesso
* Sistema de login.
* Usuários simulados.
* Permissões RWX.
* Proprietário, grupo e outros.

### Metadados
* File Control Block (FCB).
* Inode simulado.
* Datas de criação, acesso e modificação.
* Tamanho dos arquivos.

### Gerenciamento de Disco
* Simulação de blocos.
* Alocação de memória.
* Visualização dos blocos utilizados.

---

## Estado Atual
Atualmente o projeto possui:

* Estrutura modular do sistema.
* Menu principal implementado.
* Sistema de diretórios em árvore.
* Navegação entre diretórios.
* Retorno ao diretório pai.
* Utilização de alocação dinâmica.
* Organização do projeto em múltiplos arquivos.

---

## Exemplo de Execução
```text
=================================
 MINI SISTEMA DE ARQUIVOS
=================================

Diretorio atual: /

1 - Criar diretorio
2 - Entrar em diretorio
3 - Listar diretorio
15 - Voltar diretorio
0 - Sair
```

---

## Compilação
```bash
g++ main.cpp SistemaArquivos.cpp Diretorio.cpp -o sistema
```

---

## Execução
```bash
./sistema
```

---

## Conceitos de Sistemas Operacionais Aplicados
* Estrutura de diretórios em árvore.
* Gerenciamento hierárquico.
* Ponteiros e alocação dinâmica.
* Simulação de sistema de arquivos.
* Navegação entre diretórios.
* Organização modular do sistema.

---

## Autor
Eduardo Fabeni Johannsen

---

## Disciplina
Sistemas Operacionais
Universidade do Vale do Itajaí – UNIVALI

---

## Professor
Michael D. C. Alves
