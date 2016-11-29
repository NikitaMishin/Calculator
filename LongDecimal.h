#pragma once
#include "Doublylinkedlist.h"

void read_LongDecimal(Dlist *BigNum,int *oper);
void show_LongDecimal(Dlist *BigNum);
void delete_odd_Node(Dlist *BigNum);
void sum_LongDecimal(Dlist *BigNum1, Dlist *BigNum2, Dlist *Result);
void set_leadingzeros_Node(Dlist *BigNum,Node *list);//beeter title
int abscompare_LongDecimal(Dlist *BigNum1,Dlist *BigNum2);
void sub_LongDecimal (Dlist *BigNum1,Dlist *BigNum2,Dlist *Result);
