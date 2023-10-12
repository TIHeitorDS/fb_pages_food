#include "grafo/grafo.c"

int main()
{
    Grafo ** matrizadj = cria_matriz();
    matrizadj = preenche_matriz(matrizadj);
    
    return 0;
}