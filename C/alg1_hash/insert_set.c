#include <stdio.h>
#include <stdlib.h>

#define SIZE 1021

typedef struct _node {
	int content;
	struct _node *next;
} node;

typedef struct {
	node *head;
} list;

typedef list** Hash;

node *new_node(int value) {
	node *n = (node*) malloc(sizeof(node));
	n->content = value;
	n->next = NULL;

	return n;
}

list *new_list() {
	list *fwd_list = (list *) malloc(sizeof(list));
	fwd_list->head = NULL;

	return fwd_list;
}

Hash new_table() {
	Hash t = malloc(sizeof(Hash)*SIZE);
	for(int i = 0; i < SIZE; i++)
		t[i] = new_list();

	return t;
}

int hash(int key) {
	return key % SIZE;
}

node *search(Hash tab, int key) {
	int h = hash(key);
	node *a = tab[h]->head;

	while(a != NULL) {
		if(a->content == key)
			return a;
		a = a->next;
	}
	return NULL;
}

void insert(Hash tab, int data) {
	node *in = new_node(data);
	int h = hash(data);

	if(search(tab, data) == NULL) {
		in->next = tab[h]->head;
		tab[h]->head = in;
	}
}

void print(Hash tab) {
	for(int i = 0; i < SIZE; i++) {
		node *a = tab[i]->head;
		
		while(a != NULL) {
			printf("%d ", a->content);
			a = a->next;
		}
	}
}

int main() {
	Hash t = new_table();
	int n = 0;
	scanf("%d", &n);
	int d;

	for(int i = 0; i < n; i++) {
		scanf(" %d", &d);
		insert(t, d);
	}

	print(t);

	return 0;
}
