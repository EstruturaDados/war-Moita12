#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


Territorio* cadastrarTerritorios(int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

void trim_newline(char *s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') s[len - 1] = '\0';
}

int main() {
    srand((unsigned int) time(NULL)); // inicializa gerador de números aleatórios

    int n;
    printf("=== Simulador de Territórios (War - versão com ataque) ===\n");
    printf("Informe a quantidade de territórios a cadastrar: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Entrada inválida. Encerrando.\n");
        return 1;
    }
    while (getchar() != '\n'); 


    Territorio *mapa = cadastrarTerritorios(n);
    if (!mapa) {
        printf("Falha na alocação de memória. Encerrando.\n");
        return 1;
    }


    int opcao = 0;
    do {
        printf("\n--- Menu ---\n");
        printf("1 - Exibir territórios\n");
        printf("2 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Encerrando.\n");
            break;
        }
        while (getchar() != '\n');

        if (opcao == 1) {
            exibirTerritorios(mapa, n);
        } else if (opcao == 2) {
            exibirTerritorios(mapa, n);
            int idA, idD;
            printf("\nDigite o número do território ATACANTE (1 a %d): ", n);
            if (scanf("%d", &idA) != 1) { printf("Entrada inválida.\n"); while(getchar()!='\n'); continue; }
            printf("Digite o número do território DEFENSOR (1 a %d): ", n);
            if (scanf("%d", &idD) != 1) { printf("Entrada inválida.\n"); while(getchar()!='\n'); continue; }
            while (getchar() != '\n');


            if (idA < 1 || idA > n || idD < 1 || idD > n) {
                printf("Índices inválidos. Tente novamente.\n");
                continue;
            }
            if (idA == idD) {
                printf("Um território não pode atacar ele mesmo. Tente novamente.\n");
                continue;
            }

            Territorio *atac = &mapa[idA - 1];
            Territorio *def = &mapa[idD - 1];


            if (strcmp(atac->cor, def->cor) == 0) {
                printf("Operação inválida: não é permitido atacar um território da mesma cor (%s).\n", atac->cor);
                continue;
            }


            if (atac->tropas < 1) {
                printf("O território atacante '%s' não possui tropas suficientes para atacar.\n", atac->nome);
                continue;
            }


            atacar(atac, def);


            printf("\nMapa atualizado após o ataque:\n");
            exibirTerritorios(mapa, n);
        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}


Territorio* cadastrarTerritorios(int n) {

    Territorio *mapa = (Territorio*) calloc((size_t)n, sizeof(Territorio));
    if (!mapa) return NULL;

    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do Território %d/%d ===\n", i + 1, n);

        printf("Nome do território: ");
        if (fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin) == NULL) {
            strcpy(mapa[i].nome, "SemNome");
        }
        trim_newline(mapa[i].nome);

        printf("Cor do exército (dono): ");
        if (fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin) == NULL) {
            strcpy(mapa[i].cor, "Neutro");
        }
        trim_newline(mapa[i].cor);

        printf("Quantidade de tropas: ");
        if (scanf("%d", &mapa[i].tropas) != 1 || mapa[i].tropas < 0) {
            printf("Entrada inválida. Definindo tropas = 0.\n");
            mapa[i].tropas = 0;
        }
        while (getchar() != '\n');
    }

    return mapa;
}


void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n--- Lista de Territórios ---\n");
    for (int i = 0; i < n; i++) {

        Territorio *t = &mapa[i];
        printf("%2d) Nome: %-20s | Cor: %-8s | Tropas: %d\n",
               i + 1, t->nome, t->cor, t->tropas);
    }
}


void atacar(Territorio* atacante, Territorio* defensor) {
    if (!atacante || !defensor) return;

    printf("\n>>> Iniciando ataque: %s (%s, %d tropas)  -->  %s (%s, %d tropas)\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    int dadoAtac = (rand() % 6) + 1; // 1..6
    int dadoDef = (rand() % 6) + 1;

    printf("Rolagem: atacante tira %d | defensor tira %d\n", dadoAtac, dadoDef);

    if (dadoAtac > dadoDef) {
        
        int transferencia = atacante->tropas / 2; 
        if (transferencia < 1) transferencia = 1; 
        printf("Atacante venceu! Transferindo %d tropas e mudando o dono do defensor para '%s'.\n",
               transferencia, atacante->cor);

        strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor) - 1);
        defensor->cor[sizeof(defensor->cor) - 1] = '\0';

       
        defensor->tropas = transferencia;

       
        atacante->tropas -= transferencia;
        if (atacante->tropas < 0) atacante->tropas = 0;
    } else {
        
        printf("Defensor defendeu com sucesso! Atacante perde 1 tropa.\n");
        if (atacante->tropas > 0) atacante->tropas -= 1;
    }
}


void liberarMemoria(Territorio* mapa) {
    if (mapa) {
        free(mapa);
    }
}
