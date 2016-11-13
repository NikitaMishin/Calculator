#pragma once

typedef struct
{
int *number;
int sign;
int size;

}Longdecimal;

void get_Longdecimal (Longdecimal *BigNum) ;
void add (Longdecimal *a, Longdecimal *b, Longdecimal *result);
void sub (Longdecimal *a, Longdecimal *b, Longdecimal *result); 
void mul (Longdecimal *a, Longdecimal *b, Longdecimal *result);
void div (Longdecimal *a, Longdecimal *b, Longdecimal *result);
int MaxModuleNum (Longdecimal a, Longdecimal b);
int isDigit (char *c);
