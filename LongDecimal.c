#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <assert.h>
#include "LongDecimal.h"
#include "Doublylinkedlist.h"





static const long long int numberbase =  1000000000;//
static const int base = 9;
//base 10e+10
//oper need to signalize when it's not the BigNum  
void read_LongDecimal(Dlist *BigNum,int *oper) //change  extra massive where wiill be numbers in char 

{
  int symbol;
  int leadingzeros;
  unsigned long long int number;
  int size;
  char *number_in_string;
  char *end;
  size = 0;
  end = NULL;
  number = 0;
  number_in_string = (char*)malloc(1024*sizeof(char));//need to free when return
  symbol = 0 ;
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
      number_in_string[size++] = symbol;
    }
  }
  else   number_in_string[size++] = symbol;  //not good shape
  
  
  
  while (((symbol = getchar() ) != '\n') && (symbol != EOF)) //ADD REALOC!
  { 
    number_in_string[size++] = symbol;     
  }
  number_in_string[size++] = '\n'; //insert '\n'    
//size-2 --last symbol-number // (base-1)
  int position = 0;
  errno = 0;
  int q = size;//bool for firstt
  
  printf("size=%d\n",size);
  while ((size  > 0 && position > 0) ||q == size )
  {
    position = 0;
    leadingzeros = 0;
    if ( (position =  size-2-base+1) < 0) position = 0;
    number = strtoll (number_in_string+position,&end,10);
    while(number_in_string[position+leadingzeros] == '0' ) leadingzeros++;
    if(number == 0) leadingzeros--;
    size = size - base ; 
    if (end == number_in_string) 
    {
      fprintf(stderr, "WRONG INPUT\n");
      exit(EXIT_FAILURE);
    }
    if ((*end)!='\n') //failed when --
    {
      fprintf(stderr, "WRONG INPUT");
      exit(EXIT_FAILURE);
    }
    if (errno == ERANGE)
    {
      printf("ERROR ");
      exit(1);        
    }
            
    insert_to_begin_Dlist ( BigNum, &number);
    BigNum->head->leadingzeros = leadingzeros;
    number_in_string[position] = '\n';
  }  
  free(number_in_string);
  delete_odd_Node(BigNum);
}

void show_LongDecimal(Dlist *BigNum)
{
  assert(BigNum->size > 0);
  if (BigNum->sign == 1) printf("-");
  Node *tmp = BigNum->head;
  int leadingzeros;

  while(tmp)
  {
    leadingzeros = tmp->leadingzeros;
  //  printf("leading=%d\n",leadingzeros);
    while(leadingzeros-- > 0) printf("%c",'0');
    printf("%lld",tmp->number);
    tmp = tmp->next;
  }
  printf("\n");
}



void sum_LongDecimal(Dlist *BigNum1, Dlist *BigNum2, Dlist *Result)  // 25
{
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  //assert() if result unempty then clean him and start
  long long int number = 0;   
  long long int tmp = 0;
  Node *num1 = BigNum1->tail;
  Node *num2 = BigNum2->tail;
  Result->sign = BigNum1->sign;
  long long int sum;
  while(num1 && num2)
  {
    sum = num1->number + num2->number+tmp;
    number = sum % numberbase;
    insert_to_begin_Dlist(Result,&number);
    printf("sum=%lld",sizeof(numberbase));
    set_leadingzeros_Node(Result,Result->head);
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num1 = num1->prev;       
    num2 = num2->prev;                                                 
  }  
  while(num1)
  {
    sum = num1->number + tmp;
    number = sum % numberbase;
    insert_to_begin_Dlist(Result,&number); 
    set_leadingzeros_Node(Result,Result->head);
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num1 = num1->prev;
  }
  while(num2)
  {
    sum = num2->number + tmp;
    number = sum % numberbase;
    insert_to_begin_Dlist(Result,&number);
    set_leadingzeros_Node(Result,Result->head); 
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num2 = num2->prev;
  } 
  if(tmp)
  {
    insert_to_begin_Dlist(Result,&tmp);
    set_leadingzeros_Node(Result,Result->head);
  }
  delete_odd_Node(Result);  
}

void delete_odd_Node(Dlist *BigNum)//bettert name
{
  assert(BigNum->size > 0);
  Node *tmp = BigNum->head;
  while( tmp->next && (tmp->number == 0)) 
  {
    tmp = tmp->next;
    delete_head(BigNum);
  }
  BigNum->head->leadingzeros = 0;
}


 void set_leadingzeros_Node(Dlist *BigNum,Node *list) 
{
  long long int i;
  int t = 0;
  i = list->number;
  while((i = i/10) > 0)t++;  
  list->leadingzeros = base-1 - t;
}


// return 2 when BigNum1 > BigNum2
//return 1 when BigNum1 >= BigNum2
//return  0  when BigNum1 < BigNum2
int abscompare_LongDecimal(Dlist *BigNum1,Dlist *BigNum2) 
{
  int result;
  if (BigNum1->size != BigNum2->size)
  {
    result = (BigNum1->size > BigNum2->size)?2:0;
    return result;  
  }   
  Node *first = BigNum1->head;
  Node *second = BigNum2->head;
  while(first)
  {
   if(first->number != second->number )
   {
    result = (first->number > second->number)?2:0; 
    return result;
   }
   first = first->next;
   second = second->next;
  }
  return 1;
}




void sub_LongDecimal (Dlist *BigNum1,Dlist *BigNum2,Dlist *Result)
{
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  Node *num1,*num2;
  long long int tmp = 0;
  long long int sum ; 
  long long int number;
  if ( abscompare_LongDecimal(BigNum1,BigNum2) )
  {
    num1 = BigNum1->tail;
    num2 = BigNum2->tail;
  }
  else
  {
    num2 = BigNum1->tail;
    num1 = BigNum2->tail;
  }
   while(num1 && num2)
  {
    sum = num1->number - num2->number-tmp;
    number = (sum >= 0)?sum:(sum +numberbase ) ;
    tmp = (sum < 0)?1:0;
    insert_to_begin_Dlist(Result,&number);
    set_leadingzeros_Node(Result,Result->head);
    num1 = num1->prev;       
    num2 = num2->prev;                                                 
  }  
  while(num1)
  {
    sum = num1->number - tmp;
    number = (sum >= 0)?sum:(sum +numberbase ) ;
    tmp = (sum < 0)?1:0;
    insert_to_begin_Dlist(Result,&number); 
    set_leadingzeros_Node(Result,Result->head);
    num1 = num1->prev;
  }
  delete_odd_Node(Result);  
}

