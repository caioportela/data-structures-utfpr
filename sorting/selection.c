#include "foo.h"

void select_sort(int *sequence, int size) {
	int minimun;
	for(int i = 0; i < size-1; i++) {
		minimun = i;

		for(int j = i+1; j < n; i++)
			if(sequence[j] < sequence[minimun])
				minimun = j;

		swap(sequence, minimun, i);
	}
}
