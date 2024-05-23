#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/structs.h"
#include "../lib/listaDoentes.h"
#include "../lib/registos.h"
#include "../lib/misc.h"

void apresentarDoente(Doente *doente)
{
    printf("        > ID: %d\n", doente->id);
    printf("        > Nome: %s\n", doente->nome);
    printf("        > Data de nascimento: %d/%d/%d\n", doente->nascimento.dia, doente->nascimento.mes, doente->nascimento.ano);
    printf("        > CC: %s\n", doente->cc);
    printf("        > Telefone: %d\n", doente->tel);
    printf("        > Email: %s\n\n", doente->email);
}

void carregarDoentes(lista_doentes_t *listaDoentes, int BUFFER_SIZE)
{
    // Abertura dos ficheiros para leitura e carregamento dos dados dos doentes
    FILE *fileDoentes = fopen("./doentes.txt", "r");

    if (fileDoentes == NULL)
    {
        printVermelho();
        printf("\n    [!] Não foi possivel abrir o ficheiro de doentes.\n\n");
        printBranco();
        exit(1);
    }

    char line[BUFFER_SIZE]; // Buffer para armazenar temporariamente cada linha

    unsigned int i = 0; // Contador da linha (a ser interpretada no while)
    Doente doente;

    while (fgets(line, BUFFER_SIZE, fileDoentes)) // Iteração por todas as linhas do ficheiro
    {

        // Remoção do '\n' do final da linha (se existir), guardado pelo fgets()
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }

        // Analisar o conteudo de uma determinada linha em analise: o resto da divisao por 6 do número de uma linha dá-nos a informação sobre o que estamos a ler:  exemplo: linha 7 -> 7 % 6 = 1 -> estamos a ler um ID de um doente
        switch (i % 6)
        {
        case 0:
            // ID
            doente.id = atoi(line);
            // printf("ID: %d\n", doente.id);
            break;
        case 1:
            // NOME
            strcpy(doente.nome, line);
            // printf("NOME: %s\n", doente.nome);
            break;
        case 2:
        {
            // DATA DE NASCIMENTO
            char *token = strtok(line, "/");
            doente.nascimento.dia = atoi(token);
            token = strtok(NULL, "/");
            doente.nascimento.mes = atoi(token);
            token = strtok(NULL, "/");
            doente.nascimento.ano = atoi(token);
            break;
        }
        case 3:
            // CARTAO DE CIDADAO
            strcpy(doente.cc, line);
            break;
        case 4:
            // NUMERO DE TELEFONE
            doente.tel = atoi(line);
            break;
        case 5:
            // EMAIL
            strcpy(doente.email, line);
            printVermelho();
            printf("\n> Informacoes do doente [%u] lidas do ficheiro: novo doente armazenado na estrutura.\n", doente.id);
            printBranco();

            doente.listaRegistos = (lista_registos_t *)malloc(sizeof(lista_registos_t)); // Alocar memória para a lista de registos de um doente
            if (doente.listaRegistos == NULL)
            {
                printVermelho();
                printf("\n    [!] Não foi possivel alocar memoria para a criacao de uma lista de registos.\n\n");
                printBranco();
                exit(1);
            }

            // Inicializar a lista de registos de um doente
            initListaRegistos(doente.listaRegistos);

            // Após a leitura de todos os campos de um doente, inserir o doente na lista
            inserirNodeDoente(listaDoentes, doente);
            printVerde();
            printf("> Informacoes lidas: novo doente armazenado na lista de doentes.\n");
            printBranco();
            break;
        }

        i++;
    }

    fclose(fileDoentes);
}

void receberNovoDoente(unsigned int id, Doente *novoDoente, char *bufferInput, int BUFFER_SIZE)
{
    novoDoente->id = id; // Atribuir o ID fornecido ao novo doente. Assume-se que o ID é unico e incremental e gerido pelo sistema, pelo que não necessita de ser validado

    printAmarelo();
    printf("\n>------------------[INTRODUÇÂO DE DADOS DE UM NOVO DOENTE]------------------<\nInsira as seguintes informacoes de modo a guardar os dados de um novo doente:\n");

    if (bufferInput == NULL)
    {
        printf("Alocacao de memoria falhou\n");
    }

    // ! NOME
    printCiano();
    printf("\n    > Nome do doente: ");
    printBranco();
    strcpy(novoDoente->nome, receberNome(bufferInput, BUFFER_SIZE)); // Receber o nome do doente

    // ! DATA DE NASCIMENTO

    printCiano();
    printf("\n    > Data de nascimento do doente [DD-MM-AAAA]: ");
    printBranco();
    novoDoente->nascimento = receberData(bufferInput, BUFFER_SIZE); // Receber a data de nascimento do doente

    // ! CARTAO DE CIDADAO
    printCiano();
    printf("\n    > Cartao de Cidadao do doente [12345678-1-XX1] (Apenas maiusculas sao aceites): ");
    printBranco();
    strcpy(novoDoente->cc, receberCC(bufferInput, BUFFER_SIZE)); // Receber o número de cartão de cidadão do doente

    // ! NUMERO DE TELEFONE

    printCiano();
    printf("\n    > Numero de telefone do doente [912345678]: ");
    printBranco();
    novoDoente->tel = receberTel(bufferInput, BUFFER_SIZE); // Receber o número de telefone do doente

    // ! EMAIL
    printCiano();
    printf("\n    > Endereço de email do doente [email@dominio.com]: ");
    printBranco();
    strcpy(novoDoente->email, receberEmail(bufferInput, BUFFER_SIZE)); // Receber o email do doente

    // ! LISTA DE REGISTOS
    novoDoente->listaRegistos = (lista_registos_t *)malloc(sizeof(lista_registos_t));
    if (novoDoente->listaRegistos == NULL)
    {
        printVermelho();
        printf("\n    [!] Não foi possivel alocar memoria para criar a lista de registos.\n\n");
        printBranco();
        exit(1);
    }
    initListaRegistos(novoDoente->listaRegistos); // Inicializar a lista de registos de um doente
}

void atualizarFicheiroDoentes(lista_doentes_t *listaDoentes) // Função que reescreve todos os conteudos do ficheiro de doentes com todos os nodes presentes na lista
{
    FILE *fileDoentes = fopen("./doentes.txt", "w");
    if (fileDoentes == NULL)
    {
        printVermelho();
        printf("\n    [!] Não foi possivel abrir o ficheiro de doentes.\n\n");
        printBranco();
        exit(1);
    }

    l_node_doente_t *cur = listaDoentes->front;

    printAmarelo();
    printf("\n    [!] Atualização do ficheiro de doentes em curso...\n");
    printBranco();
    while (cur != NULL)
    {
        fprintf(fileDoentes, "%d\n", cur->doente.id);
        fprintf(fileDoentes, "%s\n", cur->doente.nome);
        fprintf(fileDoentes, "%d/%d/%d\n", cur->doente.nascimento.dia, cur->doente.nascimento.mes, cur->doente.nascimento.ano);
        fprintf(fileDoentes, "%s\n", cur->doente.cc);
        fprintf(fileDoentes, "%d\n", cur->doente.tel);
        fprintf(fileDoentes, "%s\n", cur->doente.email);

        cur = cur->next;
    }
    fclose(fileDoentes);

    printVerde();
    printf("\n    [!] Atualização do ficheiro de doentes em concluida.\n");
    printBranco();
}

void appendFicheiroDoentes(Doente *doente) // Função que acrescenta um novo doente ao ficheiro de doentes
{
    FILE *fileDoentes = fopen("./doentes.txt", "a");
    if (fileDoentes == NULL)
    {
        printVermelho();
        printf("\n    [!] Não foi possivel abrir o ficheiro de doentes.\n\n");
        printBranco();
        exit(1);
    }

    printAmarelo();
    printf("\n    [!] Acrescimo ao ficheiro de doentes em curso...\n\n");
    fprintf(fileDoentes, "%d\n", doente->id);
    fprintf(fileDoentes, "%s\n", doente->nome);
    fprintf(fileDoentes, "%d/%d/%d\n", doente->nascimento.dia, doente->nascimento.mes, doente->nascimento.ano);
    fprintf(fileDoentes, "%s\n", doente->cc);
    fprintf(fileDoentes, "%d\n", doente->tel);
    fprintf(fileDoentes, "%s\n", doente->email);
    fclose(fileDoentes);

    printVerde();
    printf("\n    [!] Acrescimo ao ficheiro de doentes concluido.\n\n");
    printBranco();
}

int pesquisarDoenteNome(lista_doentes_t *listaDoentes, char *nome) // Pesquisar e apresentar um doente no sistema através de um nome
{
    l_node_doente_t *cur = listaDoentes->front;

    int c = 0;
    while (cur != NULL)
    {
        if (strcmp(cur->doente.nome, nome) == 0)
        {
            c++;
            printVerde();
            printf("\n    [%d] Doente encontrado:\n", c);
            printAzul();
            apresentarDoente(&cur->doente);
        }
        cur = cur->next;
    }
    if (c == 0)
    {
        printVermelho();
        printf("\n    [!] Não foi encontrado nenhum doente.\n");
        printBranco();
        return 0;
    }
    else
        return 1;
}

l_node_doente_t *pesquisarDoenteID(lista_doentes_t *list, unsigned int id) // Devolve o ponteiro para um node de um doente através do seu ID
{
    l_node_doente_t *node = list->front;

    while (node != NULL)
    {
        if (node->doente.id == id)
        {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

void apresentarInfoDoenteID(lista_doentes_t *listaDoentes, unsigned int id) // Apresentar as informações de um doente procurado pelo ID
{
    l_node_doente_t *cur = listaDoentes->front;
    while (cur != NULL)
    {
        if (cur->doente.id == id)
        {
            printVerde();
            printf("\n    Informacoes do doente encontrado:\n\n");
            printAzul();
            apresentarDoente(&cur->doente);
            printBranco();
            if (cur->doente.listaRegistos->n_elem > 0)
                apresentarListaRegistos(cur->doente.listaRegistos);
            else
                printf("\n    [!] O doente nao possui registos.\n\n");
            break;
        }
        cur = cur->next;
    }
}

unsigned int pesquisarDoenteAtravesInfo(lista_doentes_t *listaDoentes, char *bufferInput, int BUFFER_SIZE) // Encontrar o ID de um doente através do nome
{
    int val = 0;
    do
    {
        printCiano();
        printf("    - Opções de pesquisa disponiveis: ID / Nome : ");
        printBranco();
        recebeInputLimpaStream(bufferInput, BUFFER_SIZE); // Receber a opcao de pesquisa

        if (strcmp(toUpperString(bufferInput), "ID") == 0)
        {
            val = 1;
            break;
        }
        else if (strcmp(toUpperString(bufferInput), "NOME") == 0)
        {
            val = 2;
            break;
        }
        else
        {
            printVermelho();
            printf("\n    [!] Opcao invalida. Por favor insira uma opcao de entre as fornecidas.\n\n");
            printBranco();
        }
    } while (1);

    switch (val)
    {
    case 1: // Pesquisar por ID
        printCiano();
        printf("    > Insira o ID do doente a selecionar: ");
        printBranco();
        do
        {
            recebeInputLimpaStream(bufferInput, BUFFER_SIZE); // Receber o ID do doente a eliminar

            unsigned int id = (unsigned int)atoi(bufferInput); // Guardar o id guardado no buffer

            if (pesquisarDoenteID(listaDoentes, id) != NULL) // Verificar se o doente existe e apresentar os resultados da pesquisa ao utilizador
            {
                apresentarInfoDoenteID(listaDoentes, id);
                do
                {
                    printAmarelo();
                    printf("\n    [!] Tem a certeza que o doente selecinado (ID=%u) está correto? (S/N): ", id);
                    printBranco();
                    recebeInputLimpaStream(bufferInput, BUFFER_SIZE);

                    if (strcmp(toUpperString(bufferInput), "S") == 0)
                    {
                        return id;
                        break;
                    }
                    else if (strcmp(toUpperString(bufferInput), "N") == 0)
                    {
                        return 0;
                        break;
                    }
                    else
                    {
                        printVermelho();
                        printf("\n    [!] Opcao invalida. Por favor insira uma opcao de entre as fornecidas.\n");
                        printBranco();
                    }
                } while (1);

                break;
            }
            else
            {
                printVermelho();
                printf("\n    [!] Doente nao encontrado.\n");
                printCiano();
                printf("\n    > Insira o ID do doente a selecionar: ");
                printBranco();
            }
        } while (1);

        break;
    case 2: // Pesquisar por Nome
    {
        printCiano();
        printf("    > Insira o Nome do doente a selecionar (Case-sensitive): ");
        printBranco();
        char nome[BUFFER_SIZE]; // Guardar o nome guardado no buffer, uma vez que este será reutilizado

        do
        {
            recebeInputLimpaStream(bufferInput, BUFFER_SIZE); // Receber o nome do doente a eliminar

            strcpy(nome, bufferInput);

            if (pesquisarDoenteNome(listaDoentes, nome) == 1) // Verificar se o doente existe e apresentar os resultados da pesquisa ao utilizador
            {
                do
                {
                    printCiano();
                    printf("\n    > Selecione o ID do doente a selecionar: ");
                    printBranco();
                    recebeInputLimpaStream(bufferInput, BUFFER_SIZE);

                    unsigned int id = (unsigned int)atoi(bufferInput); // Guardar o id guardado no buffer

                    if (pesquisarDoenteID(listaDoentes, id) != NULL) // Verificar se o doente existe e apresentar os resultados da pesquisa ao utilizador
                    {
                        do
                        {
                            printAmarelo();
                            printf("\n[!] Tem a certeza que deseja selecionar o doente com o ID %u? (S/N): ", id);
                            printBranco();
                            recebeInputLimpaStream(bufferInput, BUFFER_SIZE);

                            if (strcmp(toUpperString(bufferInput), "S") == 0)
                            {
                                return id;
                                break;
                            }
                            else if (strcmp(toUpperString(bufferInput), "N") == 0)
                            {
                                return 0;
                                break;
                            }
                            else
                            {
                                printVermelho();
                                printf("\n    [!] Opcao invalida. Por favor insira uma opcao de entre as fornecidas.\n");
                                printBranco();
                            }
                        } while (1);

                        break;
                    }
                    else
                    {
                        printVermelho();
                        printf("\n    [!] Doente nao encontrado.\n");
                        printBranco();
                    }

                } while (1);

                break;
            }
            else
            {
                printCiano();
                printf("\n    > Insira o Nome do doente a eliminar dos registos (Case-sensitive): ");
                printBranco();
            }
        } while (1);
        break;
    }

    default:
        return 0;
        break;
    }
}

void apresentarDoentes(lista_doentes_t *listaDoentes) // Apresentar todos os doentes (excluindo registos)
{
    l_node_doente_t *cur = listaDoentes->front;
    printAmarelo();
    printf("\nListagem de doentes por ordem alfabetica:\n\n");
    while (cur != NULL)
    {
        printAmarelo();
        printf("        ---------------------------------------------\n\n");
        printAzul();
        apresentarDoente(&cur->doente);
        printBranco();
        cur = cur->next;
    }
}

int tensaoMaximaDoente(Doente *doente) // Retorna o valor da tensaoMaxima mais alta de um doente
{
    l_node_registo_t *cur = doente->listaRegistos->frontTensaoMax;
    int max = 0;
    while (cur != NULL)
    {
        if (cur->registo.tensaoMax > max)
            max = cur->registo.tensaoMax;
        cur = cur->nextTensaoMax;
    }
    return max;
}
