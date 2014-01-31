#ifndef __LK_QUEUE_H__
#define __LK_QUEUE_H__

#include "node.h"				// �����

// ��������

class LinkQueue
{
protected:
//  ������ʵ�ֵ����ݳ�Ա:
	Node *front, *rear;					// ��ͷ��βָָ

// ��������:
	//void Init();									// ��ʼ������

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	LinkQueue();									// �޲����Ĺ��캯��
	virtual ~LinkQueue();							// ��������
	int Length() const;								// ����г���
	bool Empty() const;								// �ж϶����Ƿ�Ϊ��
	void Clear();									// ���������
	void Traverse() const ;	// ��������
    void OutQueue(int &e);				// ���Ӳ���
	void GetHead(int &e) const;			// ȡ��ͷ����
    void InQueue(const int &e);			// ��Ӳ���
	LinkQueue(const LinkQueue &copy);		// ���ƹ��캯��
	LinkQueue &operator =(const LinkQueue &copy);// ��ֵ�������
};

// ���������ʵ�ֲ���
/*
void LinkQueue::Init()
// �����������ʼ������
{
	rear = front = new Node;	// ����ͷ���
}*/

LinkQueue::LinkQueue()
// �������������һ���ն���
{
    rear = front = new Node;	// ����ͷ���
}

LinkQueue::~LinkQueue()
// ������������ٶ���
{
	Clear();
}

int LinkQueue::Length() const
// ������������ض��г���
{
	int count = 0;		// ������
	for (Node *tmpPtr = front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;		// ��ջÿ��Ԫ�ؽ��м���
	}
	return count;
}

bool LinkQueue::Empty() const
// ��������������Ϊ�գ��򷵻�true�����򷵻�false
{
   return rear == front;
}

void LinkQueue::Clear()
// �����������ն���
{
	int tmpElem;	// ��ʱԪ��ֵ
	while (Length() > 0)
	{	// ���зǿգ������
		OutQueue(tmpElem);                   // ����ó�������ʾ��Ч��ͬɾ��
	}
}

void LinkQueue::Traverse() const
// ������������ζԶ��е�ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node *tmpPtr = front->next; tmpPtr != NULL;
		tmpPtr = tmpPtr->next)
	{	// �Զ���ÿ��Ԫ�ص��ú���(*visit)
        std::cout << tmpPtr->data << "  ";
	}
}


void LinkQueue::OutQueue(int &e)
// ���������������зǿգ���ôɾ����ͷԪ�أ�����e������ֵ����������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!Empty())
	{	// ���зǿ�
		Node *tmpPtr = front->next;	// ָ�����ͷ��
		e = tmpPtr->data;						// ��e���ض�ͷԪ��
		front->next = tmpPtr->next;				// frontָ����һԪ��
		if (rear == tmpPtr)
		{	// ��ʾ����ǰ������ֻ��һ��Ԫ�أ����Ӻ�Ϊ�ն���
			rear = front;
		}
		delete tmpPtr;							// �ͷų��ӵĽ��
		//return SUCCESS;
	}
	else
	{	// ����Ϊ��
		//return UNDER_FLOW;
	}
}

void LinkQueue::GetHead(int &e) const
// ���������������зǿգ���ô��e���ض�ͷԪ�أ���������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!Empty())
	{	// ���зǿ�
		Node *tmpPtr = front->next;	// ָ�����ͷ��
		e = tmpPtr->data;						// ��e���ض�ͷԪ��
		//return SUCCESS;
	}
	else
	{	// ����Ϊ��
		//return UNDER_FLOW;
	}
}

void LinkQueue::InQueue(const int &e)
// �������������Ԫ��eΪ�µĶ�β������SUCCESS
{
	Node *tmpPtr = new Node(e);	// �����½��
	rear->next = tmpPtr;							// �½��׷���ڶ�β
	rear = tmpPtr;									// rearָ���¶�β
	//return SUCCESS;
}


LinkQueue::LinkQueue(const LinkQueue &copy)
// ����������ɶ���copy�����¶���--���ƹ��캯��
{
//	Init();
	rear = front = new Node;	// ����ͷ���
	for (Node *tmpPtr = copy.front->next; tmpPtr != NULL;
		tmpPtr = tmpPtr->next)
	{	// ��copy����ÿ��Ԫ�ضԵ�ǰ����������в���
		InQueue(tmpPtr->data);
	}
}

LinkQueue &LinkQueue::operator =(const LinkQueue &copy)
// ���������������copy��ֵ����ǰ����--��ֵ�������
{
	if (&copy != this)
	{
		Clear();
		for (Node *tmpPtr = copy.front->next; tmpPtr != NULL;
			tmpPtr = tmpPtr->next)
		{	// ��copy����ÿ��Ԫ�ضԵ�ǰ����������в���
			InQueue(tmpPtr->data);
		}
	}
	return *this;
}

#endif
