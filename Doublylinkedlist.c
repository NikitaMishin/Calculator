
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Doublylinkedlist.h"

void init_Dlist (Dlist *BigNum) 
//undefined sign  and number
{
	//assert(BigNum != NULL); ///??
	BigNum->size = 0;
	BigNum->head = NULL; //ok
	BigNum->tail = NULL; // or 0
	BigNum->sign = 0;
}

void destroy_pointer_Dlist (Dlist *BigNum)//work fine?
{//make assert
  //assert(BigNum != NULL);
  Node *tmp = BigNum->head; //g
  Node *next = NULL;
  while(tmp)
  {
    next = tmp->next;
    free(tmp);
    tmp = next;
  } 
	BigNum->size = 0;
	BigNum->head = NULL; //ok
	BigNum->tail = NULL; // or 0
	BigNum->sign = 0;
}

void insert_to_end_Dlist (Dlist *BigNum,  long long *number)//ok/
{
  Node *tmp = (Node*)malloc(sizeof(Node));
  tmp->number = *number;
  tmp->next = NULL;
  if (BigNum->tail == NULL)
  { 
    tmp->prev = NULL; 
    BigNum->head = tmp;  
    BigNum->tail = tmp;
  }  
  else
  {
    tmp->prev = BigNum->tail;
    BigNum->tail->next = tmp;
    BigNum->tail = tmp;
  }
  if (BigNum->size==1) BigNum->head->next = BigNum->tail;  
  BigNum->size++;
}
 
void insert_to_begin_Dlist (Dlist *BigNum,long long *number) //dod
{
  Node *tmp = (Node*)malloc(sizeof(Node));
  tmp->number = *number;
  tmp->prev = NULL;
  if (BigNum->head == NULL)    
  {
    tmp->next = NULL;
    BigNum->head = tmp;
    BigNum->tail = tmp;
  }
  else 
  { 
    tmp->next = BigNum->head;
    BigNum->head->prev = tmp;
    BigNum->head = tmp;
  }
  if (BigNum->size==1) BigNum->tail->prev =BigNum->head;  
  BigNum->size++ ;
}

void delete_head(Dlist *BigNum) 
{
  assert(BigNum->size > 0); 
  Node *tmp = BigNum->head;
  BigNum->head = tmp->next;
  BigNum->head->prev = NULL;
  //?//>
  if (BigNum->head->next == NULL) BigNum->tail = BigNum->head;
  free(tmp); 
  BigNum->size--;
}

void delete_tail(Dlist *BigNum)
{
  assert(BigNum->size > 0); 
  Node *tmp = BigNum->tail;   
  BigNum->tail = tmp->prev;  
  BigNum->tail->next = NULL;
  if (BigNum->tail->prev==NULL) BigNum->head = BigNum->tail;
  free(tmp);
  BigNum->size--;
}

void delete_Node_pointer_Dlist(Dlist *BigNum,long int position)
{
  assert(position >= 0);
  assert(position < BigNum->size);
  if (position == 0) 
  {
    delete_head(BigNum);
    return;
  }
  if (position == BigNum->size-1 ) 
  {
    delete_tail(BigNum);
    return;
  }
  Node *tmp = get_Node_DList(BigNum, position);
  Node *prev = tmp->prev;
  prev->next  = tmp->next;
  Node *next = tmp->next;
  next->prev = prev; 
	free(tmp);
	BigNum->size--;
}

Node *get_Node_DList( Dlist *BigNum, long int position) 
{
  assert(position >= 0);
  assert(position < BigNum->size);
  Node *tmp = BigNum->head;
  long int i = 0;
  while((i++) < position) tmp = tmp->next;
  return tmp;
}

long long *get_Node_number_Dlist(Dlist *BigNum,long int position)
{
 assert(position >= 0);
 assert(position < BigNum->size);
 Node *tmp = BigNum->head;
 long int i = 0;
 while((i++) < position) tmp = tmp->next;
 return &tmp->number;
}
