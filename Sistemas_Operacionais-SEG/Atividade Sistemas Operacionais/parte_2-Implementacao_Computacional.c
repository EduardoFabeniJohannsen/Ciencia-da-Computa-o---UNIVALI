#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAGINAS 128
#define MAX_FRAMES 128
#define HASH_SIZE 10

/* =====================================================
   1) PAGINACAO HIERARQUICA (2 NIVEIS)
===================================================== */

typedef struct {
    int valido;
    int frame;
} EntradaNivel2;

typedef struct {
    EntradaNivel2 *tabela[16];
} TabelaNivel1;

TabelaNivel1 hierarquica;

void initHierarquica() {
    for (int i = 0; i < 16; i++)
        hierarquica.tabela[i] = NULL;
}

void inserirHierarquica(int pagina, int frame) {
    int p1 = pagina / 16;
    int p2 = pagina % 16;

    if (hierarquica.tabela[p1] == NULL) {
        hierarquica.tabela[p1] = malloc(sizeof(EntradaNivel2) * 16);

        for (int i = 0; i < 16; i++) {
            hierarquica.tabela[p1][i].valido = 0;
            hierarquica.tabela[p1][i].frame = -1;
        }
    }

    hierarquica.tabela[p1][p2].valido = 1;
    hierarquica.tabela[p1][p2].frame = frame;
}

void buscarHierarquica(int pagina) {
    int p1 = pagina / 16;
    int p2 = pagina % 16;

    if (hierarquica.tabela[p1] == NULL ||
        hierarquica.tabela[p1][p2].valido == 0) {
        printf("Page Fault\n");
        return;
    }

    printf("Frame encontrado: %d\n",
           hierarquica.tabela[p1][p2].frame);
}

/* =====================================================
   2) TABELA HASH
===================================================== */

typedef struct NoHash {
    int pagina;
    int frame;
    struct NoHash *prox;
} NoHash;

NoHash *hash[HASH_SIZE];

void initHash() {
    for (int i = 0; i < HASH_SIZE; i++)
        hash[i] = NULL;
}

int funcaoHash(int pagina) {
    return pagina % HASH_SIZE;
}

void inserirHash(int pagina, int frame) {
    int pos = funcaoHash(pagina);

    NoHash *novo = malloc(sizeof(NoHash));
    novo->pagina = pagina;
    novo->frame = frame;
    novo->prox = hash[pos];

    hash[pos] = novo;
}

void buscarHash(int pagina) {
    int pos = funcaoHash(pagina);

    NoHash *aux = hash[pos];

    while (aux != NULL) {
        if (aux->pagina == pagina) {
            printf("Frame encontrado: %d\n", aux->frame);
            return;
        }
        aux = aux->prox;
    }

    printf("Page Fault\n");
}

/* =====================================================
   3) TABELA INVERTIDA
===================================================== */

typedef struct {
    int ocupado;
    int pagina;
} EntradaInvertida;

EntradaInvertida invertida[MAX_FRAMES];

void initInvertida() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        invertida[i].ocupado = 0;
        invertida[i].pagina = -1;
    }
}

void inserirInvertida(int pagina, int frame) {
    invertida[frame].ocupado = 1;
    invertida[frame].pagina = pagina;
}

void buscarInvertida(int pagina) {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (invertida[i].ocupado &&
            invertida[i].pagina == pagina) {
            printf("Frame encontrado: %d\n", i);
            return;
        }
    }

    printf("Page Fault\n");
}

/* =====================================================
   MENU
===================================================== */

int main() {
    int opcao, estrutura;
    int pagina, frame;

    initHierarquica();
    initHash();
    initInvertida();

    do {
        printf("\n===== EMULADOR PAGINACAO =====\n");
        printf("1 - Inserir pagina\n");
        printf("2 - Buscar pagina\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("\n1-Hierarquica  2-Hash  3-Invertida\n");
            scanf("%d", &estrutura);

            printf("Pagina logica: ");
            scanf("%d", &pagina);

            printf("Frame fisico: ");
            scanf("%d", &frame);

            if (estrutura == 1)
                inserirHierarquica(pagina, frame);
            else if (estrutura == 2)
                inserirHash(pagina, frame);
            else if (estrutura == 3)
                inserirInvertida(pagina, frame);

            printf("Mapeamento realizado!\n");
        }

        else if (opcao == 2) {
            printf("\n1-Hierarquica  2-Hash  3-Invertida\n");
            scanf("%d", &estrutura);

            printf("Pagina logica: ");
            scanf("%d", &pagina);

            if (estrutura == 1)
                buscarHierarquica(pagina);
            else if (estrutura == 2)
                buscarHash(pagina);
            else if (estrutura == 3)
                buscarInvertida(pagina);
        }

    } while (opcao != 0);

    return 0;
}