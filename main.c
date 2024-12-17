/*  Projeto desenvolvido por: 
        Brenda Amanda da Silva Garcez
        Nicole Louise Matias Jamuchewski

    1. Árvore AVL para gerenciar informações das salas.
    2. Heap para gerenciar prioridades de reservas.
    3. Tabela Hash para armazenar estados das salas.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "heap.h"
#include "hash.h"

No* criarNo(int codigoSala, int capacidade);
void encerrarSistema(No* raizAVL, MaxHeap* heap, HashTabela* tabelaHash);

//Funcoes por arvore
//(é utilizada para organizar e armazenar as informações das salas de forma balanceada, busca inserção e remoção eficiente)
//AVL(Gestão de sala)
//add novas salas
void removerSalaAVL();//exclui salas existentes
void buscarSalaAVL();//busca pelo código da sala
void listarSalaAVL();//exibe salas em ordem crescente

//Heap(Gestao de prioridade)
void adicionarReservaHeap(); //inserir uma reserva na heap de prioridades
void atualizarPrioridadeHeap();//Altera prioridade de uma reserva existente
void listarReservaHeap();//exibir todas as reservas em ordem de prioridade
//MaxHeap* criarMaxHeap(int capacidade);

//Hash(Gestao de estados)
void bloquearSalaHash();//alterar o estado de uma sala para bloqueada
void desbloquearSalaHash();//alterar o estado de uma sala para disponivel
void consultarEstadoHash();//Listar todas as salas por estado atual

/// Estruturas gerais
void cancelarReserva();
void encerrarSistema(); //Remover todas as informaçoes das salas e reservas antes de finalizar o sistema


int main() {
    printf("Ola, Mundo!\n");
    return 0;
}

No* criarNo(int codigoSala, int capacidade) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
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

void encerrarSistema(No* raizAVL, MaxHeap* heap, HashTabela* tabelaHash) {
    printf("Encerrando o sistema e liberando recursos...\n");
    // Libera a árvore AVL
    //liberarAVL(raizAVL);
    // Libera a heap de prioridades
    //liberarHeap(heap);
    // Libera a tabela hash
    //liberarHash(tabelaHash);
    printf("Todos os recursos foram liberados. Encerrando o sistema.\n");
}