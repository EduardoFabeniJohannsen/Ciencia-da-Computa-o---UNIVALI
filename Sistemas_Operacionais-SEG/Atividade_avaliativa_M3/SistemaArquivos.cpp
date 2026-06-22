#include <iostream>
#include "SistemaArquivos.h"

using namespace std;

SistemaArquivos::SistemaArquivos() {
}

void SistemaArquivos::exibirMenu() {

    cout << "\n===============================";
    cout << "\n MINI SISTEMA DE ARQUIVOS";
    cout << "\n===============================";

    cout << "\n1  - Criar diretorio";
    cout << "\n2  - Entrar em diretorio";
    cout << "\n3  - Listar diretorio";

    cout << "\n4  - Criar arquivo";
    cout << "\n5  - Escrever arquivo";
    cout << "\n6  - Ler arquivo";

    cout << "\n7  - Copiar arquivo";
    cout << "\n8  - Mover/Renomear arquivo";
    cout << "\n9  - Excluir arquivo";

    cout << "\n10 - Alterar permissoes";
    cout << "\n11 - Informacoes do arquivo";

    cout << "\n12 - Login";
    cout << "\n13 - Mostrar disco";
    cout << "\n14 - Arvore de diretorios";

    cout << "\n0  - Sair\n";
}

void SistemaArquivos::executar(int opcao) {

    switch(opcao) {

        case 1:
            cout << "\nCriar diretorio.\n";
            break;

        case 2:
            cout << "\nEntrar em diretorio.\n";
            break;

        case 3:
            cout << "\nListar diretorio.\n";
            break;

        case 4:
            cout << "\nCriar arquivo.\n";
            break;

        case 5:
            cout << "\nEscrever arquivo.\n";
            break;

        case 6:
            cout << "\nLer arquivo.\n";
            break;

        case 7:
            cout << "\nCopiar arquivo.\n";
            break;

        case 8:
            cout << "\nMover arquivo.\n";
            break;

        case 9:
            cout << "\nExcluir arquivo.\n";
            break;

        case 10:
            cout << "\nAlterar permissoes.\n";
            break;

        case 11:
            cout << "\nInformacoes do arquivo.\n";
            break;

        case 12:
            cout << "\nLogin.\n";
            break;

        case 13:
            cout << "\nMostrar disco.\n";
            break;

        case 14:
            cout << "\nArvore de diretorios.\n";
            break;

        case 0:
            cout << "\nEncerrando sistema...\n";
            break;

        default:
            cout << "\nOpcao invalida.\n";
    }
}