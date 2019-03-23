#include <stdio.h>
#include <stdlib.h>
#include "foo.h"

int partition(int *sequence, int start, int end) {
	int index = start + rand() % (end - start +1);
	int pi = sequence[index];
	swap(sequence, index, end);

	pi = sequence[end];
	int i = start - 1;

	for(int j = start; j < end; j++)
		if(sequence[j] <= pi)
			swap(sequence, ++i, j);

	swap(sequence, ++i, end);

	return i;
}

void quicksort(int *sequence, int first, int last) {
	if(first < last) {
		int pi = partition(sequence, first, last);

		quicksort(sequence, first, pi-1);
		quicksort(sequence, pi+1, last);
	}
}
