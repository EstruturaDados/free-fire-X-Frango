#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- 1. DEFINIÇÃO DA ESTRUTURA ---
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
} Componente;

// Variáveis globais para facilitar a medição educacional
int comparacoesGlobais = 0;
int ordenadaPorNome = 0; // Trava de segurança para a busca binária

// --- 2. ALGORITMOS DE ORDENAÇÃO ---

// Bubble Sort: Ordena por NOME (String)
void bubbleSortNome(Componente v[], int n) {
    comparacoesGlobais = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoesGlobais++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
    ordenadaPorNome = 1; // Agora a busca binária pode ser feita
}

// Insertion Sort: Ordena por TIPO (String)
void insertionSortTipo(Componente v[], int n) {
    comparacoesGlobais = 0;
    for (int i = 1; i < n; i++) {
        Componente pivo = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, pivo.tipo) > 0) {
            comparacoesGlobais++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = pivo;
    }
    ordenadaPorNome = 0; // Perde a ordenação por nome
}

// Selection Sort: Ordena por PRIORIDADE (Inteiro)
void selectionSortPrioridade(Componente v[], int n) {
    comparacoesGlobais = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoesGlobais++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        Componente temp = v[i];
        v[i] = v[min];
        v[min] = temp;
    }
    ordenadaPorNome = 0;
}

// --- 3. BUSCA BINÁRIA ---
int buscaBinariaPorNome(Componente v[], int n, char nomeBusca[]) {
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int res = strcmp(v[meio].nome, nomeBusca);
        if (res == 0) return meio;
        if (res < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// --- 4. EXIBIÇÃO E MEDIÇÃO ---

void mostrarComponentes(Componente v[], int n) {
    printf("\n--- COMPONENTES DA TORRE ---\n");
    printf("%-20s | %-15s | %-10s\n", "Nome", "Tipo", "Prioridade");
    for (int i = 0; i < n; i++) {
        printf("%-20s | %-15s | %-10d\n", v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// Função obrigatória: recebe o ponteiro do algoritmo e o executa medindo o tempo
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t t;
    t = clock(); // Início do cronômetro
    algoritmo(v, n);
    t = clock() - t; // Fim do cronômetro
    
    double tempo_ms = ((double)t) / (CLOCKS_PER_SEC / 1000);
    printf("\n>>> Desempenho: %d comparacoes em %.4f ms\n", comparacoesGlobais, tempo_ms);
}

// --- 5. MENU INTERATIVO ---

int main() {
    Componente torre[20];
    int total = 0;
    int opcao;

    do {
        printf("\n=== TORRE DE RESGATE FINAL ===\n");
        printf("1. Cadastrar Componente\n");
        printf("2. Ordenar por Nome\n");
        printf("3. Ordenar por Tipo\n");
        printf("4. Ordenar por Prioridade\n");
        printf("5. Buscar Componente-Chave\n");
        printf("6. Listar Componentes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if (total < 20) {
                    printf("Nome do componente: "); fgets(torre[total].nome, 30, stdin);
                    torre[total].nome[strcspn(torre[total].nome, "\n")] = 0;
                    printf("Tipo: (estrutura, energia...) "); fgets(torre[total].tipo, 20, stdin);
                    torre[total].tipo[strcspn(torre[total].tipo, "\n")] = 0;
                    printf("Prioridade (1-10): "); scanf("%d", &torre[total].prioridade);
                    total++;
                    ordenadaPorNome = 0;
                } else printf("Capacidade maxima da torre atingida!\n");
                break;

            case 2:
                medirTempo(bubbleSortNome, torre, total);
                mostrarComponentes(torre, total);
                break;

            case 3:
                medirTempo(insertionSortTipo, torre, total);
                mostrarComponentes(torre, total);
                break;

            case 4:
                medirTempo(selectionSortPrioridade, torre, total);
                mostrarComponentes(torre, total);
                break;

            case 5:
                if (!ordenadaPorNome) {
                    printf("\n[AVISO] A torre precisa estar ordenada por NOME para a busca binaria!\n");
                } else {
                    char busca[30];
                    printf("Qual componente-chave buscar? ");
                    fgets(busca, 30, stdin); busca[strcspn(busca, "\n")] = 0;
                    int posicao = buscaBinariaPorNome(torre, total, busca);
                    if (posicao != -1) {
                        printf("\n[SUCESSO] Componente '%s' localizado na posicao %d! Ativando torre...\n", busca, posicao + 1);
                    } else printf("\n[FALHA] Componente-chave nao encontrado.\n");
                }
                break;

            case 6:
                mostrarComponentes(torre, total);
                break;
        }
    } while (opcao != 0);

    return 0;
}