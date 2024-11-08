/*  PROJETO DE PPP

    Diogo Rodrigues
    Maria Ferraz

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/structs.h"
#include "../lib/listaDoentes.h"
#include "../lib/doentes.h"
#include "../lib/listaRegistos.h"
#include "../lib/misc.h"
#include "../lib/registos.h"

#define BUFFER_SIZE 256

/*
 * valgrind --leak-check=full --track-origins= yes./main
 * */

int main()
{
    // Criação das listas para posterior carregamento dos dados dos pacientes
    lista_doentes_t listaDoentes;
    initListaDoentes(&listaDoentes); // Inicializar a lista de doentes (front = NULL, n_elem = 0

    carregarDoentes(&listaDoentes, BUFFER_SIZE);
    carregarRegistos(&listaDoentes, BUFFER_SIZE);

    while (1)
    {

        // Apresentar o menu de opcoes
        printAsciiArt();
        printMenu();

        // Buffer para armazenar as entradas do utilizador
        char bufferInput[BUFFER_SIZE]; // Buffer para armazenar as entradas do utilizador

        printCiano();
        printf("    > Selecione a operacao a executar (1-7): ");
        printBranco();
        int opcao = receberInteiro(bufferInput, BUFFER_SIZE); // Variavel que guarda a opcao escolhida pelo utilizador, após interpretacao do input

        // ! DEBUG:
        // printf("Opcao selecionada: %d\n\n", opcao);

        switch (opcao)
        {
        case 1: // Inserir um novo doente
        {
            unsigned int id = novoID(&listaDoentes); // Determinar um novo ID para o doente a ser inserido

            Doente novoDoente;                                            // Estrutura que guarda os dados do novo doente
            receberNovoDoente(id, &novoDoente, bufferInput, BUFFER_SIZE); // Funcao que pergunta ao utilizar os dados do novo doente e os guarda devidamente na estrutura de modo a ser posteriormente inserido na lista

            printAmarelo();
            printf("\n[!] Doente a ser registado...\n\n");
            printAzul();
            apresentarDoente(&novoDoente);
            printBranco();

            if (!confirmarAcao()) // Confirmar a ação de adicionar o novo registo
                continue;

            inserirNodeDoente(&listaDoentes, novoDoente); // Inserir o novo doente na lista

            printVerde();
            printf("\n[!] Doente guardado.\n\n");
            printBranco();

            appendFicheiroDoentes(&novoDoente); // Atualizar o ficheiro com os dados do doente

            break;
        }
        case 2: // Eliminar um doente existente
        {
            unsigned int idSelecionado = pesquisarDoenteAtravesInfo(&listaDoentes, bufferInput, BUFFER_SIZE); // Encontrar o doente a ser eliminado
            if (idSelecionado != 0)
            {
                removerNodeDoente(&listaDoentes, idSelecionado); // Remover o doente da lista
                atualizarFicheiroDoentes(&listaDoentes);         // Atualizar o ficheiro com os dados dos doentes
                atualizarFicheiroRegistos(&listaDoentes);        // Atualizar o ficheiro com os dados dos registos
            }

            break;
        }
        case 3: // Listar todos os doentes por ordem alfabetica
            apresentarDoentes(&listaDoentes);
            break;
        case 4: // Listar todos os doentes com tensoes maximas acima de um determinado valor (por ordem decrescente das mesmas)
        {
            printCiano();
            printf("    > Insira o valor do limite inferior das tensões máximas: ");
            printBranco();
            listarDoentesTensaoAcimaLimite(&listaDoentes, receberInteiro(bufferInput, BUFFER_SIZE)); // Listar os doentes com tensão máxima acima de 140 (por ordem decrescente das mesmas
            break;
        }
        case 5: // Apresentar toda a informacao de um determinado doente
        {
            apresentarInfoDoenteID(&listaDoentes, pesquisarDoenteAtravesInfo(&listaDoentes, bufferInput, BUFFER_SIZE)); // Encontrar o doente a ser apresentado
            break;
        }
        case 6: // Registar as tensoes, o peso e altura de um determinado doente num determinado dia
        {
            unsigned int idSelecionado = pesquisarDoenteAtravesInfo(&listaDoentes, bufferInput, BUFFER_SIZE); // Encontrar o doente a quem se pretende adicionar um novo registo

            Registo novoRegisto;                                                                            // Estrutura que guarda os dados do novo registo
            receberNovoRegisto(pesquisarDoenteID(&listaDoentes, idSelecionado), &novoRegisto, BUFFER_SIZE); // Receber os dados do novo registo e adicioná-los à lista de registos do doente

            if (!confirmarAcao()) // Confirmar a ação de adicionar o novo registo
                continue;

            inserirNodeRegisto(pesquisarDoenteID(&listaDoentes, idSelecionado)->doente.listaRegistos, novoRegisto); // Inserir o novo registo na lista de registos do doente

            appendFicheiroRegistos(idSelecionado, &novoRegisto); // Atualizar o ficheiro com os dados dos registos
            break;
        }
        case 7: // Sair do programa
        {
            printVermelho();
            printf("\n    [!] A sair do programa...\n\n");
            printBranco();
            clearListaDoentes(&listaDoentes); // Libertar da memória a lista de doentes
            exit(0);
        }
        }
    }
}
