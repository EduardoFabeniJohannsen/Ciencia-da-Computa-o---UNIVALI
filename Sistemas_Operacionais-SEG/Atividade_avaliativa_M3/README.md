# MiniFileSystem
Mini Sistema de Arquivos desenvolvido em C++ para a disciplina de Sistemas Operacionais da Universidade do Vale do Itajaí (UNIVALI).

## Descrição
O objetivo deste projeto é simular o funcionamento de um sistema de arquivos inspirado em ambientes Linux, implementando conceitos fundamentais estudados na disciplina de Sistemas Operacionais.

O sistema será executado em modo texto e permitirá ao usuário realizar operações semelhantes às encontradas em sistemas Unix, incluindo gerenciamento de diretórios, arquivos, permissões e usuários.

## Tecnologias Utilizadas
* C++
* GCC/G++
* WSL (Windows Subsystem for Linux)
* Visual Studio Code
* Git e GitHub

## Estrutura Inicial do Projeto
```
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

## Funcionalidades Planejadas

### Diretórios
* Criar diretórios
* Navegar entre diretórios
* Listar conteúdo

### Arquivos
* Criar arquivos
* Ler arquivos
* Escrever conteúdo
* Copiar arquivos
* Renomear arquivos
* Excluir arquivos

### Controle de Acesso
* Usuários simulados
* Login
* Permissões RWX
* Controle de proprietário, grupo e outros

### Metadados
* File Control Block (FCB)
* Inode simulado
* Datas de criação e modificação
* Tamanho do arquivo

### Gerenciamento de Disco
* Simulação de blocos
* Alocação de espaço em memória
* Visualização dos blocos utilizados

## Estado Atual
Atualmente o projeto possui:

* Estrutura inicial do sistema.
* Menu principal implementado.
* Organização modular dos arquivos.
* Definição da arquitetura do simulador.

As funcionalidades serão implementadas gradualmente durante o desenvolvimento.

## Compilação
```bash
g++ main.cpp SistemaArquivos.cpp -o sistema
```

## Execução
```bash
./sistema
```

## Autor
Eduardo Fabeni Johannsen

## Disciplina
Sistemas Operacionais
Universidade do Vale do Itajaí – UNIVALI

## Professor
Michael D. C. Alves
