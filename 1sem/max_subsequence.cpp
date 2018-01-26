#define CRT_SECURE_NO_WARNINGS
#include<cstdlib>
#include<cstdio>

struct tree {
	int val;
	int num;
	int cur;
	tree* prev;
	tree *left;
	tree *right;
};

tree* search(tree*, int);
void insert(tree*, tree*);
tree* max(tree*);
void maxsubseq(tree*, tree*, int);

int main() {
	int N;
	scanf("%d", &N);
	int *a = (int*)malloc(N*sizeof(int));
	tree *b = (tree*)malloc(N*sizeof(tree));
	for (int i = 0; i < N; i++) {
		scanf("%d", &a[i]);
	}

	b[0].num = 1;
	b[0].prev = NULL;
	b[0].cur = 0;
	b[0].left = b[0].right = NULL;
	b[0].val = a[0];

	for (int i = 1; i < N; i++) {
		tree* tmp = search(&b[0], a[i]);
		if (tmp) {
			if (tmp->num + 1 > 1) {
				b[i].num = 1 + tmp->num;
				b[i].cur = i;
				b[i].prev = tmp;
				b[i].left = b[i].right = NULL;
				b[i].val = a[i];
			}
			else {
				b[i].num = 1;
				b[i].cur = i;
				b[i].prev = NULL;
				b[i].left = b[i].right = NULL;
				b[i].val = a[i];
			}
		}
		else {
			b[i].num = 1;
			b[i].cur = i;
			b[i].prev = NULL;
			b[i].left = b[i].right = NULL;
			b[i].val = a[i];
		}
		insert(&b[0], &b[i]);
	}

	tree *x = max(&b[0]);
	tree *maxsubsequence = (tree*)malloc(x->num*sizeof(tree));
	printf("max amount: %d\n", x->num);
	printf("elements:\n");
	maxsubseq(maxsubsequence, x, x->num);
	for (int i = 0; i < x->num; i++) {
		printf("%d ", maxsubsequence[i].val);
	}
	getchar();
	getchar();
	return 0;
}

tree* search(tree* p, int x) {
	tree *max = NULL;
	if (p->right == NULL && x <= p->val) {
		return NULL;
	}
	if (x > p->val) {
		max = p;
	}

	while (p->right) {
		if (p->right->val < x) {
			max = p->right;
		}
		p = p->right;
	}
	return max;
}

void insert(tree* p, tree* cur) {
	while (true) {
		if (cur->num >= p->num) {
			if (p->right == NULL) {
				p->right = cur;
				break;
			}
			else {
				p = p->right;
			}
		}
		else {
			if (p->left == NULL) {
				p->left = cur;
				break;
			}
			else {
				p = p->left;
			}
		}
	}
}

tree* max(tree* p) {
	while (p->right) {
		p = p->right;
	}
	return p;
}

void maxsubseq(tree* a, tree* p, int N) {
	a[p->num - 1] = *p;
	int i = p->num - 1;
	while (p->prev) {
		p = p->prev;
		i--;
		a[i] = *p;
	}
}