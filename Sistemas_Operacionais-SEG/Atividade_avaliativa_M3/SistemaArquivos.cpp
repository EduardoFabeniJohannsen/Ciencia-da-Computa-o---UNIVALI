#include <iostream>
#include "SistemaArquivos.h"

using namespace std;

SistemaArquivos::SistemaArquivos() {

    raiz = new Diretorio("/");

    atual = raiz;

    usuarios.push_back(
        Usuario("admin", "123")
    );

    usuarios.push_back(
        Usuario("eduardo", "123")
    );

    usuarioAtual = &usuarios[0];

    disco = Disco(50);
}

void SistemaArquivos::exibirMenu()
{
    cout << "\n=================================";
    cout << "\n MINI SISTEMA DE ARQUIVOS";
    cout << "\n=================================";

    cout << "\nDiretorio atual: " << obterCaminho(atual);

    cout << "\n\n1 - Criar diretorio";
    cout << "\n2 - Entrar em diretorio";
    cout << "\n3 - Listar diretorio";
    cout << "\n4 - Criar arquivo";
    cout << "\n5 - Escrever arquivo";
    cout << "\n6 - Ler arquivo";
    cout << "\n7 - Listar arquivos";
    cout << "\n8 - Informacoes do arquivo";
    cout << "\n9 - Login";
    cout << "\n10 - Usuario atual";
    cout << "\n11 - Alterar permissao";
    cout << "\n12 - Excluir arquivo";
    cout << "\n13 - Renomear arquivo";
    cout << "\n14 - Mostrar arvore";
    cout << "\n15 - Voltar diretorio";
    cout << "\n16 - Copiar arquivo";
    cout << "\n17 - Mostrar disco";

    cout << "\n0 - Sair\n";
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

        case 7:
            listarArquivos();
            break;

        case 8:
            informacoesArquivo();
            break;
            
        case 9:
            login();
            break;

        case 10:
            mostrarUsuario();
            break;

        case 11:
            alterarPermissao();
            break;

        case 12:
            excluirArquivo();
            break;

        case 13:
            renomearArquivo();
            break;
        
        case 14:
            exibirArvore();
            break;

        case 15:
            voltarDiretorio();
            break;

        case 16:
            copiarArquivo();
            break;

        case 17:
            mostrarDisco();
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

    Arquivo* novo = new Arquivo(
        nome,
        usuarioAtual->nome
    );

    atual->arquivos.push_back(novo);

    novo->fcb.bloco = disco.alocarBloco();

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

    Arquivo* arq = atual->arquivos[op - 1];

    if(!podeLer(arq)) {

        cout << "\nPermissao negada.\n";

        return;
    }

    cout << "\nConteudo:\n";

    cout << arq->conteudo << endl;

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

    if(op < 1 || op > atual->arquivos.size()) {

        cout << "\nArquivo invalido.\n";

        return;
    }

    Arquivo* arq = atual->arquivos[op - 1];

    if(!podeEscrever(arq)) {

        cout << "\nPermissao negada.\n";

        return;
    }

    cin.ignore();

    string texto;

    cout << "\nConteudo: ";

    getline(cin, texto);

    arq->conteudo = texto;

    arq->fcb.tamanho = texto.size();

    arq->fcb.modificacao = time(nullptr);

    cout << "\nArquivo atualizado.\n";
}

void SistemaArquivos::informacoesArquivo() {

    if(atual->arquivos.empty()) {

        cout << "\nNao existem arquivos.\n";

        return;
    }

    listarArquivos();

    int op;

    cout << "\nEscolha: ";
    cin >> op;

    if(op < 1 || op > atual->arquivos.size()) {

        cout << "\nArquivo invalido.\n";

        return;
    }

    Arquivo* arq = atual->arquivos[op - 1];

    cout << "\n===== INFORMACOES =====";

    cout << "\nNome: "
         << arq->fcb.nome;

    cout << "\nInode: "
         << arq->fcb.inode;

    cout << "\nTamanho: "
         << arq->fcb.tamanho
         << " bytes";

    cout << "\nDono: "
         << arq->fcb.dono;

    cout << "\nPermissao: "
         << arq->fcb.permissao;

    cout << "\n";
}

void SistemaArquivos::listarArquivos() {

    if(atual->arquivos.empty()) {

        cout << "\nNao existem arquivos.\n";

        return;
    }

    cout << "\nArquivos:\n";

    for(int i = 0; i < atual->arquivos.size(); i++) {

        cout << i + 1
             << " - "
             << atual->arquivos[i]->fcb.nome
             << endl;
    }
}

void SistemaArquivos::login() {

    string nome;
    string senha;

    cout << "\nUsuario: ";
    cin >> nome;

    cout << "Senha: ";
    cin >> senha;

    for(int i = 0; i < usuarios.size(); i++) {

        if(usuarios[i].nome == nome &&
           usuarios[i].senha == senha) {

            usuarioAtual = &usuarios[i];

            cout << "\nLogin realizado.\n";

            return;
        }
    }

    cout << "\nUsuario ou senha incorretos.\n";
}

void SistemaArquivos::mostrarUsuario() {

    cout << "\nUsuario atual: "
         << usuarioAtual->nome
         << endl;
}

void SistemaArquivos::alterarPermissao() {

    if(atual->arquivos.empty()) {

        cout << "\nNao existem arquivos.\n";

        return;
    }

    listarArquivos();

    int op;

    cout << "\nEscolha: ";
    cin >> op;

    if(op < 1 || op > atual->arquivos.size()) {

        cout << "\nArquivo invalido.\n";

        return;
    }

    int permissao;

    cout << "\nNova permissao: ";
    cin >> permissao;

    atual->arquivos[op - 1]->fcb.permissao = permissao;

    cout << "\nPermissao alterada.\n";
}

void SistemaArquivos::excluirArquivo() {

    if(atual->arquivos.empty()) {

        cout << "\nNao existem arquivos.\n";

        return;
    }

    listarArquivos();

    int op;

    cout << "\nEscolha: ";
    cin >> op;

    if(op < 1 || op > atual->arquivos.size()) {

        cout << "\nArquivo invalido.\n";

        return;
    }

    Arquivo* arq = atual->arquivos[op - 1];

    if(!podeExcluir(arq)) {

        cout << "\nPermissao negada.\n";

        return;
    }

    disco.liberarBloco(
        arq->fcb.bloco
    );

    delete atual->arquivos[op - 1];

    atual->arquivos.erase(
        atual->arquivos.begin() + (op - 1)
    );

    cout << "\nArquivo excluido.\n";
}

void SistemaArquivos::renomearArquivo() {

    if(atual->arquivos.empty()) {

        cout << "\nNao existem arquivos.\n";

        return;
    }

    listarArquivos();

    int op;

    cout << "\nEscolha: ";
    cin >> op;

    if(op < 1 || op > atual->arquivos.size()) {

        cout << "\nArquivo invalido.\n";

        return;
    }

    string novoNome;

    cout << "\nNovo nome: ";
    cin >> novoNome;

    atual->arquivos[op - 1]->fcb.nome = novoNome;

    cout << "\nArquivo renomeado.\n";
}

void SistemaArquivos::mostrarArvore(Diretorio* dir, int nivel) {

    for(int i = 0; i < nivel; i++) {
        cout << "   ";
    }

    cout << "|-- " << dir->nome << endl;

    for(int i = 0; i < dir->arquivos.size(); i++) {

        for(int j = 0; j < nivel + 1; j++) {
            cout << "   ";
        }

        cout << "|-- "
             << dir->arquivos[i]->fcb.nome
             << endl;
    }

    for(int i = 0; i < dir->subdiretorios.size(); i++) {

        mostrarArvore(
            dir->subdiretorios[i],
            nivel + 1
        );
    }
}

void SistemaArquivos::exibirArvore() {

    cout << "\n===== ARVORE DE DIRETORIOS =====\n";

    mostrarArvore(raiz, 0);
}

void SistemaArquivos::copiarArquivo() {


    if(atual->arquivos.empty()) {

        cout << "\nNao existem arquivos.\n";

        return;
    }

    listarArquivos();

    int op;

    cout << "\nEscolha o arquivo: ";
    cin >> op;

    if(op < 1 || op > atual->arquivos.size()) {

        cout << "\nArquivo invalido.\n";

        return;
    }

    string novoNome;

    cout << "\nNovo nome: ";
    cin >> novoNome;

    Arquivo* original = atual->arquivos[op - 1];

    Arquivo* copia = new Arquivo(
        novoNome,
        original->fcb.dono
    );

    copia->conteudo = original->conteudo;

    copia->fcb.tamanho = original->fcb.tamanho;

    copia->fcb.permissao = original->fcb.permissao;

    copia->fcb.dono = original->fcb.dono;

    atual->arquivos.push_back(copia);

    cout << "\nArquivo copiado.\n";
}

bool SistemaArquivos::podeLer(Arquivo* arq) {

    int dono = arq->fcb.permissao / 100;

    return (dono & 4);
}

bool SistemaArquivos::podeEscrever(Arquivo* arq) {

    int dono = arq->fcb.permissao / 100;

    return (dono & 2);
}

bool SistemaArquivos::podeExcluir(Arquivo* arq) {

    int dono = arq->fcb.permissao / 100;

    return (dono & 2);
}

void SistemaArquivos::mostrarDisco() {

    cout << "\n===== DISCO =====";

    cout << "\nBlocos totais: "
         << disco.totalBlocos;

    cout << "\nBlocos usados: "
         << disco.blocosUsados();

    cout << "\nBlocos livres: "
         << disco.blocosLivres();

    cout << "\n";
}

string SistemaArquivos::obterCaminho(Diretorio* dir) {

    if(dir->pai == nullptr) {

        return "/";
    }

    return obterCaminho(dir->pai) +
           dir->nome + "/";
}

