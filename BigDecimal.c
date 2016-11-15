#pragma once
#include "stack.c" 

typedef struct 
{
int *number;
int sign;
int size;
} Longdecimal;

int isDigit(int c);
int MaxModuleNum(Longdecimal *a,Longdecimal *b);

void getLongdecimal(Longdecimal *BigNum) //read to massive
{
	int symbol = 0;
	int counter = 0;
	stack_start();
	BigNum->sign = 0;
	if(	(symbol = getchar())!='\n'&& symbol!='q')   ///
		{
			switch(symbol)
			{
				case '+':break;
				case '*':break;
				case 'q':return ;
				case '/':break;
				case '-':
					if( ( symbol = getchar() ) != '\n')
					{
						if ( isDigit( symbol ) )
						{
					 		symbol -='0';
				   		stack_push(symbol);
				   		counter++;
				   		BigNum->sign = 1;
						}
					}
					else
					{					
						return;
					}//it's operand 	
					break;
				default:
					if ( isDigit( symbol ) )
					{
					 symbol -='0';
				   stack_push(symbol);
				   counter++;
					}
					break;
			}
		}
		else return;
	while ( ( (symbol = getchar())!='\n') )
	{
		if(isDigit(symbol))  
		{      // if  c is number then ok   //need to check end
			stack_push(symbol-'0');
			counter++;      //count numbers
		}
	}
	
	BigNum->size = counter;
	//BigNum->sign = (c == '-')?1:0 // checking sign our BigNum
	BigNum->number = (int*)calloc (counter,sizeof(int)*counter );
	int j = 0;
	while( (counter--) >= 0  )
	{
		BigNum->number[j++] = stack_pop();  //   if we had -5434 than now 4345 sign is -  
	}
	stack_free(); 	  
}	


void add( Longdecimal *a , Longdecimal *b,Longdecimal *result) //a+b only for -- or ++
{ 
	int size;
	if (MaxModuleNum(a,b))
	{
		size = a->size+1;
		result->number = (int*)calloc(size , sizeof(int));
	}  
	else
	{	
		 size = b->size+1;
		result->number = (int*)calloc(size , sizeof(int));
	}

	int c = 0;
	int i = 0;
	int j = 0; 
	while( (i < (a->size) ) && (j < (b->size)) )
	{
		if (a->number[i]+b->number[j] > 9)
		{
			result->number[c++] += a->number[i++]+b->number[j++]-10;
			result->number[c] += 1;
		}
		else 
		{
			result->number[c++] += a->number[i++]+b->number[j++];
		}
	
	}
	while (i < a->size)
	{
	 if (a->number[i]+result->number[c] > 9)
		{
			result->number[c++] += a->number[i++]-10;
			result->number[c] += 1;
		}
		else 
		{
			result->number[c++] += a->number[i++];
		}
	
	}
	
	while (j < b->size) 
	{
	if (b->number[j]+result->number[c] > 9)
		{
			result->number[c++] += b->number[j++]-10;
			result->number[c] += 1;
		}
		else 
		{
			result->number[c++] += b->number[j++];
		}
	}
	result->sign = a->sign;
	result->size = (result->number[c] > 0)?size:size-1;
}

void sub (Longdecimal *a, Longdecimal *b,Longdecimal *result) // >0 <0
{
	int size = 0;
	int flag = 1;
	int i = 0;;
	if (MaxModuleNum(a,b))
	{
		 size = a->size;
		result->number = (int*)calloc(size , sizeof(int));
	}  
	else
	{
		size = b->size;
		result->number = (int*)calloc(size , sizeof(int));
		flag = 0;
	}
 if (flag)  
   ///a>b     else b>a
 {
 	//????int i = a->size
 	result->sign = a->sign;
 	for( i = 0;i < b->size;i++)
 	{
 		if ( result->number[i]+a->number[i] - b->number[i] <0)
 		{
 			result->number[i] += a->number[i] - b->number[i]+10;
 	 		--result->number[i+1];
 		}
 		else result->number[i] += a->number[i] - b->number[i];
 	}

 	for(i=b->size ;i<a->size;i++)
 	{
 	 		if ( result->number[i] + a->number[i] <0)
 		{
 			result->number[i] += a->number[i]+10;
 	 		--result->number[i+1];
 		}
 		else result->number[i] += a->number[i];
 	}
 }
 else //b-1
 {
  result->sign = b->sign;
 	for( i = 0;i < a->size;i++)
 	{
 		if ( result->number[i]+b->number[i] - a->number[i] <0)
 		{
 			result->number[i] += b->number[i]-a->number[i]+10;
 	 		--result->number[i+1];
 		}
 		else result->number[i] += b->number[i] - a->number[i];
 	}
 	
 		for(i=a->size ;i<b->size;i++)
 	{
 	 		if ( result->number[i] + b->number[i] <0)
 		{
 			result->number[i] += b->number[i]+10;
 	 		--result->number[i+1];
 		}
 		else result->number[i] += b->number[i];
 	}
 }
 while(result->number[i-1]==0) --i;
 result->size = i;
}


void mul(Longdecimal *a, Longdecimal *b, Longdecimal *result) // ok
{ int pos = 0;
	int newsize = a->size + b->size;
	result->sign = a->sign ^ b->sign;
	result->size = newsize; //too a
	result->number = (int*)calloc(newsize,sizeof(int));
	if (a->size > b->size)
		{
		int p = 0;
		for (int i = 0; i < a->size;i++)
		{
			for( int j = 0 ; j < b->size; j++)
			{
				result->number[j+i] += (b->number[j] * a->number[i]);
			}
			}
			int t;
		while(p<newsize)
		{
			if(result->number[p]>9)
			{
				result->number[p+1]+=result->number[p]/10;	
				result->number[p]%=10;
								
			}
		
		p++;
		}	
	}
	else 
	{
		int p = 0;
		for (int i = 0; i < a->size;i++)
		{
			for( int j = 0 ; j < b->size; j++)
			{
				result->number[j+i] += (b->number[j] * a->number[i]);
			}
			}
			int t;
		while(p<newsize)
		{
			if(result->number[p]>9)
			{
				result->number[p+1]+=result->number[p]/10;	
				result->number[p]%=10;
								
			}
		
		p++;
		}	
	}
	if (result->number[newsize]==0) --result->size;
}	


int isDigit(int c)
 {
  if ( ( (( c = c - '0') < 10) ) && (c >= 0 ))
   {
    return 1;
   } 
  return 0;
 }
 


 
 int MaxModuleNum(Longdecimal *a,Longdecimal *b) //ok
 {
 	
 	int j = a->size;	
  if (a->size == b->size) 
  { 
  	while ( a->number[j] == b->number[j] && j >= 0 ) j--;
  	return (a->number[j] > b->number[j] )?1:0;
 	}
 	else if(a->size > b->size)
			 {
					return 1; 					
			 }
  		 else return 0;
	return 0;
 }
 
 
