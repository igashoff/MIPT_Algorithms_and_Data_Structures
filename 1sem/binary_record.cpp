#include <cstdio>
int printbytes(char* px);

int main() {
	int x;
	char* px;
	scanf("%d", &x);
	px = (char*)&x;
	for (int i =sizeof(int)-1; i > -1; i--) {
		printbytes(px+i);
	}
	getchar();
	getchar();
	return 0;
}

int printbytes(char* px){
	int i;
	
	for (i = 7; i > -1; i--){
		printf("%d", ((*px)&(1 << i))?1:0);
	}
	return 0;
}