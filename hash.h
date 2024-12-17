#ifndef HASH_H
#define HASH_H

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

void bloquearSalaHash();
void desbloquearSalaHash();
void consultarEstadoHash();
HashTabela* criarTabelaHash(int tamanho);

#endif
