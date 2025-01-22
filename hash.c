#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "avl.h"

int hashConta(int codSala, int tamanho) {
    return codSala % tamanho;  // Modulo do c�digo da sala pelo tamanho da tabela
}
// Fun��o para criar a tabela hash
HashTabela* criarTabelaHash(FILE *saida) {
    int tamanho = 8;
    HashTabela* tabela = (HashTabela*)malloc(sizeof(HashTabela));
    if (tabela == NULL) {
        fprintf(saida, "Erro: Falha ao alocar mem�ria para a tabela hash.\n");
        return NULL;
    }

    tabela->tamanho = tamanho;
    tabela->entradas = (Sala*)malloc(tamanho * sizeof(Sala));
    if (tabela->entradas == NULL) {
        fprintf(saida,"Erro: Falha ao alocar mem�ria para as entradas da tabela hash.\n");
        free(tabela);
        return NULL;
    }

    // Inicializa todas as entradas com NULL
    for (int i = 0; i < tamanho; i++) {
        tabela->entradas[i] = NULL;
    }
    tabela->tamanho = tamanho;
    return tabela;
}
HashTabela* inserirNaHash(HashTabela* tabela, int codigo, FILE *saida) {
    int mod;
    mod = codigo % tabela->tamanho;  // Calculando o �ndice para inser��o
    Sala* novaSala = (Sala*)malloc(sizeof(Sala)); // Alocando mem�ria para uma nova sala

    if (novaSala == NULL) {
        printf("Erro ao alocar memoria para a sala.\n");
        fprintf(saida,"Erro ao alocar memoria para a sala.\n");
        return tabela;
    }

    novaSala->codigoSala = codigo;
    strcpy(novaSala->estado, "disponivel"); // Definindo o estado da sala
    novaSala->prox = NULL; // Inicializando o ponteiro da pr�xima sala

    // Verificando se j� existe uma sala no �ndice
    if (tabela->entradas[mod] == NULL) {
        tabela->entradas[mod] = novaSala;  // Se n�o houver colis�o, coloca a sala diretamente
    } else {
        // Caso de colis�o: inser��o no final da lista encadeada
        Sala* temp = tabela->entradas[mod];
        while (temp->prox != NULL) {
            temp = temp->prox;  // Vai at� o final da lista
        }
        temp->prox = novaSala;  // Insere no final da lista encadeada
    }
    printf("Estado da sala atualizado para: Disponivel.\n");
    fprintf(saida,"Estado da sala atualizado para: Disponivel.\n");
    return tabela;
}

// Fun��o para consultar o estado das salas
void printTabela(HashTabela* tabela, FILE*saida) {
    for (int i = 0; i < tabela->tamanho; i++) {
        Sala* temp = tabela->entradas[i];
            while (temp != NULL) {
                printf("Sala %d - Estado: %s\n", temp->codigoSala, temp->estado);
                fprintf(saida, "Sala %d - Estado: %s\n", temp->codigoSala, temp->estado);
                temp = temp->prox;  // Move para o pr�ximo n� na lista encadeada
            }

    }
}
void buscarSalaHash(HashTabela* tabela, No* raiz, int codigo, FILE *saida) {
    No* existe=NULL;
    existe = buscarSalaAVL(raiz, codigo, saida);
    if(existe!=NULL){
        int mod = codigo % tabela->tamanho;  // Calculando o �ndice para busca

        // Percorrendo a lista encadeada no �ndice
        Sala* temp = tabela->entradas[mod];
        while (temp != NULL) {
            if (temp->codigoSala == codigo) {
                printf("O estado da sala %d e: %s\n", temp->codigoSala, temp->estado);
                return;
            }
            temp = temp->prox;  // Vai para o pr�ximo n�
        }
    }else{
        printf("Sala %d nao encontrada na hash.\n", codigo);
        fprintf(saida,"Sala %d nao encontrada na hash.\n", codigo);
    }
}

HashTabela* mudarEstado(HashTabela* tabela, No* raiz, int codigo, FILE *saida) {
    No* existe=NULL;
    existe = buscarSalaAVL(raiz, codigo, saida);
    if (existe == NULL) {
        printf("Sala %d nAo encontrada na AVL.\n", codigo);
        return tabela;
    }
    if(existe!=NULL){
        int mod = codigo % tabela->tamanho;  // Calculando o �ndice para busca

        // Percorrendo a lista encadeada no �ndice
        Sala* temp = tabela->entradas[mod];
        while (temp != NULL) {
            if (temp->codigoSala == codigo) {
                // Encontrou a sala, agora muda o estado
                if (strcmp(temp->estado, "disponivel") == 0) {
                    strcpy(temp->estado, "bloqueada");  // Muda o estado para "bloqueada"
                } else {
                    strcpy(temp->estado, "disponivel");  // Muda o estado para "disponivel"
                }
                printf("Estado da sala %d alterado para %s.\n", codigo, temp->estado);
                return tabela;  // Estado alterado com sucesso, retorna
            }
            temp = temp->prox;  // Vai para o pr�ximo n�
        }
    }
    return NULL;
}

void liberarHash(HashTabela* tabela, FILE *saida) {
    if (tabela == NULL) {
        fprintf(saida,"Tabela hash vazia.\n");
        return;
    }

    for (int i = 0; i < tabela->tamanho; i++) {
        Sala* atual = tabela->entradas[i];
        while (atual != NULL) {
            Sala* prox = atual->prox;
            free(atual);
            atual = prox;
        }
        tabela->entradas[i] = NULL;
    }

    free(tabela->entradas);
    tabela->entradas = NULL;

    free(tabela);
    tabela = NULL;

    fprintf(saida,"\nTabela hash liberada com sucesso.\n");
}

int liberarSalaHash(HashTabela* tabela, int codSala) {
    int indice = hashConta(codSala, tabela->tamanho);
    Sala* atual = tabela->entradas[indice];
    Sala* anterior = NULL;
    // Percorre a lista encadeada no �ndice especificado
    while (atual != NULL) {
        if (atual->codigoSala == codSala) {
            // Sala encontrada
            if (anterior == NULL) {
                // Caso seja a primeira sala na lista
                tabela->entradas[indice] = atual->prox;
            } else {
                // Ajusta o ponteiro do n� anterior
                anterior->prox = atual->prox;
            }
            free(atual); // Libera a mem�ria da sala
            return 1;    // Retorna sucesso
        }
        anterior = atual;
        atual = atual->prox;
    }
    // Caso n�o encontre a sala
    return 0;
}
