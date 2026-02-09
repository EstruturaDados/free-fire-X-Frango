#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1. DEFINIÇÃO DAS ESTRUTURAS ---
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura para a Lista Encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Variável para contar as comparações
int comparacoes = 0;

// --- 2. FUNÇÕES PARA VETOR (MOCHILA SEQUENCIAL) ---

void inserirVetor(Item v[], int *n, Item novo) {
    if (*n < 10) {
        v[*n] = novo;
        (*n)++;
        printf("[Vetor] Item adicionado.\n");
    } else {
        printf("[Vetor] Erro: Mochila cheia!\n");
    }
}

void removerVetor(Item v[], int *n, char nome[]) {
    int encontrado = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(v[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado != -1) {
        for (int i = encontrado; i < (*n) - 1; i++) {
            v[i] = v[i + 1];
        }
        (*n)--;
        printf("[Vetor] Item '%s' removido.\n", nome);
    } else {
        printf("[Vetor] Item nao encontrado.\n");
    }
}

void buscarSequencialVetor(Item v[], int n, char nome[]) {
    comparacoes = 0;
    for (int i = 0; i < n; i++) {
        comparacoes++;
        if (strcmp(v[i].nome, nome) == 0) {
            printf("[Vetor] Achei! (Busca Sequencial). Comparacoes: %d\n", comparacoes);
            return;
        }
    }
    printf("[Vetor] Nao encontrado. Comparacoes: %d\n", comparacoes);
}

void ordenarVetor(Item v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Item temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
    printf("[Vetor] Ordenado com sucesso (Bubble Sort).\n");
}

void buscarBinariaVetor(Item v[], int n, char nome[]) {
    comparacoes = 0;
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int res = strcmp(v[meio].nome, nome);
        if (res == 0) {
            printf("[Vetor] Achei! (Busca Binaria). Comparacoes: %d\n", comparacoes);
            return;
        }
        if (res < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    printf("[Vetor] Nao encontrado na busca binaria. Comparacoes: %d\n", comparacoes);
}

// --- 3. FUNÇÕES PARA LISTA ENCADEADA (MOCHILA DINÂMICA) ---

void inserirLista(No** topo, Item novoItem) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) return;
    novoNo->dados = novoItem;
    novoNo->proximo = *topo;
    *topo = novoNo;
    printf("[Lista] Item adicionado.\n");
}

void removerLista(No** topo, char nome[]) {
    No *atual = *topo, *anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("[Lista] Item nao encontrado.\n");
        return;
    }
    if (anterior == NULL) *topo = atual->proximo;
    else anterior->proximo = atual->proximo;
    
    free(atual);
    printf("[Lista] Item '%s' removido.\n", nome);
}

void buscarSequencialLista(No* topo, char nome[]) {
    comparacoes = 0;
    No* atual = topo;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("[Lista] Achei! (Busca Sequencial). Comparacoes: %d\n", comparacoes);
            return;
        }
        atual = atual->proximo;
    }
    printf("[Lista] Nao encontrado. Comparacoes: %d\n", comparacoes);
}

// --- 4. LISTAGEM GERAL ---
void listarTudo(Item v[], int n, No* topo) {
    printf("\n--- STATUS DA MOCHILA ---\n");
    printf("VETOR (%d/10): ", n);
    for(int i=0; i<n; i++) printf("[%s] ", v[i].nome);
    
    printf("\nLISTA: ");
    No* atual = topo;
    while(atual != NULL) {
        printf("[%s] -> ", atual->dados.nome);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// --- 5. MENU PRINCIPAL ---
int main() {
    Item vetor[10];
    int nVetor = 0;
    No* lista = NULL;
    int opcao;

    do {
        printf("\n1. Adicionar Item | 2. Remover Item | 3. Buscar (Comparar) | 4. Ordenar Vetor | 5. Listar | 0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: {
                Item temp;
                printf("Nome: "); fgets(temp.nome, 30, stdin); temp.nome[strcspn(temp.nome, "\n")] = 0;
                printf("Tipo: "); fgets(temp.tipo, 20, stdin); temp.tipo[strcspn(temp.tipo, "\n")] = 0;
                printf("Qtd: "); scanf("%d", &temp.quantidade);
                inserirVetor(vetor, &nVetor, temp);
                inserirLista(&lista, temp);
                break;
            }
            case 2: {
                char nome[30];
                printf("Nome para remover: "); fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
                removerVetor(vetor, &nVetor, nome);
                removerLista(&lista, nome);
                break;
            }
            case 3: {
                char nome[30];
                printf("Nome para busca sequencial: "); fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
                buscarSequencialVetor(vetor, nVetor, nome);
                buscarSequencialLista(lista, nome);
                break;
            }
            case 4: {
                ordenarVetor(vetor, nVetor);
                char nome[30];
                printf("Nome para busca BINARIA no vetor: "); fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
                buscarBinariaVetor(vetor, nVetor, nome);
                break;
            }
            case 5: listarTudo(vetor, nVetor, lista); break;
        }
    } while (opcao != 0);

    return 0;
}