#include "../system/system.c"
#include "grafo.h"

struct pages
{
    char nome[100];
    short id;
};
struct conexoes
{
    short id1;
    short id2;
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
        print_red("Erro de alocação de memória\n");
        exit(1);
    }
    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        matriz[i] = (Grafo *)malloc(TAMANHO_MATRIZ * sizeof(Grafo));
        if (matriz[i] == NULL)
        {
            print_red("Erro de alocação de memória\n");
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
        print_red("Erro de alocação de memória\n");
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
        token = strtok(NULL, "\n");
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
    fclose(data);
    return matriz;
}

Grafo **verifica_conexoes(Grafo **matriz)
{
    Conexoes *conexoes = (Conexoes *)malloc(2102 * sizeof(Conexoes));
    if (conexoes == NULL)
    {
        print_red("Erro de alocação de memória\n");
        exit(1);
    }
    FILE *data = fopen("../fb-pages-food/fb-pages-food.edges", "r");
    if (data == NULL)
    {
        print_red("ERRO");
        exit(1);
    }
    char linha[100];
    fgets(linha, 100, data);
    char *token;
    int i = 0, j = 0, k = 0;
    while (fgets(linha, 100, data) != NULL)
    {
        token = strtok(linha, ",");
        conexoes[i].id1 = atoi(token);
        token = strtok(NULL, ",");
        conexoes[i].id2 = atoi(token);
        i++;
    }
    for (i = 0; i < TAMANHO_MATRIZ; i++)
    {
        for (j = 0; j < TAMANHO_MATRIZ; j++)
        {
            for (k = 0; k < 2102; k++)
            {
                if (matriz[i][j].aresta1.id == conexoes[k].id1 || matriz[i][j].aresta1.id == conexoes[k].id2)
                {
                    if (matriz[i][j].aresta2.id == conexoes[k].id1 || matriz[i][j].aresta2.id == conexoes[k].id2)
                    {
                        matriz[i][j].conexao = 1; // tem conexao
                    }
                }
            }
        }
    }
    free(conexoes);
    fclose(data);
    return matriz;
}

void printConexoes(Grafo **matriz)
{
    char *aux = (char *)malloc(100 * sizeof(char));
    if (aux == NULL)
    {
        print_red("Erro de alocação de memória\n");
        exit(1);
    }
    print_yellow("\n------Exibindo todas as conexoes da matriz------\n");
    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
        {
            if (matriz[i][j].conexao == 1)
            {
                sprintf(aux, "Conexão entre %s (ID: %d) e %s (ID: %d)\n", matriz[i][j].aresta1.nome, matriz[i][j].aresta1.id, matriz[i][j].aresta2.nome, matriz[i][j].aresta2.id);
                print_green(aux);
            }
        }
    }
    free(aux);
}

#include <stdio.h>

int verifica_conexao_entre_paginas(Grafo **matriz)
{
    int id_pagina1, id_pagina2;
    print_yellow("Informe o ID da primeira página: ");
    if (scanf("%d", &id_pagina1) != 1)
    {
        print_red("Entrada inválida. Certifique-se de que você digitou um número para o ID da primeira página.\n");
        return -1;
    }
    print_yellow("Informe o ID da segunda página: ");
    if (scanf("%d", &id_pagina2) != 1)
    {
        print_red("Entrada inválida. Certifique-se de que você digitou um número para o ID da segunda página.\n");
        return -1;
    }

    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
        {
            if ((matriz[i][j].aresta1.id == id_pagina1 && matriz[i][j].aresta2.id == id_pagina2) ||
                (matriz[i][j].aresta1.id == id_pagina2 && matriz[i][j].aresta2.id == id_pagina1))
            {
                if (matriz[i][j].conexao == 1)
                {
                    printf("Há uma conexão entre as páginas com IDs %d e %d.\n", id_pagina1, id_pagina2);
                    return 1;
                }
                else
                {
                    printf("Não há conexão entre as páginas com IDs %d e %d.\n", id_pagina1, id_pagina2);
                    return 0;
                }
            }
        }
    }
    printf("Não há conexão entre as páginas com IDs %d e %d.\n", id_pagina1, id_pagina2);
    return 0;
}
