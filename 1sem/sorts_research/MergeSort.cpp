#ifndef MERGESORT_CPP
#define MERGESORT_CPP

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"Types.h"

float MergeSort(int *a, int N) {
	clock_t x = clock();

	if (N > 1) {
		int L1 = N / 2;
		int L2 = N - L1;
		int *b = &a[L1];
		float k;
		k = MergeSort(a, L1);
		k = MergeSort(b, L2);
		Merge(a, b, L1, L2);
	}

	clock_t y = clock();
	float t = (float)(y - x) / CLOCKS_PER_SEC;
	return t;
}

void Merge(int *a, int *b, int L1, int L2) {
	int *c = (int*)malloc((L1 + L2)*sizeof(int));
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < L1 && j < L2) {
		if (a[i] < b[j]) {
			c[k++] = a[i++];
		}
		else {
			c[k++] = b[j++];
		}
	}
		if (i == L1) {
			while (k < (L1 + L2)) {
				c[k++] = b[j++];
			}
		}
		else {
			while (k < (L1 + L2)) {
				c[k++] = a[i++];
			}
		}
	for (int i = 0; i < (L1 + L2); i++) {
		a[i] = c[i];
	}
	free(c);
}

#endif