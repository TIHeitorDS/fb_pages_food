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
    
    printf("%.0f\n", nodes[3].id);
    printf("%s\n", nodes[3].name);
    printf("%d\n", nodes[3].new_id);

    return 0;
}

Node *load_nodes()
{
    Node *node = (Node *)malloc(nodes_len * sizeof(Node));
    int index = 0;
    FILE *dataset = fopen("../fb-pages-food/fb-pages-food.nodes", "r");
    if (dataset == NULL)
    {
        printf("erro ao abrir o arquivo!\n");
        exit(1);
    }
    fseek(dataset, 14, SEEK_SET);

    while (!feof(dataset))
    {
        fscanf(dataset, "%f,%[^,],%d\n", &node[index].id, node[index].name, &node[index].new_id);
        index++;
    }
    
    fclose(dataset);

    return node;
}
