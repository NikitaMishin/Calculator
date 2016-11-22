#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include "LongDecimal.h"
#include "Doublylinkedlist.h"






//base 10e+10
//oper need to signalize when it's not the BigNum  
void read_LongDecimal(Dlist *BigNum,int *oper)
{
  char *number_in_string = (char*)malloc(22*sizeof(char));//need to free when return
  int symbol = 0 ;
  char *end = NULL;
  unsigned long long int number = 0;
  // - + t*10e+20 + \0
  int i = 0;
  symbol = getchar();
  if (symbol == '\n' || (symbol == EOF) || symbol == '+'
   || symbol == '*'|| symbol == '/' || symbol == '=')  
  {
    *oper = symbol;
    free (number_in_string );
    return;
  }
  if ( symbol == '-')
  {
    if (( symbol = getchar()) == '\n' || (symbol == EOF)) 
    {
      *oper = symbol;
      free (number_in_string );
      return;
    }
    else 
    {
      BigNum->sign = 1;
      number_in_string[i++] = symbol;
    }
   }
   else   number_in_string[i++] = symbol;  //not good shape
   
  while ((symbol = getchar() ) != '\n' && (symbol != EOF))
  { 
    if (i > 9)//change on base-1
    { 
      number_in_string[i] = '\0';
      i = 0;
      number = strtoull (number_in_string, &end , 10);
    if (end == number_in_string) 
    {
      fprintf(stderr, "Цифры отсутствуют\n");
      exit(EXIT_FAILURE);
    }
    if ((*end)!='\0')
    {
      fprintf(stderr, "Некорректный ввод\n");
      exit(EXIT_FAILURE);
    }
      insert_to_end_Dlist ( BigNum, &number);
      free(number_in_string);             // put in macros
      number_in_string = NULL;
      number_in_string = (char*)malloc(sizeof(char)*22);
      printf("vot%llu\n",number);
    }
    number_in_string[i++] = symbol; 
  }
  if (i != 0)
  {
     number_in_string[i] = '\0'; //avoid undefined behaviour in function stroull
    i = 0;
    number = strtoull (number_in_string, &end , 10);
    if (end == number_in_string) 
    {
      fprintf(stderr, "Цифры отсутствуют\n");
      exit(EXIT_FAILURE);
    }
    if ((*end)!='\0')
    {
      fprintf(stderr, "Некорректный ввод\n");
      exit(EXIT_FAILURE);
    }
    insert_to_end_Dlist ( BigNum, &number);
    printf("vot%llu",number);
  } 
   free(number_in_string);             // put in macros
    number_in_string = NULL;
}

