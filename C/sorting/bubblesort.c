#include "foo.h"

void bubble_sort(int *sequence, int size) {
	for(int i = 0; i < size-1; i++)
		for(int j = 0; j < size-i-1; j++)
			if(sequence[j] > sequence[j+1])
				swap(sequence, j, j+1);
}