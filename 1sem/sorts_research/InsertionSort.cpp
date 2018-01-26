#ifndef INSERTIONSORT_CPP
#define INSERTIONSORT_CPP

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"Types.h"

float InsertionSort(int *a, int N) {
	clock_t x = clock();

	for (int i = 0; i < N; i++) {
		int tmp = a[i];
		int j = i - 1;
		while (tmp < a[j] && j>-1) {
			j--;
		}
		for (int k = i; k > j + 1; k--) {
			a[k] = a[k - 1];
		}
		a[j + 1] = tmp;
	}

	clock_t y = clock();
	float t = (float)(y - x) / CLOCKS_PER_SEC;
	return t;
}

#endif