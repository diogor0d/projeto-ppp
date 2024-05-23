#ifndef PROJETO_MISC_H
#define PROJETO_MISC_H

#include "../lib/structs.h"

void recebeInputLimpaStream(char *bufferOpcao, int BUFFER_SIZE);
int confirmarAcao();
char *toUpperString(char *str);

int anoBissexto(int ano);
int anoValido(int dia, int mes, int ano);
int comparaDatas(Data data1, Data data2);

int verificarCC(char *cc);
int verificarTel(char *tel);
int verificarEmail(char *email);

Data receberData(char *bufferInput, int BUFFER_SIZE);
int receberInteiro(char *bufferInput, int BUFFER_SIZE);
char *receberNome(char *bufferInput, int BUFFER_SIZE);
char *receberCC(char *bufferInput, int BUFFER_SIZE);
unsigned int receberTel(char *bufferInput, int BUFFER_SIZE);
char *receberEmail(char *bufferInput, int BUFFER_SIZE);

void printMsgErroData();
void printMsgErroCC();
void printMsgErroTel();
void printMsgErroEmail();
void printAsciiArt();
void printMenu();

void printVermelho();
void printVerde();
void printAmarelo();
void printAzul();
void printRoxo();
void printCiano();
void printBranco();

#endif