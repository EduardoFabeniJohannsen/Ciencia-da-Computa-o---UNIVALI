# MiniFileSystem
Mini Sistema de Arquivos desenvolvido em C++ para a disciplina de Sistemas Operacionais da Universidade do Vale do Itajaí (UNIVALI).

## Descrição
O objetivo deste projeto é simular o funcionamento de um sistema de arquivos inspirado em ambientes Linux, implementando conceitos fundamentais estudados na disciplina de Sistemas Operacionais.

O sistema é executado em modo texto e permite a manipulação de diretórios e arquivos através de um menu interativo.

## Tecnologias Utilizadas
- C++
- GCC / G++
- WSL (Windows Subsystem for Linux)
- Visual Studio Code
- Git e GitHub

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

## Funcionalidades Implementadas

### Gerenciamento de Diretórios
- Criação de diretórios.
- Navegação entre diretórios.
- Retorno ao diretório pai.
- Listagem dos diretórios existentes.
- Estrutura hierárquica em árvore.

### Gerenciamento de Arquivos
- Criação de arquivos.
- Escrita de conteúdo.
- Leitura de arquivos.
- Armazenamento do conteúdo em memória.

### File Control Block (FCB)
Cada arquivo possui:
- Inode simulado.
- Nome do arquivo.
- Tamanho do arquivo.
- Data de criação.
- Data de modificação.
- Proprietário.
- Permissões.

### Interface
- Menu numérico interativo.
- Navegação simples.
- Tratamento de opções inválidas.

## Funcionalidades em Desenvolvimento

### Controle de Usuários
- Sistema de login.
- Usuários simulados.
- Grupos de usuários.

### Permissões
- Leitura (R)
- Escrita (W)
- Execução (X)
- Controle de proprietário, grupo e outros.

### Gerenciamento de Disco
- Simulação de blocos.
- Alocação de espaço.
- Visualização dos blocos ocupados.

### Informações do Sistema
- Exibição de metadados.
- Informações dos arquivos.
- Estrutura completa da árvore de diretórios.

## Estado Atual
Atualmente o sistema possui:
- Menu principal.
- Estrutura modular.
- Sistema de diretórios em árvore.
- Navegação entre diretórios.
- Criação de arquivos.
- Escrita e leitura de conteúdo.
- Implementação inicial do FCB.
- Inodes simulados.
- Alocação dinâmica de memória.

## Exemplo de Execução
```text
=================================
 MINI SISTEMA DE ARQUIVOS
=================================

Diretorio atual: /

1 - Criar diretorio
2 - Entrar em diretorio
3 - Listar diretorio
4 - Criar arquivo
5 - Escrever arquivo
6 - Ler arquivo
15 - Voltar diretorio
0 - Sair
```

## Compilação
```bash
g++ main.cpp SistemaArquivos.cpp Diretorio.cpp Arquivo.cpp -o sistema
```

Windows (PowerShell):

```powershell
.\sistema.exe
```

Linux / WSL:

```bash
./sistema
```

## Conceitos de Sistemas Operacionais Aplicados
- Estrutura hierárquica de diretórios.
- File Control Block (FCB).
- Inodes simulados.
- Gerenciamento de arquivos.
- Alocação dinâmica de memória.
- Organização modular do sistema.
- Estruturas de dados em árvore.

## Próximas Etapas
- Sistema de usuários.
- Permissões RWX.
- Simulação de disco.
- Gerenciamento de blocos.
- Informações detalhadas dos arquivos.
- Árvore completa de diretórios.

## Autor
Eduardo Fabeni Johannsen

## Disciplina
Sistemas Operacionais  
Universidade do Vale do Itajaí – UNIVALI

## Professor
Michael D. C. Alves