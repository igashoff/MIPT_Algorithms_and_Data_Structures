#include<cstdio>
#include<cstdlib>

struct student {
	char* name;
	int mark;
};

int compare_by_name(void*, void*);
int compare_by_mark(void*, void*);
void sort(void*, int, int, int(*)(void*, void*));

int main() {
	FILE *fr = fopen("data.txt", "r");
	FILE *fw = fopen("results.txt", "w");
	int N = 0;
	int choice;
	char* string = (char*)malloc(17 * sizeof(char));
	char c;

	while (fgets(string, 17, fr)) N++;
	student *a = (student*)malloc(N*sizeof(student));
	for (int i = 0; i < N; i++) {
		a[i].name = (char*)malloc(17 * sizeof(char));
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 17; j++) {
			a[i].name[j] = 0;
		}
	}

	for (int i = 0; i < N; i++) {
		int j = -1;
		do {
			j++;
			fscanf(fr, "%c", &string[j]);
		} while (string[j] != '\n');
		for (int k = 0; k < j-2; k++) a[i].name[k] = string[k];
		/*int j = 0;
		do {
			c = fgetc(fr);
			a[i].name[j] = c;
			j++;
		} while (c != ' ');*/
		a[i].mark = (int)string[j-1];
	}

	printf("Type of sort\n");
	printf("Name - 1\n");
	printf("Mark - 2\n");
	scanf("%d", &choice);

	switch (choice) {
	case 1: sort(a, sizeof(student), N, compare_by_name);
	case 2: sort(a, sizeof(student), N, compare_by_mark);
	default: printf("incorrect\n");
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 17; j++) {
			fputc(a[i].name[j], fw);
		}
		fprintf(fw, "%d\n", a[i].mark);
	}
	fclose(fw);
	printf("\nOKAY");
	free(a);
	getchar();
	getchar();
	return 0;
}

int compare_by_name(void *a, void *b) {
	student* sa = (student*)a;
	student* sb = (student*)b;
	int i = 0;
	while (sa->name[i++] == sb->name[i++] && sa->name[i++] && sb->name[i++]);
	return(sa->name[i] - sb->name[i]);
}

int compare_by_mark(void *a, void *b) {
	student* sa = (student*)a;
	student* sb = (student*)b;
	return (sa->mark - sb->mark);
}

void sort(void* a, int size, int len, int(*compare)(void* a, void* b)) {
	student *sa = (student*) a;
	for (int i = 1; i < len; i++) {
		int k = i-1;
		char* string=(char*)malloc(17*sizeof(char));
		//char string1[17];
		int m;
		//int m1;
		while (compare(&sa[i], &sa[k--]) < 0 && k-- > -1);
		string = sa[i].name;
		m = sa[i].mark;
		for (int j = i; j > k; j--) {
			sa[j].name = sa[j - 1].name;
			sa[j].mark = sa[j - 1].mark;
		}
		sa[k].name = string;
		sa[k].mark = m;
	}
	a = (void*)sa;
}