#ifndef SISTEMAARQUIVOS_H
#define SISTEMAARQUIVOS_H

#include "Diretorio.h"
#include "Usuario.h"
#include <vector>
#include "Disco.h"

class SistemaArquivos {

private:

    Diretorio* raiz;
    Diretorio* atual;

    vector<Usuario> usuarios;
    Usuario* usuarioAtual;

    Disco disco;

public:
    string obterCaminho(Diretorio* dir);
    
    SistemaArquivos();

    void exibirMenu();

    void executar(int opcao);

    void criarDiretorio();

    void entrarDiretorio();

    void listarDiretorio();

    void voltarDiretorio();

    void criarArquivo();

    void escreverArquivo();

    void lerArquivo();

    void listarArquivos();

    void informacoesArquivo();

    void login();

    void mostrarUsuario();

    void alterarPermissao();

    void excluirArquivo();

    void renomearArquivo();

    void mostrarArvore(Diretorio* dir, int nivel);

    void exibirArvore();

    void copiarArquivo();

    bool podeLer(Arquivo* arq);

    bool podeEscrever(Arquivo* arq);

    bool podeExcluir(Arquivo* arq);

    void mostrarDisco();
};

#endif