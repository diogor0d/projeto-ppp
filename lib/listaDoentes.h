#include <stdlib.h>

#include "../lib/structs.h"

#ifndef PROJETO_LISTADOENTES_H
#define PROJETO_LISTADOENTES_H

typedef struct l_node_doente
{
    Doente doente;
    struct l_node_doente *next;
} l_node_doente_t;

typedef struct lista_doentes
{
    size_t n_elem;
    l_node_doente_t *front;
} lista_doentes_t;

void initListaDoentes(lista_doentes_t *list);
void clearListaDoentes(lista_doentes_t *list);
void procurarNodeDoente(lista_doentes_t *list, char *nome, l_node_doente_t **prev, l_node_doente_t **cur);
void procurarNodeDoenteID(lista_doentes_t *list, unsigned int id, l_node_doente_t **prev, l_node_doente_t **cur);
void inserirNodeDoente(lista_doentes_t *list, Doente doente);
void removerNodeDoente(lista_doentes_t *list, unsigned int id);

unsigned int novoID(lista_doentes_t *list);

#endif
