#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct node 
{
	int num;
	struct node* pNext;
	struct node* pPrev;
} Node;

typedef struct list 
{
	Node* head;
	Node* top;
	int size;
} List;

void clearTop(List* list) {
	Node* buf = list->top->pPrev;
	Node* currant = list->top;
	free(currant);
	list->size--;
	list->top = buf;
}

void clear(List* list) {
 
	while (list->size) {
		clearTop(list);
   }
}

void pushback(List* list, int num)
{
	
	Node* p = (Node*)malloc(sizeof(Node));
	p->num = num;
	p->pNext = NULL;
	p->pPrev = NULL;
	if (list->head == NULL) {
		list->head = list->top = p;	
	}
	else {
		p->pPrev = list->top;
		list->top->pNext = p;
		list->top = p;
	}
	list->size++;
	
}


void print(List list)
{
	

	Node* p = list.head;
	while (p) 
	{
		printf("%d", p->num);
		p = p->pNext;
	}
}

void printNorm(List list)
{


	Node* p = list.top;
	p = p->pPrev;
	while (p) {
		printf("%d", p->num);
		p = p->pPrev;
	}
}

void Calculate(List* list, int power) {
	Node* p = list->head;
	int s = 0, ostatok=0, main=0;
	for (int i = 0; i < power-1; i++) {

		while (p)
		{
			s = p->num;
			s = s * 3;
			ostatok = s % 10;
			if (ostatok + main >= 10) 
			{
				p->num = ostatok + main-10;
				main = s / 10+1;
			}
			else {
				p->num = ostatok + main;
				main = s / 10;
			}
			
			
			p = p->pNext;
		}
		p = list->head;

		if (list->top->num != 0) {
			pushback(list, 0);
		}
	}


	    
}


int main()
{
	List list = { NULL,NULL,0};
	pushback(&list, 3);
	pushback(&list, 0);
	Calculate(&list,100);
	printNorm(list);
	clear(&list);
}