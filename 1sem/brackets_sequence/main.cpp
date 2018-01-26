#define USE_SECURE_NO_WARNINGS
#include<cstdlib>
#include<cstdio>

int main() {
	FILE *f1 = fopen("brackets.txt", "r");
	int c;
	int k = 0;
	while ((c = getc(f1)) != EOF) k++;
	fclose(f1);
	if (k % 2) {
		printf("incorrect");
		getchar();
		return 0;
	}
	//printf("1\n");
	k /= 2;
	int **a = (int**)malloc((k + 1)*sizeof(int*));
	for (int i = 0; i < k + 1; i++) {
		a[i] = (int*)malloc((k + 1)*sizeof(int));
	}
	for (int i = 0; i < k + 1; i++) {
		for (int j = 0; j < k + 1; j++) {
			a[i][j] = 0;
		}
	}
	FILE *f2 = fopen("brackets.txt", "r");
	int i = 0;
	int j = 0;
	while ((c = getc(f2)) != EOF) {
		if (c == '(') a[i][++j] = 1;
		else a[++i][j] = 1;
		if (i > j) {
			printf("incorrect");
			getchar();
			return 0;
		}
	}
	//printf("2\n");
	if (a[k][k]) printf("correct");
	else printf("incorrect");

	getchar();
	return 0;
}