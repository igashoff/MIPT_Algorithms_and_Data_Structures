#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include<cmath>
#define M 4               //мощность алфавита
#define ASC 97             //код первого символа
#define L 15
#define DIGIT 48

struct node {
	char ch;			   //символ
	int f;                 //частота
	char* code;			   //новый код
	node *right;
	node *left;
};

void sort(node*, int, int);
void huffman(node*, char**, int);
int putcode(FILE*, FILE*, char**);
void press(FILE*, FILE*);
void decode(FILE*, FILE*, node, int);

int main() {
	FILE *f = fopen("text.txt", "r");
	node *a = (node*)malloc((int)pow(2, M)*sizeof(node));
	char **b = (char**)malloc(M*sizeof(char*));

	for (int i = 0; i < M; i++) {
		b[i] = (char*)malloc(L*sizeof(char));
		for (int j = 0; j < L; j++) {
			b[i][j] = '=';
		}
	}

	for (int i = 0; i < M; i++) {
		a[i].f = 0;
		a[i].ch = i + ASC;
		a[i].left = NULL;
		a[i].right = NULL;
		a[i].code = (char*)malloc(L*sizeof(char));
		for (int j = 0; j < L; j++) {
			a[i].code[j] = '=';
		}
	}
	for (int i = M; i < (int)pow(2, M); i++) {
		a[i].left = NULL;
		a[i].right = NULL;
		//a[i].code = 0;
	}

	char c;
	while ((c = getc(f)) != EOF) {
		a[c - ASC].f++;
	}

	int i = 0;
	int N = M;
	for (i = 0; i < N - 1; i += 2) {
		sort(a, i, N);
		N++;
		a[N - 1].f = a[i].f + a[i + 1].f;
		a[N - 1].left = &a[i];
		a[N - 1].right = &a[i + 1];
		a[N - 1].code = (char*)malloc(L*sizeof(char));
		for (int j = 0; j < L; j++) {
			a[i].code[j] = '=';
		}
	}


	int k = 0;
	node root = a[i];
	printf("%d\n", root.f);
	root.left->code[k] = 0;
	root.right->code[k] = 1;
	huffman(root.left, b, k);
	huffman(root.right, b, k);

	/*printf("%d\n", root.f);
	for (int j = 0; j < N; j++) {
	printf("%c, %d\n", a[j].ch, a[j].f);
	}*/

	for (int i = 0; i < M; i++) {
		printf("%c ", (char)(i + ASC));
		int j = 0;
		while (b[i][j] != '=') {
			printf("%d", (int)b[i][j]);
			j++;
		}
		printf("\n");
	}

	int amount;
	FILE *fr = fopen("text.txt", "r");
	FILE *fw = fopen("coded.txt", "w");
	amount = putcode(fr, fw, b);
	fclose(fw);

	FILE *f1 = fopen("coded.txt", "r");
	FILE *f2 = fopen("small.txt", "w");
	press(f1, f2);
	fclose(f2);
	fclose(f1);

	FILE *frr = fopen("small.txt", "r");
	FILE *fww = fopen("decoded.txt", "w");
	decode(frr, fww, root, amount);
	fclose(fww);

	getchar();
	return 0;
}



void sort(node* a, int beg, int N) {
	for (int i = beg + 1; i < N; i++) {
		node cur = a[i];
		int j = i - 1;
		while (cur.f < a[j].f && j>-1) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = cur;
	}
}

void huffman(node* p, char** b, int k) {
	if (p->left != NULL || p->right != NULL) {
		k++;
		if (p->left != NULL) {
			for (int i = 0; i < k; i++) {
				p->left->code[i] = p->code[i];
			}
			p->left->code[k] = 0;
			huffman(p->left, b, k);
		}
		if (p->right != NULL) {
			for (int i = 0; i < k; i++) {
				p->right->code[i] = p->code[i];
			}
			p->right->code[k] = 1;
			huffman(p->right, b, k);
		}
	}
	else {
		int i = 0;
		//for (int i = 0; i < k; i++) {
		while (p->code[i] != '=') {
			b[(int)p->ch - ASC][i] = p->code[i];
			i++;
		}
	}
}

int putcode(FILE* fr, FILE* fw, char** b) {
	char c;
	int amount = 0;
	while ((c = getc(fr)) != EOF) {
		int i = 0;
		while (b[c - ASC][i] != '=') {
			amount++;
			fprintf(fw, "%d", b[c - ASC][i]);
			//printf("%d", b[c - ASC][i]);
			i++;
		}
	}
	return amount;
}

void press(FILE *fr, FILE *fw) {
	char c = 0;
	char read;
	int i = 0;
	while ((read = getc(fr)) != EOF) {
		c <<= 1;
		//printf("%c ", read);
		if (read == '1') { c++; }
		i++;
		//printf("%d\n", i);
		//printf("%d\n", (int)c);
		if (i == 8) {
			i = 0;
			putc(c, fw);
			printf("%c\n", c);
			c = 0;
		}
	}
	c <<= 8 - i;
	putc(c, fw);
}


void decode(FILE* fr, FILE* fw, node root, int amount) {
	char tmp;
	char c;
	int i = 7;
	int check = 0;
	node *p = &root;
	while ((c = getc(fr)) != EOF) {
		while (i >= 0) {
			if (check == amount) {
				return;
			}
			tmp = c;
			if ((tmp & (char)pow(2, i)) == 0) {
				p = p->left;
				check++;
			}
			else {
				p = p->right;
				check++;
			}
			i--;
			if (p->left == NULL && p->right == NULL) {
				fprintf(fw, "%c", p->ch);
				//printf("%c", p->ch);
				p = &root;
			}
		}
		i = 7;
	}
}