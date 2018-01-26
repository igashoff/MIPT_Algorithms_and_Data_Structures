#ifndef TYPES_H
#define TYPES_H

#include<cstdio>
#include<cstdlib>
#include<ctime>

float Bubble(int *a, int N);
float InsertionSort(int *a, int N);
float MergeSort(int *a, int N);
void Merge(int *a, int *b, int L1, int L2);
float QuickSort(int *a, int p, int r);
int Partition(int *a, int p, int r);
float HeapSort(int*, int);
void MakeHeap(int*, int);
void SiftDown(int*, int, int);
float RadixSortLSD(int*, int);

#endif