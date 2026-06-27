# MiniFileSystem

Mini Sistema de Arquivos desenvolvido em C++ para a disciplina de Sistemas Operacionais da Universidade do Vale do Itajaí (UNIVALI).

## Descrição

O projeto simula o funcionamento de um sistema de arquivos inspirado em sistemas Linux, implementando conceitos fundamentais de Sistemas Operacionais, como gerenciamento de diretórios, arquivos, usuários, permissões e alocação de disco.

O sistema foi desenvolvido em C++ e executado em modo texto, permitindo ao usuário navegar pela estrutura de diretórios e realizar operações semelhantes às encontradas em sistemas Unix.

## Tecnologias Utilizadas

* C++
* GCC / G++
* WSL (Windows Subsystem for Linux)
* Visual Studio Code
* Git e GitHub

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

│── README.md
```

## Funcionalidades Implementadas

### Gerenciamento de Diretórios

* Criar diretórios
* Navegar entre diretórios
* Voltar ao diretório pai
* Listar diretórios
* Exibir árvore completa de diretórios
* Exibir caminho atual

### Gerenciamento de Arquivos

* Criar arquivos
* Ler arquivos
* Escrever conteúdo
* Listar arquivos
* Renomear arquivos
* Copiar arquivos
* Excluir arquivos

### Controle de Usuários

* Login de usuários
* Exibição do usuário logado
* Arquivos associados ao usuário proprietário

### Permissões

* Alteração de permissões numéricas (Linux)
* Controle de leitura
* Controle de escrita
* Controle de exclusão
* Mensagem de permissão negada quando necessário

### File Control Block (FCB)

Cada arquivo possui:

* Inode
* Nome
* Tamanho
* Data de criação
* Data de modificação
* Dono
* Permissões
* Bloco do disco associado

### Simulação de Disco

* Simulação de blocos de armazenamento
* Alocação automática de blocos
* Liberação de blocos ao excluir arquivos
* Exibição da quantidade de blocos totais, utilizados e livres

## Menu do Sistema

```text
1  - Criar diretório
2  - Entrar em diretório
3  - Listar diretório
4  - Criar arquivo
5  - Escrever arquivo
6  - Ler arquivo
7  - Listar arquivos
8  - Informações do arquivo
9  - Login
10 - Usuário atual
11 - Alterar permissão
12 - Excluir arquivo
13 - Renomear arquivo
14 - Mostrar árvore
15 - Voltar diretório
16 - Copiar arquivo
17 - Mostrar disco
0  - Sair
```

## Conceitos de Sistemas Operacionais Aplicados

* Sistema de Arquivos
* Estrutura hierárquica de diretórios
* File Control Block (FCB)
* Inodes
* Controle de usuários
* Permissões de acesso
* Alocação de blocos em disco
* Gerenciamento de arquivos
* Organização modular em C++

## Compilação

```bash
g++ main.cpp SistemaArquivos.cpp Diretorio.cpp Arquivo.cpp Usuario.cpp Disco.cpp -o sistema
```

## Execução

### Windows (PowerShell)

```powershell
.\sistema.exe
```

## Autor

Eduardo Fabeni Johannsen

## Disciplina

Sistemas Operacionais

Universidade do Vale do Itajaí – UNIVALI

## Professor

Michael D. C. Alves
