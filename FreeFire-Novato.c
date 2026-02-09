#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct conforme o requisito
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das funções obrigatórias
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

int main() {
    // Vetor de structs com capacidade para 10 itens
    Item mochila[10];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n--- MOCHILA DE LOOT ---\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Inventario\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida, tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Função para cadastrar novos itens
void inserirItem(Item mochila[], int *total) {
    if (*total >= 10) {
        printf("Mochila cheia! Nao cabe mais nada.\n");
        return;
    }

    printf("Nome do item: ");
    fgets(mochila[*total].nome, 30, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = 0; // Remove o 'enter'

    printf("Tipo (arma, municao, cura): ");
    fgets(mochila[*total].tipo, 20, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    getchar();

    (*total)++;
    printf("Item coletado com sucesso!\n");
}

// Função para listar todos os itens (usada após cada operação)
void listarItens(Item mochila[], int total) {
    printf("\n--- ITENS NA MOCHILA ---\n");
    if (total == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d. Nome: %s | Tipo: %s | Qtd: %d\n", 
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função de busca sequencial
void buscarItem(Item mochila[], int total) {
    char nomeBusca[30];
    printf("Digite o nome do item que procura: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado: %s | Tipo: %s | Quantidade: %d\n", 
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("Item '%s' nao esta na mochila.\n", nomeBusca);
}

// Função para remover item e reorganizar a lista
void removerItem(Item mochila[], int *total) {
    char nomeRemover[30];
    printf("Nome do item para excluir: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = 0;

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // "Puxa" os itens da frente para trás para não deixar buraco no vetor
            for (int j = i; j < (*total) - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("Item removido da mochila.\n");
            return;
        }
    }
    printf("Item nao encontrado para remocao.\n");
}