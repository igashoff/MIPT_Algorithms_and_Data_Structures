#ifndef HEAPSORT_CPP
#define HEAPSORT_CPP

#include<cstdio> 
#include<cstdlib> 
#include<ctime>
#include"Types.h"


float HeapSort(int *a, int N) {
	clock_t x = clock();
	CLOCKS_PER_SEC;
	MakeHeap(a, N);
	while (N > 0) {
		int k = a[0];
		a[0] = a[N - 1];
		a[N - 1] = k;
		N--;
		SiftDown(a, 0, N);
	}

	clock_t y = clock();
	float t = (float)(y - x) / CLOCKS_PER_SEC;
	return t;
}

void MakeHeap(int *a, int N) {
	for (int i = N - 1; i >= 0; i--) {
		SiftDown(a, i, N);
	}
}

void SiftDown(int *a, int i, int N) {
	if (2 * i + 1 < N) {
		if (2 * i + 2 < N) {
			if (a[i] < a[2 * i + 1] || a[i] < a[2 * i + 2]) {
				int max;
				if (a[2 * i + 1] > a[2 * i + 2]) {
					max = a[2 * i + 1];
					a[2 * i + 1] = a[i];
					a[i] = max;
					SiftDown(a, 2 * i + 1, N);
				}
				else {
					max = a[2 * i + 2];
					a[2 * i + 2] = a[i];
					a[i] = max;
					SiftDown(a, 2 * i + 2, N);
				}
			}
		}
		else {
			if (a[i] < a[2 * i + 1]) {
				int max = a[2 * i + 1];
				a[2 * i + 1] = a[i];
				a[i] = max;
				SiftDown(a, 2 * i + 1, N);
			}
		}
	}
}



#endif