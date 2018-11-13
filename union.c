#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

	char *X; // 계산할 문자열의 읽는 위치
	char Oper(const char *o);
	double Term();
	double MultiplyDivide();
	double PlusMinus();

typedef struct Node {
	int val;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	int size;
} DLL;

Node *newnode(int n)
{
	Node *temp = (Node *)malloc(sizeof(Node));
	temp->val = n;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

DLL *newDLL() {
	DLL *temp = (DLL *)malloc(sizeof(DLL));
	temp->head = NULL;
	temp->size = 0;
	return temp;
}

void append(DLL *list, Node *newnode) {
	struct Node* temp = list->head;
	struct Node* newNode = newnode;
	if (list->head == NULL) {
		list->head = newNode;
		list->size++;
		return;
	}
	while (temp->next != NULL) {
		temp = temp->next;
	}
	list->size++;
	temp->next = newNode;
	newNode->prev = temp;
}
//----------------------------------------------------------------------------------------------------
void skipSpace()
{
	while (isspace(*X)) X++;
}// 연산자

char Oper(const char *op)
{ // 연산자 읽기
	skipSpace();
	if (*X && strchr(op, *X))
		return *X++;// 원하는 연산자들에 속하면 연산자를 되돌리고 return 0; 
		// 그렇지 않으면 0 
}// 항목 : 수치, (수식)의 값을 읽음
double Term()
{
	double n = 0; // 수치 읽기
	skipSpace();
	if (isdigit(*X) || *X == '.')
	{ // 수치 
		char N[32]; // 읽어들인 숫자
		int dot;
		char *x = N;
		do
		{
			dot = (*X == '.');
			*x++ = *X++;
		}

		while (isdigit(*X) || (!dot && *X == '.'));
		*x = '\0'; n = atof(N);
	}

	else if (*X == '-' || *X == '+')
	{ // 부호
		int minus = (*X == '-');
		X++;
		n = Term(); if (minus) n = -n;
	}

	else if (*X == '(')
	{ // 괄호
		X++;
		n = PlusMinus(); // 괄호 속 수식 계산
		if (Oper(")") != ')')
		{
			printf("괄호 쌍이 맞지 않습니다.\n");
			exit(-1);
		}
	}

	return n;
}// 곱셈 나눗셈 : 수치를 연산

double MultiplyDivide()
{
	double v1, v2;
	char op;
	v1 = Term(); // 앞 항목
	while (op = Oper("*/%"))
	{ // *, /, % 연산자이면 계속 연산
		v2 = Term(); // 뒷 항목
		switch (op)
		{
		case '*': v1 = v1 * v2;
			break;

		case '/': if (v2 == 0.)
		{
			printf("0 으로 나눌 수 없습니다.\n");
			exit(-1);
		}

				  v1 = v1 / v2;
				  break;

		case '%': if (v2 == 0.)
		{
			printf("0 으로 나눌 수 없습니다.\n");
			exit(-1);
		}

				  v1 = fmod(v1, v2);
				  break;
		}
	}

	return v1;
}// 덧셈 뺄셈 : 곱셈,나눗셈의 결과를 연산

double PlusMinus()
{
	double v1, v2;
	char op;
	v1 = MultiplyDivide(); // 앞 곱셈항
	while (op = Oper("+-"))
	{ // +, - 연산자이면 계속 연산
		v2 = MultiplyDivide(); // 뒷 곱셈항
		switch (op)
		{
		case '+': v1 = v1 + v2;
			break;
		case '-': v1 = v1 - v2;
			break;
		}
	}
	return v1;
}// 수식 계산

double CalcX(char *x)
{
	X = x; // 계산할 문자열의 시작 포인터 설정
	return PlusMinus();
}

void print(DLL *list) {
	struct Node* temp = list->head;
	printf("Forward: ");
	while (temp != NULL) {
		printf("[%d] ", temp->val);
		temp = temp->next;
	}
	printf("\n");
}
//--------------------------------------------------------------------------------------------------
int main() {
	DLL *list = newDLL();
/*
	char *X; // 계산할 문자열의 읽는 위치
	char Oper(const char *o);
	double Term();
	double MultiplyDivide();
	double PlusMinus();
*/
	printf("please insert documents :\n");

	char x[256] = "45 * -(4 + 5) + 0.26 / -(3.5 - 0.3)";
	double res;
	printf("수와 연산을 입력하세요: \n");

  int i;
	for (i = 1; i < 6; i++) {
		append(list, newnode(i));
	}

	fgets(x, sizeof(x), stdin); //여기를 더블링크드리스트와 연결 //더블링크드 리스트에 입력
	res = CalcX(x); //더블링크드리스트에서 출력
	printf("%f", res);
	getchar();

	print(list);

	return 0;
}
