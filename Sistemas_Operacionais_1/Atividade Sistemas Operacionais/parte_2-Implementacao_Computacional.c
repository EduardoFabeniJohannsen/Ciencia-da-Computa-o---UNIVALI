#include <stdio.h>
#include <stdlib.h>

#define MAXIMO_FRAMES 128
#define TAMANHO_HASH 10

/* ================= PAGINAÇÃO HIERÁRQUICA ================= */

typedef struct {
    int paginaExiste;
    int numeroFrame;
} EntradaSegundoNivel;

typedef struct {
    EntradaSegundoNivel *tabelasSecundarias[16];
} TabelaPrimeiroNivel;

TabelaPrimeiroNivel tabelaHierarquica;

void iniciarHierarquica() {
    for (int indice = 0; indice < 16; indice++) {
        tabelaHierarquica.tabelasSecundarias[indice] = NULL;
    }
}

void inserirHierarquica(int numeroPagina, int numeroFrame) {

    int indicePrimeiroNivel = numeroPagina / 16;
    int indiceSegundoNivel = numeroPagina % 16;

    // Cria tabela secundária apenas quando necessário
    if (tabelaHierarquica.tabelasSecundarias[indicePrimeiroNivel] == NULL) {

        tabelaHierarquica.tabelasSecundarias[indicePrimeiroNivel] =
            malloc(sizeof(EntradaSegundoNivel) * 16);

        for (int indice = 0; indice < 16; indice++) {
            tabelaHierarquica.tabelasSecundarias[indicePrimeiroNivel][indice].paginaExiste = 0;
            tabelaHierarquica.tabelasSecundarias[indicePrimeiroNivel][indice].numeroFrame = -1;
        }
    }

    tabelaHierarquica.tabelasSecundarias[indicePrimeiroNivel][indiceSegundoNivel].paginaExiste = 1;
    tabelaHierarquica.tabelasSecundarias[indicePrimeiroNivel][indiceSegundoNivel].numeroFrame = numeroFrame;
}

void buscarHierarquica(int numeroPagina) {

    int indicePrimeiroNivel = numeroPagina / 16;
    int indiceSegundoNivel = numeroPagina % 16;

    if (tabelaHierarquica.tabelasSecundarias[indicePrimeiroNivel] == NULL ||
        tabelaHierarquica.tabelasSecundarias[indicePrimeiroNivel][indiceSegundoNivel].paginaExiste == 0) {

        printf("Page Fault\n");
        return;
    }

    printf("Frame encontrado: %d\n",
        tabelaHierarquica.tabelasSecundarias[indicePrimeiroNivel][indiceSegundoNivel].numeroFrame);
}

/* ================= TABELA HASH ================= */

typedef struct ItemHash {

    int numeroPagina;
    int numeroFrame;
    struct ItemHash *proximo;

} ItemHash;

ItemHash *tabelaHash[TAMANHO_HASH];

void iniciarHash() {
    for (int indice = 0; indice < TAMANHO_HASH; indice++) {
        tabelaHash[indice] = NULL;
    }
}

int calcularHash(int numeroPagina) {
    return numeroPagina % TAMANHO_HASH;
}

void inserirHash(int numeroPagina, int numeroFrame) {

    int indiceHash = calcularHash(numeroPagina);

    ItemHash *novoItem = malloc(sizeof(ItemHash));

    novoItem->numeroPagina = numeroPagina;
    novoItem->numeroFrame = numeroFrame;

    // Colisão é tratada por lista encadeada
    novoItem->proximo = tabelaHash[indiceHash];
    tabelaHash[indiceHash] = novoItem;
}

void buscarHash(int numeroPagina) {

    int indiceHash = calcularHash(numeroPagina);

    ItemHash *itemAtual = tabelaHash[indiceHash];

    while (itemAtual != NULL) {

        if (itemAtual->numeroPagina == numeroPagina) {
            printf("Frame encontrado: %d\n", itemAtual->numeroFrame);
            return;
        }

        itemAtual = itemAtual->proximo;
    }

    printf("Page Fault\n");
}

/* ================= TABELA INVERTIDA ================= */

typedef struct {

    int frameOcupado;
    int numeroPagina;

} EntradaInvertida;

EntradaInvertida tabelaInvertida[MAXIMO_FRAMES];

void iniciarInvertida() {

    for (int indice = 0; indice < MAXIMO_FRAMES; indice++) {
        tabelaInvertida[indice].frameOcupado = 0;
        tabelaInvertida[indice].numeroPagina = -1;
    }
}

void inserirInvertida(int numeroPagina, int numeroFrame) {

    tabelaInvertida[numeroFrame].frameOcupado = 1;
    tabelaInvertida[numeroFrame].numeroPagina = numeroPagina;
}

void buscarInvertida(int numeroPagina) {

    // Procura página percorrendo todos os frames físicos
    for (int numeroFrame = 0; numeroFrame < MAXIMO_FRAMES; numeroFrame++) {

        if (tabelaInvertida[numeroFrame].frameOcupado == 1 &&
            tabelaInvertida[numeroFrame].numeroPagina == numeroPagina) {

            printf("Frame encontrado: %d\n", numeroFrame);
            return;
        }
    }

    printf("Page Fault\n");
}

/* ================= MENU ================= */

int main() {

    int opcaoMenu;
    int tipoEstrutura;
    int numeroPagina;
    int numeroFrame;

    iniciarHierarquica();
    iniciarHash();
    iniciarInvertida();

    do {

        printf("\n===== EMULADOR DE PAGINACAO =====\n");
        printf("1 - Inserir pagina\n");
        printf("2 - Buscar pagina\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcaoMenu);

        if (opcaoMenu == 1) {

            printf("\nEscolha a estrutura:\n");
            printf("1 - Hierarquica\n");
            printf("2 - Hash\n");
            printf("3 - Invertida\n");
            scanf("%d", &tipoEstrutura);

            printf("Numero da pagina logica: ");
            scanf("%d", &numeroPagina);

            printf("Numero do frame fisico: ");
            scanf("%d", &numeroFrame);

            if (tipoEstrutura == 1)
                inserirHierarquica(numeroPagina, numeroFrame);

            else if (tipoEstrutura == 2)
                inserirHash(numeroPagina, numeroFrame);

            else if (tipoEstrutura == 3)
                inserirInvertida(numeroPagina, numeroFrame);

            printf("Mapeamento realizado com sucesso!\n");
        }

        else if (opcaoMenu == 2) {

            printf("\nEscolha a estrutura:\n");
            printf("1 - Hierarquica\n");
            printf("2 - Hash\n");
            printf("3 - Invertida\n");
            scanf("%d", &tipoEstrutura);

            printf("Numero da pagina logica: ");
            scanf("%d", &numeroPagina);

            if (tipoEstrutura == 1)
                buscarHierarquica(numeroPagina);

            else if (tipoEstrutura == 2)
                buscarHash(numeroPagina);

            else if (tipoEstrutura == 3)
                buscarInvertida(numeroPagina);
        }

    } while (opcaoMenu != 0);

    return 0;
}