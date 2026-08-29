#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <string>
#include "FCB.h"

using namespace std;

class Arquivo {

public:

    FCB fcb;

    string conteudo;

    Arquivo(string nome, string dono);
};

#endif