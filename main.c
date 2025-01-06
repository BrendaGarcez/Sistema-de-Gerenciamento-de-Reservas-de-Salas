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

// Inclusão de bibliotecas para AVL, Heap e Hash
#include "avl.h"
#include "heap.h"
#include "hash.h"

void menu(FILE *entrada, FILE *saida, No *avl  /*,Sala *heap, HashTabela *hash*/);
void encerrarSistema(No* raizAVL, MaxHeap* heap, HashTabela* tabelaHash);

//Funcoes por arvore
//(é utilizada para organizar e armazenar as informações das salas de forma balanceada, busca inserção e remoção eficiente)
//AVL(Gestão de sala)
//add novas salas
//void removerSalaAVL();//exclui salas existentes
//void buscarSalaAVL();//busca pelo código da sala
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

    FILE *entrada, *saida;

    entrada = fopen("entrada1.txt", "r");
    if (!entrada) {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 1;
    }
    saida = fopen("saida.txt", "w");
    if (!saida) {
        printf("Erro ao abrir arquivo de saída.\n");
        fclose(entrada);
        return 1;
    }

     // Inicialização das estruturas de dados
    No *avl = NULL;
    Sala *heap = NULL;
    HashTabela *hash = NULL;

    // Processar operações
    menu(entrada, saida, avl/*, heap, hash*/ );

    // Encerrar e liberar memória
    liberarAVL(avl);
    //liberarHeap(heap);
    //liberarHashTable(hash);

    fclose(entrada);
    fclose(saida);
    printf("Operações concluídas com sucesso.\n");
    getchar(); 
    return 0;
}

void menu(FILE *entrada, FILE *saida, No *avl/*, Sala *heap,HashTabela *hash*/ ) {

    char comando[30];
    int codigo, capacidade, prioridade;
    
    ///Leitura de arquivo de entrada até a ultima linha
    while (!feof(entrada)) {
        fscanf(entrada, "%s", comando);
        if (strcmp(comando, "CRIAR_SALA") == 0) {
            fscanf(entrada, "%*s %d %d", &codigo, &capacidade);
            if (inserirSalaAVL(avl, codigo, capacidade)) {
                printf("Sala %d criada com sucesso.\n", codigo);
                fprintf(saida, "Sala %d criada com sucesso.\n", codigo);
                //inserirEstadoHash(hash, codigo, "disponivel");
            } else {
                printf("Erro ao criar sala %d.\n", codigo);
                fprintf(saida, "Erro ao criar sala %d.\n", codigo);
            }
        }
        else if (strcmp(comando, "RESERVAR_SALA") == 0) {
            fscanf(entrada, "%*s %d %d", &codigo, &prioridade);
            /*if (adicionarReservaHeap(heap, codigo, prioridade)) {
                printf("Reserva da sala %d adicionada com prioridade %d.\n", codigo, prioridade);
                fprintf(saida, "Reserva da sala %d adicionada com prioridade %d.\n", codigo, prioridade);
            } else {
                printf("Erro ao reservar sala %d.\n", codigo);
                fprintf(saida, "Erro ao reservar sala %d.\n", codigo);
            }*/
        }
        else if (strcmp(comando, "BLOQUEAR_SALA") == 0) {
            fscanf(entrada, "%*s %d", &codigo);
            /*if (alterarEstadoHash(hash, codigo, "bloqueada")) {
                printf("Sala %d bloqueada.\n", codigo);
                fprintf(saida, "Sala %d bloqueada.\n", codigo);
            } else {
                printf("Erro ao bloquear sala %d.\n", codigo);
                fprintf(saida, "Erro ao bloquear sala %d.\n", codigo);
            }*/
        }
        else if (strcmp(comando, "DESBLOQUEAR_SALA") == 0) {
            fscanf(entrada, "%*s %d", &codigo);
            /*if (alterarEstadoHash(hash, codigo, "disponivel")) {
                printf("Sala %d desbloqueada.\n", codigo);
                fprintf(saida, "Sala %d desbloqueada.\n", codigo);
            } else {
                printf("Erro ao desbloquear sala %d.\n", codigo);
                fprintf(saida, "Erro ao desbloquear sala %d.\n", codigo);
            }*/
        }
        else if (strcmp(comando, "CANCELAR_RESERVA") == 0) {
            fscanf(entrada, "%*s %d", &codigo);
            /*if (removerReservaHeap(heap, codigo)) {
                printf("Reserva da sala %d cancelada.\n", codigo);
                fprintf(saida, "Reserva da sala %d cancelada.\n", codigo);
            } else {
                printf("Erro ao cancelar reserva da sala %d.\n", codigo);
                fprintf(saida, "Erro ao cancelar reserva da sala %d.\n", codigo);
            }*/
        }
        else if (strcmp(comando, "CONSULTAR_SALA") == 0) {
            fscanf(entrada, "%*s %d", &codigo);
            //consultarSalaAVL(saida, avl, codigo);
        }
        else if (strcmp(comando, "LISTAR_SALAS") == 0) {
            //listarSalasAVL(saida, avl);
        }
        else {
            printf("Comando desconhecido: %s\n", comando);
            fprintf(saida, "Comando desconhecido: %s\n", comando);
        }
    }
}

void encerrarSistema(No* raizAVL, MaxHeap* heap, HashTabela* tabelaHash) {
    printf("Encerrando o sistema e liberando recursos...\n");
    // Libera a árvore AVL
    liberarAVL(raizAVL);
    // Libera a heap de prioridades
    liberarHeap(heap);
    // Libera a tabela hash
    liberarHash(tabelaHash);
    printf("Todos os recursos foram liberados. Encerrando o sistema.\n");
}