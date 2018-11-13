#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX 100

	char *X; // 계산할 문자열의 읽는 위치
	char Oper(const char *o);
	double Term();
	double MultiplyDivide();
	double PlusMinus();

  int stack[MAX];        // 스택의 긴  통
  int top;            // 스택의 상단

typedef struct Node {
	char val;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	int size;
} DLL;

Node *newnode(char n)
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

void insertAt(DLL *list, int index, Node *newnode) {

	struct Node* temp = list->head;

	if (index < 0 || index > list->size) {
		printf("INSERT ERROR: Out of Bound\n");
	}
	else if (index == 0) {
		newnode->next = list->head;
		list->head->prev = newnode;
		list->head = newnode;
		list->size++;
	}
	else if (index == list->size) {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		newnode->prev = temp;
		newnode->next = NULL;
		temp->next = newnode;
		list->size++;
	}
	else {
		for (int i = 0; i < index - 1; i++) {
			temp = temp->next;
		}

		newnode->prev = temp;
		newnode->next = temp->next;
		temp->next->prev = newnode;
		temp->next = newnode;
		list->size++;
	}
}

void deleteAt(DLL *list, int index) {
	//save reference to first link

	struct Node* temp = list->head;

	if (index < 0 || index >= list->size) {
		printf("DELETE ERROR: Out of Bound\n");
	}
	else if (index == 0) {
		temp->next->prev = NULL;
		list->head = temp->next;
		list->size--;
	}
	else if (index + 1 == list->size) {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->prev->next = NULL;
		free(temp);

		list->size--;
	}

	else {
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}

		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		free(temp);

		list->size--;
	}
}
	/*if (temp->next != NULL)
		temp->next->prev = temp;
		*/

void print(DLL *list) {
	struct Node* temp = list->head;
	printf("Forward: ");
	while (temp != NULL) {
		printf("[%d] ", temp->val);
		temp = temp->next;
	}
	printf("\n");
}

//----------------------------------------------------------------------------------------------------

int stack[MAX];        // 스택의 긴  통
int top;            // 스택의 상단

void init_stack(void){
    top = -1;
}

int push(int t){

    if (top >= MAX - 1){
        printf("\n    Stack overflow.");
        return -1;
    }

    stack[++top] = t;
    return t;
}

int pop(void){
    if (top < 0){
        printf("\n   Stack underflow.");
        return -1;
    }
    return stack[top--];
}

void print_stack(void){
    int i;
    printf("\n Stack contents : TOP ----> Bottom\n");
    for (i = top; i >= 0; i--){
        printf("%-6d", stack[i]);
    }
}

// 스택의 TOP의 값을 가져온다.
int get_stack_top(void){
    return (top < 0) ? -1 : stack[top];
}

// 스택이 비어있는지 검사
int is_stack_empty(void){
    return (top < 0);
}

// k 가 연산자인지 판단한다.
int is_operator(int k){
    return (k == '+' || k == '-' || k == '*' || k == '/');
}

// 후위표기법 수식이 적접한가 체크
int is_legal(char *s){
    int f = 0;
    while (*s){
        // 처음 공백 넘어가기
        while (*s == ' '){
            s++;
        }

        if (is_operator(*s)){
            f--;
        }
        else{
            f++;
            while (*s != ' '){
                s++;
            }
        }
        if (f < 1) break;
        s++;
    }
    return (f == 1);
}

// 연산자의 우선순위를 수치로 변환해준다.
int precedence(int op){
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}

// 중위표기법을 후위표기법으로 변환
void postfix(char *dst, char *src){
    char c;
    init_stack();
    while (*src){
        if (*src == '('){
            push(*src);
            src++;
        }
        else if (*src == ')'){
            while (get_stack_top() != '('){
                *dst++ = pop();
                *dst++ = ' ';
            }
            pop();
            src++;
        }
        else if (is_operator(*src)){
            while (!is_stack_empty() &&
                precedence(get_stack_top()) >= precedence(*src)){
                *dst++ = pop();
                *dst++ = ' ';
            }
            push(*src);
            src++;
        }
        else if (*src >= '0' && *src <= '9'){
            do{
                *dst++ = *src++;
            } while (*src >= '0' && *src <= '9');
            *dst++ = ' ';
        }
        else{
            src++;
        }
    }

    while (!is_stack_empty()){
        *dst++ = pop();
        *dst++ = ' ';
    }
    dst--;
    *dst = 0;
}

// 후위표기법을 계산한다.
int calc(char *p){
    int i;
    init_stack();
    while (*p){
        if (*p >= '0' && *p <= '9'){
            i = 0;
            do{
                i = i * 10 + *p - '0';
                p++;
            } while (*p >= '0' && *p <= '9');
            push(i);
        }
        else if (*p == '+'){
            push(pop() + pop());
            p++;
        }
        else if (*p == '*'){
            push(pop() * pop());
            p++;
        }
        else if (*p == '-'){
            i = pop();
            push(pop() - i);
            p++;
        }
        else if (*p == '/'){
            i = pop();
            push(pop() / i);
            p++;
        }
        else{
            p++;
        }
    }
    return pop();
}
//------------------------------------------------------------------------------------------------
int main() {
  
  DLL *list = newDLL();

  printf("please insert documents :\n");

  char val;
	while(val != '\n') {
    scanf("%c",&val);
		append(list, newnode(val));
	}
//위는 입력받는 구성이다. 다만 저장시 ascii코드에 따른 문자가 들어간다.
  int i=0;

  while(i != list->size) {
    if(list->head->val == '\0')
      deleteAt(list,i);

    list->head = list->head->next;
    i++;
  }
	print(list);
//위는 공백지우고 다시 리스트 연결하는 구성

  struct Node* temp = list->head;

  
    int r;

    char exp[256] = "2*3+6/2-4";
    char pf[256];

    postfix(pf, exp);
    printf("\nPostfix : %s", pf);

//위는 후위표기법으로 변환

    if (!is_legal(pf)){
        printf("\n Exprssion is legal!");
        exit(1);
    }
    r = calc(pf);
    printf("\nAnswer : %d", r);
//위는 계산과 출력
    return 0;
}

//--------------------------------------------------------------------------------------------------
/*
	char *X; // 계산할 문자열의 읽는 위치
	char Oper(const char *o);
	double Term();
	double MultiplyDivide();
	double PlusMinus();

	/*아니면 midfix -> postfix로 바꾸어 선저장 후 꺼내어 다른 head로 옮겨서 계산.
	연산자 우선순위를 처리하기 위해 저장 전에 해주어야 하나?
	저장 후 처리해주는 것이 맞다. 왜냐하면 선저장 방식시 링크드리스트를 또 써야하거나 char[]을 쓰는데 이건 취지에 맞지않다.
	같이 처리해주는 건 어떤가? - 안된다. 스택을 이용하는 방식으로 정해져있다.
	1. 입력을 링크드리스트에 저장.(while문을 써서 append로 연달아 붙이기 - 각 노드의 int val은 char val로 고칠것)
	(한 노드에는 하나의 문자만 저장 - 한노드에 여러 문자열시 연산시 맞지 않는  경우가 생긴다.
	2. 입력된 문자열을 연산자 우선순위로 바꾸어 다시 링크드리스트에 저장. ( + - * / 를 만날때 마다 우선순위 연산하기, '.'은 무리수이니 주의할것.)
	3. 계산
	4. 계산 출력
	*/

/*플럼빙 해야할 요소들
1.계산 해주는 함수*/
