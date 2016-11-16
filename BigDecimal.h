#pragma once
#include "BigDecimal.c"


// need to check
typedef struct
{
int *number;
int sign;
int size;

}Longdecimal;

int isDigit (int c);
int MaxModuleNum (Longdecimal *a, Longdecimal *b);
void get_Longdecimal (Longdecimal *BigNum) ;
void add (Longdecimal *a, Longdecimal *b, Longdecimal *result);
void sub (Longdecimal *a, Longdecimal *b, Longdecimal *result); 
void mul (Longdecimal *a, Longdecimal *b, Longdecimal *result);
void reverse(int *massive, int size);
void divide (Longdecimal *a, Longdecimal *b, Longdecimal *result);
void mulsimple(Longdecimal a, int n );
void get_minsubnumber(Longdecimal *a, Longdecimal *b, Longdecimal *result);
void show_longdecimal(Longdecimal a);
