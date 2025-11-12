#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct stack {
	int data[MAX_STACK_SIZE];
	int top;
} stack;

typedef enum Precedence {
	lparen,
	rparen,
	plus,
	minus,
	times,
	divide,
	mod,
	eos,
	operand
} Precedence;

int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

void initstack(stack *s)
{
	s->top = -1;
}

int isFull(stack *s)
{
	if (s->top == MAX_STACK_SIZE - 1) {
		return 1;
	}
	return 0;
}

int isEmpty(stack *s)
{
	if (s->top == -1) {
		return 1;
	}
	return 0;
}

int peek(stack *s)
{
	if (isEmpty(s)) {
		fprintf(stderr, "스택비어있음");
		exit(1);
	}
	return s->data[s->top];
}

void push(stack *s, int a)
{
	if (isFull(s)) {
		fprintf(stderr, "스택꽉참");
		exit(1);
	}
	s->data[++s->top] = a;
}

Precedence pop(stack *s)
{
	if (isEmpty(s)) {
		fprintf(stderr, "스택비어있음");
		exit(1);
	}
	return s->data[s->top--];
}

Precedence getToken(char *symbol, int *n, char *expr)
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(':
		return lparen;
		break;
	case ')':
		return rparen;
		break;
	case '+':
		return plus;
		break;
	case '-':
		return minus;
		break;
	case '*':
		return times;
		break;
	case '/':
		return divide;
		break;
	case '%':
		return mod;
		break;
	case '\0':
		return eos;
		break;
	default:
		return operand;
		break;
	}
}

void printToken(Precedence token, char *symbol)
{
	if (token == operand)
		printf("%c", *symbol);
	else if (token == plus)
		printf("+");
	else if (token == minus)
		printf("-");
	else if (token == times)
		printf("*");
	else if (token == divide)
		printf("/");
	else if (token == mod)
		printf("%%");
	else if (token == lparen)
		printf("(");
	else if (token == rparen)
		printf(")");
}

void toPostfix(char *expr)
{
	char symbol;
	int n = 0;
	stack s;
	initstack(&s);
	push(&s, eos);

	for (Precedence p = getToken(&symbol, &n, expr); p != eos; p = getToken(&symbol, &n, expr)) {
		if (p == operand)
			printToken(p, &symbol);
		else if (p == rparen) {
			while (peek(&s) != lparen) {
				printToken(pop(&s), 0);
			}
			pop(&s);
		} else {
			while (isp[peek(&s)] >= icp[p])
				printToken(pop(&s), 0);
			push(&s, p);
		}
	}

	while (peek(&s) != eos) {
		printToken(pop(&s), 0);
	}
	printf("\n");
}
