#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Enum para critérios de ordenação
typedef enum { NOME, TIPO, PRIORIDADE } CriterioOrdenacao;

// Struct Item conforme a edição "Mestre"
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Variáveis de controle globais para facilitar o fluxo acadêmico
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

// Protótipos
void exibirMenu();
void inserirItem(Item mochila[]);
void removerItem(Item mochila[]);
void listarItens(Item mochila[]);
void menuDeOrdenacao(Item mochila[]);
void insertionSort(Item mochila[], CriterioOrdenacao criterio);
void buscaBinariaPorNome(Item mochila[]);
void limparTela();

int main() {
    Item mochila[MAX_ITENS];
    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa buffer

        switch (opcao) {
            case 1: inserirItem(mochila); break;
            case 2: removerItem(mochila); break;
            case 3: listarItens(mochila); break;
            case 4: menuDeOrdenacao(mochila); break;
            case 5: buscaBinariaPorNome(mochila); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void limparTela() {
    for (int i = 0; i < 30; i++) printf("\n");
}

void exibirMenu() {
    printf("\n=== CODIGO DA ILHA - INVENTARIO MESTRE ===\n");
    printf("Status: %s\n", ordenadaPorNome ? "Ordenado por Nome (Busca Binaria Ativa)" : "Nao Ordenado");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("4. Ordenar Itens (Insertion Sort)\n");
    printf("5. Busca Binaria por Nome\n");
    printf("0. Sair\n");
}

void inserirItem(Item mochila[]) {
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    printf("Nome: "); fgets(mochila[numItens].nome, 30, stdin);
    mochila[numItens].nome[strcspn(mochila[numItens].nome, "\n")] = 0;
    
    printf("Tipo: "); fgets(mochila[numItens].tipo, 20, stdin);
    mochila[numItens].tipo[strcspn(mochila[numItens].tipo, "\n")] = 0;

    printf("Quantidade: "); scanf("%d", &mochila[numItens].quantidade);
    printf("Prioridade (1-5): "); scanf("%d", &mochila[numItens].prioridade);
    
    numItens++;
    ordenadaPorNome = false; // Nova inserção quebra a ordenação
    printf("Item adicionado!\n");
}

void removerItem(Item mochila[]) {
    char busca[30];
    printf("Nome do item para remover: ");
    fgets(busca, 30, stdin);
    busca[strcspn(busca, "\n")] = 0;

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, busca) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            numItens--;
            printf("Item removido.\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

void listarItens(Item mochila[]) {
    printf("\n%-20s | %-15s | %-5s | %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    for (int i = 0; i < numItens; i++) {
        printf("%-20s | %-15s | %-5d | %-10d\n", 
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

void insertionSort(Item mochila[], CriterioOrdenacao criterio) {
    comparacoes = 0;
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        bool condicao = false;

        while (j >= 0) {
            comparacoes++;
            if (criterio == NOME) condicao = (strcmp(mochila[j].nome, chave.nome) > 0);
            else if (criterio == TIPO) condicao = (strcmp(mochila[j].tipo, chave.tipo) > 0);
            else if (criterio == PRIORIDADE) condicao = (mochila[j].prioridade < chave.prioridade); // Maior primeiro

            if (condicao) {
                mochila[j + 1] = mochila[j];
                j--;
            } else break;
        }
        mochila[j + 1] = chave;
    }
    if (criterio == NOME) ordenadaPorNome = true;
    printf("Ordenacao concluida. Comparacoes realizadas: %d\n", comparacoes);
}

void menuDeOrdenacao(Item mochila[]) {
    int esc;
    printf("Ordenar por: 1. Nome | 2. Tipo | 3. Prioridade: ");
    scanf("%d", &esc);
    if (esc == 1) insertionSort(mochila, NOME);
    else if (esc == 2) insertionSort(mochila, TIPO);
    else if (esc == 3) insertionSort(mochila, PRIORIDADE);
}

void buscaBinariaPorNome(Item mochila[]) {
    if (!ordenadaPorNome) {
        printf("Erro: Ordene a mochila por NOME antes de usar busca binaria!\n");
        return;
    }
    char busca[30];
    printf("Buscar nome: ");
    fgets(busca, 30, stdin);
    busca[strcspn(busca, "\n")] = 0;

    int inicio = 0, fim = numItens - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int res = strcmp(mochila[meio].nome, busca);

        if (res == 0) {
            printf("Encontrado! Tipo: %s, Qtd: %d, Prioridade: %d\n", 
                   mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        }
        if (res < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    printf("Item nao encontrado.\n");
}