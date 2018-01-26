#include<cstdio>
#include<cstdlib>

struct obj {
	int w;
	int p;
};

int max(int, int);

int main() {
	int wmax;
	int N;
	printf("max weight: ");
	scanf("%d", &wmax);
	printf("\namount of objects: ");
	scanf("%d", &N);
	printf("\navailable objects(weight, price):\n");
	obj *mass = (obj*)malloc((N + 1)*sizeof(obj));
	for (int i = 1; i < N+1; i++) {
		scanf("%d %d", &mass[i].w, &mass[i].p);
	}
	mass[0].w = mass[0].p = 0;
	int **a = (int**)malloc((N + 1)*sizeof(int*));
	for (int i = 0; i < N + 1; i++) {
		a[i] = (int*)malloc((wmax + 1)*sizeof(int));
	}
	for (int i = 0; i < wmax + 1; i++) {
		a[0][i] = 0;
	}
	for (int i = 0; i < N + 1; i++) {
		a[i][0] = 0;
	}
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < wmax + 1; j++) {
			if (j < mass[i].w) {
				a[i][j] = a[i][j - 1];
			}
			else {
				a[i][j] = max(a[i - 1][j], mass[i].p + a[i - 1][j - mass[i].w]);
			}
		}
	}
	printf("\nmax price: %d", a[N][wmax]);
	getchar();
	getchar();
	return 0;
}

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}