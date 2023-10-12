#include "grafo/grafo.c"

int main()
{
    Grafo **matrizadj = cria_matriz();
    matrizadj = preenche_matriz(matrizadj);
    matrizadj = verifica_conexoes(matrizadj);
    printConexoes(matrizadj);
    char opc;
    do
    {
        menu();
        opc = le_opcao(OPCAO0,OPCAO8);
        switch (opc)
        {
        case OPCAO1:
            break;
        case OPCAO2:
            break;
        case OPCAO3:
            break;
        case OPCAO4:
            break;
        case OPCAO5:
            break;
        case OPCAO6:
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