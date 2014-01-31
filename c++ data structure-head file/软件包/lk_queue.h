#ifndef __LK_QUEUE_H__
#define __LK_QUEUE_H__

#include "node.h"				// �����

// ��������

template<class ElemType>
class LinkQueue 
{
protected:
//  ������ʵ�ֵ����ݳ�Ա:
	Node<ElemType> *front, *rear;					// ��ͷ��βָָ

// ��������:
	void Init();									// ��ʼ������

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	LinkQueue();									// �޲����Ĺ��캯��
	virtual ~LinkQueue();							// ��������
	int Length() const;								// ����г���			 
	bool Empty() const;								// �ж϶����Ƿ�Ϊ��
	void Clear();									// ���������
	void Traverse(void (*Visit)(const ElemType &)) const ;	// ��������
	StatusCode OutQueue(ElemType &e);				// ���Ӳ���
	StatusCode GetHead(ElemType &e) const;			// ȡ��ͷ����
	StatusCode InQueue(const ElemType &e);			// ��Ӳ���
	LinkQueue(const LinkQueue<ElemType> &copy);		// ���ƹ��캯��
	LinkQueue<ElemType> &operator =(const LinkQueue<ElemType> &copy);// ��ֵ�������
};

// ���������ʵ�ֲ���

template <class ElemType>
void LinkQueue<ElemType>::Init()
// �����������ʼ������
{
	rear = front = new Node<ElemType>;	// ����ͷ���
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
// �������������һ���ն���
{
	Init();
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
// ������������ٶ���
{
	Clear();		
}

template<class ElemType>
int LinkQueue<ElemType>::Length() const
// ������������ض��г���			 
{
	int count = 0;		// ������ 
	for (Node<ElemType> *tmpPtr = front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;		// ��ջÿ��Ԫ�ؽ��м���
	}
	return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::Empty() const
// ��������������Ϊ�գ��򷵻�true�����򷵻�false
{
   return rear == front;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear() 
// �����������ն���
{
	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (Length() > 0)
	{	// ���зǿգ������
		OutQueue(tmpElem);
	}
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void (*Visit)(const ElemType &)) const 
// ������������ζԶ��е�ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node<ElemType> *tmpPtr = front->next; tmpPtr != NULL; 
		tmpPtr = tmpPtr->next)
	{	// �Զ���ÿ��Ԫ�ص��ú���(*visit)
		(*Visit)(tmpPtr->data);
	}
}


template<class ElemType>
StatusCode LinkQueue<ElemType>::OutQueue(ElemType &e)
// ���������������зǿգ���ôɾ����ͷԪ�أ�����e������ֵ����������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!Empty()) 
	{	// ���зǿ�
		Node<ElemType> *tmpPtr = front->next;	// ָ�����ͷ��
		e = tmpPtr->data;						// ��e���ض�ͷԪ��
		front->next = tmpPtr->next;				// frontָ����һԪ��
		if (rear == tmpPtr)
		{	// ��ʾ����ǰ������ֻ��һ��Ԫ�أ����Ӻ�Ϊ�ն���
			rear = front;
		}
		delete tmpPtr;							// �ͷų��ӵĽ��
		return SUCCESS;
	}
	else
	{	// ����Ϊ��
		return UNDER_FLOW;
	}
}

template<class ElemType>
StatusCode LinkQueue<ElemType>::GetHead(ElemType &e) const
// ���������������зǿգ���ô��e���ض�ͷԪ�أ���������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!Empty()) 
	{	// ���зǿ�
		Node<ElemType> *tmpPtr = front->next;	// ָ�����ͷ��
		e = tmpPtr->data;						// ��e���ض�ͷԪ��
		return SUCCESS;
	}
	else
	{	// ����Ϊ��
		return UNDER_FLOW;
	}
}

template<class ElemType>
StatusCode LinkQueue<ElemType>::InQueue(const ElemType &e)
// �������������Ԫ��eΪ�µĶ�β������SUCCESS
{
	Node<ElemType> *tmpPtr = new Node<ElemType>(e);	// �����½��
	rear->next = tmpPtr;							// �½��׷���ڶ�β
	rear = tmpPtr;									// rearָ���¶�β
	return SUCCESS;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &copy)
// ����������ɶ���copy�����¶���--���ƹ��캯��
{
	Init();
	for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != NULL; 
		tmpPtr = tmpPtr->next)
	{	// ��copy����ÿ��Ԫ�ضԵ�ǰ����������в���
		InQueue(tmpPtr->data);
	}
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator =(const LinkQueue<ElemType> &copy)
// ���������������copy��ֵ����ǰ����--��ֵ�������
{
	if (&copy != this)
	{
		Clear();
		for (Node<ElemType> *tmpPtr = copy.front->next; tmpPtr != NULL; 
			tmpPtr = tmpPtr->next)
		{	// ��copy����ÿ��Ԫ�ضԵ�ǰ����������в���
			InQueue(tmpPtr->data);
		}
	}
	return *this;
}

#endif
