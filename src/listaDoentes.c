#include <stdio.h>
#include <string.h>

#include "../lib/listaDoentes.h"
#include "../lib/structs.h"
#include "../lib/misc.h"
#include "../lib/doentes.h"

void initListaDoentes(lista_doentes_t *list) // Inicializa a lista
{
    list->n_elem = 0;
    list->front = NULL;
}

void clearListaDoentes(lista_doentes_t *list) // Limpa a lista, liberta a memória alocada para os nós
{
    l_node_doente_t *node;

    while (list->front != NULL)
    {
        node = list->front;
        clearListaRegistos(node->doente.listaRegistos);
        free(node->doente.listaRegistos);
        list->front = list->front->next;
        free(node);
    }

    initListaDoentes(list);
}

void procurarNodeDoente(lista_doentes_t *list, char *nome, l_node_doente_t **prev, l_node_doente_t **cur) // Itera pelos doentes da listas para encontrar a posição onde inserir um novo doente com o nome fornecido
{

    *prev = NULL;
    *cur = list->front;
    while (*cur != NULL && strcmp((*cur)->doente.nome, nome) != 0)
    {
        *prev = *cur;
        *cur = (*cur)->next;
    }
}

void procurarNodeDoenteID(lista_doentes_t *list, unsigned int id, l_node_doente_t **prev, l_node_doente_t **cur) // Itera pelos doentes da listas para encontrar a posição onde inserir um novo doente com o nome fornecido
{

    *prev = NULL;
    *cur = list->front;
    while (*cur != NULL && (*cur)->doente.id != id)
    {
        *prev = *cur;
        *cur = (*cur)->next;
    }
}

void inserirNodeDoente(lista_doentes_t *list, Doente doente) // Insere um novo nó na lista, com informações de um novo doente
{
    l_node_doente_t *node = (l_node_doente_t *)malloc(sizeof(l_node_doente_t));
    if (node == NULL)
    {
        printVermelho();
        printf("\n    [!] Não foi possivel alocar memoria para um novo node.\n\n");
        printBranco();
        exit(1);
    }

    l_node_doente_t *prev, *cur;

    if (node != NULL)
    {

        node->doente.id = doente.id;
        strcpy(node->doente.nome, doente.nome);
        node->doente.nascimento = doente.nascimento;
        strcpy(node->doente.cc, doente.cc);
        node->doente.tel = doente.tel;
        strcpy(node->doente.email, doente.email);
        node->doente.listaRegistos = doente.listaRegistos;

        procurarNodeDoente(list, doente.nome, &prev, &cur);
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
        list->n_elem++;
    }
}

void removerNodeDoente(lista_doentes_t *list, unsigned int id) // Remove um nó da lista, através do ID do doente
{
    l_node_doente_t *prev, *cur;

    procurarNodeDoenteID(list, id, &prev, &cur);

    if (cur != NULL && cur->doente.id == id)
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

unsigned int novoID(lista_doentes_t *list) // Retorna um novo ID para a criação de um novo doente
{
    unsigned int max = 0;

    l_node_doente_t *node = list->front;

    while (node != NULL)
    {
        if (node->doente.id > max)
        {
            max = node->doente.id;
        }
        node = node->next;
    }

    return max + 1;
}
