#include "../system/system.c"
#include "grafo.h"

struct pages
{
    char nome[100];
    short id;
};

struct grafo
{
    Pages aresta1;
    Pages aresta2;
    int conexao; // 1 caso estejam ligados e 0 caso não
};

Grafo **cria_matriz()
{
    Grafo **matriz = (Grafo **)malloc(TAMANHO_MATRIZ * sizeof(Grafo *));
    if (matriz == NULL)
    {
        printf("ERRO");
        exit(1);
    }
    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        matriz[i] = (Grafo *)malloc(TAMANHO_MATRIZ * sizeof(Grafo));
        if (matriz[i] == NULL)
        {
            printf("ERRO");
            exit(1);
        }
    }
    return matriz;
}

Grafo **preenche_matriz(Grafo **matriz)
{
    FILE *data = fopen("../fb-pages-food/fb-pages-food.nodes", "r");
    if (data == NULL)
    {
        printf("ERRO");
        exit(1);
    }
    char linha[100];
    fgets(linha, 100, data);
    char *token;
    Pages aux;
    int i, linhas = 0, colunas = 0;
    while (fgets(linha, 100, data) != NULL)
    {
        token = strtok(linha, ",");
        token = strtok(NULL, ",");
        strcpy(aux.nome, token);
        token = strtok(NULL, ",");
        aux.id = atoi(token);
        for (i = 0; i < TAMANHO_MATRIZ; i++)
        {
            matriz[linhas][i].aresta1 = aux;
            matriz[linhas][i].conexao = 0;
            matriz[i][colunas].aresta2 = aux;
            matriz[i][colunas].conexao = 0;
        }
        linhas++;
        colunas++;
    }
    return matriz;
}

