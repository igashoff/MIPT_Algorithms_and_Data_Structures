#include<cstdlib>
#include<cstdio>

int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	int **a = (int**)malloc(m*sizeof(int*));
	for (int i = 0; i < m; i++) {
		a[i] = (int*)malloc(n*sizeof(int));
	}
	for (int i = 0; i < n; i++) {
		a[0][i] = 1;
	}
	for (int i = 0; i < m; i++) {
		a[i][0] = 1;
	}
	a[0][0] = 0;
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			a[i][j] = a[i - 1][j] + a[i][j - 1];
		}
	}
	printf("\nIn total %d variants", a[m - 1][n - 1]);
	getchar();
	getchar();
	return 0;
}