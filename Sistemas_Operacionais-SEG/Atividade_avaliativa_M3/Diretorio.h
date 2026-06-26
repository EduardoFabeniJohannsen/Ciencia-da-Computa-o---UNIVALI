#ifndef DIRETORIO_H
#define DIRETORIO_H

#include "Arquivo.h"
#include <string>
#include <vector>

using namespace std;

class Diretorio {

public:

    string nome;

    Diretorio* pai;

    vector<Diretorio*> subdiretorios;

    vector<Arquivo*> arquivos;

    Diretorio(string nome, Diretorio* pai = nullptr);
};

#endif