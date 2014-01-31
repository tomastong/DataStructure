#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#include "node.h"				// �����

// ��ջ��
class LinkStack
{
protected:
//  ��ջʵ�ֵ����ݳ�Ա:
	Node *top;								// ջ��ָ��

// ��������
	void Init();										// ��ʼ��ջ

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	LinkStack();										// �޲����Ĺ��캯��
	virtual ~LinkStack();								// ��������
	int Length() const;									// ��ջ����
	bool Empty() const;									// �ж�ջ�Ƿ�Ϊ��
	void Clear();										// ��ջ���
	void Traverse() const ;		// ����ջ
	void Push(const int &e);					// ��ջ
	void Top(int &e) const;					// ����ջ��Ԫ��
	void Pop(int &e);						// ��ջ
	//LinkStack(const LinkStack<ElemType> &copy);			// ���ƹ��캯��
	//LinkStack<ElemType> &operator =(const LinkStack<ElemType> &copy); // ��ֵ�������
};


// ��ջ���ʵ�ֲ���
void LinkStack::Init()
// �����������ʼ��ջ
{
	top = NULL;				// ����ջ��ָ��
}

LinkStack::LinkStack()
// �������������һ����ջ��
{
	Init();
}

LinkStack::~LinkStack()
// �������������ջ
{
	Clear();
}

int LinkStack::Length() const
// �������������ջԪ�ظ���
{
	int count = 0;		// ������
	for (Node * tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;		// ��ջÿ��Ԫ�ؽ��м���
	}
	return count;
}

bool LinkStack::Empty() const
// �����������ջΪ�գ��򷵻�true�����򷵻�false
{
	return top == NULL;
}

void LinkStack::Clear()
// ������������ջ
{
	int tmpElem;	// ��ʱԪ��ֵ
	while (!Empty())
		Pop(tmpElem);
}

void LinkStack::Traverse() const
// �����������ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)
{
	Node *tmpPtr;
//	LinkStack tmpS;	// ��ʱջ,tmpS��Ԫ��˳���뵱ǰջԪ��˳���෴
	for (tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ǰջ��ÿ��Ԫ��
		std::cout << tmpPtr->data << "  ";	// �Ե�ǰջ��ÿ��Ԫ����ջ��tmpS��
	}

    //int e;
	//for (tmpPtr = tmpS.top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	//{	// ��tmpPtr��ջ����ջ������ָ��ջtmpS��ÿ��Ԫ��
	//	tmpS.Pop(e);		// ��ջtmpS��ÿ��Ԫ�ص��ú���(*visit)
	//	std::cout << e << "  ";
	//}
}

 void LinkStack::Push(const int &e)
// �����������Ԫ��e׷�ӵ�ջ��,��ɹ��򷵼�SUCCESS,�����綯̬�ڴ��Ѻľ�
//	������OVER_FLOW
{
	Node * new_top = new Node(e, top);
	if (new_top == NULL)
	{	// ��̬�ڴ�ľ�
		//return OVER_FLOW;
	}
	else
	{	// �����ɹ�
		top = new_top;
		//return SUCCESS;
	}

}

void LinkStack::Top(int &e) const
// �����������ջ�ǿ�,��e����ջ��Ԫ��,��������SUCCESS,����������UNDER_FLOW
{
	if(Empty())
	{	// ջ��
		//return UNDER_FLOW;
	}
	else
	{	// ջ�ǿ�,�����ɹ�
		e = top->data;				// ��e����ջ��Ԫ��
		//return SUCCESS;
	}
}

void LinkStack::Pop(int &e)
// �����������ջ�ǿ�,ɾ��ջ��Ԫ��,����e����ջ��Ԫ��,��������SUCCESS,����
//	��������UNDER_FLOW
{
	if (Empty())
	{	// ջ��
	//	return UNDER_FLOW;
	}
	else
	{	// �����ɹ�
		Node *old_top = top;	// ��ջ��
		e = old_top->data;				// ��e����ջ��Ԫ��
		top = old_top->next;			// topָ����ջ��
		delete old_top;					// ɾ����ջ��
	//	return SUCCESS;
	}
}


/*
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
*/
#endif
