#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <assert.h>
#include "LongDecimal.h"
#include "Doublylinkedlist.h"

#define BLOCK_OF_INITIALIZATION()  long long int number = 0;long long int tmp = 0;long long int sum;Node *num1 = BigNum1->tail;Node *num2 = BigNum2->tail;

static const long long int numberbase = 1000000000;
static const int base = 9;

void read_LongDecimal(Dlist *BigNum,int *oper)  
{
  int symbol;
  unsigned long long int number;
  long long int size;
  char *number_in_string;
  symbol = 0;
  number = 0; 
  long long int massivesize = 1024;
  number_in_string = (char*)malloc(massivesize*sizeof(char));
  size = 0;
  symbol = getchar();
  if (symbol == '\n' || (symbol == EOF) || symbol == '+'
      || symbol == '*'|| symbol == '/' || symbol == '='|| symbol == 'q')  
  {
    *oper = symbol;
    free (number_in_string );
    return;
  }
  if ( symbol == '-')
  {
    if (( symbol = getchar()) == '\n' || (symbol == EOF)) 
    {
      *oper = '-';
      free (number_in_string );
      return;
    }
    else 
    {
      BigNum->sign = 1;
      number_in_string[size++] = symbol;
    }
  }
  else   number_in_string[size++] = symbol;  
  while (((symbol = getchar() ) != '\n') && (symbol != EOF)) 
  { 
    number_in_string[size++] = symbol;
    if (size+3 >= massivesize )  
    {
      massivesize *=2; 
      number_in_string = (char*)realloc(number_in_string,massivesize);     
    }
  }
  number_in_string[size++] = '\n';    
  //size-2 --last symbol-number // 
  int position = 0;
  errno = 0;
  char *end = NULL;
  int q = size;//bool for first entrance
  while ((size  > 0 && position > 0) ||q == size )
  {
    position = 0;
    if ( (position =  size-2-base+1) < 0) position = 0;
    number = strtoll (number_in_string+position,&end,10);
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
    insert_to_begin_Dlist (BigNum, &number);
    number_in_string[position] = '\n';
  }  
  free(number_in_string);
  delete_odd_Node(BigNum);
}

void show_LongDecimal(Dlist *BigNum)
{
  assert(BigNum->size > 0);
  if (BigNum->head->number == 0) 
  {
    printf("0\n");
    return;  
  }
  if (BigNum->sign == 1) printf("-");
  Node *tmp = BigNum->head;
  printf("%lld",tmp->number);
  tmp = tmp->next;
  while(tmp)
  {
    printf("%.9lld",tmp->number);
    tmp = tmp->next;
  }
  printf("\n");
}

void sum_LongDecimal(Dlist *BigNum1, Dlist *BigNum2, Dlist *Result)  
{
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  if(BigNum1->sign != BigNum2->sign)
  {
    int c = BigNum2->sign;
    int s = (abscompare_LongDecimal(BigNum1,BigNum2))?BigNum1->sign:BigNum2->sign;
    BigNum2->sign = BigNum1->sign ; 
    sub_LongDecimal (BigNum1,BigNum2,Result);
    BigNum2->sign = c;
    Result->sign = s;
    return;
  }
  BLOCK_OF_INITIALIZATION();
  if(Result->size != 0)
  {
    if (Result == BigNum1)
    {
      add_to_first_LongDecimal(BigNum1,BigNum2);
      return;
    }
    if (Result == BigNum2)  
    {
      add_to_first_LongDecimal(BigNum2,BigNum1);
      return;
    }
     destroy_pointer_Dlist(Result);
     init_Dlist (Result);
  }
  while(num1 && num2)
  {
    sum = num1->number + num2->number+tmp;
    number = sum % numberbase;
    insert_to_begin_Dlist(Result,&number);
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num1 = num1->prev;       
    num2 = num2->prev;                                                 
  } 
  Result->sign = BigNum1->sign; 
  while(num1)
  {
    sum = num1->number + tmp;
    number = sum % numberbase;
    insert_to_begin_Dlist(Result,&number); 
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num1 = num1->prev;
  }
  while(num2)
  {
    sum = num2->number + tmp;
    number = sum % numberbase;
    insert_to_begin_Dlist(Result,&number);
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num2 = num2->prev;
  } 
  if(tmp)
  {
    insert_to_begin_Dlist(Result,&tmp);
  }
  delete_odd_Node(Result);  
  
}

void delete_odd_Node(Dlist *BigNum)//bettert name
{
  assert(BigNum->size > 0);
  Node *tmp = BigNum->head;
  while((tmp->number == 0) &&(tmp->next != NULL)) 
  {
    tmp = tmp->next;
    delete_head(BigNum);  
  }
}

// return 2 when BigNum1 > BigNum2
//return 1 when BigNum1 >= BigNum2
//return  0  when BigNum1 < BigNum2
int abscompare_LongDecimal(Dlist *BigNum1,Dlist *BigNum2) 
{
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
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
  if(BigNum1->sign ^ BigNum2->sign)
  {
    int c = BigNum2->sign;;
    BigNum2->sign = BigNum1->sign;
    sum_LongDecimal (BigNum1,BigNum2,Result); 
    BigNum1->sign = c;
    return;
  }
  BLOCK_OF_INITIALIZATION();
  if ( abscompare_LongDecimal(BigNum1,BigNum2) )
  {
    num1 = BigNum1->tail;
    num2 = BigNum2->tail;
    Result->sign = BigNum1->sign;
  }
  else
  {
    num2 = BigNum1->tail;
    num1 = BigNum2->tail;
    Result->sign = (BigNum2->sign)?0:1;
  }
   while(num1 && num2)
  {
    sum = num1->number - num2->number-tmp;
    number = (sum >= 0)?sum:(sum +numberbase ) ;
    tmp = (sum < 0)?1:0;
    insert_to_begin_Dlist(Result,&number);
    num1 = num1->prev;       
    num2 = num2->prev;                                                 
  }  
  while(num1)
  {
    sum = num1->number - tmp;
    number = (sum >= 0)?sum:(sum + numberbase ) ;
    tmp = (sum < 0)?1:0;
    insert_to_begin_Dlist(Result,&number); 
    num1 = num1->prev;
  }
  delete_odd_Node(Result);  
}

void mul_LongDecimal(Dlist *BigNum1,Dlist *BigNum2, Dlist *Result)
{
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  Node *num = NULL;
  long long int tmp = 0;////////////////
  long long int sum = 0;
  long long int number = 0;
  long int probablysize = BigNum1->size + BigNum2->size; 
  for(long int p = 0; p < probablysize;p++)  insert_to_begin_Dlist (Result,  &number);
  Node *trace = Result->tail;
  Node *second = BigNum2->tail;
  Node *first = BigNum1->tail; 
  for(long int i  = 0; i < BigNum1->size;i++ )
  {  
    num = trace;
    second = BigNum2->tail;
    for(long int j = 0;  j < BigNum2->size;j++)
    {
     
        sum = first->number * second->number+tmp + num->number;
        num->number = sum%numberbase;
        tmp = (sum / numberbase);
        num = num->prev;
         second = second->prev;    
    }
    first = first->prev;
    num->number += tmp;
    trace = trace->prev;
    tmp = 0;
  }  
  Result->sign = BigNum1->sign ^ BigNum2->sign; 
  delete_odd_Node(Result);
}
void  add_to_first_LongDecimal(Dlist *BigNum1,Dlist *BigNum2)
{//razvetlv
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  BLOCK_OF_INITIALIZATION();
  while(num1 && num2)
  {
    sum = num1->number + num2->number+tmp;
    number = sum % numberbase;
    num1->number = number;   
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num1 = num1->prev;       
    num2 = num2->prev;                                                 
  }  
  while(num1)
  {
    sum = num1->number + tmp;
    number = sum % numberbase;
    num1->number = number;
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num1 = num1->prev;
  }
  while(num2)
  {
    sum = num2->number + tmp;
    number = sum % numberbase;
    insert_to_begin_Dlist(BigNum1,&number); 
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num2 = num2->prev;
  } 
  if(tmp)
  {
    insert_to_begin_Dlist(BigNum1,&tmp);
  }
  delete_odd_Node(BigNum1);  
}

void  sub_from_first_LongDecimal(Dlist *BigNum1,Dlist *BigNum2)
{
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  BLOCK_OF_INITIALIZATION();//DSGHDSJGHKSD
  if ( abscompare_LongDecimal(BigNum1,BigNum2) )
  {
    num1 = BigNum1->tail;
    num2 = BigNum2->tail;
    BigNum1->sign = BigNum1->sign;
  }
  else
  {
     destroy_pointer_Dlist(BigNum1);
     insert_to_begin_Dlist(BigNum1,&tmp);
     return;
  }
   while(num1 && num2)
  {
    sum = num1->number - num2->number-tmp;
    number = (sum >= 0)?sum:(sum +numberbase ) ;
    tmp = (sum < 0)?1:0;
    num1->number = number; 
    num1 = num1->prev;       
    num2 = num2->prev;                                             
  }  
  while(num1)
  {
    sum = num1->number - tmp;
    number = (sum >= 0)?sum:(sum +numberbase ) ;
    tmp = (sum < 0)?1:0;
    num1->number = number;
    num1 = num1->prev;
  }
  delete_odd_Node(BigNum1);
}

void get_subDlist_LongDecimal(Dlist *BigNum1, Dlist *BigNum2,Dlist* Result)
{
  long long int prev = 0;
  long long int number = 0;
  Node *num1 = BigNum1->head; 
  if (abscompare_LongDecimal(BigNum1,BigNum2) == 0)
  {
    insert_to_begin_Dlist(Result,&number);
    Result->sign = 0;//?
    return;
  }
  long long int counter;
  long long const int position = numberbase/10;
  int flag;
  long long int tmp;
  insert_to_begin_Dlist(Result,&number);
  long long int you = 0;
  while(num1)
  {
    counter = position;
    flag = 1;  
    tmp = num1->number ;
    prev = 0;
    
    while((abscompare_LongDecimal(BigNum2, Result) == 2) && flag)//base
    {
      if (counter == 1) flag = 0;
      number  = tmp/counter ;
      you = number;
      number = number - 10*prev;// get one number
      mul_on_small_ld(Result,10);
      prev = you;
      Result->tail->number += number ;// insert this number 
       counter /= 10;
    }
    if (abscompare_LongDecimal(Result,BigNum2)) return;
    num1 = num1->next;
  }
}

void mul_on_small_ld (Dlist *BigNum, long  int number)
{
  (long long int)number;
  Node *num = BigNum->tail;
  long long int tmp = 0;
  long long int sum = 0;
  while(num)
  {
    sum = num->number * number+tmp;
    num->number = sum%numberbase;
    tmp = (sum / numberbase);
    num = num->prev; 
  }
  if (tmp != 0 && num == NULL) insert_to_begin_Dlist(BigNum,&tmp);
}  

Dlist * get_ostatok_Dlist(Dlist *BigNum1,Dlist* BigNum2,int *symbol) 
{
  int counter = 1;
  int flag;
  Dlist *Num2 = (Dlist*)(malloc(sizeof(Dlist)));
  init_Dlist(Num2);
  copy_Dlist(BigNum2 , Num2) ;
  Dlist *Result = (Dlist*)(malloc(sizeof(Dlist)));
  init_Dlist(Result);
  copy_Dlist(BigNum2 , Result) ;
  while((flag = abscompare_LongDecimal(BigNum1,Result)) == 2)
  {
    counter++ ;
    add_to_first_LongDecimal(Result,Num2);
  }

  if(flag == 0) { sub_from_first_LongDecimal(Result,Num2);counter--;}
  *symbol = counter;  
  destroy_pointer_Dlist(Num2);
  free(Num2);
  return Result; 
}   
 
void copy_Dlist(Dlist *BigNum , Dlist*Result)
{
  Node *tmp = BigNum->head;
  init_Dlist (Result);
  while(tmp)
  {
    insert_to_end_Dlist(Result,&tmp->number);
    tmp = tmp->next;
  }
  Result->sign = BigNum->sign;
}

int get_sizeofhead_Dlist(Dlist* BigNum)
{
  int size = 0;
  assert(BigNum->size > 0);
  long long int number = BigNum->head->number;
  while(number)
  {
    number/=10;
    size++;
  }
  return size;
}

void div_on_10 (Dlist *BigNum)
{
  Node *num = BigNum->tail;
  long long int tmp = 0;
  long long int sum = 0;
  long long int bas = numberbase/10;
  while(num)
  {
    tmp = num->number%10;    
    if(num->next) num->next->number = num->next->number+ bas*tmp;
    num->number = num->number/10;
    num = num->prev; 
  }
  delete_odd_Node(BigNum);
}

void divide_LongDecimal(Dlist *BigNum1,Dlist *BigNum2,Dlist *Result) // can better
{
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  assert(BigNum2->head->number != 0);//division by zero  
  Result->sign = BigNum1->sign^BigNum2->sign;
  int symbol = 0;
  long long int tmp = 0;
  int i = 0;
  int sizeNum;
  int sizeDifference;
  int sizeSubnumber;
  if (abscompare_LongDecimal(BigNum1,BigNum2)==0)
  {
    Result->sign = 0;
    insert_to_begin_Dlist(Result,&tmp);
    return;
  }
  Dlist *Subtrahend ;
  Dlist *Difference = (Dlist*)(malloc(sizeof(Dlist)));
  Dlist *Num = (Dlist*)(malloc(sizeof(Dlist)));
  Dlist *Divider = (Dlist*)(malloc(sizeof(Dlist)));
  Dlist *Subnumber = (Dlist*)(malloc(sizeof(Dlist)));
  copy_Dlist(BigNum1 , Num);//
  copy_Dlist(BigNum2 , Divider);
  init_Dlist(Difference);
  init_Dlist(Subnumber);
  insert_to_begin_Dlist(Result,&tmp);
  Num->sign = 0;
  Divider->sign = 0;  
  sizeNum = get_sizeofhead_Dlist(Num) + (Num->size -1)*base;
  get_subDlist_LongDecimal(Num, Divider, Subnumber);
  Subtrahend = get_ostatok_Dlist(Subnumber, Divider, &symbol);
  Result->tail->number = symbol;
  sizeSubnumber = get_sizeofhead_Dlist(Subnumber) + (Subnumber->size -1)*base;
  int expectResultsize = sizeNum - sizeSubnumber+1;//&?
  sub_LongDecimal(Subnumber,Subtrahend,Difference);
  sizeDifference = get_sizeofhead_Dlist(Difference) + (Difference->size -1)*base;
  if(Difference->head->number == 0) sizeDifference = 0; //equal a==b
  int expectsize = sizeNum-sizeSubnumber+sizeDifference;
  int flag = 1;
  while((flag = abscompare_LongDecimal(Num,Subtrahend)) == 2)
  {
    mul_on_small_ld(Subtrahend,10);
  }
  if(flag == 0) div_on_10(Subtrahend);
  sub_from_first_LongDecimal(Num,Subtrahend);
  destroy_pointer_Dlist (Subnumber);
  destroy_pointer_Dlist (Subtrahend);
  destroy_pointer_Dlist(Difference);
  free(Subtrahend);
  int oddzeros = 0;  
  while (abscompare_LongDecimal(Num,Divider) )
  {
    sizeNum = get_sizeofhead_Dlist(Num) + (Num->size -1)*base;
    get_subDlist_LongDecimal(Num, Divider, Subnumber);
    Subtrahend = get_ostatok_Dlist(Subnumber, Divider, &symbol);    
    oddzeros = expectsize - sizeNum;
    while(oddzeros>0) 
    { 
      mul_on_small_ld(Result,10);
      oddzeros--;
    }  
    sizeSubnumber = get_sizeofhead_Dlist(Subnumber) + (Subnumber->size -1)*base;
    sub_LongDecimal(Subnumber,Subtrahend,Difference);
    i = 0;
    while(sizeDifference + 1 + (i++) < sizeSubnumber) mul_on_small_ld(Result,10);
    sizeDifference = get_sizeofhead_Dlist(Difference) + (Difference->size -1)*base;
    if(Difference->head->number == 0) sizeDifference = 0;
    expectsize = sizeNum-sizeSubnumber + sizeDifference;
    mul_on_small_ld(Result,10);
    Result->tail->number += symbol;
    while((flag = abscompare_LongDecimal(Num,Subtrahend)) == 2)
    {
      mul_on_small_ld(Subtrahend,10);
    }
    if(flag == 0) div_on_10(Subtrahend);
    sub_from_first_LongDecimal(Num,Subtrahend);
    destroy_pointer_Dlist (Subnumber);
    destroy_pointer_Dlist (Subtrahend);
    destroy_pointer_Dlist(Difference); 
    free(Subtrahend);
  }
  int  sizeofResult = get_sizeofhead_Dlist(Result) + (Result->size -1)*base;
  expectResultsize-=sizeofResult;
  while((expectResultsize--) > 0)// if error it wiil be threre 
  {
    mul_on_small_ld(Result,10);
  } 
  destroy_pointer_Dlist (Divider);
  destroy_pointer_Dlist(Num);
  free(Divider);
  free(Num);
  free(Difference); 
  free(Subnumber);
} 
