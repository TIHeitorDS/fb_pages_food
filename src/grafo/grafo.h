typedef struct grafo Grafo;

typedef struct pages Pages;

typedef struct conexoes Conexoes;

Grafo **cria_matriz();

Grafo **preenche_matriz(Grafo **matriz);

void print_conexoes(Grafo **matriz);

Grafo **verifica_conexoes(Grafo **matriz);

int verifica_conexao_entre_paginas(Grafo **matriz);

void buscar_pagina_por_id(Grafo **matriz);

void exibe_quantidade_de_vertices(Grafo **matriz);

void exibe_quantidade_de_arestas(Grafo **matriz);

void pagina_com_mais_conexoes(Grafo **matriz);

void pagina_com_menos_conexoes(Grafo **matriz);

void paginas_isoladas(Grafo **matriz);

void calcular_e_exibir_media_graus(Grafo **matriz);
