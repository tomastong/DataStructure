#ifndef __SIMPLE_CIRC_LK_LIST_H__
#define __SIMPLE_CIRC_LK_LIST_H__

#include "node.h"					// �����

// ��ѭ��������
template <class ElemType>
class SimpleCircLinkList 
{
protected:
//  ѭ������ʵ�ֵ����ݳ�Ա:
	Node<ElemType> *head;			// ͷ���ָ��

// ��������
	Node<ElemType> *GetElemPtr(int position) const;	// ����ָ���position������ָ��
	void Init();					// ��ʼ�����Ա�

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SimpleCircLinkList();			// �޲����Ĺ��캯��
	virtual ~SimpleCircLinkList();	// ��������
	int Length() const;				// �����Ա���			 
	bool Empty() const;				// �ж����Ա��Ƿ�Ϊ��
	void Clear();					// �����Ա����
	void Traverse(void (*Visit)(const ElemType &)) const;	// �������Ա�
	StatusCode GetElem(int position, ElemType &e) const;	// ��ָ��λ�õ�Ԫ��	
	StatusCode SetElem(int position, const ElemType &e);	// ����ָ��λ�õ�Ԫ��ֵ
	StatusCode Delete(int position, ElemType &e);			// ɾ��Ԫ��		
	StatusCode Insert(int position, const ElemType &e);		// ����Ԫ��
	SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy); // ���ƹ��캯��
	SimpleCircLinkList<ElemType> &operator =(const SimpleCircLinkList<ElemType> &copy); // ��ֵ�������
};


// ���������ʵ�ֲ���
template<class ElemType>
Node<ElemType> *SimpleCircLinkList<ElemType>::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	if (position == 0)
	{	// ͷ�������Ϊ0
		return head;
	}

	Node<ElemType> *tmpPtr = head->next;// ��tmpPtr�������Ա��Բ��ҵ�position�����
	int curPosition = 1;				// tmpPtr��ָ����λ�� 

	while (tmpPtr != head && curPosition < position)
	// ˳ָ�������ң�ֱ��tmpPtrָ���position�����
	{
		tmpPtr = tmpPtr->next;
		curPosition++;
	}

	if (tmpPtr != head && curPosition == position)
	{	// ���ҳɹ�
		return tmpPtr;	
	}
	else
	{	// ����ʧ��
		return NULL;	
	}

}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Init()
// �����������ʼ�����Ա�
{
	head = new Node<ElemType>;		// ����ͷָ��
	head->next = head;				// ��ѭ�������ͷ�����Ϊͷ��㱾��
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList()
// �������������һ��������
{
	Init();
}

template <class ElemType>
SimpleCircLinkList<ElemType>::~SimpleCircLinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�������ռ�
}

template <class ElemType>
int SimpleCircLinkList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	int count = 0;		// ������ 
	for (Node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;	// �����Ա��ÿ��Ԫ�ؽ��м���
	}
	return count;
}

template <class ElemType>
bool SimpleCircLinkList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == head;
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Clear()
// ���������������Ա�
{

	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (Length() > 0)
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void SimpleCircLinkList<ElemType>::Traverse(int position) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	Node *tmpPtr = GetElemPtr(position);
	for (; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		std::cout << tmpPtr->data;	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,
//	����������NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return NOT_PRESENT;				// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��	
		e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
		return ENTRY_FOUND;
	}
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ����e������ֵ,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position-1������ָ��
		Node<ElemType> *nextPtr = tmpPtr->next;	// nextPtrΪtmpPtr�ĺ��
		tmpPtr->next = nextPtr->next;			// ɾ�����
		e = nextPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ	
		delete nextPtr;							// �ͷű�ɾ���
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode SimpleCircLinkList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e
//	position��ȡֵ��ΧΪ1��position��Length()+1
//	position�Ϸ�ʱ����SUCCESS, ����������RANGE_ERROR
{
	if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		return RANGE_ERROR; // λ�ò��Ϸ�
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
		Node<ElemType> *newPtr;
		newPtr = new Node<ElemType>(e, tmpPtr->next);// �����½��
		tmpPtr->next = newPtr;			// ��tmpPtr���뵽������
		return SUCCESS;
	}
}

template <class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList(const SimpleCircLinkList<ElemType> &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��
{
	int copyLength = copy.Length();		// copy�ĳ���
	ElemType e;
	Init();								// ��ʼ�����Ա�

	for (int curPosition = 1; curPosition <= copyLength; curPosition++)
	{	// ��������Ԫ��
		copy.GetElem(curPosition, e);	// ȡ����curPosition��Ԫ��
		Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
	}
}

template <class ElemType>
SimpleCircLinkList<ElemType> &SimpleCircLinkList<ElemType>::operator =(const SimpleCircLinkList<ElemType> &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա�����ֵ�������
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy�ĳ���
		ElemType e;
		Clear();							// ��յ�ǰ���Ա�

		for (int curPosition = 1; curPosition <= copyLength; curPosition++)
		{	// ��������Ԫ��
			copy.GetElem(curPosition, e);	// ȡ����curPosition��Ԫ��
			Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
		}
	}
	return *this;
}

#endif
