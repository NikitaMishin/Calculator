#pragma once


// 
// Deсlaration of DoublyLnked List
//
typedef struct Node
{
 int number;  // or double 2^16 -1 
 struct Node *prev;
 struct Node *next;
} Node;

typedef struct Dlist
{
 int size; // size of number
 char sign;//? //sign of number
 Node *head; // [pointer on head
 Node *tail; // pointr on tail
 
} Dlist;

void init_Dlist (Dlist *BigNum);
void destroy_pointer_Dlist (Dlist *BigNum);
void destroy_fixed_Dlist (Dlist *BigNum);
void insert_to_end_Dlist (Dlist *BigNum, int *number);
void insert_to_begin_Dlist (Dlist *BigNum ,int *number);
void delete_head (Dlist *BigNum);
void delete_tail (Dlist *BigNum);
void delete_Node_pointer_Dlist (Dlist *BigNum, int position);
Node *get_Node_DList (Dlist* BigNum, int position);
void insert_Node_Dlist (Dlist *BigNum, int position);
int *get_Node_number_Dlist(Dlist *BigNum,int position);

