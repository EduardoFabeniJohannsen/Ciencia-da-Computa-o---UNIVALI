#ifndef FCB_H
#define FCB_H

#include <string>
#include <ctime>

using namespace std;

struct FCB {

    int inode;

    string nome;

    int tamanho;

    time_t criacao;

    time_t modificacao;

    string dono;

    int permissao;
    int bloco;
};

#endif