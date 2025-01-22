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


int main() {
    ////Abertura de arquivos, para entrada de dados, e saidas de logs de erro e sucesso
    FILE *entrada= fopen("entrada2.txt", "r"), *saida = fopen("saida.txt", "w");
    if (!entrada) {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 1;
    }
    if (!saida) {
        perror("Erro ao abrir arquivo de saída");
        return 1;
    }

    //Declaração das estruturas que levarão as informações das salas
    No* avl = NULL;
    MaxHeap* heap = criarMaxHeap(2, saida);
    HashTabela* hash = criarTabelaHash(saida);
    int op1, codSala, result, cod, capac, prioridade;
    char opcao[20];
    char CS[]= "CRIAR_SALA";
    char RS[]= "RESERVAR_SALA";
    char BS[]= "BLOQUEAR_SALA";
    char DS[]= "DESBLOQUEAR_SALA";
    char CR[]= "CANCELAR_RESERVA";
    char CONS[]= "CONSULTAR_SALA";
    char LS[]= "LISTAR_SALAS";
    char LR[]= "LISTAR_RESERVAS";
    char AP[]= "ATUALIZAR_PRIORIDADE";
    char RemoveS[]= "REMOVER_SALA";


    printf("SISTEMA DE GERENCIAMENTO DE SALAS\n");
    fprintf(saida,"Arquivo de saida de logs do sistema de Gerenciamento\n");
    while(fscanf(entrada, "%s", opcao)!= EOF)////Linha que diz para o programa ler o arquivo de entrada até o final
    {
        if((result = strcmp(opcao, CS)) == 0){
            fprintf(saida,"[COMANDO: Criar Sala AVL]\n");
            fscanf(entrada, "%d %d", &codSala, &capac);
            printf("\nCriando sala %d com capacidade %d.\n", codSala, capac);
            avl = inserirNoAVL(avl, codSala, capac, saida);
            hash = inserirNaHash(hash, codSala, saida);

            fprintf(saida,"\n\nEstrutura AVL\n");
            printf("\n\nEstrutura AVL\n");
            listarSalaAVL(avl,saida);
            fprintf(saida,"\nEstrutura Hash\n");
            printf("\nEstrutura Hash\n");
            printTabela(hash,saida);
        }else if((result = strcmp(opcao, LR)) == 0){
            printf("\nListando todas as reservas.(HEAP)\n");
            listarReservaHeap(heap, saida);
        }else if((result = strcmp(opcao, RS)) == 0){
            fscanf(entrada, "%d %d", &codSala, &prioridade);
            printf("\n\nReservando sala %d com prioridade %d.\n", codSala, prioridade);
            No *resultado = buscarSalaAVL(avl, codSala, saida);
            if (resultado == NULL) {
                printf("Erro na Busca(AVL)\n");
                fprintf(saida, "Erro na Busca(AVL)\n");
            }else{
                inserirReservaHeap(heap, codSala, prioridade, saida);
            }

            fprintf(saida,"\n\nEstrutura Heap");
            printf("\n\nEstrutura Heap");
            listarReservaHeap(heap, saida);
        }else if((result = strcmp(opcao, AP)) == 0){
            fscanf(entrada, "%d %d", &codSala, &prioridade);
            printf("\nAtualizando prioridade da sala %d com valor = %d.\n", codSala, prioridade);
            fprintf(saida,"Atualizando prioridade da sala %d com valor = %d.\n", codSala, prioridade);
            Reserva *resultado = buscarReservaHeap(heap, codSala);
            if (resultado == NULL) {
                printf("Erro na Busca(Heap)\n");
                fprintf(saida, "Erro na Busca(Heap)\n");
            }else{
                atualizarPrioridadeHeap(heap, codSala, prioridade,saida);
            }

            fprintf(saida,"\n\nEstrutura HEAP\n");
            printf("\n\nEstrutura HEAP\n");
            listarReservaHeap(heap,saida);
        }else if((result = strcmp(opcao, CR)) == 0){
            fscanf(entrada, "%d", &codSala);
            printf("\nCancelando reservas da sala %d.\n", codSala);
            cancelarReservaHeap(heap, codSala, saida);

            fprintf(saida,"\n\nEstrutura HEAP\n");
            printf("\n\nEstrutura HEAP\n");
            listarReservaHeap(heap,saida);
        }else if((result = strcmp(opcao, BS)) == 0){
            fscanf(entrada, "%d", &codSala);
            printf("\n\nBloqueando sala %d.\n", codSala);
            hash = mudarEstado(hash, avl, codSala, saida);

            fprintf(saida,"\n\nEstrutura HASH\n");
            printf("\n\nEstrutura HASH\n");
            printTabela(hash,saida);
        }else if((result = strcmp(opcao, DS)) == 0){
            fscanf(entrada, "%d", &codSala);
            printf("\nDesbloqueando sala %d.\n", codSala);
            hash = mudarEstado(hash, avl, codSala, saida);

            fprintf(saida,"\n\nEstrutura HASH\n");
            printf("\n\nEstrutura HASH\n");
            printTabela(hash,saida);
        }else if((result = strcmp(opcao, CONS)) == 0){
            fscanf(entrada, "%d", &codSala);
            printf("\nConsultando sala %d.\n", codSala);
            buscarSalaHash(hash, avl, codSala, saida);

            fprintf(saida,"\n\nEstrutura HASH\n");
            printf("\n\nEstrutura HASH\n");
            printTabela(hash,saida);
        }else if((result = strcmp(opcao, LS)) == 0){
            printf("\n\nListando todas as salas.\n");
            printf("Estrutura AVL\n");
            fprintf(saida,"\nEstrutura AVL\n");
            listarSalaAVL(avl, saida);

        }else if((result = strcmp(opcao, RemoveS)) == 0){
            fscanf(entrada, "%d", &codSala);
            printf("\nRemovendo sala %d.\n", codSala);
            avl = removerNoAVL(avl, cod, saida);
            cancelarReservaHeap(heap,cod,saida);
            liberarSalaHash(hash, cod);

            printf("\n\nEstrutura AVL\n");
            fprintf(saida,"\nEstrutura AVL\n");
            listarSalaAVL(avl,saida);
        }else{
            printf("Comando desconhecido: %s \n", opcao);
            fprintf(saida,"Comando desconhecido: %s \n", opcao);
        }
    }

    ////Menu de opções de entrada para usuário
    fprintf(saida,"\nEntradas de Usuario\n");
    while(op1 != 12){
        printf("\n\n--- Menu de Operacoes ---\n");
        //Manipulando a Avl
        printf("0. Criar Sala\n");
        printf("1. Buscar Sala\n");
        printf("2. Listar Salas \n");
        //Manipulando a Heap
        printf("3. Reservar Sala\n");
        printf("4. Listar Reservas \n");
        printf("5. Atualizar Prioridade \n");
        printf("6. Cancelar Reservas \n");
        //Manipulando a Hash
        printf("7. Consultar Estado\n");
        printf("8. Consultar o estado de todas as Salas \n");
        printf("9. Bloquear Sala \n");
        printf("10. Desbloquear Sala \n");
        //Remove de todas as estruturas
        printf("11. Remover Sala \n");
        //Encerra todas as estruturas e libera o arquivo de saida
        printf("12. Sair(Liberar arquivo de saida.txt)\n");
        printf("-------------------------\n");

        scanf("%d", &op1);
        switch(op1){
            case 0:
                fprintf(saida,"[Criar sala AVL]\n");
                printf("Criar sala:\n");
                printf("Qual o codigo da sala?\n");
                scanf("%d", &cod);
                printf("Qual a capacidade da sala?\n");
                scanf("%d", &capac);

                avl = inserirNoAVL(avl, cod, capac, saida);
                hash = inserirNaHash(hash, cod, saida);

                fprintf(saida,"\n\nEstrutura AVL\n");
                printf("\n\nEstrutura AVL\n");
                listarSalaAVL(avl,saida);

                fprintf(saida,"\nEstrutura Hash\n");
                printf("\nEstrutura Hash\n");
                printTabela(hash,saida);
                break;
            case 1:
                fprintf(saida,"[Buscar salas AVL]\n");
                printf("Qual o codigo da sala que deseja [BUSCAR]?\n");
                scanf("%d", &cod);
                No* resultado = buscarSalaAVL(avl, cod, saida);
                if (resultado == NULL) {
                    printf("Erro na Busca(AVL)\n");
                    fprintf(saida, "Erro na Busca(AVL)\n");
                }else{
                    fprintf(saida,"Busca do usuario pelo codigo %d\n", cod);
                }
                fprintf(saida,"\n\nEstrutura AVL\n");
                printf("\n\nEstrutura AVL\n");
                listarSalaAVL(avl,saida);
                break;
            case 2:
                fprintf(saida,"[Listar salas AVL]\n");
                printf("Listar salas(AVL):\n");
                listarSalaAVL(avl,saida);
                if(avl == NULL){
                    printf("\nLista Vazia!\n");
                }
                break;
            case 3:
                fprintf(saida, "[Reservar sala HEAP]\n");
                printf("Reservar sala:\n");
                printf("Qual o codigo da sala?\n");
                scanf("%d", &cod);
                printf("Qual a prioridade da sala\n");
                scanf("%d", &prioridade);
                resultado = buscarSalaAVL(avl, cod, saida);
                if (resultado == NULL) {
                    printf("Erro na Busca(AVL)\n");
                    fprintf(saida, "Erro na Busca(AVL)\n");
                }else{
                    inserirReservaHeap(heap, cod, prioridade,saida);
                }

                fprintf(saida,"\n\nEstrutura HEAP\n");
                printf("\n\nEstrutura HEAP\n");
                listarReservaHeap(heap,saida);

                break;
            case 4:
                fprintf(saida,"[Listando HEAP]\n");
                printf("Listando todas as reservas (HEAP).\n");
                listarReservaHeap(heap, saida);
                break;
            case 5:
                fprintf(saida,"[Atualizando prioridade HEAP]");
                printf("Digite o codigo da sala e nova prioridade: ");
                scanf("%d %d", &cod, &prioridade);
                printf("Atualizando prioridade da sala %d para %d.\n", cod, prioridade);
                atualizarPrioridadeHeap(heap, cod, prioridade,saida);

                ////Estrutura apos a mudança atual
                fprintf(saida,"\n\nEstrutura HEAP\n");
                printf("\n\nEstrutura HEAP\n");
                listarReservaHeap(heap,saida);
                break;
            case 6:
                printf("Cancelar reserva:\n");
                printf("Qual o codigo da sala?\n");
                scanf("%d", &cod);
                cancelarReservaHeap(heap,cod,saida);

                fprintf(saida,"\n\nEstrutura HEAP\n");
                printf("\n\nEstrutura HEAP\n");
                listarReservaHeap(heap,saida);
                break;
            case 7:
                printf("Consultar estado da sala:\n");
                scanf("%d", &cod);
                buscarSalaHash(hash, avl, cod, saida);
                fprintf(saida,"\n\nEstrutura HASH\n");
                printf("\n\nEstrutura HASH\n");
                printTabela(hash,saida);
                break;
            case 8:
                printf("Consultando estado das salas:\n");
                printTabela(hash, saida);
                break;
            case 9:
                printf("Bloquear sala:\n");
                printf("Qual o codigo da sala?\n");
                scanf("%d", &cod);
                hash = mudarEstado(hash, avl, cod, saida);

                fprintf(saida,"\n\nEstrutura HASH\n");
                printf("\n\nEstrutura HASH\n");
                printTabela(hash,saida);
                break;
            case 10:
                printf("Desbloquear sala:\n");
                printf("Qual o codigo da sala?\n");
                scanf("%d", &cod);
                hash = mudarEstado(hash, avl, cod, saida);

                fprintf(saida,"\n\nEstrutura HASH\n");
                printf("\n\nEstrutura HASH\n");
                printTabela(hash,saida);
                break;
            case 11:
                ////Removendo sala do sistema
                printf("Digite o codigo da sala para remover: ");
                scanf("%d", &cod);
                avl = removerNoAVL(avl, cod, saida);
                cancelarReservaHeap(heap,cod,saida);
                liberarSalaHash(hash, cod);


                fprintf(saida,"\n\nEstrutura AVL\n");
                printf("\n\nEstrutura AVL\n");
                listarSalaAVL(avl,saida);
                fprintf(saida,"\nEstrutura HASH\n");
                printf("\nEstrutura HASH\n");
                printTabela(hash,saida);
                fprintf(saida,"\nEstrutura HEAP\n");
                printf("\nEstrutura HEAP\n");
                listarReservaHeap(heap,saida);
                break;
            case 12:
                printf("Encerrando programa.\n");
                fprintf(saida,"12 - Encerrar Sistema\n");
                break;
            default:
                printf("Opcao nao existente, tente outra\n");
        }
    }

    //Encerrando o sistema
    liberarAVL(&avl, saida);
    destruirHeap(&heap, saida);
    liberarHash(hash, saida);
    hash = NULL;

    printf("Todos os recursos foram liberados.\n");
    fprintf(saida, "Todos os recursos foram liberados. Encerrando o sistema.\n");

    //encerrarSistema(avl, heap, hash, saida);
    fclose(entrada);
    fclose(saida);
    return 0;
}
