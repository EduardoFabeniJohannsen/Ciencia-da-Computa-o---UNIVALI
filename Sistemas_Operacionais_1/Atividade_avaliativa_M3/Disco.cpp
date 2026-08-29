#include <iostream>
#include "Disco.h"

using namespace std;

Disco::Disco(int total) {

    totalBlocos = total;

    blocos.resize(total, false);
}

int Disco::alocarBloco() {

    for(int i = 0; i < totalBlocos; i++) {

        if(!blocos[i]) {

            blocos[i] = true;

            return i;
        }
    }

    return -1;
}

void Disco::liberarBloco(int bloco) {

    if(bloco >= 0 && bloco < totalBlocos) {

        blocos[bloco] = false;
    }
}

void Disco::mostrarEstado() {

    cout << "\n===== DISCO =====\n";

    for(int i = 0; i < totalBlocos; i++) {

        cout << "Bloco "
             << i
             << " - ";

        if(blocos[i])
            cout << "Ocupado";
        else
            cout << "Livre";

        cout << endl;
    }
}

int Disco::blocosLivres() {

    int livres = 0;

    for(int i = 0; i < totalBlocos; i++) {

        if(!blocos[i]) {

            livres++;
        }
    }

    return livres;
}

int Disco::blocosUsados() {

    int usados = 0;

    for(int i = 0; i < totalBlocos; i++) {

        if(blocos[i]) {

            usados++;
        }
    }

    return usados;
}
