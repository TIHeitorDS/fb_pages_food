#include "grafo/grafo.c"

int main()
{
    Grafo **matrizadj = cria_matriz();
    matrizadj = preenche_matriz(matrizadj);
    matrizadj = verifica_conexoes(matrizadj);
    char opc;
    do
    {
        menu();
        opc = le_opcao(OPCAO0, OPCAO8);
        switch (opc)
        {
        case OPCAO1:
            verifica_conexao_entre_paginas(matrizadj);
            break;
        case OPCAO2:
            buscar_pagina_por_id(matrizadj);
            break;
        case OPCAO3:
            exibe_quantidade_de_vertices(matrizadj);
            break;
        case OPCAO4:
            exibe_quantidade_de_arestas(matrizadj);
            break;
        case OPCAO5:
            break;
        case OPCAO6:
            pagina_com_mais_conexoes(matrizadj);
            break;
        case OPCAO7:
            break;
        case OPCAO8:
            break;
        case OPCAO0:
            print_green("Obrigado por utilizar meu programa!\n");
            break;
        default:
            print_red("Opcao invalida!\n");
            break;
        }
    } while (opc != '0');

    return 0;
}