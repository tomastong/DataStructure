#include <stdio.h>
#include <iostream>
#include <conio.h>

#define MAX_LENGTH 20         // ����ջ���ڴ� 

typedef int ElemType;

struct STACK
{
    ElemType elements[MAX_LENGTH];
    int top[2];
};

void SETNULL(STACK &S)           // �������ȡ���÷��ţ����𣬶�ʵ��Stack��ֵûӰ�� 
{
    S.top[0] = 0;
    S.top[1] = MAX_LENGTH;       // ������뽫����ȫ����ʼ��Ϊ�� 
}

bool EMPTY(STACK S)
{                            // ֻ�����ߵ�ȫΪ�ղ�Ϊ�� 
    return (S.top[1] == MAX_LENGTH)&&(S.top[0] == 0); 
}

bool FULL(STACK S)
{                     // ֻ�����ߵ�ջ��Ԫ�����1��˵��ջ�� 
    return S.top[1] - S.top[0] == 1; 
}

void PUSH(ElemType x, int i, STACK &S)     // ����ͨ������ջ����ָ�롱��Ч����� 
{
    if ( (S.top[1]-S.top[0]) == 1)
        printf("stack is full");
    else
    {
        switch(i)        // ��switch�����Чѡ���ĸ�ջ 
        {
            case 0:
            {
                S.elements[++S.top[0]] = x;
                break;
            }
            case 1:
            {
                 S.elements[--S.top[1]] = x;
                 break;
            }
            default:
                    printf("ջ����������");
        }    
    }    
} 

ElemType TOP(int i, STACK S)   
{
    if (EMPTY(S))
    {
        return 0;
    }
    else
    {
        switch(i)
        {
            case 0:
            {
                return S.elements[S.top[0]];
                //break;
            }
            case 1:
            {
                 return S.elements[S.top[1]];
                 //break;
            }
            default:
                    printf("ջ����������");
        } 
    }
}

ElemType POP(int i, STACK &S)           // �������ȡ���÷��ţ����𣬶�ʵ��Stack��ֵûӰ�� 
{
    //printf("%d ", S.top);
    if (EMPTY(S))
    {
         printf("Stack is Empty.\n");
    }
    else
    {
        switch(i)
        {
            case 0:
            {
                S.top[0]--;
                return S.elements[S.top[0]+1];
                //break;
            }
            case 1:
            {
                 S.top[1]++;
                 return S.elements[S.top[1]-1];
                 //break;
            }
            default:
                    printf("ջ����������");
        } 
    }
}

int main()
{
    int i=1, x;
    STACK Stack;
    
    SETNULL(Stack);   // ʹ��Ϊ�� 
    
    printf("PUSH��ջԪ��˳��\n");
    printf("Top[0]��ջԪ��˳��\n");
    for(; i<5; i++)
    {
        PUSH(i, 0, Stack);
        printf("%d ", i);
    } 
    printf("\nTop[1]��ջԪ��˳��\n");
    for (i=1; i<5; i++) 
    {
        PUSH(2*i, 1, Stack);
        printf("%d ", 2*i);    
    }
    printf("\n\nPOP��ջԪ��˳��\n");
    printf("Top[0]��ջԪ��˳��\n");
    for (i=1; i<5; i++)
    {   
        x = POP(0, Stack);
        printf("%d ", x);
    }
    printf("\nTop[1]��ջԪ��˳��\n");
    for (i=1; i<5; i++)
    {   
        x = POP(1, Stack);
        printf("%d ", x);
    } 
    printf("\n");
    
    getch();
    return 0;
}













