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

int search(Hash tab, int key) {
	int h = hash(key);
	node *a = tab[h]->head;

	while(a != NULL) {
		if(a->content == key)
			return 1;
		a = a->next;
	}
	return 0;
}

void insert(Hash tab, int data) {
	node *in = new_node(data);
	int h = hash(data);

	if(!search(tab, data)) {
		in->next = tab[h]->head;
		tab[h]->head = in;
	}
}

Hash set_intersection(Hash A, Hash B) {
	Hash C = new_table();
	node *a;

	for(int i = 0; i < SIZE; i++) {
		a = A[i]->head;

		while(a != NULL) {
			if(search(B, a->content))
				insert(C, a->content);
			a = a->next;
		}
	}

	return C;
}

Hash set_union(Hash A, Hash B) {
	Hash C = new_table();
	node *set_node;

	for(int i = 0; i < SIZE; i++) {
		set_node = A[i]->head;
		
		while(set_node != NULL) {
			insert(C, set_node->content);
			set_node = set_node->next;
		}

		set_node = B[i]->head;
		
		while(set_node != NULL) {
			insert(C, set_node->content);
			set_node = set_node->next;
		}
	}

	return C;
}

void print(Hash tab) {
	for(int i = 0; i < SIZE; i++) {
		node *a = tab[i]->head;
		
		while(a != NULL) {
			printf("%d ", a->content);
			a = a->next;
		}
	}
	printf("\n");
}

int main() {
	Hash A = new_table();
	Hash B = new_table();
	int n, d;
	
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf(" %d", &d);
		insert(A, d);
	}

	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf(" %d", &d);
		insert(B, d);
	}

	Hash C = set_intersection(A, B);

	print(C);

	return 0;
}
