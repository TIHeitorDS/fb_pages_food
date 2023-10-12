#include <stdio.h>
#include <stdlib.h>

#define nodes_len 620

typedef struct node
{
    float id;
    char name[100]; // Tamanho arbitrário para o nome, ajuste conforme necessário
    int new_id;
} Node;

Node *load_nodes();

int main()
{
    Node *nodes = load_nodes();
    
    printf("%.0f\n", nodes->id);
    printf("%s\n", nodes->name);
    printf("%d\n", nodes->new_id);

    free(nodes);
    return 0;
}

Node *load_nodes()
{
    Node *node = (Node *)malloc(sizeof(Node));
    FILE *dataset = fopen("../fb-pages-food/fb-pages-food.nodes", "r");
    if (dataset == NULL)
    {
        printf("erro ao abrir o arquivo!\n");
        exit(1);
    }

    fscanf(dataset, "%f,%[^,],%d", &node->id, node->name, &node->new_id);
    

    fclose(dataset);

    return node;
}
