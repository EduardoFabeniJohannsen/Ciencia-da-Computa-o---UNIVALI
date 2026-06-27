#ifndef DISCO_H
#define DISCO_H

#include <vector>

using namespace std;

class Disco {

public:

    int totalBlocos;

    vector<bool> blocos;

    Disco(int total = 50);

    int alocarBloco();

    void liberarBloco(int bloco);

    void mostrarEstado();

    int blocosLivres();
    int blocosUsados();
};

#endif