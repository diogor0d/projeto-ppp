#include <stdio.h>
#include <string.h>

#include "../lib/misc.h"
#include "../lib/structs.h"
#include "../lib/listaRegistos.h"
#include "../lib/listaDoentes.h"
#include "../lib/registos.h"
#include "../lib/doentes.h"

void apresentarRegisto(Registo *registo)
{
    printf("    > ID Registo: %u\n", registo->registoId);
    printf("    > Data: %d/%d/%d\n", registo->data.dia, registo->data.mes, registo->data.ano);
    printf("    > TensaoMax: %d\n", registo->tensaoMax);
    printf("    > TensaoMin: %d\n", registo->tensaoMin);
    printf("    > Peso: %d\n", registo->peso);
    printf("    > Altura: %d\n\n", registo->altura);
}

void carregarRegistos(lista_doentes_t *listaDoentes, int BUFFER_SIZE) // Função que percorre o ficheiro de registos, procura a correspondência entre o ID do doente e o ID do registo, e insere o registo na lista de registos do doente correspondente
{
    FILE *fileRegistos = fopen("./registos.txt", "r");

    if (fileRegistos == NULL)
    {
        printVermelho();
        printf("\n    [!] Não foi possivel abrir o ficheiro de registos.\n\n");
        printBranco();
        exit(1);
    }

    printAmarelo();
    printf("\n> A carregar registos dos doentes...\n");

    Registo registo;
    char line[BUFFER_SIZE];

    unsigned int i = 0; // Contador da linha (a ser interpretada no while)
    unsigned int idDoente;
    l_node_doente_t *doente;

    while (fgets(line, BUFFER_SIZE, fileRegistos) != NULL)
    {

        // Remoção do '\n' do final da linha (se existir), guardado pelo fgets()
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }

        switch (i % 6)
        {
        case 0:
        {
            idDoente = atoi(line);
            doente = pesquisarDoenteID(listaDoentes, idDoente);

            break;
        }
        case 1:
        {
            if (doente == NULL)
                break;

            char *token = strtok(line, "/");
            registo.data.dia = atoi(token);
            token = strtok(NULL, "/");
            registo.data.mes = atoi(token);
            token = strtok(NULL, "/");
            registo.data.ano = atoi(token);

            break;
        }
        case 2:
            if (doente == NULL)
                break;

            registo.tensaoMax = atoi(line);
            break;
        case 3:
            if (doente == NULL)
                break;

            registo.tensaoMin = atoi(line);
            break;
        case 4:
            if (doente == NULL)
                break;

            registo.peso = atoi(line);
            break;
        case 5:
            if (doente == NULL)
                break;

            registo.altura = atoi(line);

            inserirNodeRegisto(doente->doente.listaRegistos, registo);
            printVerde();
            printf("    > Registo guardado no doente com ID %d\n", doente->doente.id);

            printBranco();
            break;
        }

        i++;
    }

    fclose(fileRegistos);
}

void listarDoentesTensaoAcimaLimite(lista_doentes_t *list, int limite) // Função que lista todos os doentes com tensões máximas acima de um determinado valor "limite"
{
    l_node_doente_t *node = list->front;

    printAmarelo();
    printf("\n---------------------------------------------\n");
    printf("Os seguintes doentes possuem tensões máximas acima de %d (listadas por ordem decrescente):\n", limite);

    int existemResultados = 0; // Flag para verificar se existem doentes com tensões acima do limite

    while (node != NULL) // Percorrer a lista de doentes
    {

        l_node_registo_t *nodeRegisto = node->doente.listaRegistos->frontTensaoMax;

        int nomeApresentado = 0;    // Flag para apresentar o nome do doente apenas uma vez
        while (nodeRegisto != NULL) // Percorrer a lista de registos de cada doente
        {
            if (nodeRegisto->registo.tensaoMax > limite)
            {
                existemResultados = 1;
                if (!nomeApresentado)
                {
                    printAmarelo();
                    printf("\n---------------------------------------------\n");
                    printAzul();
                    printf("> DOENTE ID: %d\n", node->doente.id);
                    printf("> Nome: %s\n", node->doente.nome);
                    printAmarelo();
                    printf("---------------------------------------------\n\n");
                    printAzul();
                    nomeApresentado = 1;
                }
                apresentarRegisto(&nodeRegisto->registo);
            }
            nodeRegisto = nodeRegisto->nextTensaoMax;
        }
        printBranco();

        node = node->next;
    }

    if (!existemResultados)
        printf("\n      [!] Nao foi encontrado nenhum doente nas condicoes fornececidas.\n\n");
}

void appendFicheiroRegistos(unsigned int id, Registo *registo) // Acrescenta um registo diretamente ao fim do ficheiro de registos
{
    FILE *fileRegistos = fopen("./registos.txt", "a");
    if (fileRegistos == NULL)
    {
        printVermelho();
        printf("\n    [!] Não foi possivel abrir o ficheiro de registos.\n\n");
        printBranco();
        exit(1);
    }

    printAmarelo();
    printf("\n    [!] Acrescimo ao ficheiro de registos em curso...\n");
    fprintf(fileRegistos, "%u\n", id);
    fprintf(fileRegistos, "%d/%d/%d\n", registo->data.dia, registo->data.mes, registo->data.ano);
    fprintf(fileRegistos, "%d\n", registo->tensaoMax);
    fprintf(fileRegistos, "%d\n", registo->tensaoMin);
    fprintf(fileRegistos, "%d\n", registo->peso);
    fprintf(fileRegistos, "%d\n", registo->altura);
    fclose(fileRegistos);
    printVerde();
    printf("\n    [!] Acrescimo ao ficheiro de registos concluido.\n");
    printBranco();
}

void atualizarFicheiroRegistos(lista_doentes_t *listaDoentes) // Função que reescreve todos os conteudos do ficheiro de registos com todos os nodes da lista de registos de cada node presente na lista de doentes
{
    FILE *fileRegistos = fopen("./registos.txt", "w");
    if (fileRegistos == NULL)
    {
        printf("Erro ao abrir o ficheiro de registos.\n");
        return;
    }

    l_node_doente_t *curDoente = listaDoentes->front;

    while (curDoente != NULL)
    {
        lista_registos_t *listaRegistos = curDoente->doente.listaRegistos;
        l_node_registo_t *curRegisto = listaRegistos->front;

        while (curRegisto != NULL)
        {
            fprintf(fileRegistos, "%u\n", curDoente->doente.id);
            fprintf(fileRegistos, "%d/%d/%d\n", curRegisto->registo.data.dia, curRegisto->registo.data.mes, curRegisto->registo.data.ano);
            fprintf(fileRegistos, "%d\n", curRegisto->registo.tensaoMax);
            fprintf(fileRegistos, "%d\n", curRegisto->registo.tensaoMin);
            fprintf(fileRegistos, "%d\n", curRegisto->registo.peso);
            fprintf(fileRegistos, "%d\n", curRegisto->registo.altura);

            curRegisto = curRegisto->next;
        }

        curDoente = curDoente->next;
    }
    fclose(fileRegistos);
}

void receberNovoRegisto(l_node_doente_t *doente, Registo *novoRegisto, int BUFFER_SIZE) // Função que determina um IDRegisto para um novo registo, recebe os dados de um novo registo, insere-os na estrutura Registo fornecida
{
    char bufferInput[BUFFER_SIZE]; // Buffer para armazenar temporariamente cada linha

    novoRegisto->registoId = novoIDRegisto(doente->doente.listaRegistos);

    printAmarelo();
    printf("\n    > Insira a data do registo (dd-mm-aaaa): ");
    printBranco();
    novoRegisto->data = receberData(bufferInput, BUFFER_SIZE);

    printAmarelo();
    printf("    > Insira a tensao maxima: ");
    printBranco();
    novoRegisto->tensaoMax = receberInteiro(bufferInput, BUFFER_SIZE); // Receber a tensão máxima

    printAmarelo();
    printf("    > Insira a tensao minima: ");
    printBranco();
    novoRegisto->tensaoMin = receberInteiro(bufferInput, BUFFER_SIZE);

    printAmarelo();
    printf("    > Insira o peso: ");
    printBranco();
    novoRegisto->peso = receberInteiro(bufferInput, BUFFER_SIZE);

    printAmarelo();
    printf("    > Insira a altura: ");
    printBranco();
    novoRegisto->altura = receberInteiro(bufferInput, BUFFER_SIZE);

    printVerde();
    printf("\n    Registo inserido na estrutura.\n");
    printBranco();
}
