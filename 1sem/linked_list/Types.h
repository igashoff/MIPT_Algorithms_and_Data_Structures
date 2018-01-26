#ifndef TYPES_H
#define TYPES_H


#include <cstdio>
#include <cstdlib>

struct list {
	int data;
	list *next;
	list *prev;
};

void ClearScreen();

void input(int , list *);

list *delet(int, list *);

list* add(int, list *);

int summarize(int, list *);

char existence(int, list *);

#endif