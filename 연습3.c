#include <stdio.h>
#include <stdlib.h>
#define MAX_ROWS 7
#define MAX_COLS 7
#define MAX_STACK_SIZE (MAX_ROWS) * (MAX_COLS)
#define START_ROW 1
#define START_COL 1
#define EXIT_ROW 5
#define EXIT_COL 5

typedef struct element {
	int row;
	int col;
	int dir;
} element;

typedef struct stack {
	element data[MAX_STACK_SIZE];
	int top;
} stack;

typedef struct offset {
	int dr;
	int dc;
} offset;

void initstack(stack *s)
{
	s->top = -1;
}

void push(stack *s, element a)
{
	if (s->top == MAX_STACK_SIZE - 1)
		exit(1);
	s->data[++s->top] = a;
}

element pop(stack *s)
{
	if (s->top == -1)
		exit(1);
	return s->data[s->top--];
}

offset move8[8] = {
	{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

int maze[MAX_ROWS][MAX_COLS] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 1, 0, 1},
	{1, 1, 1, 0, 0, 1, 1},
	{1, 1, 1, 0, 1, 1, 1},
	{1, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1}};

int mark[MAX_ROWS][MAX_COLS];

void print_path(stack *s)
{
	for (int i = 0; i <= s->top; i++) {
		printf("row: %d, col: %d\n", s->data[i].row, s->data[i].col);
	}
	printf("row: %d, col: %d\n", EXIT_ROW, EXIT_COL);
}

void path(stack *s)
{
	for (int r = 0; r < MAX_ROWS; r++) {
		for (int c = 0; c < MAX_COLS; c++) {
			mark[r][c] = 0;
		}
	}
	int found = 0;
	initstack(s);
	element a;
	a.row = START_ROW;
	a.col = START_COL;
	a.dir = 0;
	mark[a.row][a.col] = 1;
	push(s, a);
	while (!found && s->top != -1) {
		element position = pop(s);
		a.row = position.row;
		a.col = position.col;
		a.dir = position.dir;

		while (a.dir < 8 && !found) {
			int nextrow = a.row + move8[a.dir].dr;
			int nextcol = a.col + move8[a.dir].dc;

			if (nextrow == EXIT_ROW && nextcol == EXIT_COL) {
				found = 1;
				push(s, a);
			} else if (mark[nextrow][nextcol] == 0 && maze[nextrow][nextcol] == 0) {
				push(s, (element){a.row, a.col, a.dir + 1});
				a.row = nextrow;
				a.col = nextcol;
				mark[nextrow][nextcol] = 1;
				a.dir = 0;
			} else {
				a.dir++;
			}
		}
	}

	if (found)
		print_path(s);
	else
		printf("경로를 찾지 못했습니다");
}

int main()
{
	stack s;
	path(&s);

	return 0;
}
