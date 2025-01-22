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

// Fun��es auxiliares
int max(int a, int b);
int calcularAltura(No* no);
No* encontrarMinimo(No* raiz);

// Fun��es principais da �rvore AVL
No* inserirNoAVL(No* raiz, int codigoSala, int capacidade, FILE *saida);
void inserirSalaAVL();  // Fun��o para inserir uma sala na �rvore AVL
No* removerNoAVL(No* raiz, int codigoSala, FILE*saida);
No* buscarSalaAVL(No* raiz, int codigoSala, FILE *saida);
void listarSalaAVL(No* raiz, FILE *saida);

// Fun��es de manipula��o de n�s
No* criarNo(int codigoSala, int capacidade, FILE *saida);
No* rotacaoEsquerda(No* no);
No* rotacaoDireita(No* no);

// Fun��es de balanceamento
int fatorBalanceamento(No* no);
No* balanceamento(No* no);

// Fun��o de libera��o de mem�ria
void liberarAVL(No **raiz, FILE *saida);



#endif

