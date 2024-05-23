#include <stdio.h>
#include <string.h>

#include "../lib/listaRegistos.h"
#include "../lib/misc.h"
#include "../lib/structs.h"
#include "../lib/registos.h"

void initListaRegistos(lista_registos_t *list) // Inicializa a lista
{
    list->n_elem = 0;
    list->front = NULL;
    list->frontTensaoMax = NULL;
}

void clearListaRegistos(lista_registos_t *list) // Limpa a lista, liberta a memória alocada para os nós
{
    l_node_registo_t *node;
    while (list->front != NULL)
    {
        node = list->front;
        list->front = list->front->next;
        free(node);
    }

    initListaRegistos(list);
}

int emptyListaRegistos(lista_registos_t *list) // Permite avaliar se a lista se encontra vazia
{
    return list->front == NULL;
}

void procurarNodeRegisto(lista_registos_t *list, Data data, int tensao, l_node_registo_t **prev, l_node_registo_t **cur, l_node_registo_t **prevTensao, l_node_registo_t **curTensao) // Procura a posição onde inserir um registo (conforme a data)
{

    *prev = NULL;
    *cur = list->front;
    while (*cur != NULL && comparaDatas((*cur)->registo.data, data) != 1)
    {
        *prev = *cur;
        *cur = (*cur)->next;
    }

    *prevTensao = NULL;
    *curTensao = list->frontTensaoMax;
    while (*curTensao != NULL && (*curTensao)->registo.tensaoMax > tensao)
    {
        *prevTensao = *curTensao;
        *curTensao = (*curTensao)->nextTensaoMax;
    }
}

void procurarNodeRegistoID(lista_registos_t *list, unsigned int id, l_node_registo_t **prev, l_node_registo_t **cur) // Devolve a posição de um registo na lista, através do ID
{

    *prev = NULL;
    *cur = list->front;
    while (*cur != NULL && (*cur)->registo.registoId != id)
    {
        *prev = *cur;
        *cur = (*cur)->next;
    }
}

unsigned int novoIDRegisto(lista_registos_t *list) // Devolve um novo ID para um registo
{
    unsigned int max = 0;

    l_node_registo_t *node = list->front;

    while (node != NULL)
    {
        if (node->registo.registoId > max)
        {
            max = node->registo.registoId;
        }
        node = node->next;
    }

    return max + 1;
}

void inserirNodeRegisto(lista_registos_t *list, Registo registo) // Insere um novo nó na lista, com informações de um novo registo
{
    l_node_registo_t *node = (l_node_registo_t *)malloc(sizeof(l_node_registo_t));
    if (node == NULL)
    {
        printVermelho();
        printf("\n    [!] Não foi possivel alocar memoria para um novo node.\n\n");
        printBranco();
        exit(1);
    }

    l_node_registo_t *prev, *cur, *prevTensao, *curTensao;

    if (node != NULL)
    {

        node->registo.registoId = novoIDRegisto(list);
        node->registo.data = registo.data;
        node->registo.tensaoMax = registo.tensaoMax;
        node->registo.tensaoMin = registo.tensaoMin;
        node->registo.peso = registo.peso;
        node->registo.altura = registo.altura;

        procurarNodeRegisto(list, node->registo.data, node->registo.tensaoMax, &prev, &cur, &prevTensao, &curTensao);
        if (prev != NULL)
        {
            prev->next = node;
            node->next = cur;
        }
        else
        {
            list->front = node;
            node->next = cur;
        }

        if (prevTensao != NULL)
        {
            prevTensao->nextTensaoMax = node;
            node->nextTensaoMax = curTensao;
        }
        else
        {
            list->frontTensaoMax = node;
            node->nextTensaoMax = curTensao;
        }

        list->n_elem++;
    }
}

void removerNodeRegisto(lista_registos_t *list, unsigned int id) // Remove um nó da lista, através do ID do registo
{
    l_node_registo_t *prev, *cur;

    procurarNodeRegistoID(list, id, &prev, &cur);

    if (cur != NULL && cur->registo.registoId == id)
    {
        if (prev != NULL)
        {
            prev->next = cur->next;
        }
        else
        {
            list->front = cur->next;
        }
        free(cur);
        list->n_elem--;
    }
}

void apresentarListaRegistos(lista_registos_t *list) // Imprime os conteúdos da lista
{
    printAmarelo();
    printf("\n    ---------------------------------------------\n       Lista Registos do doente:\n");
    l_node_registo_t *node = list->front;
    while (node != NULL)
    {
        // apresentarRegisto(node->registo);
        printAmarelo();
        printf("    ---------------------------------------------\n");
        printAzul();
        printf("    > ID: %u\n", node->registo.registoId);
        printf("    > Data: %d/%d/%d\n", node->registo.data.dia, node->registo.data.mes, node->registo.data.ano);
        printf("    > TensaoMax: %d\n", node->registo.tensaoMax);
        printf("    > TensaoMin: %d\n", node->registo.tensaoMin);
        printf("    > Peso: %d\n", node->registo.peso);
        printf("    > Altura: %d\n", node->registo.altura);
        node = node->next;
    }
    printAmarelo();
    printf("    ---------------------------------------------\n");
}
