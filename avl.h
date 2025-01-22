#ifndef AVL_H
#define AVL_H

typedef struct No {
    int codigoSala;
    int capacidade;
    int altDireita;
    int altEsquerda;
    struct No* direita;
    struct No* esquerda;
} No;

// Funções auxiliares
int max(int a, int b);
int calcularAltura(No* no);
No* encontrarMinimo(No* raiz);

// Funções principais da árvore AVL
No* inserirNoAVL(No* raiz, int codigoSala, int capacidade, FILE *saida);
void inserirSalaAVL();  // Função para inserir uma sala na árvore AVL
No* removerNoAVL(No* raiz, int codigoSala, FILE*saida);
No* buscarSalaAVL(No* raiz, int codigoSala, FILE *saida);
void listarSalaAVL(No* raiz, FILE *saida);

// Funções de manipulação de nós
No* criarNo(int codigoSala, int capacidade, FILE *saida);
No* rotacaoEsquerda(No* no);
No* rotacaoDireita(No* no);

// Funções de balanceamento
int fatorBalanceamento(No* no);
No* balanceamento(No* no);

// Função de liberação de memória
void liberarAVL(No **raiz, FILE *saida);



#endif

