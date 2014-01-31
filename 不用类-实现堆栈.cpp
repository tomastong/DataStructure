#include <stdio.h>
#include <iostream>
#include <conio.h>

#define MAX_LENGTH 64

typedef int ElemType;

struct STACK
{
    ElemType elements[MAX_LENGTH];
    int top;
};

void SETNULL(STACK &S)           // 这里必须取引用符号，负责，对实参Stack的值没影响 
{
    S.top = MAX_LENGTH;    
}

bool EMPTY(STACK S)
{
    return S.top == MAX_LENGTH;
}

bool FULL(STACK S)
{
    return S.top == 0;
}

void PUSH(int x, STACK &S)     // 这里必须取引用符号，负责，对实参Stack的值没影响
{
    if (S.top == 0)
    {
        printf("Stack is Full.");
    }
    else
    {
        S.top--;
        S.elements[S.top] = x;
    }    
} 

ElemType TOP(STACK S)   
{
    if (EMPTY(S))
    {
        return NULL;
    }
    else
    {
        return S.elements[S.top];
    }
}

ElemType POP(STACK &S)           // 这里必须取引用符号，负责，对实参Stack的值没影响 
{
    //printf("%d ", S.top);
    if (EMPTY(S))
    {
         printf("Stack is Empty.");
    }
    else
    {
        S.top++;
        return S.elements[S.top-1];
    }
}

int main()
{
    int i=0, x;
    STACK Stack;
    
    SETNULL(Stack);   // 使其为空 
    
    printf("PUSH入栈元素顺序\n");
    for(; i<10; i++)
    {
        PUSH(i, Stack);
        printf("%d ", i);    
    }
    printf("\n\nPOP出栈元素顺序\n");
    for (i=0; i<10; i++)
    {   
        x = POP(Stack);
        printf("%d ", x);
    }
    printf("\n");
    
    getch();
    return 0;
}













