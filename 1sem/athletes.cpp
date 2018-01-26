#define USE_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>

struct ath {
	int m;
	int s;
};

void sort(ath *list, int N);

int main() {
	int N;
	scanf("%d", &N);
	ath *list = (ath*)malloc(N*sizeof(ath));
	ath *tower = (ath*)malloc(N*sizeof(ath));
	for (int i = 0; i < N; i++) {
		printf("\n");
		scanf("%d %d", &list[i].m, &list[i].s);
	}
	sort(list, N);

	tower[0] = list[0];
	int cur_m = list[0].m;
	int k = 1;
	for (int i = 1; i < N; i++) {
		if (list[i].s >= cur_m) {
			tower[k] = list[i];
			cur_m += list[i].m;
			k++;
		}
	}

	printf("\nTower contains %d athletes:\n", k);
	printf("m   s\n");
	for (int i = 0; i < k; i++) {
		printf("%d %d\n", tower[i].m, tower[i].s);
	}
	free(list);
	free(tower);
	getchar();
	getchar();
	return 0;
}

void sort(ath *list, int N) {
	for (int i = 1; i < N; i++) {
		ath cur = list[i];
		int j = i - 1;
		while (cur.s < list[j].s) {
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = cur;
	}
}