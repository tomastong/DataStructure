/***************************Program Description******************************
purpose: ѭ�����еĽ����Ͳ���
         ����һ�£�����ѭ�������ص㣬��׷�Ҹϣ�һ�����ֽ���취
         1�����貼���������ֶ��еĿպ���
         2������һ��Ԫ�صĿռ䣨rear��ָ��ĵ�ԪΪ�գ�
         3��ʹ��һ����������¼������Ԫ�ص�����
         ������õڶ��ַ���
author: Dong-Hong-Yan
created: 2013/4/24 11:08:23
version: codeblocks 10.05����ͨ��
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
    int front;    // �����ͷԪ�ص�λ��
    int rear;     // �����βԪ�ص�λ��
};

void MAKENULL(QUEUE &Q)
{
    Q.front = 0;
    Q.rear = 0;   //���α�����0
}

bool EMPTY(QUEUE *Q)
{
    if (Q->rear== Q->front)     // �ж϶���Ϊ�յ��������мǣ�
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
    if ((Q->rear+1)%MAX_LENGTH == Q->front)     // �ж϶���Ϊ�����������мǣ�
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
        Q.rear = (Q.rear+1)%MAX_LENGTH;     // �ж϶���Ϊ����������������βָ�룬�мǣ�
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
        Q.front = (Q.front+1)%MAX_LENGTH;   // �ж϶���Ϊ������������������ָ�룬�мǣ�
        return Q.elements[Q.front-1];
    }
}

int QUEUELENGTH(QUEUE *Q)         // ����г��ȵ��㷨���мǣ�
{
    return (Q->rear - Q->front + 1 + MAX_LENGTH)%MAX_LENGTH;
}

int main()
{
    QUEUE Q;
    MAKENULL(Q);

    ElemType e;
    int i;
    printf("����ѭ������\n���˳��:\n");
    for (i=1; i<=10; i++)
    {
		      printf("%d ", i);
        ENQUEUE(i, Q);
    }
    ///cout << EMPTY(Q);

    printf("\n����˳��:\n");
    for (i=1; i<=10; i++)
    {
        e = DEQUEUE(Q);
        printf("%d ", e);
    }

   	printf("\n");
    getch();
    return 0;
}
