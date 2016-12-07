#include <stdio.h>
#include <stdlib.h>
#include "Mystack.h"
#include "Doublylinkedlist.h"
#include "LongDecimal.h"
#


int main()
{
  Dlist *n; 
  Dlist *c;
  int  oper = 0;
  n = (Dlist*)malloc(sizeof(Dlist));
  init_Dlist(n);
  stack_init();
  int flag = 1;
  while (flag)
  {
    oper = 0;
    read_LongDecimal(n,&oper);
    switch(oper)
    {
      case '\n':
        {
          break;
        }
      case '-': 
      {   
        sub_stack();
        break;
      }  
      case '+':
      {
        add_stack();
        break;
      }  
      case '/':
      {
        div_stack();
        break;
      }
      case '=':
      {
        show_top_stack();
        break;
      }
      case '*':
      {
        mul_stack();
        break;
      }
      case 'q':
      {
        flag = 0;
        break;
      }
      default: 
      {
        stack_push(n);
        break;
      }
    }
    destroy_pointer_Dlist(n);
  }
  free(n);
  //stack_pop()
//free(n);
 stack_destroy();
  return 0;
}




