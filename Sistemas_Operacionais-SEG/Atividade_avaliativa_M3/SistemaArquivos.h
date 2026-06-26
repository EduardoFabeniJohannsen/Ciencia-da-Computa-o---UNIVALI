#ifndef SISTEMAARQUIVOS_H
#define SISTEMAARQUIVOS_H

#include "Diretorio.h"

class SistemaArquivos {

private:

    Diretorio* raiz;
    Diretorio* atual;

public:

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
};

#endif