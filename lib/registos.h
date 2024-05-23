#ifndef PROJETO_REGISTOS_H
#define PROJETO_REGISTOS_H

#include "../lib/structs.h"
#include "../lib/listaDoentes.h"

#include <stdio.h>

void carregarRegistos(lista_doentes_t *listaDoentes, int BUFFER_SIZE);
void listarDoentesTensaoAcimaLimite(lista_doentes_t *list, int limite);
void receberNovoRegisto(l_node_doente_t *doente, Registo *novoRegisto, int BUFFER_SIZE);
void appendFicheiroRegistos(unsigned int id, Registo *registo);
void atualizarFicheiroRegistos(lista_doentes_t *listaDoentes);
void apresentarRegisto(Registo *registo);

#endif
