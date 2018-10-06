/* 재귀호출을 이용한 계산기*/
/* 한번 pull request라는 걸 해보자*/
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
// 공백 스킵
void skipSpace()
{ 
  while (isspace(*X)) X++;
}// 연산자

char Oper(const char *op)
{ // 연산자 읽기
  skipSpace(); 
  if(*X && strchr(op,*X)) 
  return *X++;// 원하는 연산자들에 속하면 연산자를 되돌리고 return 0; 
  // 그렇지 않으면 0 
}// 항목 : 수치, (수식)의 값을 읽음
double Term()
{ 
  double n = 0; // 수치 읽기
  skipSpace();
  if ( isdigit(*X) || *X == '.')
  { // 수치 
    char N[32]; // 읽어들인 숫자
    int dot;
    char *x = N;
    do
    { 
      dot = (*X == '.');
      *x++ = *X++;
    }
  
  while ( isdigit(*X) || (!dot && *X == '.') );
    *x = '\0'; n = atof(N);
  }
  
  else if ( *X == '-' || *X == '+')
  { // 부호
    int minus = (*X == '-');
    X++;
    n = Term(); if(minus) n = -n;
  }
  
  else if ( *X == '(' )
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
  double v1,v2;
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
    
    v1 = fmod(v1,v2);
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
                    
int main()
{
  char x[256] = "45 * -(4 + 5) + 0.26 / -(3.5 - 0.3)";
  double res;
  printf("수와 연산을 입력하세요: \n");
  fgets(x,sizeof(x),stdin);
  res = CalcX(x);
  printf("%f",res);
  getchar();
}

//get char 사용법 좀더 익히기.
