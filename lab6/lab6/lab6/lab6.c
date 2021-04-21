#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct binaryNode
{
	int num;
	struct binaryNode* left_child;
	struct binaryNode* right_child;
	struct binaryNode* pNext;
	struct binaryNode* pPrev;
} BinaryNode;

typedef struct queue {
	BinaryNode* head;
	BinaryNode* top;
	int size;
}Queue;

void pushQueue(Queue* qu,BinaryNode* object)
{
	BinaryNode* currant = qu->head;
	if (currant == NULL) {
		qu->head = object;
		qu->top = object;
	}
	else {
		qu->top->pNext = object;
		object->pPrev = qu->top;
		qu->top = object;
	}
	qu->size++;
}

void printQueue(Queue* qu) {
	BinaryNode* currant = qu->head;
	while (currant->pNext) {
		printf("%d\n", currant->num);
		currant = currant->pNext;
	}
	printf("%d\n", currant->num);
}

BinaryNode* pop(Queue* qu) {
	if (qu->size == 1) {
		BinaryNode* object = qu->head;
		qu->head = NULL;
		qu->top = NULL;
		(qu->size)--;
		return object;
	}
	else
	{
		BinaryNode* object = qu->head;
		qu->head->pNext->pPrev = NULL;
		qu->head = qu->head->pNext;
		(qu->size)-=1;
		return object;
	}
}

BinaryNode *search(BinaryNode* currant,int index) {

	if (currant->num == index) {
		return currant;
	}

	if (currant->num > index) {
		if (currant->left_child) {
			return search(currant->left_child,index);
		}
		else {
			return NULL;
		}
	}

	if (currant->num < index) {
		if (currant->right_child) {
			return search(currant->right_child,index);
		}
		else {
			return NULL;
		}
	}
}

BinaryNode* searchPrev(BinaryNode* currant,int index, BinaryNode* Prev) {
	if (currant->num == index) {
		return Prev;
	}

	if (currant->num > index) {
		if (currant->left_child) {
			return searchPrev(currant->left_child,index, currant);
		}
		else {
			return NULL;
		}
	}

	if (currant->num < index) {
		if (currant->right_child) {
			return searchPrev(currant->right_child,index, currant);
		}
		else {
			return NULL;
		}
	}
}

int defineNode(BinaryNode* p) {
	if (p->left_child || p->right_child) {
		return 1;
	}
	else {
		return 0;
	}
}

void removeList(BinaryNode* currant, BinaryNode* pred) {
	if (pred->left_child == currant) {
		pred->left_child = NULL;
	}
	else if (pred->right_child == currant) {
		pred->right_child = NULL;
	}
}

BinaryNode* findMin(BinaryNode* currant)
{
	if (currant->left_child) {
		findMin(currant->left_child);
	}
	else {
		return currant;
	}

}

BinaryNode* findMax(BinaryNode* currant)
{
	if (currant->right_child) {
		findMax(currant->right_child);
	}
	else {
		return currant;
	}

}

void Remove(BinaryNode* root,int index) {
	
	int def;
	BinaryNode* currant;
	BinaryNode* pred = root;
	currant = search(root,index);
	if (currant != NULL&& currant!= root)
	{
		//printf("%d", currant->num);
		pred = searchPrev(root, index, pred);
		def = defineNode(currant);
		BinaryNode* currantMaxElementInSubTree;
		BinaryNode* predtMaxElementInSubTree;


		if (def == 0) {
			removeList(currant, pred);
			free(currant);
		}
		else if (def == 1) {
			if (currant->left_child != NULL) {
				currantMaxElementInSubTree = findMax(currant->left_child);
			}
			else {
				currantMaxElementInSubTree = findMin(currant->right_child);
			}
			predtMaxElementInSubTree = currantMaxElementInSubTree;
			predtMaxElementInSubTree = searchPrev(root, currantMaxElementInSubTree->num, predtMaxElementInSubTree);
			//cout << predtMaxElementInSubTree->str << endl;
			if (currant != predtMaxElementInSubTree) {
				if (pred->left_child == currant) {
					pred->left_child = currantMaxElementInSubTree;
				}
				else if (pred->right_child == currant) {
					pred->right_child = currantMaxElementInSubTree;
				}

				if (currant->left_child) {
					predtMaxElementInSubTree->right_child = currantMaxElementInSubTree->left_child;
					currantMaxElementInSubTree->left_child = currant->left_child;
					currantMaxElementInSubTree->right_child = currant->right_child;
				}
				else {
					currantMaxElementInSubTree->right_child = currant->right_child;
					predtMaxElementInSubTree->left_child = NULL;
				}

			}
			else {
				if (pred->left_child == currant) {
					pred->left_child = currantMaxElementInSubTree;
				}
				else if (pred->right_child == currant) {
					pred->right_child = currantMaxElementInSubTree;
				}
				//currantMaxElementInSubTree->right_child = currant->right_child;
				//currantMaxElementInSubTree->left_child = currant->left_child;
				if (currant->left_child)
				{
					currantMaxElementInSubTree->right_child = currant->right_child;
				}
			}
			free(currant);
		}
	}
}

void push(BinaryNode* currant,int num) {
	BinaryNode* cheak=search(currant, num);
	if (cheak == NULL) {
		if (currant->num > num) {
			if (currant->left_child) {
				push(currant->left_child, num);
			}
			else {
				BinaryNode* p = (BinaryNode*)malloc(sizeof(BinaryNode));
				p->left_child = NULL;
				p->right_child = NULL;
				p->num = num;
				currant->left_child = p;
			}
		}
		else {
			if (currant->right_child) {
				push(currant->right_child, num);
			}
			else {
				BinaryNode* p = (BinaryNode*)malloc(sizeof(BinaryNode));
				p->left_child = NULL;
				p->right_child = NULL;
				p->num = num;
				currant->right_child = p;
			}
		}
	}

}

void TraversePrev(BinaryNode* currant) {
	printf("%d\n", currant->num);

	if (currant->left_child) {
		TraversePrev(currant->left_child);
	}

	if (currant->right_child) {
		TraversePrev(currant->right_child);
	}
}

void TraverseObrat(BinaryNode* currant) {
	if (currant->left_child) {
		TraverseObrat(currant->left_child);
	}

	if (currant->right_child) {
		TraverseObrat(currant->right_child);
	}
	printf("%d\n", currant->num);
}

void TraverseSim(BinaryNode* currant) {
	if (currant->left_child) {
		TraverseSim(currant->left_child);
	}
	printf("%d\n", currant->num);
	if (currant->right_child) {
		TraverseSim(currant->right_child);
	}
}

void combine(BinaryNode* root1, BinaryNode* root2) {
	BinaryNode* buf;
	buf=search(root1, root2->num);
	if (buf == NULL) {
		push(root1, root2->num);
	}
	if (root2->left_child) {
		combine(root1, root2->left_child);
	}

	if (root2->right_child) {
		combine(root1, root2->right_child);
	}
}

void TraverseWidth(Queue* qu,BinaryNode* root1)
{
	//Queue *qu;
//	qu.pushBack(root1);
	pushQueue(qu, root1);
	BinaryNode* buf;

	while (qu->size != 0)
	{
		buf = pop(qu);
		//cout << buf->str << endl;
		printf("%d\n", buf->num);
		if (buf->left_child) {
			//qu.pushBack(buf->left_child);
			pushQueue(qu, buf->left_child);
		}

		if (buf->right_child) {
			//qu.pushBack(buf->right_child);
			pushQueue(qu, buf->right_child);
		}

	}

}

int main()
{
	
	BinaryNode root = { 80,NULL,NULL };
	push(&root, 35);
	push(&root, 18);
	push(&root, 43);
	push(&root, 120);
	push(&root, 90);
	push(&root, 150); 
	push(&root, 39);
	push(&root, 37);
	push(&root, 36);
	push(&root, 41);
	push(&root, 40);
	push(&root, 60);
	push(&root, 59);
	push(&root, 110);
	push(&root, 20);

	BinaryNode root2 = { 40,NULL,NULL };
	push(&root2, 30);
	push(&root2, 18);
	push(&root2, 35);
	push(&root2, 66);
	push(&root2, 56);
	push(&root2, 60);
	push(&root2, 73);
	push(&root2, 67);
	push(&root2, 999);
	
	Queue qu = { NULL,NULL,0 };
	printf("root1:\n");
	//Remove(&root, 110);
	TraversePrev(&root);
	//Remove(&root, 35);
	
	printf("\n\nroot2:\n");
	TraversePrev(&root2);

	printf("\n\nroot general:\n");
	combine(&root, &root2);
	TraversePrev(&root);

	//TraverseObrat(&root);
	//TraverseSim(&root);
	//TraverseWidth(&qu, &root);
	
}