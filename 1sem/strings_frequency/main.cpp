#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define S 10

struct string {
	char *str;
	int amount;
};

char strcm(char*, char*);

int main() {
	FILE *f = fopen("strings.txt", "r");
	char *s = (char*)malloc(S * sizeof(char));
	string *p = (string*)malloc(sizeof(string));
	p[0].str = (char*)malloc(S * sizeof(char));
	fgets(p[0].str, S, f);
	p[0].amount = 1;
	int N = 1;

	for (int i = 0; i < S; i++) {
		s[i] = 0;
	}

	while (fgets(s, S, f) != NULL) {
		int check = 1;
		for (int i = 0; i < N; i++) {
			//char cmp = strcm(s, p[i].str);
			if (strcm(s, p[i].str) == 0) {
				p[i].amount++;
				check = 0;
				break;
			}
		}
		if (check) {
			N++;
			p = (string*)realloc(p, N*sizeof(string));
			p[N - 1].str = (char*)malloc(S * sizeof(char));
			int j = 0;
			while (s[j] != '\n') {
				p[N - 1].str[j] = s[j];
				j++;
			}
			p[N - 1].amount = 1;
		}
			/*for (int i = 0; i < N; i++) {
				printf("%s\n", p[i].str);
				printf("am: %d\n", p[i].amount);
			}*/
			for (int i = 0; i < S; i++) {
				s[i] = 0;
			}
	}

	string max;
	//max.str = (char*)malloc(S * sizeof(char));
	max.amount = -1;
	for (int i = 0; i < N; i++) {
		if (p[i].amount > max.amount) {
			max.str = p[i].str;
			max.amount = p[i].amount;
		}
	}
	printf("Most frequent is ''%s''. Appears %d times.\n", max.str, max.amount);
	getchar();
	return 0;
}


char strcm(char* s1, char* s2) {
	int i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i]) {
		i++;
	}
	char cmp = s1[i] - s2[i];
	return cmp;
}