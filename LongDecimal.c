#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <assert.h>
#include "LongDecimal.h"
#include "Doublylinkedlist.h"





static const long long int numberbase = 1000000000;//
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
  int massivesize = 1024;
  size = 0;
  end = NULL;
  number = 0;
   errno = 0;
  number_in_string = (char*)malloc(massivesize*sizeof(char));//need to free when return
  symbol = 0;
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
    if (size+3 >= massivesize )  
    {
      massivesize *=2; 
      number_in_string = (char*)realloc(number_in_string,massivesize);     
    }
  }
  number_in_string[size++] = '\n';    
  //size-2 --last symbol-number // (base-1)
  int position = 0;
  int q = size;//bool for first entrance
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
  set_leadingzeros_LongDecimal(BigNum);
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
    //printf("\nledinszeros=%d\n",tmp->leadingzeros);
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
  long long int number = 0;   
  long long int tmp = 0;
  Node *num1 = BigNum1->tail;
  Node *num2 = BigNum2->tail;
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
  long long int sum;
  while(num1 && num2)
  {
    sum = num1->number + num2->number+tmp;
    number = sum % numberbase;
    insert_to_begin_Dlist(Result,&number);
    set_leadingzeros_Node(Result,Result->head);
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
  if (BigNum->size ==1) 
  {
    tmp->leadingzeros = 0;
    return;
  }
  while((tmp->number == 0) &&(tmp->next != NULL)) 
  {
    tmp = tmp->next;
    delete_head(BigNum);  
  }
  BigNum->head->leadingzeros = 0;
  set_size_LongDecimal (BigNum);

}


 void set_leadingzeros_Node(Dlist *BigNum,Node *list) 
{
  long long int i;
  int t = 0;
  i = list->number;
  while((i = i/10) > 0)t++;  
  list->leadingzeros = base-1 - t;
}
void set_leadingzeros_LongDecimal (Dlist *BigNum) //maybe onbt
{
  long long int i;
  Node *tmp = BigNum->head;
  int  t = 0;
  while(tmp)
  {
    t = 0;
    i = tmp->number;
    while((i = i/10) > 0)t++; 
    tmp->leadingzeros = base-1 -t;
    tmp = tmp->next;
  }
  BigNum->head->leadingzeros = 0;
}

void set_size_LongDecimal (Dlist *BigNum)
{
  int size = 0;
  Node *tmp = BigNum->head;
  while(tmp)
  {
    tmp = tmp->next;
    size++;
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

/*int compare_LongDecimal(Dlist *BigNum1,Dlist *BigNum2)//dode
{
  
 assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  int result;
  if (BigNum1->sign < BigNum2->sign) return 0;
  if (BigNum1->sign > BigNum2->sign) return 2;
    
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


*/

void sub_LongDecimal (Dlist *BigNum1,Dlist *BigNum2,Dlist *Result) //perexod and sign
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
  Node *num1,*num2;
  long long int tmp = 0;
  long long int sum ; 
  long long int number;
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
    Result->sign = BigNum2->sign;
  }
   while(num1 && num2)
  {
    sum = num1->number - num2->number-tmp;
    number = (sum >= 0)?sum:(sum +numberbase ) ;
    tmp = (sum < 0)?1:0;
    insert_to_begin_Dlist(Result,&number);
    set_leadingzeros_Node(Result,Result->head);//&
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

void mul_LongDecimal(Dlist *BigNum1,Dlist *BigNum2, Dlist *Result)
{
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  Node *num = NULL;
  long long int tmp = 0;
  long long int sum = 0;
  long int probablysize = BigNum1->size + BigNum2->size; 
  long long int number = 0;
  for(long int p = 0; p < probablysize;p++)  insert_to_begin_Dlist (Result,  &number);
  Node *trace = Result->tail; 
  for(long int i  = 0; i < BigNum1->size;i++ )
  {  
    num = trace;
    //for(long int j = i;  j < BigNum2->size;j++)
    for(long int j = 0;  j < BigNum2->size;j++)
    {
      //num = 
       //num = get_Node_DList (Result,probablysize-j-1);   
       sum = *get_Node_number_Dlist(BigNum1, BigNum1->size-i-1) * (*get_Node_number_Dlist(BigNum2, BigNum2->size-j-1))+tmp + num->number;
        num->number = sum%numberbase;
        tmp = (sum / numberbase);
        num = num->prev;
     
    }
    num->number += tmp;
    trace = trace->prev;
    tmp = 0;
  }  
  Result->sign = BigNum1->sign ^ BigNum2->sign; 
  
 delete_odd_Node(Result);
 set_leadingzeros_LongDecimal(Result);
}

void  add_to_first_LongDecimal(Dlist *BigNum1,Dlist *BigNum2)
{//razvetlv
  assert(BigNum1->size > 0);
  assert(BigNum2->size > 0);
  long long int number = 0;   
  long long int tmp = 0;
  Node *num1 = BigNum1->tail;
  Node *num2 = BigNum2->tail;
  long long int sum;
  while(num1 && num2)
  {
    sum = num1->number + num2->number+tmp;
    number = sum % numberbase;
    num1->number = number;   
    set_leadingzeros_Node(BigNum1,num1);
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
    set_leadingzeros_Node(BigNum1,num1);
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num1 = num1->prev;
  }
  while(num2)
  {
    sum = num2->number + tmp;
    number = sum % numberbase;
    insert_to_begin_Dlist(BigNum1,&number);
    set_leadingzeros_Node(BigNum1,BigNum1->head); 
    tmp = 0;
    if(sum - numberbase >= 0) tmp = 1;
    num2 = num2->prev;
  } 
  if(tmp)
  {
    insert_to_begin_Dlist(BigNum1,&tmp);
    set_leadingzeros_Node(BigNum1,BigNum1->head);
  }
  delete_odd_Node(BigNum1);  
}

void  sub_from_first_LongDecimal(Dlist *BigNum1,Dlist *BigNum2)//think sign mot good 3/5
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
    set_leadingzeros_Node(BigNum1,num1);
    num1 = num1->prev;       
    num2 = num2->prev;                                             
  }  
  while(num1)
  {
    sum = num1->number - tmp;
    number = (sum >= 0)?sum:(sum +numberbase ) ;
    tmp = (sum < 0)?1:0;
    num1->number = number;
    set_leadingzeros_Node(BigNum1,num1);
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
  long long const int position = numberbase/10;///10;
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
      // 45454/100000000 = 0;
      number  = tmp/counter ;
      you = number;
      number = number - 10*prev;// get one number
      mul_on_small_ld(Result,10);
      prev = you;
      Result->tail->number += number ;// insert this number 
       counter /= 10;
      //if (counter == 1) flag = 0;
    }
    if (abscompare_LongDecimal(Result,BigNum2)) return;
    num1 = num1->next;
  }
}


/*
void divide_Dlist(Dlist *BigNum1,Dlist *BigNum2,Dlist *Result) // or can i just a copy
{
  int symbol = 0;
  int flag = 1;
  long long int tmp = 0;
  Dlist *Num = (Dlist*)(malloc(sizeof(Dlist)));
   Dlist *Divider = (Dlist*)(malloc(sizeof(Dlist)));
  Dlist *Subnumber = (Dlist*)(malloc(sizeof(Dlist)));
  copy_Dlist(BigNum1 , Num);//now in n is BigNum 
  copy_Dlist(BigNum2 , Divider);
  Dlist *Subtrahend = (Dlist*)(malloc(sizeof(Dlist)));
  init_Dlist(Subtrahend);
  init_Dlist(Subnumber);
  insert_to_begin_Dlist(Result,&tmp);  
   Dlist *tmpr = (Dlist*)(malloc(sizeof(Dlist)));
    init_Dlist(tmpr);
    int i = 0;
    int size = 0;
    get_subDlist_LongDecimal(Num,BigNum2,tmpr);
    while(tmpr->head->number)
    {
      i++;// ok
      div_on_10(tmpr);  
    }//free tmpr
    printf("i=%d",i);  
   destroy_pointer_Dlist(tmpr);
  while(abscompare_LongDecimal(Num,Divider) ==2  )//o,,,r create a copy of this number?  or without *?
  {
    size = 0;
    flag  = 1;
    get_subDlist_LongDecimal(Num,BigNum2,Subnumber);////
     copy_Dlist(Subnumber,tmpr);
     while(tmpr->head->number)
    {
      size++;// ok
      div_on_10(tmpr);  
    }
    destroy_pointer_Dlist(tmpr);
    if(size>i)mul_on_small_ld (Result, 10); //free tmpr
  
    show_LongDecimal(Subnumber);
    Subtrahend = get_ostatok_Dlist(Subnumber,BigNum2 ,&symbol);//25/3  would be 24
     
     //show_LongDecimal(Subtrahend);
    mul_on_small_ld (Result, 10);
    Result->tail->number += symbol;  
    while((flag = abscompare_LongDecimal(Num,Subtrahend)) == 2)
    {
      mul_on_small_ld(Subtrahend,10);
    }
    if(flag == 0) div_on_10(Subtrahend);  
   
    printf("\nsubtrahene=");
    show_LongDecimal(Subtrahend);
    printf("\nResult=");
    show_LongDecimal(Result);
    sub_from_first_LongDecimal(Num,Subtrahend);
         printf("\nnum=");
    show_LongDecimal(Num);
 
    destroy_pointer_Dlist (Subnumber);
    destroy_pointer_Dlist (Subtrahend);


  }
  // printf("dfsign",Result->sign);
}


//first  get+subDlist
//get a/k*c get c  mul k*0..9 while   max k*c<a
  // mul on short
 
  
*/

void mul_on_small_ld (Dlist *BigNum, long  int number)// ogranicj 
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
  set_leadingzeros_LongDecimal(BigNum);
}  

//Bignum1-subnuumber  максимальное наименьшее число меньшее первого числа 
//BigNum2- divider//and about sign
Dlist * get_ostatok_Dlist(Dlist *BigNum1,Dlist* BigNum2,int *symbol) // скольк раз надо взять второе число чтобы было миним наименьшее
{
  int counter = 1;
  int flag;
  Dlist *Num2 = (Dlist*)(malloc(sizeof(Dlist)));//?
  copy_Dlist(BigNum2 , Num2) ;
   Dlist *Result = (Dlist*)(malloc(sizeof(Dlist)));//?
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
  
// определенно если число A>b      и рахмер 1 больше мин на 
void copy_Dlist(Dlist *BigNum , Dlist*Result)
{
  Node *tmp = BigNum->head;
  init_Dlist (Result);
  while(tmp)
  {
    insert_to_end_Dlist(Result,&tmp->number);
    tmp = tmp->next;
  }
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
  set_leadingzeros_LongDecimal(BigNum);

}
////
///       в делении не учтен ноль когда набратьнельзя\
/
//
// 



void divide_Dlist(Dlist *BigNum1,Dlist *BigNum2,Dlist *Result) // or can i just a copy
{
  Dlist *Raznost = (Dlist*)(malloc(sizeof(Dlist)));
  init_Dlist(Raznost);
  int lenost = 0;
  int symbol = 0;
  long long int tmp = 0;
  int i = 0;
  int size = 0;
  int sizeheadNum;
  int sizeNum;
  int sizeheadSubnumber;
  int indicator;
  int sizeRaznost;
  int sizeSubnumber;
  Dlist *Num = (Dlist*)(malloc(sizeof(Dlist)));
  Dlist *Divider = (Dlist*)(malloc(sizeof(Dlist)));
  Dlist *Subnumber = (Dlist*)(malloc(sizeof(Dlist)));
  copy_Dlist(BigNum1 , Num);//now in n is BigNum 
  copy_Dlist(BigNum2 , Divider);
  Dlist *Subtrahend = (Dlist*)(malloc(sizeof(Dlist)));
  init_Dlist(Subtrahend);
  init_Dlist(Subnumber);
  insert_to_begin_Dlist(Result,&tmp);
  
  
  sizeNum = get_sizeofhead_Dlist(Num) + (Num->size -1)*base;
  get_subDlist_LongDecimal(Num, Divider, Subnumber);
  Subtrahend = get_ostatok_Dlist(Subnumber, Divider, &symbol);
  printf("Subtrahend = ");
  show_LongDecimal(Subtrahend); 
  Result->tail->number = symbol;
  sizeSubnumber = get_sizeofhead_Dlist(Subnumber) + (Subnumber->size -1)*base;
   int expsize = sizeNum - sizeSubnumber+1;
   
  sub_LongDecimal(Subnumber,Subtrahend,Raznost);//was raznos
  sizeRaznost = get_sizeofhead_Dlist(Raznost) + (Raznost->size -1)*base;
  if(Raznost->head->number == 0) sizeRaznost = 0; //equal a==b
  int expectsize = sizeNum-sizeSubnumber+sizeRaznost;
  printf("expsize=%d\n",sizeRaznost);
  int flag = 1;
  while((flag = abscompare_LongDecimal(Num,Subtrahend)) == 2)
  {
    mul_on_small_ld(Subtrahend,10);
  }
  if(flag == 0) div_on_10(Subtrahend);// okey block   
  flag = 1;//really nedd?
  sub_from_first_LongDecimal(Num,Subtrahend);
  destroy_pointer_Dlist (Subnumber);
  destroy_pointer_Dlist (Subtrahend);
  destroy_pointer_Dlist(Raznost);
  int oddzeros = 0;
  
   printf("sizeraznost=%d,i=%d,sizeSubnumber=%d\n",sizeRaznost,i,sizeSubnumber); 
  
  while (abscompare_LongDecimal(Num,Divider) )
  {
    sizeNum = get_sizeofhead_Dlist(Num) + (Num->size -1)*base;
    get_subDlist_LongDecimal(Num, Divider, Subnumber);
    Subtrahend = get_ostatok_Dlist(Subnumber, Divider, &symbol);    
    oddzeros = expectsize - sizeNum;
    //printf("oddzeros=%d\n",oddzeros);
    while(oddzeros>0) 
    { 
      mul_on_small_ld(Result,10);
      oddzeros--;
    }  
     
    sizeSubnumber = get_sizeofhead_Dlist(Subnumber) + (Subnumber->size -1)*base;
    sub_LongDecimal(Subnumber,Subtrahend,Raznost);//was raznos
   
    i = 0;
    
    show_LongDecimal(Subtrahend);
    
     printf("sizeraznost=%d,i=%d,sizeSubnumber=%d\n",sizeRaznost,i,sizeSubnumber); 
    while(sizeRaznost + 1 + (i++) < sizeSubnumber) mul_on_small_ld(Result,10);
     sizeRaznost = get_sizeofhead_Dlist(Raznost) + (Raznost->size -1)*base;
    if(Raznost->head->number == 0) sizeRaznost = 0;
    expectsize = sizeNum-sizeSubnumber + sizeRaznost;//?   
 printf("\n");
     show_LongDecimal(Result);
    mul_on_small_ld(Result,10);
    Result->tail->number += symbol;
    while((flag = abscompare_LongDecimal(Num,Subtrahend)) == 2)
    {
      mul_on_small_ld(Subtrahend,10);
    }
    if(flag == 0) div_on_10(Subtrahend);// okey block   
    flag = 1;//really nedd?
    sub_from_first_LongDecimal(Num,Subtrahend);
    destroy_pointer_Dlist (Subnumber);
    destroy_pointer_Dlist (Subtrahend);
    destroy_pointer_Dlist(Raznost); 
   
   
  }

  //get_subDlist_LongDecimal(Num, Divider, Subnumber);
  //show_LongDecimal(Subnumber);
  //sizeSubnumber = get_sizeofhead_Dlist(Subnumber) + (Subnumber->size -1)*base;
 // while(oddzeros--) mul_on_small_ld(Result,10);
 // printf("size[xerazmost=%d,i=%d,sizesub=%d\n",sizeNum,i,sizeSubnumber);
 // while(sizeRaznost + 1 + (i++) < sizeSubnumber) mul_on_small_ld(Result,10);// or think
 //
   // expectsize--;  
  //} 
 // printf("res=%d,niw=%d\n",sizeResult,result);
 int  sizeResult = get_sizeofhead_Dlist(Result) + (Result->size -1)*base;
 printf("sizeres=%d\n",sizeResult);
  expsize-=sizeResult;
   while((expsize--) > 0)// if error it wiil be threre 
  {
    mul_on_small_ld(Result,10);
  } 
} 
  //fisrts block
  /*sizeheadNum = get_sizeofhead_Dlist(Num);
  sizeNum = sizeheadNum + (Num->size -1)*base;//size NUM  
  
  get_subDlist_LongDecimal(Num, Divider, Subnumber);
  Subtrahend = get_ostatok_Dlist(Subnumber, Divider, &symbol);
  printf("Subtrahend = ");
    show_LongDecimal(Subtrahend); 
  Result->tail->number = symbol;  
  sizeheadSubnumber = get_sizeofhead_Dlist(Subnumber);
  
  //int  sizeSubtrahendnumberhead = get_sizeofhead_Dlist(Subtrahend);
  indicator = 0;
  sub_LongDecimal(Subnumber,Subtrahend,raznost);
  show_LongDecimal(Num);
  
  int sizeheadraznost = get_sizeofhead_Dlist(raznost); ////////////////
  int sizeSubnumber = sizeheadSubnumber + (Subnumber->size-1)* base;
  if (raznost->head->number == 0)  sizeheadraznost = 0;
      lenost = sizeheadraznost+(raznost->size-1)*9;/////////////of 0 in head??
       printf("lemosr%d",lenost);
  if ( lenost == 0) indicator = 1;
  int flag = 1;
  while((flag = abscompare_LongDecimal(Num,Subtrahend)) == 2)
  {
    mul_on_small_ld(Subtrahend,10);
  }
  
  
 if(flag == 0) div_on_10(Subtrahend);// okey block   
  flag = 1;//really nedd?
  
  show_LongDecimal(Subtrahend);
  // find the length
  printf("Subtrahend = ");
    show_LongDecimal(Subtrahend);
  
  sub_from_first_LongDecimal(Num,Subtrahend);
  printf("\nnum=  ");
  show_LongDecimal(Num);
  int  expectsize ;
  if (indicator)   
  {
  //   expectsize = sizeNum -  sizeSubnumber;
     expectsize = sizeNum -  sizeSubnumber -get_sizeofhead_Dlist(Num) -9*(Num->size-1);
     while(expectsize-->0) mul_on_small_ld(Result,10);// first proxod
   //Result->tail->number += symbol;  
  }
  indicator=0;
  destroy_pointer_Dlist (Subnumber);
  destroy_pointer_Dlist (Subtrahend);
  destroy_pointer_Dlist(raznost);//////////////////54
 while (abscompare_LongDecimal(Num,Divider) )
  {
  
    indicator = 0;
    //show_LongDecimal(Num);
    sizeheadNum = get_sizeofhead_Dlist(Num);
    sizeNum = sizeheadNum + (Num->size -1)*base;//size NUM  
    get_subDlist_LongDecimal(Num, Divider, Subnumber);
    Subtrahend = get_ostatok_Dlist(Subnumber, Divider, &symbol);
    sizeheadSubnumber = get_sizeofhead_Dlist(Subnumber);
    sizeSubnumber =  sizeheadSubnumber +(Subnumber->size-1)* base;
   // printf("lenost-=%d,sizesub=%d\n",lenost,sizeSubnumber);
     while((lenost++) < sizeSubnumber-1) {mul_on_small_ld(Result,10);}
     sub_LongDecimal(Subnumber,Subtrahend,raznost);
    sizeheadraznost = get_sizeofhead_Dlist(raznost);
 
    if (raznost->head->number == 0)  sizeheadraznost = 0;
    lenost = sizeheadraznost+(raznost->size-1)*9;
  //int  sizeSubtrahendnumberhead = get_sizeofhead_Dlist(Subtrahend);
    if (lenost == 0) indicator = 1;
     
    
  while((flag = abscompare_LongDecimal(Num,Subtrahend)) == 2) 
  {
    mul_on_small_ld(Subtrahend,10);
  }
  if(flag == 0) div_on_10(Subtrahend);// okey block   
  flag = 1;//really nedd?
    //= mul_on_small_ld(Result,10);
    mul_on_small_ld(Result,10);
    if (indicator)   
  {
  printf("expect=%d",sizeSubnumber);
     expectsize = -sizeSubnumber+get_sizeofhead_Dlist(Num) +9*(Num->size-1);//z?
     printf("expect=%d",expectsize);
     while(expectsize-- > 0) mul_on_small_ld(Result,10);// first proxod
   //Result->tail->number += symbol;  
  }
    Result->tail->number += symbol;  
    printf("Subtrahend = ");
    show_LongDecimal(Subtrahend);
     printf("\n");
  sub_from_first_LongDecimal(Num,Subtrahend);
    printf("Num = ");
    show_LongDecimal(Num);
    
   printf("\n");
  destroy_pointer_Dlist (raznost);
   destroy_pointer_Dlist (Subnumber);
  destroy_pointer_Dlist (Subtrahend);
  
  }
   
 // if ((abscompare_LongDecimal(Num,Divider)==0)&&( Num->head->number != 0)) mul_on_small_ld(Result,10);
  
}


*/

/*

Дано число
узнаем его размер size of whole number = size of head +(BIgNum->size-1)*9
получаем субнамбер в первый раз
получаем число  от 1 до 9 для результата
если суб намбер = дивайдеру то сложно ниже
если суб намбер != дивайдеру все ок пропускаем нижнее(понятро к чему)
домножаем субнамбер
вычитаем из основного числа субнамбер *10^k



ожидаемая длина(в первый раз )  = длина числа - длина субнамбера 

получаем новое число если его длина  =  ожидаемой Ок
сколько нулей еще надо для числа? ожидаемая длина - длина нового числа-> приписываем нули 

 и теперь каждый раз , когда берем вычисляем субнумбер-- снесли  число длина субнамбера -1(не уверен)
 
 конец когда число < делителя 



*/
