#include <stdio.h>
#include <stdlib.h>

typedef struct _Data
{
      int   value;
      struct _Data *next;
} Data;

Data *head;
Data *tail;

void init_linkedlist(void);
void push(int);
void pop(void);
void print_list(void);

int main()
{
      int returnVal;

      init_linkedlist();
 
      push(3);
      push(4);
      push(7);
      push(10);

      print_list();
 
      pop();
      pop();
      pop();
      pop();
      pop();
 
      return 0;
}

void init_linkedlist(void)
{
      head = (Data *) malloc(sizeof(Data));
      tail = (Data *) malloc(sizeof(Data));

      head -> next = tail;
      tail -> next = tail;
}

void push(int inputValue)
{
      Data *newData;

      newData = (Data *) malloc(sizeof(Data));

      newData -> value = inputValue;
      newData -> next = head -> next;
      head -> next = newData;
}

void print_list(void)
{
      Data *printData;
      int printValue;

      printData = head -> next;

      while (1)
      { 
            printValue = printData -> value;
  
            if (printData == tail)
            {
                  printf("The Print is over.\n");
                  break;
            }
            else
            {
                  printData = printData -> next;
                  printf("%d is print value.\n", printValue);    
            }
      }
}
  
void pop(void)
{
      Data *nextData;
      int returnVal;
 
      if (head -> next == tail)
      {
            printf("This Linked List is empty\n");
            exit(0);
      }
 
      nextData = head -> next;
      returnVal = nextData -> value;
      printf("returnVal is %d\n", returnVal);
 
      head -> next = nextData -> next;
      free(nextData);

      printf("%d is popup.\n", returnVal);
}  



/*출처: http://basketlinux.tistory.com/entry/간단한-Linked-List를-사용한-Stack [유누아빠의 웹개발]*/
