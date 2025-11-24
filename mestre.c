#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

Territorio* cadastrarTerritorios(int n) {
    Territorio* mapa = calloc(n, sizeof(Territorio));
    for (int i = 0; i < n; i++) {
        printf("Nome do territorio %d: ", i + 1);
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
    return mapa;
}

void exibirMapa(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d) %s | %s | %d tropas\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void atacar(Territorio* a, Territorio* d) {
    int da = rand() % 6 + 1;
    int dd = rand() % 6 + 1;
    if (da > dd) {
        int metade = a->tropas / 2;
        if (metade < 1) metade = 1;
        strcpy(d->cor, a->cor);
        d->tropas = metade;
        a->tropas -= metade;
    } else {
        if (a->tropas > 0) a->tropas--;
    }
}

void atribuirMissao(char* destino, char* missoes[], int total) {
    int r = rand() % total;
    strcpy(destino, missoes[r]);
}

int verificarMissao(char* missao, Territorio* mapa, int n) {
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        int cont = 0;
        for (int i = 0; i < n; i++) {
            if (mapa[i].tropas > 0) cont++;
        }
        return cont >= 3;
    }
    if (strcmp(missao, "Eliminar tropas vermelhas") == 0) {
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0) return 0;
        }
        return 1;
    }
    if (strcmp(missao, "Manter 2 territorios vivos") == 0) {
        int vivos = 0;
        for (int i = 0; i < n; i++) {
            if (mapa[i].tropas > 0) vivos++;
        }
        return vivos >= 2;
    }
    if (strcmp(missao, "Dominar qualquer territorio") == 0) {
        for (int i = 0; i < n; i++) {
            if (mapa[i].tropas > 0) return 1;
        }
        return 0;
    }
    if (strcmp(missao, "Eliminar 1 territorio inimigo") == 0) {
        for (int i = 0; i < n; i++) {
            if (mapa[i].tropas == 0) return 1;
        }
        return 0;
    }
    return 0;
}

void exibirMissao(char* missao) {
    printf("Sua missao: %s\n", missao);
}

void liberarMemoria(Territorio* mapa, char* m1, char* m2) {
    free(mapa);
    free(m1);
    free(m2);
}

int main() {
    srand(time(NULL));
    int n;
    printf("\nQuantidade de territorios: ");
    scanf("%d", &n);
    getchar();

    Territorio* mapa = cadastrarTerritorios(n);

    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar tropas vermelhas",
        "Manter 2 territorios vivos",
        "Dominar qualquer territorio",
        "Eliminar 1 territorio inimigo"
    };

    int totalMissoes = 5;

    char* missao1 = malloc(200);
    char* missao2 = malloc(200);

    atribuirMissao(missao1, missoes, totalMissoes);
    atribuirMissao(missao2, missoes, totalMissoes);

    printf("\nJogador 1: ");
    exibirMissao(missao1);

    printf("Jogador 2: ");
    exibirMissao(missao2);

    int turno = 1;
    while (1) {
        printf("\n=== Turno %d ===\n", turno);
        exibirMapa(mapa, n);

        int a, d;
        printf("Atacante: ");
        scanf("%d", &a);
        printf("Defensor: ");
        scanf("%d", &d);
        getchar();

        if (a >= 1 && a <= n && d >= 1 && d <= n && strcmp(mapa[a-1].cor, mapa[d-1].cor) != 0) {
            atacar(&mapa[a-1], &mapa[d-1]);
        }

        if (verificarMissao(missao1, mapa, n)) {
            printf("\nJogador 1 venceu!\n");
            break;
        }
        if (verificarMissao(missao2, mapa, n)) {
            printf("\nJogador 2 venceu!\n");
            break;
        }

        turno++;
    }

    liberarMemoria(mapa, missao1, missao2);
    return 0;
}
