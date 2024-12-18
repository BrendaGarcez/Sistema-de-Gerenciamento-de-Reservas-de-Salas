#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "avl.h"

// Função para bloquear uma sala
void bloquearSalaHash() {
    printf("Função para bloquear sala ainda não implementada.\n");
}

// Função para desbloquear uma sala
void desbloquearSalaHash() {
    printf("Função para desbloquear sala ainda não implementada.\n");
}

// Função para consultar o estado das salas
void consultarEstadoHash() {
    printf("Função para consultar estado das salas ainda não implementada.\n");
}
HashTabela* criarTabelaHash(int tamanho) {
    HashTabela* tabela = (HashTabela*)malloc(sizeof(HashTabela));
    tabela->entradas = (Sala**)malloc(tamanho * sizeof(Sala*));
    for (int i = 0; i < tamanho; i++) {
        tabela->entradas[i] = NULL; // Inicializa cada entrada como nula
    }
    tabela->tamanho = tamanho;
    return tabela;
}
void liberarHash(HashTabela* tabela) {
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->entradas[i] != NULL) {
            free(tabela->entradas[i]); // libera cada sala na tabela
        }
    }
    free(tabela->entradas);
    free(tabela);
}
