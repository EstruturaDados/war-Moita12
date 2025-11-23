#include <stdio.h>
#include <string.h>

/*
    Definição da struct Territorio:
    Armazena nome, cor do exército e quantidade de tropas.
*/
typedef struct {  
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Vetor para armazenar os 5 territórios
    Territorio territorios[5];

    // Entrada dos dados dos territórios
    for (int i = 0; i < 5; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);

        // Lendo o nome
        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);

        // Lendo a cor do exército
        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor);

        // Lendo a quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos territórios cadastrados
    printf("\n===== Territórios Cadastrados =====\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
