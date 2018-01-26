#ifndef BUBBLESORT_CPP
#define BUBBLESORT_CPP

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"Types.h"

float Bubble(int *a, int N) {
	clock_t x = clock();

	for (int i = N - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (a[j + 1] < a[j]) {
				int k = a[j];
				a[j] = a[j + 1];
				a[j + 1] = k;
			}
		}
	}

	clock_t y = clock();
	float t = (float)(y - x) / CLOCKS_PER_SEC;
	return t;
}

#endif