#ifndef _LIST_H_
#define _LIST_H_

#include "pesti.h"

/* INCEPUT DEFINITII LISTA */
typedef struct Node
{
	Peste *peste;
	struct Node *next;
} Node;
 
typedef struct List
{
	Node *head;
	int max_elems;
	int current_elems;
} List;
/* SFARSIT DEFINITII LISTA */

/* INCEPUT FUNCTII LISTA */
List List_Init(void);
Node *Node_Init(Peste *peste);
void List_append(List *list, Peste *peste);
Peste* List_Delete(List *list, int index);
void List_ForEach(List *list, void (*callbackPeste)(Peste*));
void List_Free(List *list);
void handle_nr_parasiri_si_refa_lista(void);
void do_something(Peste *peste);
/* SFARSIT FUNCTII LISTA */

#endif /* _LIST_H_ */