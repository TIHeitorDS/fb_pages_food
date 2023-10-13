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
        print_red("Erro de alocacao de memoria\n");
        exit(1);
    }
    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        matriz[i] = (Grafo *)malloc(TAMANHO_MATRIZ * sizeof(Grafo));
        if (matriz[i] == NULL)
        {
            print_red("Erro de alocacao de memoria\n");
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
        print_red("Erro de alocacao de memoria\n");
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
        print_red("Erro de alocacao de memoria\n");
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
    int i = 0, j = 0, k = 0, qnt = 0;
    while (fgets(linha, 100, data) != NULL)
    {
        token = strtok(linha, ",");
        conexoes[i].id1 = atoi(token);
        token = strtok(NULL, ",");
        conexoes[i].id2 = atoi(token);
        i++;
    }
    for (k = 0; k < 2102; k++)
    {
        int conexaoAlterada = 0; // Variável para rastrear se a conexão foi alterada para 1

        for (i = 0; i < TAMANHO_MATRIZ; i++)
        {
            for (j = 0; j < TAMANHO_MATRIZ; j++)
            {
                if (matriz[i][j].aresta1.id == conexoes[k].id1 || matriz[i][j].aresta1.id == conexoes[k].id2)
                {
                    if (matriz[i][j].aresta2.id == conexoes[k].id1 || matriz[i][j].aresta2.id == conexoes[k].id2)
                    {
                        if (matriz[i][j].aresta1.id != matriz[i][j].aresta2.id || conexoes[k].id1 == conexoes[k].id2)
                        {
                            matriz[i][j].conexao = 1;
                            conexaoAlterada = 1; // Marque que a conexão foi alterada para 1
                            qnt++;
                        }
                    }
                }
            }
        }
        if (!conexaoAlterada)
        {
            printf("Conexão nao alterada para 1 para k = %d\n", k);
            printf("ID1: %d, ID2: %d\n", conexoes[k].id1, conexoes[k].id2);
        }
    }

    free(conexoes);
    fclose(data);
    return matriz;
}

void print_conexoes(Grafo **matriz)
{
    char *aux = (char *)malloc(100 * sizeof(char));
    if (aux == NULL)
    {
        print_red("Erro de alocacao de memoria\n");
        exit(1);
    }
    print_yellow("\n------Exibindo todas as conexoes da matriz------\n");
    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
        {
            if (matriz[i][j].conexao == 1)
            {
                sprintf(aux, "Conexao entre %s (ID: %d) e %s (ID: %d)\n", matriz[i][j].aresta1.nome, matriz[i][j].aresta1.id, matriz[i][j].aresta2.nome, matriz[i][j].aresta2.id);
                print_green(aux);
            }
        }
    }
    free(aux);
}

int verifica_conexao_entre_paginas(Grafo **matriz)
{
    int id_pagina1, id_pagina2;
    print_yellow("Informe o ID da primeira pagina: ");
    if (scanf("%d", &id_pagina1) != 1)
    {
        limpa_buffer();
        print_red("Entrada invalida. Certifique-se de que voce digitou um numero para o ID da pagina.\n");
        return -1;
    }
    print_yellow("Informe o ID da segunda página: ");
    if (scanf("%d", &id_pagina2) != 1)
    {
        limpa_buffer();

        print_red("Entrada invalida. Certifique-se de que voce digitou um numero para o ID da pagina.\n");
        return -1;
    }
    char *aux = (char *)malloc(100 * sizeof(char));
    if (aux == NULL)
    {
        print_red("Erro de alocacao de memoria\n");
        exit(1);
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
                    sprintf(aux, "Ha uma conexao entre as paginas com IDs %d e %d.\n", id_pagina1, id_pagina2);
                    print_green(aux);
                    free(aux);
                    return 1;
                }
                else
                {
                    sprintf(aux, "Nao ha conexao entre as paginas com IDs %d e %d.\n", id_pagina1, id_pagina2);
                    print_red(aux);
                    free(aux);
                    return 0;
                }
            }
        }
    }
    sprintf(aux, "Nao ha conexao entre as paginas com IDs %d e %d.\n", id_pagina1, id_pagina2);
    print_red(aux);
    free(aux);
    return 0;
}

void buscar_pagina_por_id(Grafo **matriz)
{
    int id_pagina;
    print_yellow("Informe o ID da pagina que deseja buscar: ");
    if (scanf("%d", &id_pagina) != 1)
    {
        limpa_buffer();
        print_red("Entrada invalida. Certifique-se de que voce digitou um numero para o ID da pagina.\n");
        return;
    }
    int encontrou = 0;
    char *aux = (char *)malloc(100 * sizeof(char));
    if (aux == NULL)
    {
        print_red("Erro de alocacao de memoria\n");
        exit(1);
    }
    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        if (matriz[i][0].aresta1.id == id_pagina)
        {
            sprintf(aux, "Pagina encontrada com ID %d: %s\n", id_pagina, matriz[i][0].aresta1.nome);
            print_green(aux);
            encontrou = 1;
        }
    }
    if (!encontrou)
    {
        sprintf(aux, "Nenhuma pagina encontrada com o ID %d.\n", id_pagina);
        print_red(aux);
    }
    free(aux);
}

void exibe_quantidade_de_vertices(Grafo **matriz)
{
    int quantidade_vertices = 0;

    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        if (matriz[i][0].aresta1.id >= 0)
        {
            quantidade_vertices++;
        }
    }
    char *aux = (char *)malloc(100 * sizeof(char));
    if (aux == NULL)
    {
        print_red("Erro de alocacao de memoria\n");
        exit(1);
    }
    sprintf(aux, "A quantidade de vertices (paginas) na matriz e: %d\n", quantidade_vertices);
    print_green(aux);
    free(aux);
}

void exibe_quantidade_de_arestas(Grafo **matriz)
{
    int quantidade_arestas = 0;

    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
        {
            if (matriz[i][j].conexao == 1)
            {
                if (matriz[i][j].conexao == 1 && i == j)
                {
                    quantidade_arestas += 2;
                }
                else
                {
                    quantidade_arestas++;
                }
            }
        }
    }
    char *aux = (char *)malloc(100 * sizeof(char));
    if (aux == NULL)
    {
        print_red("Erro de alocacao de memoria\n");
        exit(1);
    }
    sprintf(aux, "A quantidade de arestas na matriz e: %d\n", quantidade_arestas / 2);
    print_green(aux);
    free(aux);
}

void pagina_com_mais_conexoes(Grafo **matriz)
{
    int maxConexoes = 0;
    int idPaginaComMaisConexoes = -1;
    char nomePaginaComMaisConexoes[100];
    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        int conexoesAtuais = 0;
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
        {
            if (matriz[i][j].conexao == 1)
            {
                conexoesAtuais++;
            }
        }
        if (conexoesAtuais >= maxConexoes)
        {
            maxConexoes = conexoesAtuais;
            idPaginaComMaisConexoes = matriz[i][0].aresta1.id;
            strcpy(nomePaginaComMaisConexoes, matriz[i][0].aresta1.nome);
        }
    }
    if (idPaginaComMaisConexoes >= 0)
    {
        char *aux = (char *)malloc(100 * sizeof(char));
        if (aux == NULL)
        {
            print_red("Erro de alocacao de memoria\n");
            exit(1);
        }
        sprintf(aux, "A pagina com mais conexoes é %s (ID: %d) com um total de %d conexoes.\n", nomePaginaComMaisConexoes, idPaginaComMaisConexoes, maxConexoes);
        print_green(aux);
        free(aux);
    }
    else
    {
        print_red("Nao ha paginas com conexoes na matriz.\n");
    }
}

void pagina_com_menos_conexoes(Grafo **matriz)
{
    int minConexoes = 5000;
    int idPaginaComMenosConexoes = -1;
    char nomePaginaComMenosConexoes[100];

    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        int conexoesAtuais = 0;
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
        {
            if (matriz[i][j].conexao == 1)
            {
                conexoesAtuais++;
            }
        }
        if (conexoesAtuais < minConexoes)
        {
            minConexoes = conexoesAtuais;
            idPaginaComMenosConexoes = matriz[i][0].aresta1.id;
            strcpy(nomePaginaComMenosConexoes, matriz[i][0].aresta1.nome);
        }
    }

    if (idPaginaComMenosConexoes >= 0)
    {
        char *aux = (char *)malloc(100 * sizeof(char));
        if (aux == NULL)
        {
            print_red("Erro de alocacao de memoria\n");
            exit(1);
        }
        sprintf(aux, "A pagina com menos conexoes é %s (ID: %d) com um total de %d conexoes.\n", nomePaginaComMenosConexoes, idPaginaComMenosConexoes, minConexoes);
        print_green(aux);
        free(aux);
    }
    else
    {
        print_red("Nao ha paginas com conexoes na matriz.\n");
    }
}

void paginas_isoladas(Grafo **matriz)
{
    print_yellow("\n------Paginas Isoladas------\n");
    int isoladasEncontradas = 0;

    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        int conexoesAtuais = 0;
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
        {
            if (matriz[i][j].conexao == 1)
            {
                conexoesAtuais++;
            }
        }
        if (conexoesAtuais == 0)
        {
            char *aux = (char *)malloc(100 * sizeof(char));
            if (aux == NULL)
            {
                print_red("Erro de alocacao de memoria\n");
                exit(1);
            }
            sprintf(aux, "Pagina isolada: %s (ID: %d)\n", matriz[i][0].aresta1.nome, matriz[i][0].aresta1.id);
            print_green(aux);
            free(aux);
            isoladasEncontradas++;
        }
    }

    if (isoladasEncontradas == 0)
    {
        print_yellow("Nenhuma pagina isolada encontrada.\n\n");
    }
}

void calcular_e_exibir_media_graus(Grafo **matriz)
{
    int total_graus = 0;
    int total_paginas = 0;

    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        int graus_pagina = 0;
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
        {
            if (matriz[i][j].conexao == 1 && i == j)
            {
                graus_pagina += 2;
            }
            else if (matriz[i][j].conexao == 1 && i != j)
            {
                graus_pagina++;
            }
        }
        if (graus_pagina > 0)
        {
            total_graus += graus_pagina;
            total_paginas++;
        }
    }

    if (total_paginas == 0)
    {
        print_red("A matriz nao contem paginas com conexoes.\n");
        return; // Evita a divisão por zero
    }

    float media_graus = (float)total_graus / total_paginas;
    char *aux = (char *)malloc(100 * sizeof(char));
    if (aux == NULL)
    {
        print_red("Erro de alocacao de memoria\n");
        exit(1);
    }
    sprintf(aux, "A media dos graus na matriz e: %.2f\n", media_graus);
    print_green(aux);
    free(aux);
}
