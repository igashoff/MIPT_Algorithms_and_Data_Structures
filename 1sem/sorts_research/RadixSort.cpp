#ifndef RADIXSORT_CPP
#define RADIXSORT_CPP

#include<cstdio> 
#include<cstdlib> 
#include<ctime>
#include"Types.h"


/*float LSD(int*, int);

int main() {
	int a[M];
	for (int i = 0; i < M; i++) {
		scanf("%d", &a[i]);
	}
	float t = LSD(a, M);
	for (int i = 0; i < M; i++) {
		printf("\n%d", a[i]);
	}
	getchar();
	getchar();
	return 0;
}*/

float RadixSortLSD(int *a, int N) {
	clock_t x = clock();

	int max = a[0];
	for (int i = 1; i < N; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	int k = 1;
	while (max /= 10) k++;
	//printf("\n%d\n", k);

	int* count = (int*)malloc(10 * sizeof(int));
	int* index = (int*)malloc(10 * sizeof(int));
	int* b = (int*)malloc(N * sizeof(int));
	int d = 10;
	for (int i = 0; i < k; i++, d *= 10) {
		for (int j = 0; j < 10; j++) {
			count[j] = 0;
			index[j] = 0;
		}
		for (int j = 0; j < N; j++) {
			count[(a[j] % d) / (d / 10)]++;
		}
		index[0] = 0;
		//	printf("index[%d]=%d, count[%d]=%d\n", 0, index[0], 0, count[0]);
		for (int j = 1; j < 10; j++) {
			index[j] = index[j - 1] + count[j - 1];
			//		printf("index[%d]=%d, count[%d]=%d\n", j, index[j], j, count[j]);
		}
		for (int j = 0; j < N; j++) {
			b[index[(a[j] % d) / (d / 10)]++] = a[j];
		}
		for (int j = 0; j < N; j++) {
			a[j] = b[j];
		}
	}

	free(count);
	free(index);
	free(b);

	clock_t y = clock();
	float t = (float)(y - x) / CLOCKS_PER_SEC;
	return t;
}

#endif