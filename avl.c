#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}
int calcularAltura(No* no) {
    if (no == NULL) {
        return -1;
    }
    return 1 + (max(calcularAltura(no->esquerda), calcularAltura(no->direita)));
}

No* criarNo(int codigoSala, int capacidade, FILE *saida) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria.\n");
        fprintf(saida, "Erro ao alocar memoria.\n");
        exit(1);
    }
    novoNo->codigoSala = codigoSala;
    novoNo->capacidade = capacidade;
    novoNo->altDireita = 0;
    novoNo->altEsquerda = 0;
    novoNo->direita = NULL;
    novoNo->esquerda = NULL;
    return novoNo;
}

// Fun��o para inserir uma sala na �rvore AVL
No* inserirNoAVL(No* raiz, int codigoSala, int capacidade, FILE *saida) {
    if (raiz == NULL) {
        printf("\nSala criada com sucesso: Codigo %d, Capacidade %d.\n", codigoSala, capacidade);
        fprintf(saida, "\nSala criada com sucesso: Codigo %d, Capacidade %d.\n", codigoSala, capacidade);
        return criarNo(codigoSala, capacidade, saida); // Cria e retorna um novo n� se a raiz for NULL
    }

    // Inser��o na sub�rvore esquerda
    if (codigoSala < raiz->codigoSala) {
        raiz->esquerda = inserirNoAVL(raiz->esquerda, codigoSala, capacidade, saida);
    }
    // Inser��o na sub�rvore direita
    else if (codigoSala > raiz->codigoSala) {
        raiz->direita = inserirNoAVL(raiz->direita, codigoSala, capacidade, saida);
    }
    else {
        // Caso o c�digo da sala j� exista
        printf("Codigo de sala ja existe: %d\n", codigoSala);
        fprintf(saida,"Codigo de sala ja existe: %d\n", codigoSala);
        return raiz;
    }

    // Atualizar a altura da raiz ap�s inser��o
    raiz->altEsquerda = calcularAltura(raiz->esquerda);
    raiz->altDireita = calcularAltura(raiz->direita);

    // Verificar e aplicar balanceamento
    return balanceamento(raiz);
}

//Se aplica na escolha do qual ter prioridade em caso de remo��o
No* encontrarMinimo(No* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    // Iterar at� o n� mais � esquerda (menor valor)
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

No* rotacaoEsquerda(No* no) {
    No *aux1, *aux2;
    aux1 = no->direita;
    aux2 = aux1->esquerda;
    no->direita = aux2;
    aux1->esquerda = no;

    if (no->direita == NULL) {
        no->altDireita = 0;
    } else if (no->direita->altEsquerda > no->direita->altDireita) {
        no->altDireita = no->direita->altEsquerda + 1;
    } else {
        no->altDireita = no->direita->altDireita + 1;
    }

    if (aux1->esquerda->altEsquerda > aux1->esquerda->altDireita) {
        aux1->altEsquerda = aux1->esquerda->altEsquerda + 1;
    } else {
        aux1->altEsquerda = aux1->esquerda->altDireita + 1;
    }

    return aux1;
}
No* rotacaoDireita(No* no) {
    No *aux1, *aux2;
    aux1 = no->esquerda;
    aux2 = aux1->direita;
    no->esquerda = aux2;
    aux1->direita = no;

    if (no->esquerda == NULL) {
        no->altEsquerda = 0;
    } else if (no->esquerda->altEsquerda > no->esquerda->altDireita) {
        no->altEsquerda = no->esquerda->altEsquerda + 1;
    } else {
        no->altEsquerda = no->esquerda->altDireita + 1;
    }

    if (aux1->direita->altDireita > aux1->direita->altEsquerda) {
        aux1->altDireita = aux1->direita->altDireita + 1;
    } else {
        aux1->altDireita = aux1->direita->altEsquerda + 1;
    }

    return aux1;
}
////Fun��es de Balanceamento
int fatorBalanceamento(No* no) {
    return calcularAltura(no->direita) - calcularAltura(no->esquerda);
}
No* balanceamento(No* no) {
    int fb = fatorBalanceamento(no);
    // Caso de desbalanceamento para a direita
    if (fb == 2) {
        if (fatorBalanceamento(no->direita) >= 0) {
            no = rotacaoEsquerda(no);
        } else {
            no->direita = rotacaoDireita(no->direita);
            no = rotacaoEsquerda(no);
        }
    }
    // Caso de desbalanceamento para a esquerda
    else if (fb == -2) {
        if (fatorBalanceamento(no->esquerda) <= 0) {
            no = rotacaoDireita(no);
        } else {
            no->esquerda = rotacaoEsquerda(no->esquerda);
            no = rotacaoDireita(no);
        }
    }

    // Atualiza as alturas ap�s as rota��es
    no->altEsquerda = calcularAltura(no->esquerda);
    no->altDireita = calcularAltura(no->direita);

    return no;
}
// Fun��o para buscar uma sala na �rvore AVL
No* buscarSalaAVL(No* raiz, int codigoSala, FILE *saida) {
    if (raiz == NULL) {
        printf("Sala com codigo %d nao encontrada.\n", codigoSala);
        fprintf(saida,"Sala com codigo %d nao encontrada.\n", codigoSala);
        return NULL;
    }
    if (codigoSala == raiz->codigoSala) {
        printf("Sala encontrada: [Codigo %d, Capacidade %d]\n", raiz->codigoSala, raiz->capacidade);
        return raiz;
    }
    // sub�rvore esquerda
    if (codigoSala < raiz->codigoSala) {
        return buscarSalaAVL(raiz->esquerda, codigoSala, saida);
    }
    //sub�rvore direita
    return buscarSalaAVL(raiz->direita, codigoSala,saida);
}
// Fun��o para listar as salas em ordem crescente
void listarSalaAVL(No* raiz, FILE *saida) {
    if (raiz == NULL) {
        return;
    }
    listarSalaAVL(raiz->esquerda, saida);
    printf("Sala %d - Capacidade: %d\n", raiz->codigoSala, raiz->capacidade);
    fprintf(saida, "Sala %d - Capacidade: %d\n", raiz->codigoSala, raiz->capacidade);
    listarSalaAVL(raiz->direita, saida);
}
// Fun��o para remover um n� da �rvore AVL
No* removerNoAVL(No* raiz, int codigoSala, FILE*saida) {
    if (raiz == NULL) {
        return NULL;
    }

    // Encontrar o n� a ser removido
    if (codigoSala < raiz->codigoSala) {
        raiz->esquerda = removerNoAVL(raiz->esquerda, codigoSala, saida);  // Busca na sub�rvore esquerda
    } else if (codigoSala > raiz->codigoSala) {
        raiz->direita = removerNoAVL(raiz->direita, codigoSala, saida);  // Busca na sub�rvore direita
    } else {
        // Caso o n� a ser removido seja encontrado
        if (raiz->esquerda == NULL) {
            // N� com apenas filho � direita ou sem filhos
            No* temp = raiz->direita;
            free(raiz);
            raiz = NULL;
            return temp;
        } else if (raiz->direita == NULL) {
            // N� com apenas filho � esquerda
            No* temp = raiz->esquerda;
            free(raiz);
            raiz = NULL;
            return temp;
        }
        // Caso o n� tenha dois filhos
        No* temp = encontrarMinimo(raiz->direita);  // Encontra o sucessor (menor n� na sub�rvore direita)
        raiz->codigoSala = temp->codigoSala;  // Substitui o valor do n�
        raiz->capacidade = temp->capacidade;

        // Remove o sucessor na sub�rvore direita
        raiz->direita = removerNoAVL(raiz->direita, temp->codigoSala, saida);
    }

    // Atualiza as alturas das sub�rvores
    raiz->altEsquerda = calcularAltura(raiz->esquerda);
    raiz->altDireita = calcularAltura(raiz->direita);

    // Verifica e aplica balanceamento
    return balanceamento(raiz);
}
void liberarAVL(No **raiz, FILE *saida) {
    if (*raiz == NULL) {
        return;
    }
    liberarAVL(&(*raiz)->esquerda, saida);
    liberarAVL(&(*raiz)->direita, saida);
    free(*raiz);// Garantir que o ponteiro seja nulo ap�s liberar
    *raiz = NULL;
}
