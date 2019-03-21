#include "foo.h"

void merge(int *sequence, int start, int mid, int end) {
	int temp[end-start+1];
	int a = start;
	int b = mid + 1;
	int k = 0;

	for(int i = start; i <= end; i++)
		if(a > mid)
			temp[k++] = sequence[b++];

		else if(b > end)
			temp[k++] = sequence[a++];
		
		else if(sequence[a] < sequence[b])
			temp[k++] = sequence[a++];
		
		else
			temp[k++] = sequence[b++];

	for(a = 0; a < k; a++)
		sequence[start++] = temp[a];
}

void mergesort(int *sequence, int start, int end) {
	if(start < end) {
		int mid = (start + end)/2;
		
		mergesort(sequence, start, mid);
		mergesort(sequence, mid+1, end);
		merge(sequence, start, mid, end);
	}
}
