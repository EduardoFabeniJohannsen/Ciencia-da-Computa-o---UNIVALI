// main.cpp

#include <iostream>
#include "SistemaArquivos.h"

using namespace std;

int main() {

    SistemaArquivos sistema;

    int opcao;

    do {

        sistema.exibirMenu();

        cout << "\nOpcao: ";
        cin >> opcao;

        sistema.executar(opcao);

    } while (opcao != 0);

    return 0;
}