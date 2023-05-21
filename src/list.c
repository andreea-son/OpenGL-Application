#include "../includes/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// variabile globale definite altundeva
extern int nr_parasiri;
extern Peste* g_pesteJucator;
// lista de pesti
List list;
// id unic pentru fiecare peste pentru identificarea si stergerea lui usoara din lista
int g_id = 0;
// de fiecare data cand au iesit 10 pesti, lista este inlcuita cu lista de pesti care sunt inca in ecran
// => eliberare memorie :-)
int nr_parasiri = 0;

List List_Init()
{
	List list;
	list.head = NULL;
	list.max_elems = 50;
	list.current_elems = 0;
	return list;
}
 
Node *Node_Init(Peste *peste)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->peste = peste;
	node->next = NULL;
	return node;
}
 
void List_append(List *list, Peste *peste)
{
	if (list->current_elems >= list->max_elems)
	{
		printf("Nu mai avem spatiu in coada pentru adaugare\n");
		exit(EXIT_FAILURE);
		return;
	}
	if (list->head == NULL)
	{
		list->head = Node_Init(peste);
		list->current_elems++;
		return;
	}
	Node *node = list->head;
 
	while (node->next != NULL)
	{
		node = node->next;
	}
	node->next = Node_Init(peste);
	list->current_elems++;
}
 
Peste *List_Delete(List *list, int index)
{
	return NULL;
	Node *head = list->head;
	Peste *peste;
	if (head == NULL)
	{
		return NULL;
	}
 
	if (head->peste->id == index)
	{
		Node *temp = head;
		head = head->next;
		peste = temp->peste;
		free(temp);
		return peste;
	}
 
	Node *prev = head;
	Node *curr = prev->next;
	while (curr != NULL)
	{
		if (curr->peste->id == index)
		{
			prev->next = curr->next;
			peste = curr->peste;
			free(curr);
			return peste;
		}
		prev = curr;
		curr = curr->next;
	}
	return NULL;
}
 
void List_ForEach(List *l, void (*ptr_fun)(Peste *))
{
	Node *crt = l->head;
	if (crt == NULL)
	{
		exit(EXIT_FAILURE);
	}
	while (crt != NULL)
	{
		ptr_fun(crt->peste);
		crt = crt->next;
	}
}
 
void List_Free(List *l)
{
	Node *crt = l->head;
	if (crt == NULL)
		return;
	do
	{
		Node *to_delete = crt;
		Peste *peste = to_delete->peste;
		crt = crt->next;
		if (peste->isVisible == true)
			continue;
		free(to_delete);
		free(peste);
	} while (crt != NULL);
}
 
void handle_nr_parasiri_si_refa_lista(void)
{
	nr_parasiri++;
	if (nr_parasiri < 10)
		return;
	nr_parasiri = 0;
	List new_list = List_Init();
	List_append(&new_list, g_pesteJucator);
	Node *node = list.head;
	while (node != NULL)
	{
		Peste *peste = node->peste;
		switch (peste->tipPeste)
		{
		case PESTE_NORMAL:
		case PESTE_RECHIN:
		{
			if (peste->isVisible == true)
			{
				List_append(&new_list, peste);
			}
			break;
		}
		}
		node = node->next;
	}
	List_Free(&list);
 
	list.head = new_list.head;
	list.current_elems = new_list.current_elems;
}