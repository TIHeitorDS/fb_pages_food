#include "grafo/grafo.c"

int main()
{
    Grafo **matrizadj = cria_matriz();
    matrizadj = preenche_matriz(matrizadj);
    matrizadj = verifica_conexoes(matrizadj);
    printConexoes(matrizadj);
    return 0;
}