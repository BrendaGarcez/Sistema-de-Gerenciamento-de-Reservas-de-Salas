#include <stdio.h>
#include "hash.h"

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