/*  Projeto desenvolvido por: 
        Brenda Amanda da Silva Garcez
        Nicole Louise Matias Jamuchewski

    1. Árvore AVL para gerenciar informações das salas.
    2. Heap para gerenciar prioridades de reservas.
    3. Tabela Hash para armazenar estados das salas.
*/
#include <stdio.h>
#include <stdlib.h>

//Funcoes por arvore
//(é utilizada para organizar e armazenar as informações das salas de forma balanceada, busca inserção e remoção eficiente)
//AVL(Gestão de sala)
void inserirSalaAVL();//add novas salas
void removerSalaAVL();//exclui salas existentes
void buscarSalaAVL();//busca pelo código da sala
void listarSalaAVL();//exibe salas em ordem crescente

//Heap(Gestao de prioridade)
void adicionarReservaHeap(); //inserir uma reserva na heap de prioridades
void atualizarPrioridadeHeap();//Altera prioridade de uma reserva existente
void listarReservaHeap();//exibir todas as reservas em ordem de prioridade

//Hash(Gestao de estados)
void bloquearSalaHash();//alterar o estado de uma sala para bloqueada
void desbloquearSalaHash();//alterar o estado de uma sala para disponivel
void consultarEstadoHash();//Listar todas as salas por estado atual


/// Estruturas gerais
void cancelarReserva();
void encerrarSistema(); //Remover todas as informaçoes das salas e reservas antes de finalizar o sistema
int main() {
    printf("Olá, Mundo!\n");
    return 0;
}
