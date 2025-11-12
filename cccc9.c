#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* ---- 스레드 이진 트리 노드 ---- */
typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
	short int leftThread; // TRUE면 leftChild는 전임자 스레드
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread; // TRUE면 rightChild는 후속자 스레드
} threadedTree;

/* ---- 유틸: 헤더/노드 생성 ---- */
threadedPointer createHead()
{
	threadedPointer head = (threadedPointer)malloc(sizeof(threadedTree));
	head->data = 0;
	head->leftThread = TRUE;
	head->rightThread = TRUE;
	head->leftChild = head;	 // 초기엔 공트리
	head->rightChild = head; // 순회 종료용
	return head;
}
threadedPointer createNode(char c)
{
	threadedPointer p = (threadedPointer)malloc(sizeof(threadedTree));
	p->data = c;
	p->leftThread = TRUE; // 처음엔 양쪽 다 스레드로 시작
	p->rightThread = TRUE;
	p->leftChild = NULL;
	p->rightChild = NULL;
	return p;
}
/* 루트 연결 (헤더와 루트 연결 세팅) */
void attachRoot(threadedPointer head, threadedPointer root)
{
	root->leftChild = head;
	root->rightChild = head;
	head->leftChild = root;
	head->leftThread = FALSE; // 이제 왼쪽은 진짜 자식(루트)
}

/* ---- 후속자 / 순회 ---- */
threadedPointer insucc(threadedPointer x)
{
	threadedPointer t = x->rightChild;
	if (!x->rightThread)
		while (!t->leftThread)
			t = t->leftChild;
	return t;
}
void tinorder(threadedPointer head)
{
	threadedPointer t = head;
	for (;;) {
		t = insucc(t);
		if (t == head)
			break;
		printf("%c ", t->data);
	}
}

/* ---- 삽입: 오른쪽/왼쪽 ---- */
void insertRight(threadedPointer s, threadedPointer r)
{
	threadedPointer temp;
	/* 1) r의 기본 방향을 s의 기존 오른쪽과 동일하게 */
	r->rightChild = s->rightChild;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->leftThread = TRUE;
	/* 2) s의 오른쪽 자식으로 r을 달기 */
	s->rightChild = r;
	s->rightThread = FALSE;
	/* 3) 스레드 보정: r의 후속자의 왼쪽 스레드를 r로 */
	if (!r->rightThread) {
		temp = insucc(r);
		temp->leftChild = r;
	}
}
void insertLeft(threadedPointer s, threadedPointer l)
{
	threadedPointer temp;
	/* 1) l의 기본 방향을 s의 기존 왼쪽과 동일하게 */
	l->leftChild = s->leftChild;
	l->leftThread = s->leftThread;
	l->rightChild = s;
	l->rightThread = TRUE;
	/* 2) s의 왼쪽 자식으로 l을 달기 */
	s->leftChild = l;
	s->leftThread = FALSE;
	/* 3) 스레드 보정: l의 왼쪽 서브트리의 맨오른쪽 노드 rightThread를 l로 */
	if (!l->leftThread) {
		temp = l->leftChild;
		while (!temp->rightThread)
			temp = temp->rightChild;
		temp->rightChild = l;
	}
}

/* ---- (옵션) 중위열 비교: 두 트리가 같은 중위열인지 간단 체크 ---- */
int equalInorder(threadedPointer h1, threadedPointer h2)
{
	threadedPointer a = h1, b = h2;
	for (;;) {
		a = insucc(a);
		b = insucc(b);
		if (a == h1 && b == h2)
			return TRUE; // 둘 다 끝
		if ((a == h1) ^ (b == h2))
			return FALSE; // 한쪽만 끝
		if (a->data != b->data)
			return FALSE;
	}
}

/* ---- 사용 예시 ---- */
int main(void)
{
	/* 1) 헤더+루트 준비 */
	threadedPointer head = createHead();
	threadedPointer root = createNode('A');
	attachRoot(head, root);

	/* 2) 왼/오 삽입 사용 예시 */
	threadedPointer nB = createNode('B');
	threadedPointer nC = createNode('C');
	threadedPointer nD = createNode('D');
	threadedPointer nE = createNode('E');

	insertLeft(root, nB);  // A의 왼쪽에 B
	insertRight(root, nC); // A의 오른쪽에 C
	insertLeft(nC, nD);	   // C의 왼쪽에 D
	insertRight(nC, nE);   // C의 오른쪽에 E

	/* 3) 중위 순회 출력 */
	printf("Inorder: ");
	tinorder(head); // 기대: B A D C E
	printf("\n");

	/* 4) 비교용 트리 하나 더 만들어 같은 순서인지 검사 */
	threadedPointer h2 = createHead();
	threadedPointer r2 = createNode('A');
	attachRoot(h2, r2);
	insertLeft(r2, createNode('B'));
	insertRight(r2, createNode('C'));
	insertLeft(r2->rightChild, createNode('D'));
	insertRight(r2->rightChild, createNode('E'));

	printf("두 트리 중위열 동일? %s\n",
		   equalInorder(head, h2) ? "YES" : "NO");

	return 0;
}