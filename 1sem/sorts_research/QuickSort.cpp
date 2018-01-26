#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"Types.h"

float QuickSort(int *a, int p, int r) {
	clock_t x = clock();

	if (p < r) {
		int q = Partition(a, p, r);
		float b;
		b = QuickSort(a, p, q);
		b = QuickSort(a, q + 1, r);
	}

	clock_t y = clock();
	float t = (float)(y - x) / CLOCKS_PER_SEC;
	return t;
}

int Partition(int *a, int p, int r) {
	int mid = a[p];
	int i = p - 1;
	int j = r + 1;
	while (true) {
		do { j--; } while (a[j] > mid);
		do { i++; } while (a[i] < mid);
		if (i < j) {
			int k = a[i];
			a[i] = a[j];
			a[j] = k;
		}
		else {
			return j;
		}
	}
}


#endif