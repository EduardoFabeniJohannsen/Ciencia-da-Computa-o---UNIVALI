#include <iostream>
#include "SistemaArquivos.h"

using namespace std;

SistemaArquivos::SistemaArquivos() {

    raiz = new Diretorio("/");

    atual = raiz;
}

void SistemaArquivos::exibirMenu() {

    cout << "\n=================================";
    cout << "\n MINI SISTEMA DE ARQUIVOS";
    cout << "\n=================================";

    cout << "\nDiretorio atual: " << atual->nome;

    cout << "\n\n1 - Criar diretorio";
    cout << "\n2 - Entrar em diretorio";
    cout << "\n3 - Listar diretorio";

    cout << "\n4 - Criar arquivo";
    cout << "\n5 - Escrever arquivo";
    cout << "\n6 - Ler arquivo";

    cout << "\n15 - Voltar diretorio";

    cout << "\n0 - Sair";
}

void SistemaArquivos::executar(int opcao) {

    switch(opcao) {

        case 1:
            criarDiretorio();
            break;

        case 2:
            entrarDiretorio();
            break;

        case 3:
            listarDiretorio();
            break;

        case 4:
            criarArquivo();
            break;

        case 5:
            escreverArquivo();
            break;

        case 6:
            lerArquivo();
            break;

        case 15:
            voltarDiretorio();
            break;

        case 0:
            cout << "\nEncerrando...\n";
            break;

        default:
            cout << "\nOpcao invalida.\n";
    }
}

void SistemaArquivos::criarDiretorio() {

    string nome;

    cout << "\nNome do diretorio: ";
    cin >> nome;

    Diretorio* novo = new Diretorio(nome, atual);

    atual->subdiretorios.push_back(novo);

    cout << "\nDiretorio criado com sucesso.\n";
}

void SistemaArquivos::listarDiretorio() {

    if(atual->subdiretorios.empty()) {

        cout << "\nNenhum diretorio encontrado.\n";

        return;
    }

    cout << "\nDiretorios:\n";

    for(int i = 0; i < atual->subdiretorios.size(); i++) {

        cout << i + 1 << " - "
             << atual->subdiretorios[i]->nome
             << endl;
    }
}

void SistemaArquivos::entrarDiretorio() {

    if(atual->subdiretorios.empty()) {

        cout << "\nNao existem diretorios.\n";

        return;
    }

    listarDiretorio();

    int opcao;

    cout << "\nEscolha: ";
    cin >> opcao;

    if(opcao < 1 || opcao > atual->subdiretorios.size()) {

        cout << "\nDiretorio invalido.\n";

        return;
    }

    atual = atual->subdiretorios[opcao - 1];

    cout << "\nEntrou em "
         << atual->nome
         << endl;
}

void SistemaArquivos::voltarDiretorio() {

    if(atual->pai == nullptr) {

        cout << "\nVoce ja esta na raiz.\n";

        return;
    }

    atual = atual->pai;

    cout << "\nRetornou para "
         << atual->nome
         << endl;
}

void SistemaArquivos::criarArquivo() {

    string nome;

    cout << "\nNome do arquivo: ";
    cin >> nome;

    Arquivo* novo = new Arquivo(nome);

    atual->arquivos.push_back(novo);

    cout << "\nArquivo criado.\n";
}

void SistemaArquivos::lerArquivo() {

    if(atual->arquivos.empty()) {

        cout << "\nNao existem arquivos.\n";
        return;
    }

    for(int i = 0; i < atual->arquivos.size(); i++) {

        cout << i + 1 << " - "
             << atual->arquivos[i]->fcb.nome
             << endl;
    }

    int op;

    cout << "\nEscolha: ";
    cin >> op;

    if(op < 1 || op > atual->arquivos.size()) {

        cout << "\nArquivo invalido.\n";
        return;
    }

    cout << "\nConteudo:\n";

    cout << atual->arquivos[op - 1]->conteudo << endl;
}

void SistemaArquivos::escreverArquivo() {

    if(atual->arquivos.empty()) {

        cout << "\nNao existem arquivos.\n";
        return;
    }

    for(int i = 0; i < atual->arquivos.size(); i++) {

        cout << i + 1 << " - "
             << atual->arquivos[i]->fcb.nome
             << endl;
    }

    int op;

    cout << "\nEscolha: ";
    cin >> op;

    cin.ignore();

    string texto;

    cout << "\nConteudo: ";

    getline(cin, texto);

    atual->arquivos[op - 1]->conteudo = texto;

    atual->arquivos[op - 1]->fcb.tamanho =
        texto.size();

    atual->arquivos[op - 1]->fcb.modificacao =
        time(nullptr);

    cout << "\nArquivo atualizado.\n";
}