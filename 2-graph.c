#include <stdio.h>
#include <stdlib.h>

#define INF 9999
#define NO 0
#define YES 1

/*-----------------------------Estrutura da Fila-----------------------------*/

typedef struct _element {
	int content;
	struct _element *next;
} element;

typedef struct {
	element *head;
	int size;
} queue;

element *element_init(int value) {
	/*Aloca memória para um elemento na fila.*/
	element *n = (element*)malloc(sizeof(element));
	n->content = value;
	n->next = NULL;
	
	return n;
}

queue *queue_init() {
	/*Aloca memória para uma fila.*/
	queue *list = (queue*)malloc(sizeof(queue));
	list->head = NULL;
	list->size = 0;
	
	return list;
}

void _free(queue *list) {
	/*Libera a memória alocada para a fila.*/
	element *a;
	
	while(list->head != NULL) {
		a = list->head;
		list->head = a->next;
		free(a);
	}
	free(list);
}

void enqueue(queue *list, int value) {
	/*Adiciona elementos na fila.*/
	element *in = element_init(value);
	
	if(list->head == NULL) {
		list->head = in;
	} else {
		element *a = list->head;

		while(a->next != NULL)
			a = a->next;
		a->next = in;
	}
	list->size++;
}

int find_in(queue *list, int value) {
	/*Informa se já existe na fila o valor recebido.*/
	element *a = list->head;
	while(a != NULL) {
		if(a->content == value)
			return 1;
		a = a->next;
	}
	return 0;
}

int dequeue(queue *list) {
	/*Remove elementos da fila.*/
	element *a = list->head;
	list->head = a->next;
	int value = a->content;
	free(a);
	
	return value;
}

void remove_elem(queue *list, int value) {
	/*Remove um determinado elemento da lista.*/
	if(list->head == NULL)
		return;

	element *a = list->head;
	if(a->content == value) {
		list->head = a->next;
		free(a);
		return;
	}

	while(a->next != NULL && a->next->content != value)
		a = a->next;
	
	element *temp = a->next;
	a->next = temp->next;
	free(temp);
	return;
}

/*----------------------------Estrutura do Grafo-----------------------------*/

typedef struct _edge {
	/*Estrutura que armazena a identificação dos vértices adjacentes, peso das
	arestas e endereço para o próximo vértice.*/ 
	int vertice;
	int weight;
	struct _edge *next;
} Edge;

typedef struct _node {
	/*Estrutura que armazena a identificação, grau e vizinhança de um vértice*/
	int vertice;
	int degree;
	Edge *list;
	struct _node *next;
} Node;

typedef struct {
	/*Estrutura que armazena um ponteiro para o início da representação em
	lista de adjacências e a quantidade de vértices no grafo.*/
	Node *start;
	int vertice;
} Graph;

Graph *graph_init() {
	/*Aloca memória para a estrutura do grafo.*/
	Graph *new = (Graph*)malloc(sizeof(Graph));
	new->start = NULL;
	new->vertice = 0;

	return new;
}

Node *node_init(int vert) {
	/*Aloca memória para a estrutura dos vértices no grafo; definindo a 
	identificação do vértice com o inteiro recebido como parâmetro e 
	definindo o grau do vértice como zero.*/
	Node *new = (Node*)malloc(sizeof(Node));
	new->vertice = vert;
	new->degree = 0;
	new->list = NULL;
	new->next = NULL;

	return new;
}

Edge *edge_init(int vert, int w) {
	/*Aloca memória para a estrutura das arestas; recebe a identificação
	e peso da aresta por parâmetro.*/
	Edge* new = (Edge*)malloc(sizeof(Edge));
	new->vertice = vert;
	new->weight = w;
	new->next = NULL;

	return new;
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int node_verifier(Graph *G, int vert) {
	/*Verifica se existe no grafo o vértice recebido.*/ 
	Node *a = G->start;

	while(a != NULL) {
		if(a->vertice == vert)
			return 1;
		a = a->next;
	}
	return 0;
}

int edge_verifier(Node *point, int vert) {
	/*Verifica se existe no vértice a aresta recebida.*/
	Edge *a = point->list;

	while(a != NULL) {
		if(a->vertice == vert)
			return 1;
		a = a->next;
	}
	return 0;
}

void node_insert(Graph *G, int vert) {
	/*Insere na estrutura do grafo um vértice recebido como inteiro*/
	Node *in = node_init(vert);

	if(node_verifier(G, vert))
		/*verfica se já existe o nó indicado;*/
		return;

	if(G->start == NULL)
		/*Se o grafo estiver vazio, insere no início da lista;*/
		G->start = in;
	else	
		/*Senão, faz verificação e insere o vértice ordenadamente no grafo.*/
		if(vert < G->start->vertice) {
			in->next = G->start;
			G->start = in;
		} else {
			Node *a = G->start;

			while(a->next != NULL && a->next->vertice < vert)
				a = a->next;

			in->next = a->next;
			a->next = in;
		}
	G->vertice++;
}

void create_edge(Node *point, int vert, int w) {
	/*Adiciona um elemento na lista de adjacências do vértice recebido.*/
	Edge *adj = edge_init(vert, w);

	if(edge_verifier(point, vert))
		return;

	if(point->list == NULL)
		/*Se a lista de adjacências estiver vazia, insere no início da lista;*/
		point->list = adj;
	else
		/*Senão, faz verificação e insere o elemento ordenadamente na lista.*/
		if(vert < point->list->vertice) {
			adj->next = point->list;
			point->list = adj;
		} else {
			Edge *a = point->list;

			while(a->next != NULL && a->next->vertice < vert)
				a = a->next;

			adj->next = a->next;
			a->next = adj;
		}
}

void edge_insert(Graph *G, int vert1, int vert2, int w) {
	/*Insere uma aresta com peso entre dois vértices.*/
	Node *a = G->start;

	if(w <= 0)
		/*Verifica se o peso recebido é não-negativo;*/
		return;

	if(vert1 == vert2)
		/*Verifica se os vértices recebidos são o mesmo;*/
		return;

	if(!node_verifier(G, vert1))
		/*Verifica se existe um dos vértices informado para inserir aresta;*/
		return;

	if(!node_verifier(G, vert2))
		/*Verifica se existe um dos vértices informado para inserir aresta;*/
		return;

	if(vert2 < vert1)
		/*Ordena os parâmetros recebidos, de forma a percorrer a estrutura do
		grafo somente uma vez;*/
		swap(&vert1, &vert2);

	while(a != NULL && a->vertice != vert1)
		a = a->next;
	create_edge(a, vert2, w); //Adiciona na lista de adjacências.
	a->degree++;

	while(a != NULL && a->vertice != vert2)
		a = a->next;
	create_edge(a, vert1, w); //Adiciona na lista de adjacências.
	a->degree++;
}

void erase_edge(Node *point, int vert) {
	/*Remove da lista de adjacências de um vértice específico.*/
	Edge *a = point->list;
	
	if(a == NULL)
		return;
	
	if(a->vertice == vert) {
		point->list = a->next;
		free(a);
	} else {
		while(a->next != NULL && a->next->vertice != vert)
			a = a->next;

		if(a != NULL) {
			Edge *temp = a->next;
			if(temp != NULL) {
				a->next = temp->next;
				free(temp);
			}
		}
	}
}

void remove_edge(Graph *G, int vert1, int vert2) {
	/*Remove uma aresta entre dois vértices dados.*/
	Node *a = G->start;

	if(!node_verifier(G, vert1))
		/*Verifica se existe o vértice dado.*/
		return;

	if(!node_verifier(G, vert2))
		/*Verifica se existe o vértice dado.*/
		return;

	if(vert2 < vert1)
		/*Ordena os vértices dados a fim de otimizar a operação.*/
		swap(&vert1, &vert2);

	while(a != NULL && a->vertice != vert1) 
		a = a->next;
	erase_edge(a, vert2); //Remove da lista de adjacências.
	a->degree--;

	while(a != NULL && a->vertice != vert2)
		a = a->next;
	erase_edge(a, vert1); //Remove da lista de adjacências.
	a->degree--;
}

void node_remove(Graph *G, int vert) {
	/*Remove o vértice da estrutura do Grafo.*/
	if(G->start == NULL)
		return;
	Node *a = G->start;

	while(a != NULL) {
		/*Remove todas as ocorrências do vértice em listas de adjacências.*/
		remove_edge(G, a->vertice, vert);
		a = a->next;
	}

	a = G->start;
	if(a->vertice == vert) {
		G->start = a->next;
		free(a);
		G->vertice--;
		return;
	}

	while(a->next != NULL && a->next->vertice != vert)
		a = a->next;

	if(a != NULL) {
		/*Remove o vértice do grafo.*/
		Node *temp = a->next;
		if(temp != NULL) {
			a->next = temp->next;
			G->vertice--;
			free(temp);
		}
	}
}

void vertex_degree(Graph *G, int vert) {
	/*Informa o grau do vertice.*/
	Node *a = G->start;

	while(a != NULL && a->vertice != vert)
		a = a->next;
	
	if(a != NULL)
		printf("\nGrau do vertice %d: %d\n", vert, a->degree);	
}

void adjacency_matrix(Graph *G) {
	/*Converte o grafo de sua representação de lista de adjacências para
	Matriz de Adjacências.*/
	int n = G->vertice + 1;
	int adj[n][n];
	Node *a = G->start;

	if(G->start == NULL)
		return;

	adj[0][0] = 0;
	for(int i = 1; i < n; i++) {
			adj[0][i] = a->vertice;
			adj[i][0] = a->vertice;
			a = a->next;
	}

	a = G->start;
	for(int i = 1; i < n; i++) {
		for(int j = 1; j < n; j++) {
			adj[i][j] = edge_verifier(a, adj[0][j]);
		}
		a = a->next;
	}

	printf("\nMatriz de Adjacencias:\n");
	printf("   ");
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == 0 && j == 0)
				continue;
			printf(" %2d", adj[i][j]);	
		}
		printf("\n");
	}
}

void visit(Graph *G, int x, int *visited, int *p, int *d, int *f, int *time) {
	/* G -> é um ponteiro para o grafo;
	x -> é o vértice;
	visited -> é o vetor de cor;
	p -> é o vetor de antecedentes;
	d -> é o vetor de tempo de descobrimento;
	f -> é o vetor de tempo de finalização;
	time -> é o tempo de operação.*/

	Node *a = G->start;
	int i = 0;
	while(a != NULL && a->vertice != x) {
		/*Identifica o índice do vértice.*/
		a = a->next;
		i++;
	}
	visited[i] = YES;
	d[i] = ++*time;

	Edge *adj = a->list;
	int j = 0;
	a = G->start;
	while(adj != NULL) {
		while(a != NULL && a->vertice != adj->vertice) {
			/*Identifica o índice do vértice.*/
			a = a->next;
			j++;
		}

		if(!visited[j]) {
			/*Se o vértice não foi visitado, atualiza o antecedente e executa
			a função recursivamente*/
			p[j] = x;
			visit(G, adj->vertice, visited, p, d, f, time);
		}
		adj = adj->next;
	}

	f[i] = ++*time;
}

void depth_first_search(Graph *G) {
	/*Realiza a Busca em Profundidade a partir de um vértice recebido.*/
	int n = G->vertice;
	int visited[n], parent[n];
	int d[n], f[n];
	int time = 0;

	for(int i = 0; i < n; i++) {
		/*Inicializa os vetores de vértice visitado e antecedentes.*/
		visited[i] = NO;
		parent[i] = -1;
	}

	int i = 0;
	Node *a = G->start;
	while(a != NULL) {
		if(!visited[i])
			/*Se o vértice ainda não foi visitado, executa a função visit().*/
			visit(G, a->vertice, visited, parent, d, f, &time);
		a = a->next;
		i++;
	}

	i = 0;
	a = G->start;
	printf("\nCaminhamento em Profundidade:\n");
	while(a != NULL) {
		/*Imprime o resultado da busca em largura no formato:
		vértice: descobrimento|finalização -> pai*/
		printf("%2d: %2d|%2d -> %2d\n", a->vertice, d[i], f[i], parent[i]);
		a = a->next;
		i++;
	}
	printf("\n");
}

typedef struct {
	int vertice;
	int key;
	int parent;
} Attribute;

Attribute *attribute_init(Graph *G, int root) {
	/*Aloca memória e inicializa valores para uma estrutura de atributos
	auxiliar.*/
	Attribute *new = (Attribute*)malloc(sizeof(Attribute) * G->vertice);
	
	Node *a = G->start;
	for(int i = 0; a != NULL; i++) {
		new[i].vertice = a->vertice;
		new[i].key = INF;
		new[i].parent = -1;

		if(a->vertice == root)
			new[i].key = 0;
		a = a->next;
	}

	return new;
}

void breadth_first_search(Graph *G, int source) {
	/*Realiza a busca em largura a partir de um vértice recebido.*/
	if(G->start == NULL)
		/*Se o grafo estiver vazio, encerra a função.*/
		return;

	if(!node_verifier(G, source))
		/*Verifica se existe o vértice recebido.*/
		return;

	Attribute *attr = attribute_init(G, source);
	queue *S = queue_init(); //Fila S indica se o vértice já foi visitado.
	queue *Q = queue_init();
	enqueue(S, source);
	enqueue(Q, source); //Adiciona na fila o vértice raiz.

	Node *a;
	while(Q->head != NULL) {
		a = G->start;
		int x = dequeue(Q);
		
		int i = 0;
		while(a != NULL && a->vertice != x) {
			/*Identifica o índice do vértice que saiu da fila.*/
			a = a->next;
			i++;
		}
		
		Edge *adj = a->list;
		int j = 0;
		a = G->start;
		while(adj != NULL) {
			while(a != NULL && a->vertice != adj->vertice) {
				/*Identifica o índice do vértice recebido.*/
				a = a->next;
				j++;
			}

			if(!find_in(S, attr[j].vertice)) {
				/*Se o vértice ainda não foi visitado, altera a distância,
				define um antecedente, marca como visitado e adiciona o
				elemento na fila.*/
				enqueue(S, attr[j].vertice);
				attr[j].key = attr[i].key + 1;
				attr[j].parent = attr[i].vertice;
				enqueue(Q, adj->vertice);
			}
			adj = adj->next;
		}
	}
	
	printf("\nCaminhamento em Largura:\n");
	for(int i = 0; i < G->vertice; i++)
		printf("%2d: %2d|%2d\n", attr[i].vertice, attr[i].parent, attr[i].key);
	printf("\n");

	_free(Q); //Libera memória da fila.
	_free(S);
	free(attr);
}

int connectivity(Graph *G) {
	/*Informa se o grafo é conexo. Utiliza a função de Busca em Profundidade
	para obter o resultado.*/

	if(G->start == NULL)
		return 0;

	/*--------Busca em Profundidade--------*/
	int n = G->vertice;
	int visited[n], parent[n];
	int d[n], f[n];
	int time = 0;

	for(int i = 0; i < n; i++) {
		/*Inicializa os vetores de vértice visitado e antecedentes.*/
		visited[i] = NO;
		parent[i] = -1;
	}

	int i = 0;
	Node *a = G->start;
	while(a != NULL) {
		if(!visited[i])
			/*Se o vértice ainda não foi visitado, executa a função visit().*/
			visit(G, a->vertice, visited, parent, d, f, &time);
		a = a->next;
		i++;
	}
	/*-----------------------------------------------------------------*/

	for(int i = 1; i < n; i++)
		if(parent[i] == -1) {
			/*Se houver mais de um vértice sem antecedente, o grafo é
			desconexo, e a função se encerra.*/
			return 0;
		}
	return 1;
}

int extract_min(queue *list, Attribute *atr, int n) {
	/*Extrai o menor elemento da fila de prioridade.*/
	int i;

	for(i = 0; !find_in(list, atr[i].vertice); i++);
	Attribute min = atr[i++];

	for(i; i < n; i++) {
		if(find_in(list, atr[i].vertice) && atr[i].key < min.key)
			min = atr[i];
	}

	remove_elem(list, min.vertice);
	return min.vertice;
}

void shortest_path(Graph *G, int root) {
	/*Executa o Algoritmo de Djikstra para o Caminho Mínimo.*/
	if(G->start == NULL)
		/*Se o grafo for vazio, encerra a execução.*/
		return;

	if(!node_verifier(G, root))
		/*Verifica se existe o vértice recebido.*/
		return;

	Attribute *attr = attribute_init(G, root); //Estrutura auxiliar
	queue *Q = queue_init();

	Node *a = G->start;
	while(a != NULL) {
		/*Adiciona na fila todos os vértices do grafo.*/
		enqueue(Q, a->vertice);
		a = a->next;
	}

	while(Q->head != NULL) {
		int min = extract_min(Q, attr, G->vertice); //Mínimo da fila

		a = G->start;
		int i = 0;
		while(a != NULL && a->vertice != min) {
			/*Identifica o índice do valor extraído da fila.*/
			a = a->next;
			i++;
		}

		Edge *adj = a->list;
		int j = 0;
		a = G->start;
		while(adj != NULL) {
			while(a != NULL && a->vertice != adj->vertice) {
				a = a->next;
				j++;
			}

			if(attr[j].key > attr[i].key + adj->weight){
				attr[j].key = attr[i].key + adj->weight;
				attr[j].parent = attr[i].vertice;
			}
			adj = adj->next;
		}
	}

	printf("\nCaminho Minimo:\n");
	for(int i = 0; i < G->vertice; i++) {
		/*Imprime no formato:
		Vértice: pai|key*/
		printf("%2d: %2d|%2d\n", attr[i].vertice, attr[i].parent, attr[i].key);
	}
	printf("\n");

	free(attr);
	_free(Q);
}

void spanning_tree(Graph *G, int root) {
	/*Executa o Algoritmo de Prim para Árvore Geradora Mínima*/
	if(G->start == NULL)
		/*Se o grafo é vazio, encerra a execução.*/
		return;

	if(!connectivity(G))
		/*Não tem solução se o grafo for desconexo.*/
		return;

	if(!node_verifier(G, root))
		/*Verifica se existe o vértice recebido.*/
		return;

	Attribute *attr = attribute_init(G, root); //Estrutura auxiliar
	queue *Q = queue_init();

	Node *a = G->start;
	while(a != NULL) {
		/*Adiciona na fila todos os vértices do grafo.*/
		enqueue(Q, a->vertice);
		a = a->next;
	}

	while(Q->head != NULL) {
		int min = extract_min(Q, attr, G->vertice); //Mínimo da fila

		a = G->start;
		while(a != NULL && a->vertice != min)
			a = a->next;
		int p = a->vertice; //Armazena o vértice

		Edge *adj = a->list;
		int i = 0;
		a = G->start;
		while(adj != NULL) {
			while(a != NULL && a->vertice != adj->vertice) {
				/*Identifica o índice do vértice*/
				a = a->next;
				i++;
			}

			if(find_in(Q, adj->vertice) && adj->weight < attr[i].key) {
				attr[i].key = adj->weight;
				attr[i].parent = p;
			}
			adj = adj->next;
		}
	}

	printf("\nArvore Geradora Minima:\n");
	for(int i = 0; i < G->vertice; i++) {
		printf("%2d: %2d|%2d\n", attr[i].vertice, attr[i].parent, attr[i].key);
	}
	printf("\n");

	free(attr);
	_free(Q);
}

void print(Graph *G) {
	/*Imprime o grafo, na forma: vertice -> vizinho|peso*/
	Node *a = G->start;

	printf("\n");
	while(a != NULL) {
		printf("%2d", a->vertice);
		Edge *adj = a->list;

		while(adj != NULL) {
			printf(" -> %2d|%2d", adj->vertice, adj->weight);
			adj = adj->next;
		}
		printf("\n");
		a = a->next;
	}
	printf("\n");
}

void free_graph(Graph *G) {
	/*Libera a memória alocada para a estrutura do Grafo*/
	while(G->start != NULL) {
	Node *point = G->start;

		while(point->list != NULL) {
			Edge *adj = point->list;
			point->list = adj->next;
			free(adj);
		}
	
		G->start = point->next;
		free(point);
	}
}

int main() {
	int menu, vert1, vert2, w;
	Graph *new = graph_init();

/*
	//--Grafo para teste--
	node_insert(new, 4);
	node_insert(new, 10);
	node_insert(new, 1);
	node_insert(new, 2);
	node_insert(new, 5);
	node_insert(new, 7);
	node_insert(new, 3);
	node_insert(new, 9);
	node_insert(new, 6);
	node_insert(new, 8);

	edge_insert(new, 1, 2, 7);
	edge_insert(new, 1, 4, 9);
	edge_insert(new, 1, 6, 8);
	edge_insert(new, 1, 8, 9);
	edge_insert(new, 1, 10, 8);
	edge_insert(new, 2, 3, 4);
	edge_insert(new, 2, 4, 5);
	edge_insert(new, 2, 9, 9);
	edge_insert(new, 2, 10, 9);
	edge_insert(new, 3, 4, 1);
	edge_insert(new, 5, 1, 10);
	edge_insert(new, 5, 3, 4);
	edge_insert(new, 5, 4, 3);
	edge_insert(new, 5, 6, 18);
	edge_insert(new, 6, 8, 9);
	edge_insert(new, 6, 7, 9);
	edge_insert(new, 7, 8, 3);
	edge_insert(new, 7, 9, 6);
	edge_insert(new, 8, 9, 4);
	edge_insert(new, 8, 10, 2);
	edge_insert(new, 9, 10, 2);
*/

	do {
		printf(" 1. Inserir vertice\n");
		printf(" 2. Inserir aresta\n");
		printf(" 3. Remover vertice\n");
		printf(" 4. Remover aresta\n");
		printf(" 5. Visualizar grafo\n");
		printf(" 6. Informar grau do vertice\n");
		printf(" 7. Verificar se grafo conexo\n");
		printf(" 8. Converter para Matriz de Adjacencias\n");
		printf(" 9. Caminhamento em amplitude\n");
		printf("10. Caminhamento em profundidade\n");
		printf("11. Caminho minimo\n");
		printf("12. Arvore Geradora Minima\n");
		printf(" 0. Sair\n");
		printf("Selecionar: ");
		scanf("%d", &menu);

		if(menu == 1) {
			printf("Insira o vertice: ");
			scanf("%d", &vert1);
			node_insert(new, vert1);
		} else if(menu == 2) {
			printf("Insira os vertices adjacentes (separados por espaco): ");
			scanf("%d %d", &vert1, &vert2);
			printf("Insira o peso da aresta: ");
			scanf("%d", &w);
			edge_insert(new, vert1, vert2, w);
		} else if(menu == 3) {
			printf("Vertice a ser removido: ");
			scanf("%d", &vert1);
			node_remove(new, vert1);
		} else if(menu == 4) {
			printf("Vertices a serem removidos (separados por espaco): ");
			scanf("%d %d", &vert1, &vert2);
			remove_edge(new, vert1, vert2);
		} else if(menu == 5) {
			print(new);
		} else if(menu == 6) {
			printf("Insira o vertice: ");
			scanf("%d", &vert1);
			vertex_degree(new, vert1);
		} else if(menu == 7) {
			if(new->start != NULL)
				if(connectivity(new))
					printf("Grafo conexo.\n");
				else
					printf("Grafo desconexo.\n");
		} else if(menu == 8) {
			adjacency_matrix(new);
		} else if(menu == 9) {
			printf("Informe o vertice raiz: ");
			scanf("%d", &vert1);
			breadth_first_search(new, vert1);
		} else if(menu == 10) {
			depth_first_search(new);
		} else if(menu == 11) {
			printf("Informe o vertice raiz: ");
			scanf("%d", &vert1);
			shortest_path(new, vert1);
		} else if(menu == 12) {
			printf("Informe o vertice raiz: ");
			scanf("%d", &vert1);
			spanning_tree(new, vert1);
		}
		printf("\n");
	} while(menu != 0);

	free_graph(new);

	return 0;
}