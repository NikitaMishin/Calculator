#pragma once
#include "Doublylinkedlist.h"

void read_LongDecimal(Dlist *BigNum,int *oper);
void show_LongDecimal(Dlist *BigNum);
void delete_odd_Node(Dlist *BigNum);
void sum_LongDecimal(Dlist *BigNum1, Dlist *BigNum2, Dlist *Result);
void set_leadingzeros_Node(Dlist *BigNum,Node *list);//beeter title
int  abscompare_LongDecimal(Dlist *BigNum1,Dlist *BigNum2);
void sub_LongDecimal (Dlist *BigNum1,Dlist *BigNum2,Dlist *Result);
void mul_LongDecimal(Dlist *BigNum1,Dlist *BigNum2, Dlist *Result);
void set_size_LongDecimal (Dlist *BigNum);
void add_to_first_LongDecimal(Dlist *BigNum1,Dlist *BigNum2);
void set_leadingzeros_LongDecimal (Dlist *BigNum);
void sub_from_first_LongDecimal(Dlist *BigNum1,Dlist *BigNum2);
void mul_on_small_ld(Dlist *BigNum, long  int number);
void get_subDlist_LongDecimal(Dlist *BigNum1, Dlist *BigNum2,Dlist* Result);
void copy_Dlist(Dlist *BigNum , Dlist*Result);
Dlist *get_ostatok_Dlist (Dlist *BigNum1,Dlist* BigNum2,int *symbol);
void div_on_10 (Dlist *BigNum);
void divide_LongDecimal(Dlist *BigNum1,Dlist *BigNum2,Dlist *Result) ;
