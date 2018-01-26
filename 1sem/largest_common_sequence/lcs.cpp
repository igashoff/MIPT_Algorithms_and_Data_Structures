#include<cstdio>
#include<cstdlib>

struct elem {
	int steps;
	int prev_i;
	int prev_j;
};

elem max(elem, elem, int, int);

int main() {
	FILE *f = fopen("seq.txt", "r");

	int m;
	int n;
	char c;
	scanf("%d", &m);
	char *a = (char*)malloc((m + 1)*sizeof(char));
	a[0] = '\0';
	int i = 1;
	while ((c = getc(f)) != '\n' && c != EOF) {
		a[i++] = c;
		//printf("%c\n", a[i++]);
	}
	scanf("%d", &n);
	char *b = (char*)malloc((n + 1)*sizeof(char));
	b[0] = '\0';
	int j = 1;
	while ((c = getc(f)) != '\n' && c != EOF) {
		b[j++] = c;
	}

	/*for (int i = 0; i < m + 1; i++) {
		printf("%c\n", a[i]);
	}*/


	elem **mat = (elem**)malloc((m + 1)*sizeof(elem*));
	for (int i = 0; i < m + 1; i++) {
		mat[i] = (elem*)malloc((n + 1)*sizeof(elem));
	}

	//mat[0][0].steps = 0;
	//mat[0][0].prev_i = mat[0][0].prev_j = -1;

	for (int i = 0; i < m + 1; i++) {
		mat[i][0].steps = 0;
		mat[i][0].prev_i = mat[i][0].prev_j = -1;
	}
	for (int i = 0; i < n + 1; i++) {
		mat[0][i].steps = 0;
		mat[0][i].prev_i = mat[0][i].prev_j = -1;
	}

	for (int i = 1; i < m + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			if (a[i] == b[j]) {
				mat[i][j].steps = mat[i - 1][j - 1].steps + 1;
				mat[i][j].prev_i = i - 1;
				mat[i][j].prev_j = j - 1;
			}
			else {
				mat[i][j] = max(mat[i - 1][j], mat[i][j - 1], i, j);
			}
		}
	}
	printf("lenght = %d\n", mat[m][n].steps);

	printf("LCS: ");

	char *s = (char*)malloc((mat[m][n].steps)*sizeof(char));
	elem tmp = mat[m][n];
	i = m;
	j = n;
	int k = mat[m][n].steps - 1;

	while (i != 0 && j != 0) {
		if (a[i] == b[j]) {
			s[k--] = a[i];
		}
		i = tmp.prev_i;
		j = tmp.prev_j;
		tmp = mat[i][j];
	}
	for (int i = 0; i < mat[m][n].steps; i++) {
		printf("%c", s[i]);
	}

	fclose(f);
	getchar();
	getchar();
	return 0;
}

elem max(elem a, elem b, int i, int j) {
	elem c;
	if (a.steps > b.steps) {
		c.steps = a.steps;
		c.prev_i = i - 1;
		c.prev_j = j;
	}
	else {
		c.steps = b.steps;
		c.prev_i = i;
		c.prev_j = j - 1;
	}
	return c;
}