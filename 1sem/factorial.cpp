#include <cstdio>

int main(){
	int x;
	int fact = 1;
	scanf("%d", &x);
	for (int i = 1; i < x + 1; i++) {
		fact *= i;
		while ((fact % 10) == 0) {
			fact = fact / 10;
		}
		fact = fact % 10;
	}
	printf("%d\n", fact);
	getchar();
	getchar();
	return 0;
}