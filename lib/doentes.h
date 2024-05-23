#ifndef PROJETO_DOENTES_H
#define PROJETO_DOENTES_H

#include "../lib/structs.h"

void carregarDoentes(lista_doentes_t *listaDoentes, int BUFFER_SIZE);
void receberNovoDoente(unsigned int id, Doente *novoDoente, char *bufferInput, int BUFFER_SIZE);
void atualizarFicheiroDoentes(lista_doentes_t *listaDoentes);
void appendFicheiroDoentes(Doente *doente);

l_node_doente_t *pesquisarDoenteID(lista_doentes_t *list, unsigned int id);
int pesquisarDoenteNome(lista_doentes_t *listaDoentes, char *nome);
unsigned int pesquisarDoenteAtravesInfo(lista_doentes_t *listaDoentes, char *bufferInput, int BUFFER_SIZE);

void apresentarInfoDoenteID(lista_doentes_t *listaDoentes, unsigned int id);
void apresentarDoente(Doente *doente);
void apresentarDoentes(lista_doentes_t *listaDoentes);

int tensaoMaximaDoente(Doente *doente);

#endif
