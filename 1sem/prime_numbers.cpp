#include <cstdio>
#include <cstdlib>

int* foo(int n);

int main() {
	int N;
	int k = 0;
	int* p;
	scanf("%d", &N);
	p = foo(N);
	while (p[k]) {
		k++;
	}
	for (int i = 0; i < k; i++) {
		printf("%d\n", p[i]);
	}
	free(p);
	getchar();
	getchar();
	return 0;
}

int* foo(int n) {
	int i,j,m,simple;
	int k = 1;
	int* mass1 = (int*) malloc(sizeof(int)*n);
	for (i = 0, j = 2; i < n; i++, j++) {
		mass1[i] = j;
	}
	for (i = 1; i < n; i++) {
		simple = 0;
		for (j = i - 1; j >= 0; j--) {
			if ((mass1[i] % mass1[j]) == 0) { simple++; }
		}
		if (simple == 0) { k++; }
	}
	int* mass2 = (int*) malloc(sizeof(int)*(k+1));
	for (i = 0; i < k + 1; i++) { mass2[i] = 0; }
	mass2[0] = 3; 
	m = 1;
	for (i = 2; i < n; i++){
		simple = 0;
		for (j = i - 1; j >= 0; j--) {
			if ((mass1[i] % mass1[j]) == 0) { simple++; }
		}
		if (simple == 0) {
			mass2[m] = mass1[i];
			m++;
		}
	}
	free(mass1);
	return mass2;
}