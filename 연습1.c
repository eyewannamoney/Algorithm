#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodelink;
typedef struct node {
	int coef;
	int exp;
	nodelink *next;
} node;

nodelink createnode(int coef, int exp)
{
	nodelink a = malloc(sizeof(node));
	a->coef = coef;
	a->exp = exp;
	a->next = NULL;

	return a;
}

nodelink multipoly(nodelink a, nodelink b)
{
	nodelink result = NULL;
	nodelink p = a;
	nodelink q = b;

	for (; p != NULL; p->next) {
		for (; q != NULL; q->next) {
			int c = p->coef * q->coef;
			int e = p->exp + q->exp;

			nodelink temp = result;
			nodelink prev = NULL;
			while (temp != NULL && temp->exp > e) {
				prev = temp;
				temp = temp->next;
			}
			if (temp != NULL && temp->exp == e) {
				temp->coef += c;
			} else {
				nodelink newnode = createnode(c, e);
				if (prev == NULL) {
					newnode->next = result;
					result = newnode;
				} else {
					newnode->next = temp; // prev->next 대신 temp로 대입해도되지?
					prev->next = newnode;
				}
			}
		}
	}
	return result;
}
