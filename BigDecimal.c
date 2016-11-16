#pragma once
#include "stack.h" 

typedef struct
{
int *number;
int sign;
int size;

}Longdecimal;


int isDigit (int c);
int MaxModuleNum (Longdecimal *a, Longdecimal *b);
void getLongdecimal(Longdecimal *BigNum) //read to massive
{
	int symbol = 0;
	int counter = 0;
	stack_start();
	BigNum->sign = 0;
	if(	(symbol = getchar())!='\n'&& symbol!='q'&&symbol!=EOF)   /// change  ---better read at once
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
	while ( ( (symbol = getchar()) !='\n') && (symbol != EOF) )
	{
		if(isDigit(symbol))  
		{      // if  c is number then ok   //need to check end
			symbol-='0';
			stack_push(symbol);
			counter++;      //count numbers
		}
	}
	
	BigNum->size = counter;
	//BigNum->sign = (c == '-')?1:0 // checking sign our BigNum
	BigNum->number = (int*)calloc (counter,sizeof(int)*counter );
	int j = 0;
	while( (counter--) > 0  )
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
	if (result->number[newsize-1]==0) --result->size;
}	


int isDigit(int c)
 {
 	c = c- '0';
  if (   ( c < 10)  &&  (c >= 0 ))
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
  	return (a->number[j] >= b->number[j] )?1:0;
 	}
 	else if(a->size > b->size)
			 {
					return 1; 					
			 }
  		 else return 0;
	return 0;
 }
 
 
 
 
 
 ///think about +0 and -0
	//case for 5/100 for Z
//and case when long decimal / 1 	
	
	//
	 void get_minsubnumber(Longdecimal *a, Longdecimal *b, Longdecimal *result);
	 
	 
/*void  divide(Longdecimal *divident, Longdecimal *divisor, Longdecimal *result)
{
	Longdecimal  subtrahend;
	int newsize =  divident->size + 1 - divisor->size; // newsize
	result->number = (int*)calloc(newsize,sizeof(int));
	result->sign = divident->sign^divisor->sign;// sign ok
	get_minsubnumber(divident,divisor,&subtrahend); 
	sub(&subtrahend,divisor,result);
	
	//for (int i  =  0; i)
	int i =1;
	
	for (int j = a->size-1; j>= 0;j++)
	{
	get_minsubnumber(divident,divisor,&subtrahend); 
	// уменьщить длину  числа а если нельзя 
	while(sub(subtrahend,mulsimple(b,i++))); //do it rANDOMLY///
	if i (==0) {;}// ist divident
	//else
	 ada = mulsimple(b,i-1); //tip ok change funtions
	sub(subtrahend,ada);// change?? get ostatok
	// присвоить в массиве  числа остатка
	// was 125/11 now 01  ->  пока не конец цисла ищем субнумбер 015 -11 = 004 ok     
	
	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	for(int i = subtrahend.size-1; i>=0;i--)
	{
		printf("%d",subtrahend.number[i]);
	}
	printf("\n");
}*/

/*
int get_max(int a,int b)
{
	return ((a>b)?a:b);
}
*/
 void reverse(int *massive, int size)
 {
 	int tmp = 0;
 	for (int i = 0 ; i < size/2;i++)
 	{
 		tmp = massive[i];
 		massive[i] = massive[size-1-i];
 		massive[size-1-i] = tmp; 
 	}
 
 }
 void get_minsubnumber(Longdecimal *a, Longdecimal *b, Longdecimal *result) //ok
 {
 	if (MaxModuleNum(a,b) )
 	{
 		int size = 0;
 		result->sign = 0;//change in the beggining
 		for ( int i = a->size-1 ,  j = b->size-1; i >= 0 && j >= 0;i--,j-- )
 		{
 			if (a->number[i] > b->number[j]) {break;}
 			else if (a->number[i] < b->number[j]) 
 			{
 				size++;
 				break;
 			}
 		}
 		result->size =size + b->size;
 		result->number = (int*)calloc(result->size, sizeof(int));
 		for (int i = a->size-1, j = 0 ;j < result->size;j++,i-- )
 		{
 			result->number[j] = a->number[i];
 		}
 		reverse(result->number,result->size);
 		// or change function 
 		/*
 		for(int i = 1; i<10;i++)
 		{
 			
 		
 		
 		}
 		while(MaxModuleNum(result,b))
 		{
 		
 		
 		
 		}
 		*/
 		
 	}
  else  //for Z
  {
  printf("dddddddddddd");
  
  } 
 }
 
 
 void mulsimple(Longdecimal a, int n )////9999 *9//  overflow(?) neeed to check
{
 	int extra = 0;
 	int tmp = 0;
	for(int i = 0; i< a.size;i++)
  {
  	if((a.number[i]*n+extra)>9)
  	{
  		tmp = (a.number[i]*n+extra) / 10;
  		a.number[i] =  (extra+a.number[i]*n)%10 ;
  		extra =  tmp;
  	}
  	else
		{
		 a.number[i] *=n + extra;
		 extra = 0; 
		}
	}
	if (extra)
	{	
		a.number[a.size]=extra;
		a.size++;
		
	}
	for (int i = a.size-1; i >= 0;i--)
	{
		printf("%d",a.number[i]);
	
	}

}

void show_longdecimal(Longdecimal a)
{
 for (int i = a.size-1; i>=0;i--)
 {
 if (a.sign) printf("-");
 printf("%d",a.number[i]);
 }


}
