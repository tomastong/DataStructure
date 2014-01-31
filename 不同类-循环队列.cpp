/***************************Program Description******************************
purpose: 循环队列的建立和操作
         简述一下，由于循环队列特点，你追我赶，一下三种解决办法
         1、另设布尔变量区分队列的空和满
         2、少用一个元素的空间（rear所指向的单元为空）
         3、使用一个计数器记录队列中元素的总数
         这里采用第二种方案
author: Dong-Hong-Yan
created: 2013/4/24 11:08:23
version: codeblocks 10.05编译通过
*****************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define MAX_LENGTH 10
typedef int ElemType;

struct QUEUE
{
    ElemType elements[MAX_LENGTH];
    int front;    // 定义队头元素的位置
    int rear;     // 定义队尾元素的位置
};

void MAKENULL(QUEUE &Q)
{
    Q.front = 0;
    Q.rear = 0;   //而课本上是0
}

bool EMPTY(QUEUE *Q)
{
    if (Q->rear== Q->front)     // 判断队列为空的条件，切记！
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool FULL(QUEUE *Q)
{
    if ((Q->rear+1)%MAX_LENGTH == Q->front)     // 判断队列为满的条件，切记！
    {
        return true;
    }
    else
    {
        return false;
    }
}

ElemType FRONT(QUEUE Q)
{
    if (EMPTY(&Q))
    {
        return NULL;
    }
    else
    {
        return Q.elements[Q.front];
    }
}

void ENQUEUE(ElemType x, QUEUE &Q)
{
    if (FULL(&Q))
    {
        printf("Queue is Full.");
    }
    else
    {
        Q.elements[Q.rear] = x;
        Q.rear = (Q.rear+1)%MAX_LENGTH;     // 判断队列为假满的条件，下移尾指针，切记！
    }
}

ElemType DEQUEUE(QUEUE &Q)
{
    if (EMPTY(&Q))
    {
        printf("Queue is Empty.");
		return -1;
    }
    else
    {
        Q.front = (Q.front+1)%MAX_LENGTH;   // 判断队列为假满的条件，下移首指针，切记！
        return Q.elements[Q.front-1];
    }
}

int QUEUELENGTH(QUEUE *Q)         // 求队列长度的算法，切记！
{
    return (Q->rear - Q->front + 1 + MAX_LENGTH)%MAX_LENGTH;
}

int main()
{
    QUEUE Q;
    MAKENULL(Q);

    ElemType e;
    int i;
    printf("线性循环队列\n入队顺序:\n");
    for (i=1; i<=10; i++)
    {
		      printf("%d ", i);
        ENQUEUE(i, Q);
    }
    ///cout << EMPTY(Q);

    printf("\n出对顺序:\n");
    for (i=1; i<=10; i++)
    {
        e = DEQUEUE(Q);
        printf("%d ", e);
    }

   	printf("\n");
    getch();
    return 0;
}
