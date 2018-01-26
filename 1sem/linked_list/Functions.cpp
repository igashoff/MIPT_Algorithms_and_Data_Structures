#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include "Types.h"
#include <cstdio>
#include <cstdlib>



void ClearScreen() {
	int n;
	for (n = 0; n < 10; n++)
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}



void input(int N, list *p) {
	ClearScreen();
	printf("Enter your elements\n");
	for (int i = 1; i <= N-1; i++) {                       //Считываем данные в цикле до предпоследнего элемента.
		scanf("%d", &p->data);                             
		p->next = (list*)malloc(sizeof(list));               
		p->next->prev = p;                                 //Указываем предыдущий элемент.      
		p = p->next;																			
	}
	scanf("%d", &p->data);								   //Последний считываем отдельно, после последнего элемента стоит NULL.			
	p->next = NULL;
}



list *delet(int N, list *p) {
	int x;
	int check;
	list *begin = p;
	list *support;
	ClearScreen();
	printf("Enter element that is to be deleted\n");
	scanf("%d", &x);

	while (p != NULL) {
		check = 0;
		if (p->next == NULL && p->prev == NULL) {											//Проверка на единственный элемент в списке
			printf("Only one element is left. You cant't continue this operation");
			check = 2;
			break;
		}
		else {
			if (p->data == x) {
				check = 1;
				if (p->next == NULL) {                         //Если это последний элемент, то 
					p->prev->next = NULL;					   //в next предыдущего элемента записываем NULL.
					break;                                     //Выходим из цикла.
				}
				else {
					if (p->prev == NULL) {					   //Если это первый элемент, то
						p->next->prev = NULL;                  //в prev следующего элемента записываем NULL.
						begin = p->next;					   //Начало списка смещается на один элемент вправо.
					}
					else {
						p->prev->next = p->next;               //Если это не первый и не последний элемент, то 
						p->next->prev = p->prev;			   //изменяем значения соседних указателей.
					}
				}
			}
			if (check == 1) {								   
				support = p;
				p = p->next;								   //Основной указатель передвигаем на один элемент вправо.
				free(support);								   //Особождаем память от "удаленного" элемента.
			}
			else {
				p = p->next;								   //Основной указатель передвигаем на один элемент вправо.
			}
		}
	}
	
	if (check != 2) {
		printf("\nCorrected list:\n");
		p = begin;
		while (p != NULL) {
			printf("%d ", p->data);							   //Выводим отредактированный список.
			p = p->next;
		}
	}

	return begin;
}



list *add(int N, list *p) {
	int x;
	int place;
	int element;
	list *begin = p;

	ClearScreen();
	printf("What element do you want to add?\n\n");
	scanf("%d", &x);
	printf("\n\nWhere do you want to add this element?\n\n");
	printf("<1>-Before-<1>\n");
	printf("<2>-After-<2>\n\n");
	scanf("%d", &place);
	
	switch (place) {

	case 1: {
		ClearScreen();
		printf("Before which one?\n");
		scanf("%d", &element);
		while (p != NULL) {
			if (p->data == element) {
				if (p->prev == NULL) {
					begin = (list*)malloc(sizeof(list));
					p->prev = begin;
					begin->data = x;
					begin->next = p;
					begin->prev = NULL;
				}
				else {
					list* support;
					support = (list*)malloc(sizeof(list));
					support->next = p->prev->next;
					support->prev = p->prev;
					support->data = x;
					p->prev->next = support;
					p->prev = support;
				}
			}
			p = p->next;
		}
		break;
	}
	case 2: {
		ClearScreen();
		printf("After which one?\n");
		scanf("%d", &element);
		while (p != NULL) {
			if (p->data == element) {
				if (p->next == NULL) {
					p->next = (list*)malloc(sizeof(list));
					p->next->prev = p;
					p->next->data = x;
					p->next->next = NULL;
				}
				else {
					list* support;
					support = (list*)malloc(sizeof(list));
					support->next = p->next;
					support->prev = p;
					support->data = x;
					p->next->prev = support;
					p->next = support;
				}
			}
			p = p->next;
		}
		break;
	}
	default: {
		printf("Invalid operation\n");
		break;
	}
	}
	p = begin;
	while (p != NULL) {
		printf("%d ", p->data);							   
		p = p->next;
	}
	return begin;
}



int summarize(int N, list *p) {
	int sum = 0;
	ClearScreen();
	while (p != NULL) {
		sum += p->data;
		p = p->next;
	}
	return sum;
}



char existence(int N, list *p) {
	int x;
	char check = 0;
	ClearScreen();
	printf("Which element do you want to check?\n");
	scanf("%d", &x);
	while (p != NULL) {
		if (p->data == x) {
			check++;
		}
		p = p->next;
	}
	return check;
}


#endif