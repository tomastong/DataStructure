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

void SETNULL(STACK &S)           // �������ȡ���÷��ţ����𣬶�ʵ��Stack��ֵûӰ�� 
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

void PUSH(int x, STACK &S)     // �������ȡ���÷��ţ����𣬶�ʵ��Stack��ֵûӰ��
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

ElemType POP(STACK &S)           // �������ȡ���÷��ţ����𣬶�ʵ��Stack��ֵûӰ�� 
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
    
    SETNULL(Stack);   // ʹ��Ϊ�� 
    
    printf("PUSH��ջԪ��˳��\n");
    for(; i<10; i++)
    {
        PUSH(i, Stack);
        printf("%d ", i);    
    }
    printf("\n\nPOP��ջԪ��˳��\n");
    for (i=0; i<10; i++)
    {   
        x = POP(Stack);
        printf("%d ", x);
    }
    printf("\n");
    
    getch();
    return 0;
}













