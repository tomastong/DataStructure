#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#include "node.h"				// �����

// ��ջ��
template<class ElemType>
class LinkStack 
{
protected:
//  ��ջʵ�ֵ����ݳ�Ա:
	Node<ElemType> *top;								// ջ��ָ��

// ��������
	void Init();										// ��ʼ��ջ

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	LinkStack();										// �޲����Ĺ��캯��
	virtual ~LinkStack();								// ��������
	int Length() const;									// ��ջ����			 
	bool Empty() const;									// �ж�ջ�Ƿ�Ϊ��
	void Clear();										// ��ջ���
	void Traverse(void (*Visit)(const ElemType &)) const ;		// ����ջ
	StatusCode Push(const ElemType &e);					// ��ջ
	StatusCode Top(ElemType &e) const;					// ����ջ��Ԫ��
	StatusCode Pop(ElemType &e);						// ��ջ
	LinkStack(const LinkStack<ElemType> &copy);			// ���ƹ��캯��
	LinkStack<ElemType> &operator =(const LinkStack<ElemType> &copy); // ��ֵ�������
};


// ��ջ���ʵ�ֲ���
template <class ElemType>
void LinkStack<ElemType>::Init()
// �����������ʼ��ջ
{
	top = NULL;				// ����ջ��ָ��
}

template<class ElemType>
LinkStack<ElemType>::LinkStack()
// �������������һ����ջ��
{
	Init();
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack()
// �������������ջ
{
	Clear();
}

template <class ElemType>
int LinkStack<ElemType>::Length() const
// �������������ջԪ�ظ���
{
	int count = 0;		// ������ 
	for (Node<ElemType> *tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;		// ��ջÿ��Ԫ�ؽ��м���
	}
	return count;
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const
// �����������ջΪ�գ��򷵻�true�����򷵻�false
{
	return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
// ������������ջ
{
	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (!Empty())
		Pop(tmpElem);
}

template <class ElemType>
void LinkStack<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// �����������ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)
{
	Node<ElemType> *tmpPtr;		
	LinkStack<ElemType> tmpS;	// ��ʱջ,tmpS��Ԫ��˳���뵱ǰջԪ��˳���෴
	for (tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ǰջ��ÿ��Ԫ��
		tmpS.Push(tmpPtr->data);	// �Ե�ǰջ��ÿ��Ԫ����ջ��tmpS��
	}
	
	for (tmpPtr = tmpS.top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr��ջ����ջ������ָ��ջtmpS��ÿ��Ԫ��
		(*Visit)(tmpPtr->data);		// ��ջtmpS��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Push(const ElemType &e)
// �����������Ԫ��e׷�ӵ�ջ��,��ɹ��򷵼�SUCCESS,�����綯̬�ڴ��Ѻľ�
//	������OVER_FLOW
{
	Node<ElemType> *new_top = new Node<ElemType>(e, top);
	if (new_top == NULL) 
	{	// ��̬�ڴ�ľ�
		return OVER_FLOW;
	}
	else
	{	// �����ɹ�
		top = new_top;
		return SUCCESS;
	}
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Top(ElemType &e) const
// �����������ջ�ǿ�,��e����ջ��Ԫ��,��������SUCCESS,����������UNDER_FLOW
{
	if(Empty())
	{	// ջ��
		return UNDER_FLOW;
	}
	else
	{	// ջ�ǿ�,�����ɹ�
		e = top->data;				// ��e����ջ��Ԫ��
		return SUCCESS;
	}
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Pop(ElemType &e)
// �����������ջ�ǿ�,ɾ��ջ��Ԫ��,����e����ջ��Ԫ��,��������SUCCESS,����
//	��������UNDER_FLOW
{
	if (Empty())
	{	// ջ��
		return UNDER_FLOW;
	}
	else
	{	// �����ɹ�
		Node<ElemType> *old_top = top;	// ��ջ��
		e = old_top->data;				// ��e����ջ��Ԫ��
		top = old_top->next;			// topָ����ջ��
		delete old_top;					// ɾ����ջ��
		return SUCCESS;
	}
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy) 
// �����������ջcopy������ջ--���ƹ��캯��
{
	if (copy.Empty())
	{	// copyΪ��
		Init();									// ����һ��ջ
	}
	else 
	{	// copy�ǿ�,����ջ
		top = new Node<ElemType>(copy.top->data);	// ���ɵ�ǰջ��
		Node<ElemType> *buttomPtr = top;			// ��ǰջ��ָ��
		for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{	// ��tmpPtr����ָ������Ԫ��
			buttomPtr->next = new Node<ElemType>(tmpPtr->data); // ��ջ��׷��Ԫ��	
			buttomPtr = buttomPtr->next;					// buttomPtrָ����ջ��
		}
	}
}


template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator = (const LinkStack<ElemType> &copy)
// �����������ջcopy��ֵ����ǰջ--��ֵ�������
{
	if (&copy != this)
	{
		if (copy.Empty())
		{	// copyΪ��
			Init();										// ����һ��ջ
		}
		else 
		{	// copy�ǿ�,����ջ
			Clear();									// ��յ�ǰջ
			top = new Node<ElemType>(copy.top->data);	// ���ɵ�ǰջ��
			Node<ElemType> *buttomPtr = top;			// ��ǰջ��ָ��
			for (Node<ElemType> *tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{	// ��tmpPtr����ָ������Ԫ��
				buttomPtr->next = new Node<ElemType>(tmpPtr->data); // ��ջ��׷��Ԫ��	
				buttomPtr = buttomPtr->next;			// buttomPtrָ����ջ��
			}
		}
	}
	return *this;
}

#endif