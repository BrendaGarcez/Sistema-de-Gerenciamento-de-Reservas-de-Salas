#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10 // Tamanho da tabela hash

// Estrutura para uma sala
typedef struct Sala {
    int codigoSala;         // Código identificador da sala
    char estado[20];        // Estado da sala: "bloqueada" ou "disponivel"
    struct Sala* prox;      // Ponteiro para o próximo elemento (tratamento de colisões)
} Sala;

// Estrutura para a tabela hash
typedef struct {
    Sala** entradas;        // Vetor de ponteiros para entradas (listas encadeadas)
    int tamanho;            // Tamanho da tabela hash
} HashTable;

// Função para criar uma tabela hash
HashTable* criarTabelaHash(int tamanho) {
    HashTable* tabela = (HashTable*)malloc(sizeof(HashTable));
    tabela->tamanho = tamanho;
    tabela->entradas = (Sala**)malloc(tamanho * sizeof(Sala*));

    for (int i = 0; i < tamanho; i++) {
        tabela->entradas[i] = NULL; // Inicializa todas as entradas como nulas
    }
    return tabela;
}

// Função hash (função simples para calcular o índice)
int funcaoHash(int codigoSala, int tamanho) {
    return codigoSala % tamanho;
}

// Função para adicionar uma sala na tabela hash
void adicionarSala(HashTable* tabela, int codigoSala, const char* estado) {
    int indice = funcaoHash(codigoSala, tabela->tamanho);

    // Cria uma nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    novaSala->codigoSala = codigoSala;
    strcpy(novaSala->estado, estado);
    novaSala->prox = NULL;

    // Adiciona no início da lista encadeada (tratamento de colisões)
    if (tabela->entradas[indice] == NULL) {
        tabela->entradas[indice] = novaSala;
    } else {
        Sala* atual = tabela->entradas[indice];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novaSala;
    }
    printf("Sala %d (%s) adicionada com sucesso!\n", codigoSala, estado);
}

// Função para consultar o estado de uma sala
void consultarEstado(HashTable* tabela, int codigoSala) {
    int indice = funcaoHash(codigoSala, tabela->tamanho);

    Sala* atual = tabela->entradas[indice];
    while (atual != NULL) {
        if (atual->codigoSala == codigoSala) {
            printf("Sala %d encontrada. Estado: %s\n", codigoSala, atual->estado);
            return;
        }
        atual = atual->prox;
    }
    printf("Sala %d não encontrada.\n", codigoSala);
}

// Função para bloquear uma sala
void bloquearSala(HashTable* tabela, int codigoSala) {
    int indice = funcaoHash(codigoSala, tabela->tamanho);

    Sala* atual = tabela->entradas[indice];
    while (atual != NULL) {
        if (atual->codigoSala == codigoSala) {
            strcpy(atual->estado, "bloqueada");
            printf("Sala %d foi bloqueada.\n", codigoSala);
            return;
        }
        atual = atual->prox;
    }
    printf("Sala %d não encontrada para bloqueio.\n", codigoSala);
}

// Função para desbloquear uma sala
void desbloquearSala(HashTable* tabela, int codigoSala) {
    int indice = funcaoHash(codigoSala, tabela->tamanho);

    Sala* atual = tabela->entradas[indice];
    while (atual != NULL) {
        if (atual->codigoSala == codigoSala) {
            strcpy(atual->estado, "disponivel");
            printf("Sala %d foi desbloqueada.\n", codigoSala);
            return;
        }
        atual = atual->prox;
    }
    printf("Sala %d não encontrada para desbloqueio.\n", codigoSala);
}

// Função para listar todas as salas
void listarSalas(HashTable* tabela) {
    printf("Listando todas as salas:\n");
    for (int i = 0; i < tabela->tamanho; i++) {
        Sala* atual = tabela->entradas[i];
        if (atual == NULL) {
            continue;
        }
        printf("Indice %d:\n", i);
        while (atual != NULL) {
            printf(" - Sala %d, Estado: %s\n", atual->codigoSala, atual->estado);
            atual = atual->prox;
        }
    }
}

// Função para liberar memória da tabela hash
void liberarTabela(HashTable* tabela) {
    for (int i = 0; i < tabela->tamanho; i++) {
        Sala* atual = tabela->entradas[i];
        while (atual != NULL) {
            Sala* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(tabela->entradas);
    free(tabela);
}

int main() {
    HashTable* tabela = criarTabelaHash(TAMANHO_TABELA);

    printf("Teste da Tabela Hash\n\n");

    // Adicionando salas
    adicionarSala(tabela, 101, "disponivel");
    adicionarSala(tabela, 102, "disponivel");
    adicionarSala(tabela, 203, "bloqueada");
    adicionarSala(tabela, 104, "disponivel");
    adicionarSala(tabela, 305, "bloqueada");

    // Listar todas as salas
    listarSalas(tabela);

    // Consultar estados específicos
    consultarEstado(tabela, 203);
    consultarEstado(tabela, 999); // Não existe

    // Alterar estado das salas
    bloquearSala(tabela, 104);
    desbloquearSala(tabela, 203);

    // Listar novamente após alterações
    listarSalas(tabela);

    // Liberar memória
    liberarTabela(tabela);
    return 0;
}
