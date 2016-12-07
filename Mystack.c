#include <stdlib.h>
#include <stdio.h>
#include "Mystack.h"
#include "Doublylinkedlist.h"
#include "LongDecimal.h"


// stack  for int massive

/*typedef  free(x);
  free(y);
  stack_push(Result);
  destroy_pointer_Dlist(Result);
  free(Result); 
*/
static  int SP=-1;
static Dlist **stack = NULL;
static  int stacksize = 1024 ;
static int freespace= 1024;

void  stack_init()
{
	stack = (Dlist**)malloc( sizeof(Dlist*)*stacksize);//?
}

int stack_size()
{
	return (SP+1);
}

void stackrealloc()
{		
	stacksize *=2;
	freespace=stacksize-stack_size();
	stack = (Dlist**)realloc(stack,sizeof(Dlist*)*stacksize); //??	
}

void stack_push(Dlist* BigNum)
{
	if (freespace  < 2) stackrealloc(); 
	SP++;
	stack[SP] = (Dlist*)malloc(sizeof(Dlist));
	init_Dlist(stack[SP]);
	copy_Dlist(BigNum,stack[SP]);
	//
	
	freespace--;
}

Dlist *stack_pop()
{
 // if (stacksize > 1024 && freespace*2 >stacksize)
  //{
  //}
	freespace++;
	SP--;
	Dlist *s = stack[SP+1];
	return (s);
}

void stack_destroy()
{
  int size = stack_size();
  for(int i = 0; i <size;i++ )
  {
    destroy_pointer_Dlist(stack[i]);
    free(stack[i]);
  }
	free(stack);
	SP=-1;
	stacksize = 1024;
  freespace = 1024;
	//stack = 0;//can null?
}

int how_space()
{
return freespace;
}



void add_stack()
{
  if(stack_size() < 2) 
  {
    printf("Not enough number in stack");
    exit(1);
  }
  Dlist *Result = (Dlist*)malloc(sizeof(Dlist));
  init_Dlist(Result);
  Dlist *y = stack_pop(); 
  Dlist *x =  stack_pop(); 
  sum_LongDecimal(x, y, Result);
  destroy_pointer_Dlist(y);
  destroy_pointer_Dlist(x);
  free(x);
  free(y);
  stack_push(Result);
  destroy_pointer_Dlist(Result);
  free(Result);
}

void sub_stack()
{
  if(stack_size() < 2) 
  {
    printf("Not enough number in stack");
    exit(1);
  }
  Dlist *Result = (Dlist*)malloc(sizeof(Dlist));
  init_Dlist(Result);
  Dlist *y = stack_pop(); 
  Dlist *x =  stack_pop(); 
  sub_LongDecimal(x, y, Result);
  destroy_pointer_Dlist(y);
  destroy_pointer_Dlist(x);
  free(x);
  free(y);
  stack_push(Result);
  destroy_pointer_Dlist(Result);
  free(Result);
}

void mul_stack()
{
  if(stack_size() < 2) 
  {
    printf("Not enough number in stack");
    exit(1);
  }
  Dlist *Result = (Dlist*)malloc(sizeof(Dlist));
  init_Dlist(Result);
  Dlist *y = stack_pop(); 
  Dlist *x =  stack_pop(); 
  mul_LongDecimal(x, y, Result);
  destroy_pointer_Dlist(y);
  destroy_pointer_Dlist(x);
  free(x);
  free(y);
  stack_push(Result);
  destroy_pointer_Dlist(Result);
  free(Result);
}
void div_stack()
{
  if(stack_size() < 2) 
  {
    printf("Not enough number in stack");
    exit(1);
  }
  Dlist *Result = (Dlist*)malloc(sizeof(Dlist));
  init_Dlist(Result);
  Dlist *y = stack_pop(); 
  Dlist *x =  stack_pop(); 
  divide_LongDecimal(x, y, Result);
  destroy_pointer_Dlist(y);
  destroy_pointer_Dlist(x); 
  free(x);
  free(y);
  stack_push(Result);
  destroy_pointer_Dlist(Result);
  free(Result);
}

void show_top_stack()
{
   if(stack_size() < 1) 
  {
    printf("Not enough number in stack");
    exit(1);
  }
  show_LongDecimal(stack[stack_size()-1]);
}
