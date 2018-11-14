#include <iostream>
#include <iomanip>
using namespace std;
 
class node
{
  public:
    float number;
    node *next;
};
 
node* push(node *stack, float data)
{
  node *utility;
  utility = new node;
  utility -> number = data;
  utility -> next = stack;
  return utility;
}
 
node* pop(node *stack, float &data)
{
  node *temp;
  if (stack != NULL)
  {
    temp = stack;
    data = stack -> number;
    stack = stack -> next;
    delete temp;
  }
  else cout << "\nERROR: Empty stack.\n";
  return stack;
}
 
int main()
{
  float answer, operand1, operand2;
  char ch;
  node *utility, *top;
 
  utility = new node;
  utility -> number = 0;
  utility -> next = NULL;
  top = new node;
  top -> number = 0;
  top -> next = utility;
 
  cout << "Postfix Calculator\n\n"
       << "Enter a legal positive integer postfix operation.\n\n";
  cin >> ch;
  while(ch != '\n')
    {
        cin >> ch;
        int operand = 0;
        while(ch == ' ')
          cin >> ch;
        if((ch >= '0')&&(ch <= '9')){
          while(ch != ' '){
            operand = operand*10 + (ch-48);
            cin >> ch;}
          top = push(top, operand);}
        else{
          pop(top, operand1);
          pop(top, operand2);
          switch(ch){
            case '+': answer = operand2 + operand1;
            case '-': answer = operand2 - operand1;
            case '*': answer = operand2 * operand1;
            case '/': answer = operand2 / operand1;}
          push(top, answer);}
    }
  pop(top, answer);
  cout << "\nAnswer: " << answer << endl;
}
