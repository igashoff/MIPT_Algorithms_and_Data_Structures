#include "Types.h"
#include <cstdio>
#include <cstdlib>

int main() {
	int N;
	int switchee;
	int sum;
	char but = 1;
	list *begin = NULL;
	list *p;

	printf("Enter your list.\n");
	printf("How many elements?\n");
	scanf("%d", &N);

	begin = (list*)malloc(sizeof(list));
	p = begin;																	//В переменный указатель записываем адрес первого элемента.
	p->prev = NULL;																//Перед первым элементом стоит NULL.
	input(N, p);

	while (but) {
		ClearScreen();

		printf("     MENU\n\n\n");
		printf("<1>--Delete an element--<1>\n\n");
		printf("<2>--Add an element--<2>\n\n");
		printf("<3>--Summarize all the elements--<3>\n\n");
		printf("<4>--Does such an element exist in my list?--<4>\n\n");
		printf("<0>--Exit--<0>\n\n");
		scanf("%d", &switchee);
		switch (switchee) {
		case 1: {
			p = begin = delet(N, p); 
			break;
		}
		case 2: {
			p = begin = add(N, p); 
			break;
		}
		case 3: {
			sum = summarize(N, p);
			printf("Sum is: %d\n", sum);
			break;
		}
		case 4: {
			if (existence(N, p)) {
				printf("EXISTS!\n");
			}
			else {
				printf("NOPE:(\n");
			}
			break;
		}
		case 0: { return 0; }
		default: {
			printf("Invalid operation\n"); 
			break;
		}
		}
		getchar();
		getchar();
		ClearScreen();
		printf("<Any key>--Return to menu--<Any key>\n\n");
		printf("<0>--Exit--<0>\n\n");
		scanf("%d", &but);
	}

	return 0;
}