#include "../system/system.c"
#include "grafo.h"

struct grafo
{
    char aresta1[100];
    char aresta2[100];
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
