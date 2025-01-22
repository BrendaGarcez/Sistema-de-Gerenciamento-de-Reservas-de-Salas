#ifndef HASH_H
#define HASH_H
#include "avl.h"

// Definindo a estrutura Sala
typedef struct Sala {
    int codigoSala;          // Código identificador da sala
    char estado[20];         // Estado da sala: "bloqueada" ou "disponivel"
    struct Sala* prox;       // Ponteiro para a próxima sala (para tratar colisões)
} Sala;

// Estrutura para a Tabela Hash
typedef struct HashTabela {
    Sala** entradas;         // Vetor de ponteiros para as entradas da tabela
    int tamanho;             // Tamanho da tabela hash
} HashTabela;

int hashConta(int codSala, int tamanho);

// Função para criar a tabela hash
HashTabela* criarTabelaHash(FILE *saida);
HashTabela* inserirNaHash(HashTabela* tabela, int codigo, FILE *saida);

// Função para consultar o estado das salas
void printTabela(HashTabela* tabela, FILE *saida);
void buscarSalaHash(HashTabela* tabela, No* raiz, int codigo, FILE *saida);
HashTabela* mudarEstado(HashTabela* tabela, No* raiz, int codigo, FILE *saida);
void liberarHash(HashTabela* tabela, FILE *saida);
int liberarSalaHash(HashTabela* tabela, int codSala);

#endif
