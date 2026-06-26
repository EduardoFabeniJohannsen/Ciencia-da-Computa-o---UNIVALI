#ifndef DIRETORIO_H
#define DIRETORIO_H

#include <string>
#include <vector>

using namespace std;

class Diretorio {

public:

    string nome;

    Diretorio* pai;

    vector<Diretorio*> subdiretorios;

    Diretorio(string nome, Diretorio* pai = nullptr);
};

#endif