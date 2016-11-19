#include <stdlib.h>
#include <stdio.h>
#include "Doublylinkedlist.h"

void init_Dlist (Dlist *BigNum) 
//undefined sign  and number
{
	//assert(sizeof(BigNum)==0); ///??
	//BigNum = (Dlist*)malloc(sizeof(Dlist)); ///?
	BigNum->size = 0;
	BigNum->head = NULL; //ok
	BigNum->tail = NULL; // or 0
}

void destroy_pointer_Dlist (Dlist *BigNum)
{
 //assert();
 Node *tmp = BigNum->head; //g
 Node *next = NULL;
 while(tmp)
 {
  next = tmp->next;
  free(tmp);
  tmp = NULL;
  tmp = next;
 } 
 Dlist *m = BigNum; //if BigNum- is pointer
 free(m);
 
}

void destroy_fixed_Dlist (Dlist *BigNum)
{
 //assert();
 Node *tmp = BigNum->head; //g
 Node *next = NULL;
 while(tmp)
 {
  next = tmp->next;
  free(tmp);
  tmp = NULL;
  tmp = next;
 } 
}

void insert_to_end_Dlist (Dlist *BigNum, int *number)
{
	//assert();
 Node *tmp = (Node*)malloc(sizeof(Node));
 tmp->number = *number;
 tmp->next = NULL;
 if (BigNum->tail == NULL)
 { 
  tmp->prev = NULL; 
  BigNum->head = tmp;  
  BigNum->tail = tmp;}  
 else
 {
  tmp->prev = BigNum->tail;
  BigNum->tail->next = tmp;
  BigNum->tail = tmp;
 }
 BigNum->size++;
}

void insert_to_begin_Dlist (Dlist *BigNum,int *number)
{
//assert();
 Node *tmp = (Node*)malloc(sizeof(Node));
 tmp->number = *number;
 tmp->prev = NULL;
 if (BigNum->head==NULL) 
 {
  tmp->next = NULL;
  BigNum->head = tmp;
  BigNum->tail = tmp;
 }
 else 
 { 
  BigNum->head->prev = tmp;
  tmp->next = BigNum->head;
  BigNum->head = tmp;
 }
 BigNum->size++ ;
}
