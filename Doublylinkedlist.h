#pragma once


// 
// Deсlaration of DoublyLnked List
//
typedef struct Node
{
 unsigned long long int number;  // 2^128 -1  .... max 19 position 
 struct Node *prev;
 struct Node *next;
} Node;

typedef struct Dlist
{
 long int size; // size of number
 char sign;//? //sign of number
 Node *head; // [pointer on head
 Node *tail; // pointr on tail
 
} Dlist;

void init_Dlist (Dlist *BigNum);
void destroy_pointer_Dlist (Dlist *BigNum);
void destroy_fixed_Dlist (Dlist *BigNum);
void insert_to_end_Dlist (Dlist *BigNum, unsigned long long int *number);
void insert_to_begin_Dlist (Dlist *BigNum ,unsigned long long int *number);
void delete_head (Dlist *BigNum);
void delete_tail (Dlist *BigNum);
void delete_Node_pointer_Dlist (Dlist *BigNum, long int position);
Node *get_Node_DList (Dlist* BigNum, long int position);
void insert_Node_Dlist (Dlist *BigNum,  long int position);
unsigned long long int  *get_Node_number_Dlist(Dlist *BigNum, long int position);

