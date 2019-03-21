#include <stdio.h>
#include <stdlib.h>

void swap(int* sequence, int x, int y) {
	if(x != y) {
		int a = sequence[x];
		sequence[x] = sequence[y];
		sequence[y] = a;
	}
}

int sorted(int *sequence, int size) {
	for(int i = 1; i < size; i++)
	 	if(sequence[i] < sequence[i-1])
	 		return 0;
	return 1;
}

void fill_sorted(int* sequence, int size) {
  	sequence[0] = rand () % 100;
  	for(int i = 1; i < size; i++)
		sequence[i] = sequence[i-1] + rand() % 100;
}

void fill_rand(int *sequence, int size) {
  	for(int i = 0; i < size; i++)
		sequence[i] = rand();
}

void nearly_sorted(int* sequence, int size) {
	fill_sorted(sequence, size);
	int n = size * 0.15;
	for(int i = 0; i < n; i++)
		swap(sequence, rand() % size-1, rand() % size-1);
}

void print(int *sequence, int size) {
  	for(int i = 0; i < size; i++)
		printf("%2d ", sequence[i]);
  	printf("\n");
}
