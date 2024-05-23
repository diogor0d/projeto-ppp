#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/structs.h"

// Cores no terminal
void printVermelho()
{
    printf("\033[1;31m");
}

void printVerde()
{
    printf("\033[1;32m");
}

void printAmarelo()
{
    printf("\033[1;33m");
}

void printAzul()
{
    printf("\033[1;34m");
}

void printRoxo()
{
    printf("\033[1;35m");
}

void printCiano()
{
    printf("\033[1;36m");
}

void printBranco()
{
    printf("\033[0m");
}
//-------------------

void printAsciiArt()
{
    printAzul();
    printf("\n"
           " _______   _______   _______          ______   __        ______  __    __  ______   ______  \n"
           "/       \\ /       \\ /       \\        /      \\ /  |      /      |/  \\  /  |/      | /      \\ \n"
           "$$$$$$$  |$$$$$$$  |$$$$$$$  |      /$$$$$$  |$$ |      $$$$$$/ $$  \\ $$ |$$$$$$/ /$$$$$$  |\n"
           "$$ |__$$ |$$ |__$$ |$$ |__$$ |      $$ |  $$/ $$ |        $$ |  $$$  \\$$ |  $$ |  $$ |  $$/ \n"
           "$$    $$/ $$    $$/ $$    $$/       $$ |      $$ |        $$ |  $$$$  $$ |  $$ |  $$ |      \n"
           "$$$$$$$/  $$$$$$$/  $$$$$$$/        $$ |   __ $$ |        $$ |  $$ $$ $$ |  $$ |  $$ |   __ \n"
           "$$ |      $$ |      $$ |            $$ \\__/  |$$ |_____  _$$ |_ $$ |$$$$ | _$$ |_ $$ \\__/  |\n"
           "$$ |      $$ |      $$ |            $$    $$/ $$       |/ $$   |$$ | $$$ |/ $$   |$$    $$/ \n"
           "$$/       $$/       $$/              $$$$$$/  $$$$$$$$/ $$$$$$/ $$/   $$/ $$$$$$/  $$$$$$/  \n"
           "                                                                                            \n");
    printCiano();
    printf("Bem vindo, Dr. Noe.\n");
    printBranco();
}

void printMenu()
{
    printAmarelo();
    printf("\nOperacoes disponiveis:\n1 -> Introduzir dados de um novo doente;\n2 -> Eliminar um doente existente;\n3 -> Listar todos os doentes por ordem alfabetica;\n4 -> Listar todos os doentes com tensoes maximas acima de um determinado valor (por ordem decrescente das mesmas);\n5 -> Apresentar toda a informacao de um determinado doente;\n6 -> Registar as tensoes, o peso e altura de um determinado doente num determinado dia;\n7 -> Sair.\n\n");
    printBranco();
}

void printMsgErroData()
{
    printVermelho();
    printf("\n[!] Data invalida! Verifique os dados que introduziu e tente novamente [DD-MM-AAAA]: ");
    printBranco();
}

void printMsgErroCC()
{
    printVermelho();
    printf("\n[!] Cartao de cidadao invalido! Verifique os dados que introduziu e tente novamente [12345678-1-XX1]: ");
    printBranco();
}

void printMsgErroTel()
{
    printVermelho();
    printf("\n[!] Numero de telefone invalido! Verifique os dados que introduziu e tente novamente [912345678]: ");
    printBranco();
}

void printMsgErroEmail()
{
    printVermelho();
    printf("\n[!] Endereço de email invalido! Verifique os dados que introduziu e tente novamente: ");
    printBranco();
}

int anoBissexto(int ano) // Determina se o ano fornecido cumpre as condições para ser bissexto
{
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))
    {
        return 1;
    }
    return 0;
}

int dataValida(Data data) // Esta funçao verifica se uma dada data fornecida existe, verificando se é possivel, dado o numero de dias, existir a correspondencia com o mês dado, tendo adicionalmente em conta se o ano é bissexto ou nao.
{
    switch (data.mes)
    {
    case 1:
        if (data.dia < 1 || data.dia > 31)
            return 0;
        break;
    case 2:
        if (((data.dia < 1 || data.dia > 28) && anoBissexto(data.ano) == 0) || ((data.dia < 1 || data.dia > 29) && anoBissexto(data.ano) == 1))
            return 0;
        break;
    case 3:
        if (data.dia < 1 || data.dia > 31)
            return 0;
        break;
    case 4:
        if (data.dia < 1 || data.dia > 30)
            return 0;
        break;
    case 5:
        if (data.dia < 1 || data.dia > 31)
            return 0;
        break;
    case 6:
        if (data.dia < 1 || data.dia > 30)
            return 0;
        break;
    case 7:
        if (data.dia < 1 || data.dia > 31)
            return 0;
        break;
    case 8:
        if (data.dia < 1 || data.dia > 31)
            return 0;
        break;
    case 9:
        if (data.dia < 1 || data.dia > 30)
            return 0;
        break;
    case 10:
        if (data.dia < 1 || data.dia > 31)
            return 0;
        break;
    case 11:
        if (data.dia < 1 || data.dia > 30)
            return 0;
        break;
    case 12:
        if (data.dia < 1 || data.dia > 31)
            return 0;
        break;
    default:
        return 0;
    }

    return 1;
}

int verificarCC(char *cc) // Devolve 1 se o cartao fornecido for valido, 0 se for invalido
{
    // Verificar se o tamanho da string é valido
    if (strlen(cc) != 14)
        return 0;

    // Verificar se existe o número certo de separadores '-' e que nao existem minusculas
    int c = 0;
    for (int i = 0; i < (int)strlen(cc); i++)
    {
        if (cc[i] == '-')
            c++;
        if (cc[i] >= 'a' && cc[i] <= 'z')
            return 0;
    }
    if (c != 2)
        return 0;

    // Valor da letra A (De acordo com o algoritmo de validação do Cartão de Cidadão Português). Este valor servirá como ponto de referencia para calcular os valores de outras letras, que seguem os números subsequentes.
    int valorA = 10; // valorB = ...

    // Aplicação do Algoritmo
    int j = 1; // Para duplicar cada segundo digito, da direita para a esquerda
    int soma = 0;

    for (int i = strlen(cc) - 1; i >= 0; i--)
    {
        if (cc[i] == '-') // Ignorar o separador
            continue;

        // Calcular o somatório dos valores de cada letra conforme o algoritmo
        int valor = 0;
        if (cc[i] >= 'A' && cc[i] <= 'Z')
        {
            valor = cc[i] - 'A' + valorA;
            if (j % 2 == 0)
            {
                valor *= 2;
            }
        }
        else
        {
            valor = cc[i] - '0';
            if (j % 2 == 0)
            {
                valor *= 2;
            }
        }

        if (j % 2 == 0 && valor > 9)
        {
            valor -= 9;
        }

        soma += valor;

        j++;
    }

    if (soma % 10 == 0)
    {
        return 1;
    }

    return 0;
}

int verificarTel(char *tel) // Converte e devolve o número de telefone para inteiro ou devolve 0 se inválido
{
    if (tel[0] - '0' != 9 || strlen(tel) != 9)
    {
        return 0;
    }
    return atoi(tel);
}

int verificarEmail(char *email) // Determina se o email fornecido é valido ou nao, retornando um resultado conforme
{
    // Verificar se o tamanho da string é valido
    if (strlen(email) > 255)
        return 0;

    // Verificar se existe apenas um '@' e pelo menos um '.' (mecanismo de integridade básico)
    int c1 = 0; // @
    int c2 = 0; // .
    for (int i = 0; i < (int)strlen(email); i++)
    {
        if (email[i] == '@')
        {
            c1++;
            if (email[i + 1] == '.' || email[i - 1] == '.')
                return 0;
        }
        if (email[i] == '.')
            c2++;
    }
    if (c1 != 1 || c2 == 0)
        return 0;

    return 1;
}

void recebeInputLimpaStream(char *buffer, int BUFFER_SIZE) // Função que recebe um input do utilizador e limpa a input stream (stdin)
{
    fgets(buffer, BUFFER_SIZE, stdin);

    // Trocar  o '\n' por '\0', se presente no buffer (o que acontece quando o utilizador pressiona 'Enter')
    if (buffer[strlen(buffer) - 1] == '\n')
    {
        buffer[strlen(buffer) - 1] = '\0';
    }
    else
    {
        // Se '\n' nao estiver no buffer significa que a entrada foi muito grande. Por isso ignoramos o resto das entradas na input stream
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
}

char *toUpperString(char *str) // Função que converte uma string para maiúsculas, através da função toupper que converte um char para maiúscula
{
    for (int i = 0; i < (int)strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

int comparaDatas(Data data1, Data data2) // Função que compara duas datas, devolvendo -1 se a primeira for maior, 1 se a segunda for maior e 0 se forem iguais
{
    // Comparar anos
    if (data1.ano < data2.ano)
        return 1;
    else if (data1.ano > data2.ano)
        return -1;

    // Sendo o ano o mesmo, comparamos o mês
    if (data1.mes < data2.mes)
        return 1;
    else if (data1.mes > data2.mes)
        return -1;

    // Sendo o mês o mesmo, comparamos o dia
    if (data1.dia < data2.dia)
        return 1;
    else if (data1.dia > data2.dia)
        return -1;

    // Se até os dias forem iguais, as datas são a mesma
    return 0;
}

Data receberData(char *bufferInput, int BUFFER_SIZE) // Recebe uma data do utilizador: processa a entrada e verifica se é válida. Retorna a data na respetiva estrutura
{
    do
    {
        recebeInputLimpaStream(bufferInput, BUFFER_SIZE);

        // Verificar se a entrada é valida, isto é, se a data foi introduzida conforme o formato pedido
        int flagValido = 1;

        // Verificar se a data tem os número de separadores necessarios para aplicar o strtok() devidamente
        int separatorCount = 0;
        for (int i = 0; i < (int)strlen(bufferInput); i++)
        {
            if (bufferInput[i] == '-')
                separatorCount++;
        }
        if (separatorCount != 2 || strlen(bufferInput) < 8)
        {
            flagValido = 0;
            printMsgErroData();
            continue;
        }

        Data output;

        // DIA
        char *tokenData = strtok(bufferInput, "-");
        if (strlen(tokenData) < 1 || strlen(tokenData) > 2)
        {
            flagValido = 0;
            printMsgErroData();
            continue;
        }
        for (int i = 0; i < (int)strlen(tokenData); i++)
        {
            if (!(tokenData[i] >= '0' && tokenData[i] <= '9'))
            {
                flagValido = 0;
                printMsgErroData();
                break;
            }
        }
        if (!flagValido)
            continue;
        output.dia = atoi(tokenData);

        // MES
        tokenData = strtok(NULL, "-");
        if (strlen(tokenData) < 1 || strlen(tokenData) > 2)
        {
            flagValido = 0;
            printMsgErroData();
            continue;
        }
        for (int i = 0; i < (int)strlen(tokenData); i++)
        {
            if (!(tokenData[i] >= '0' && tokenData[i] <= '9'))
            {
                flagValido = 0;
                printMsgErroData();
                break;
            }
        }
        if (!flagValido)
            continue;

        output.mes = atoi(tokenData);

        // ANO
        tokenData = strtok(NULL, "-");
        if (strlen(tokenData) < 1 || strlen(tokenData) > 4)
        {
            flagValido = 0;
            printMsgErroData();
            continue;
        }
        for (int i = 0; i < (int)strlen(tokenData); i++)
        {
            if (!(tokenData[i] >= '0' && tokenData[i] <= '9'))
            {
                flagValido = 0;
                printMsgErroData();
                break;
            }
        }
        if (!flagValido)
        {
            printMsgErroData();
            continue;
        }
        output.ano = atoi(tokenData);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        if (!dataValida(output) || tm.tm_year + 1900 < output.ano)
        {
            printMsgErroData();
            continue;
        }

        return output;

    } while (1);
}

int receberInteiro(char *bufferInput, int BUFFER_SIZE) // Recebe um inteiro do utilizador: processa a entrada e verifica se é válida. Retorna o inteiro
{
    do
    {
        recebeInputLimpaStream(bufferInput, BUFFER_SIZE);

        int flagValido = 1;
        for (int i = 0; i < (int)strlen(bufferInput); i++)
        {
            if (!((bufferInput[i] >= '0' && bufferInput[i] <= '9') || bufferInput[i] == '-'))
            {
                printVermelho();
                printf("\n[!] Valor inválido. Por favor insira um valor numerico: ");
                printBranco();
                flagValido = 0;
                break;
            }
        }
        if (!flagValido)
            continue;
        break;
    } while (1);

    return atoi(bufferInput);
}

char *receberNome(char *bufferInput, int BUFFER_SIZE) // Recebe um nome do utilizador: processa a entrada e verifica se é válida. Retorna o nome
{
    do
    {
        recebeInputLimpaStream(bufferInput, BUFFER_SIZE);

        // Verificar se a entrada é valida, isto é, se o nome contem apenas letras e espaços
        int flagValido = 1;

        if (strlen(bufferInput) == 0)
        {
            flagValido = 0;
            printVermelho();
            printf("\n[!] Nome invalido! Por favor insira um nome valido [a-z, A-Z, ' ']: ");
            printBranco();
            continue;
        }
        for (int i = 0; i < (int)strlen(bufferInput); i++)
        {
            if (!((bufferInput[i] >= 'a' && bufferInput[i] <= 'z') || (bufferInput[i] >= 'A' && bufferInput[i] <= 'Z') || bufferInput[i] == ' '))
            {
                flagValido = 0;
                printVermelho();
                printf("\n[!] Nome invalido! Por favor insira um nome valido [a-z, A-Z, ' ']: ");
                printBranco();
                break;
            }
        }

        if (flagValido)
            return bufferInput;

    } while (1);
}

char *receberCC(char *bufferInput, int BUFFER_SIZE) // Recebe um cartao de cidadao do utilizador: processa a entrada e verifica se é válida. Retorna o cartao de cidadao
{
    do
    {
        recebeInputLimpaStream(bufferInput, BUFFER_SIZE);

        // Verificar se a entrada é valida, isto é, se o cartao de cidadao introduzido é valido
        if (verificarCC(bufferInput))
            return bufferInput;

        printMsgErroCC();

    } while (1);
}

unsigned int receberTel(char *bufferInput, int BUFFER_SIZE) // Recebe um número de telefone do utilizador: processa a entrada e verifica se é válida. Retorna o número de telefone
{
    do
    {
        recebeInputLimpaStream(bufferInput, BUFFER_SIZE);

        // Verificar se a entrada é valida, isto é, se o número de telefone introduzido é valido
        if (verificarTel(bufferInput) != 0)
        {
            return verificarTel(bufferInput);
        }

        printMsgErroTel();

    } while (1);
}

char *receberEmail(char *bufferInput, int BUFFER_SIZE) // Recebe um email do utilizador: processa a entrada e verifica se é válido. Retorna o email
{
    do
    {

        recebeInputLimpaStream(bufferInput, BUFFER_SIZE);

        // Verificar se a entrada é valida, isto é, se o endereço de email introduzido é valido

        if (verificarEmail(bufferInput))
            return bufferInput;

        printMsgErroEmail();

    } while (1);
}

int confirmarAcao() // Função genérica que pergunta ao utilizador se deseja proceder com uma  operação, devolvendo 1 se sim e 0 se não
{
    char bufferInput[10];
    do
    {
        printAmarelo();
        printf("    > Deseja proceder com a operacao? (S/N): ");
        printBranco();
        recebeInputLimpaStream(bufferInput, 10);

        if (strcmp(toUpperString(bufferInput), "SIM") == 0 || strcmp(toUpperString(bufferInput), "S") == 0)
        {
            return 1;
        }
        else if (strcmp(toUpperString(bufferInput), "NAO") == 0 || strcmp(toUpperString(bufferInput), "N") == 0)
        {
            return 0;
        }
        else
        {
            printVermelho();
            printf("\n[!] Opcao invalida! Por favor insira 'S' ou 'N': ");
            printBranco();
        }

    } while (1);
}
