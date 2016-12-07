#pragma once
#include "Doublylinkedlist.h"

void stack_init();
void stackrealloc();
void stack_destroy();
void stack_push(Dlist *BigNum);
Dlist *stack_pop();
int stack_size();
void add_stack();
void div_stack();
void sub_stack();
void mul_stack();
void show_top_stack();

