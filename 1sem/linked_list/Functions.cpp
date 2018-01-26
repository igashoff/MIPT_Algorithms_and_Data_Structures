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
	for (int i = 1; i <= N-1; i++) {                       //��������� ������ � ����� �� �������������� ��������.
		scanf("%d", &p->data);                             
		p->next = (list*)malloc(sizeof(list));               
		p->next->prev = p;                                 //��������� ���������� �������.      
		p = p->next;																			
	}
	scanf("%d", &p->data);								   //��������� ��������� ��������, ����� ���������� �������� ����� NULL.			
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
		if (p->next == NULL && p->prev == NULL) {											//�������� �� ������������ ������� � ������
			printf("Only one element is left. You cant't continue this operation");
			check = 2;
			break;
		}
		else {
			if (p->data == x) {
				check = 1;
				if (p->next == NULL) {                         //���� ��� ��������� �������, �� 
					p->prev->next = NULL;					   //� next ����������� �������� ���������� NULL.
					break;                                     //������� �� �����.
				}
				else {
					if (p->prev == NULL) {					   //���� ��� ������ �������, ��
						p->next->prev = NULL;                  //� prev ���������� �������� ���������� NULL.
						begin = p->next;					   //������ ������ ��������� �� ���� ������� ������.
					}
					else {
						p->prev->next = p->next;               //���� ��� �� ������ � �� ��������� �������, �� 
						p->next->prev = p->prev;			   //�������� �������� �������� ����������.
					}
				}
			}
			if (check == 1) {								   
				support = p;
				p = p->next;								   //�������� ��������� ����������� �� ���� ������� ������.
				free(support);								   //���������� ������ �� "����������" ��������.
			}
			else {
				p = p->next;								   //�������� ��������� ����������� �� ���� ������� ������.
			}
		}
	}
	
	if (check != 2) {
		printf("\nCorrected list:\n");
		p = begin;
		while (p != NULL) {
			printf("%d ", p->data);							   //������� ����������������� ������.
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