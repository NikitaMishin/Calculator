#pragma once

// stack  for int massive

static  int SP = -1;
static int *stack;
static  int stacksize = 1024;
static int freespace = 1024;

void  stack_start()
{
	stack= (int*)malloc( sizeof(int)*stacksize);//?
}
 int stack_size()
{
	return (SP+1);
}

 void stackrealloc()
{	
	
	stacksize *=2;
	freespace=stacksize-stack_size();
	stack = (int*)realloc(stack,sizeof(int)*stacksize); //??
	
}

void stack_push(int a)
{
	if (!freespace) {stackrealloc(); };
	SP++;
	stack[SP] = a;
	freespace--;
}

int stack_pop()
{
	freespace++;
	return (stack[SP--]);
}



void stack_free()
{
	free(stack);
	stack = 0;//can null?
}
