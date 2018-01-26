#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include"Types.h"

int main() {

	int *a;
	FILE *f = fopen("mass.txt", "r");
	

	float t;
	int N;
	scanf("%d", &N);
	int check = 0;
	a = (int*)malloc(N*sizeof(int));

	for (int j = 0; j < N; j++) {
		fscanf(f, "%d", &a[j]);
	}
	check = 0;
	t = MergeSort(a, N);
	printf("MergeSort:\n");
	printf("%f\n", t);
	for (int j = 0; j < N - 1; j++) {
		if (a[j + 1] < a[j]) check++;
	}
	printf("%d\n", check);


	for (int j = 0; j < N; j++) {
		fscanf(f, "%d", &a[j]);
	}
	check = 0;
	t = RadixSortLSD(a, N);
	printf("RadixSort:\n");
	printf("%f\n", t);
	for (int j = 0; j < N - 1; j++) {
		if (a[j + 1] < a[j]) check++;
	}
	printf("%d\n", check);

	for (int j = 0; j < N; j++) {
		fscanf(f, "%d", &a[j]);
	}
	check = 0;
	t = QuickSort(a, 0, N - 1);
	printf("QuickSort:\n");
	printf("%f\n", t);
	for (int j = 0; j < N - 1; j++) {
		if (a[j + 1] < a[j]) check++;
	}
	printf("%d\n", check);

	for (int j = 0; j < N; j++) {
		fscanf(f, "%d", &a[j]);
	}
	check = 0;
	t = HeapSort(a, N);
	printf("HeapSort:\n");
	printf("%f\n", t);
	for (int j = 0; j < N - 1; j++) {
		if (a[j + 1] < a[j]) check++;
	}
	printf("%d\n", check);

	for (int j = 0; j < N; j++) {
		fscanf(f, "%d", &a[j]);
	}
	check = 0;
	t = InsertionSort(a, N);
	printf("InsertionSort:\n");
	printf("%f\n", t);
	for (int j = 0; j < N - 1; j++) {
		if (a[j + 1] < a[j]) check++;
	}
	printf("%d\n", check);


	for (int j = 0; j < N; j++) {
		fscanf(f, "%d", &a[j]);
	}
	check = 0;
	t = Bubble(a, N);
	printf("BubbleSort:\n");
	printf("%f\n", t);
	for (int j = 0; j < N - 1; j++) {
		if (a[j + 1] < a[j]) check++;
	}
	printf("%d\n", check);


	getchar();
	getchar();
	free(a);
	return 0;
}
	
