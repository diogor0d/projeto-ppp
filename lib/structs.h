#ifndef PROJETO_STRUCTS_H
#define PROJETO_STRUCTS_H

typedef struct dataStruct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct registoStruct
{
    unsigned int registoId;
    Data data;
    int tensaoMax;
    int tensaoMin;
    int peso;
    int altura;
} Registo;

#include "../lib/listaRegistos.h"

typedef struct doenteStruct
{
    unsigned int id;
    char nome[256];
    Data nascimento;
    char cc[16];      // 12345678-1-ZX1 \0
    unsigned int tel; // 927 578 755 \0
    char email[256];
    lista_registos_t *listaRegistos;
} Doente;

#endif // PROJETO_STRUCTS_H
