#include "foo.h"

void insert_sort(int *sequence, int size) {
	int j;
	int temp;

	for(int i = 1; i < size; i++) {
		temp = sequence[i];
		j = i-1;

		while(j >= 0 && sequence[j] > temp) {
			sequence[j+1] = sequence[j--];
		}
		
		if(j+1 != i)
			sequence[j+1] = temp;
	}
}