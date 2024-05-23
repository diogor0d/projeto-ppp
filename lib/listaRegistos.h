#include <stdlib.h>

#include "../lib/structs.h"

#ifndef PROJETO_LISTAREGISTOS_H
#define PROJETO_LISTAREGISTOS_H

typedef struct l_node_registo
{
    Registo registo;
    struct l_node_registo *next;
    struct l_node_registo *nextTensaoMax;
} l_node_registo_t;

typedef struct lista_registos
{
    size_t n_elem;
    l_node_registo_t *front;
    l_node_registo_t *frontTensaoMax;
} lista_registos_t;

void initListaRegistos(lista_registos_t *list);
void clearListaRegistos(lista_registos_t *list);
int emptyListaRegistos(lista_registos_t *list);
void procurarNodeRegisto(lista_registos_t *list, Data data, int tensao, l_node_registo_t **prev, l_node_registo_t **cur, l_node_registo_t **prevTensao, l_node_registo_t **curTensao);
void procurarNodeRegistoID(lista_registos_t *list, unsigned int id, l_node_registo_t **prev, l_node_registo_t **cur);
void inserirNodeRegisto(lista_registos_t *list, Registo registo);
void removerNodeRegisto(lista_registos_t *list, unsigned int id);

void apresentarListaRegistos(lista_registos_t *list);

unsigned int novoIDRegisto(lista_registos_t *list);

#endif
