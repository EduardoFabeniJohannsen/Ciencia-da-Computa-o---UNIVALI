#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

class Usuario {

public:

    string nome;

    string senha;

    Usuario(string nome, string senha);
};

#endif