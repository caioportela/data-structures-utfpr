#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int row;
	int col;
	int val;
	struct node *right;
	struct node *down;
} Node;

typedef struct rhead {
	int index;
	Node *right;
	struct rhead *next;
} row_head;

typedef struct chead {
	int index;
	Node *down;
	struct chead *next;
} col_head;

typedef struct {
	int row_count;
	int col_count;
	row_head *first_row;
	col_head *first_col;
} Header;

typedef struct {
	Node *item;
	Header *sparse;
	row_head **row_item;
	col_head **col_item;
} Matrix;

Header *header_init(Matrix *M, int row, int col) {
	Header *new = (Header*)malloc(sizeof(Header));
	new->row_count = row;
	new->col_count = col;
	new->first_row = M->row_item[0];
	new->first_col = M->col_item[0];

	return new;
}

row_head **row_init(int row, int col) {
	row_head **row_item = (row_head**)malloc(sizeof(row_head*) * row);

	for(int i = 0; i < row; i++) {
		row_item[i] = (row_head*)malloc(sizeof(row_head));
		row_item[i]->right = NULL;
	}

	for(int i = 0; i < row-1; i++) {
		row_item[i]->index = i;
		row_item[i]->next = row_item[i+1];
	}

	return row_item;
}

col_head **col_init(int row, int col) {
	col_head **col_item = (col_head**)malloc(sizeof(col_head*) * col);
	
	for(int i = 0; i < col; i++) {
		col_item[i] = (col_head*)malloc(sizeof(col_head));
		col_item[i]->down = NULL;
	}

	for(int i = 0; i < col-1; i++) {
		col_item[i]->index = i;
		col_item[i]->next = col_item[i+1];
	}

	return col_item;	
}

Matrix *matrix_init(int row, int col) {
	Matrix *new = (Matrix*)malloc(sizeof(Matrix));

	new->row_item = row_init(row, col);
	new->col_item = col_init(row, col);

	new->sparse = header_init(new, row, col);

	return new;
}

int verify(Matrix *M, int row, int col, int value) {
	row_head *R = M->sparse->first_row;
	Node *N;
	
	for(int i = 0; i < row; i++)
		R = R->next;
	
	N = R->right;
	
	for(int i = 0; i < col; i++)
		if(N && N->col < col)
			N = N->right;
	
	if(N && N->col == col) {
		N->val = value;
		return 1;	
	}
	return 0;
}

Node *node_init(int row, int col, int value) {
	Node *new = (Node*)malloc(sizeof(Node));
	new->row = row;
	new->col = col;
	new->val = value;
	new->right = NULL;
	new->down = NULL;

	return new;
}

void insert(Matrix *M, int row, int col, int value) {
	row_head *R;
	col_head *C;
	Node *N1, *N2;
	Header *spr = M->sparse;
	
	M->item = node_init(row, col, value);
	
	if(verify(M, row, col, value))
		return;

	R = spr->first_row;

	for(int i = 0; i < row; i++)
		R = R->next;
	
	N1 = R->right;
	
	if(!N1 || col == 0 || N1->col > col) {
		R->right = M->item;
		M->item->right = N1;
	} else {
		while(N1 && N1->col < col) {
			N2 = N1;
			N1 = N1->right;
		}
		N2->right = M->item;
		M->item->right = N1;
	}

	C = spr->first_col;

	for(int i = 0; i < col; i++) 
		C = C->next;

	N1 = C->down;

	if(!N1 || row == 0 || N1->row > row) {
		C->down = M->item;
		M->item->down = N1;
	} else {
		while(N1 && N1->row < row) {
			N2 = N1;
			N1 = N1->down;
		}
		N2->down = M->item;
		M->item->down = N1;
	}
}

void display(Matrix *M, int m, int n) {
	row_head *R = M->sparse->first_row;
	Node *a;

	for(int i = 0; i < m; i++) {
		a = R->right;

		for(int j = 0; j < n; j++) {
			if(a && a->col == j) {
				printf("%2d ", a->val);
				a = a->right;
			} else {
				printf(" 0 ");
			}
		}
		printf("\n");
		R = R->next;
	}
	printf("\n");
}

Matrix *multiply(Matrix *A, Matrix *B, int m, int p, int n)  {
	Header *sprA = A->sparse;
	Header *sprB = B->sparse;
	row_head *R = sprA->first_row;
	col_head *C;
	Node *a, *b; 
	
	Matrix *new = matrix_init(m, n);
	int x = 0;
	int y;
	int sum;
	
	for(int i = 0; i < m; i++) {
		C = sprB->first_col;
		y = 0;
		
		for(int j = 0; j < n; j++) {
			a = R->right; 			
			b = C->down;
			sum = 0;

			for(int k = 0; k < p; k++) {
				if(a && b) {
					if(a->col == b->row) {
						sum += (a->val * b->val);
						a = a->right;
						b = b->down;
					} else if(a && b && a->col > b->row) { 
						b = b->down;
					} else {
						a = a->right;
					}
				}
			}

			if(sum != 0) {
				insert(new, x, y, sum);
			}
			C = C->next;
			y++;
		}
		R = R->next;
		x++;
	}

	return new;
}

int main() {
	int m, p, n;
	int nelem;
	int x, y, data;

	scanf("%d %d", &m, &p);
	Matrix *A = matrix_init(m, p);

	scanf("%d", &nelem);
	for(int i = 0; i < nelem; i++) {
		scanf("%d %d %d", &x, &y, &data);
		insert(A, x, y, data);
	}

	scanf("%d %d", &p, &n);
	Matrix *B = matrix_init(p, n);

	scanf("%d", &nelem);
	for(int i = 0; i < nelem; i++) {
		scanf("%d %d %d", &x, &y, &data);
		insert(B, x, y, data);
	}

	Matrix *C = multiply(A, B, m, p, n);

	display(A, m, p);
	display(B, p, n);
	display(C, m, n);

	return 0;
}