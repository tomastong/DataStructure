#include <stdio.h>
#include <iostream>
#include <conio.h>

#define MAX_LENGTH 20         // 共享栈的内存 

typedef int ElemType;

struct STACK
{
    ElemType elements[MAX_LENGTH];
    int top[2];
};

void SETNULL(STACK &S)           // 这里必须取引用符号，负责，对实参Stack的值没影响 
{
    S.top[0] = 0;
    S.top[1] = MAX_LENGTH;       // 这里必须将两边全部初始化为空 
}

bool EMPTY(STACK S)
{                            // 只有两边的全为空才为空 
    return (S.top[1] == MAX_LENGTH)&&(S.top[0] == 0); 
}

bool FULL(STACK S)
{                     // 只有两边的栈顶元素相差1，说明栈满 
    return S.top[1] - S.top[0] == 1; 
}

void PUSH(ElemType x, int i, STACK &S)     // 这里通过两个栈顶“指针”有效解决了 
{
    if ( (S.top[1]-S.top[0]) == 1)
        printf("stack is full");
    else
    {
        switch(i)        // 用switch语句有效选择哪个栈 
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
                    printf("栈编号输入错误！");
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
                    printf("栈编号输入错误！");
        } 
    }
}

ElemType POP(int i, STACK &S)           // 这里必须取引用符号，负责，对实参Stack的值没影响 
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
                    printf("栈编号输入错误！");
        } 
    }
}

int main()
{
    int i=1, x;
    STACK Stack;
    
    SETNULL(Stack);   // 使其为空 
    
    printf("PUSH入栈元素顺序\n");
    printf("Top[0]入栈元素顺序\n");
    for(; i<5; i++)
    {
        PUSH(i, 0, Stack);
        printf("%d ", i);
    } 
    printf("\nTop[1]入栈元素顺序\n");
    for (i=1; i<5; i++) 
    {
        PUSH(2*i, 1, Stack);
        printf("%d ", 2*i);    
    }
    printf("\n\nPOP出栈元素顺序\n");
    printf("Top[0]出栈元素顺序\n");
    for (i=1; i<5; i++)
    {   
        x = POP(0, Stack);
        printf("%d ", x);
    }
    printf("\nTop[1]出栈元素顺序\n");
    for (i=1; i<5; i++)
    {   
        x = POP(1, Stack);
        printf("%d ", x);
    } 
    printf("\n");
    
    getch();
    return 0;
}













