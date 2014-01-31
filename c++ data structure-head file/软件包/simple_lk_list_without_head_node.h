#ifndef __SIMPLE_LK_LIST_WITHOUT_first_NODE_H__
#define __SIMPLE_LK_LIST_WITHOUT_first_NODE_H__

#include "node.h"

// ��ͷ���ļ�����������
template <class ElemType>
class SimpleLinkListWithoutHeadNode 
{
protected:
//  ����ʵ�ֵ����ݳ�Ա:
	Node<ElemType> *first;		// ָ����Ԫ�ؽṹ��ָ��

// ��������
	Node<ElemType> *GetElemPtr(int position) const;	// ����ָ���position������ָ��
	void Init();				// ��ʼ�����Ա�

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SimpleLinkListWithoutHeadNode();			// �޲����Ĺ��캯��
	virtual ~SimpleLinkListWithoutHeadNode();	// ��������
	int Length() const;			// �����Ա���			 
	bool Empty() const;			// �ж����Ա��Ƿ�Ϊ��
	void Clear();				// �����Ա����
	void Traverse(void (*Visit)(const ElemType &)) const;	// �������Ա�
	StatusCode GetElem(int position, ElemType &e) const;	// ��ָ��λ�õ�Ԫ��	
	StatusCode SetElem(int position, const ElemType &e);	// ����ָ��λ�õ�Ԫ��ֵ
	StatusCode Delete(int position, ElemType &e);			// ɾ��Ԫ��		
	StatusCode Insert(int position, const ElemType &e);		// ����Ԫ��
	SimpleLinkListWithoutHeadNode(const SimpleLinkListWithoutHeadNode<ElemType> &copy);	
		// ���ƹ��캯��
	SimpleLinkListWithoutHeadNode<ElemType> &operator =
		(const SimpleLinkListWithoutHeadNode<ElemType> &copy); // ��ֵ���������
};


// �������������ʵ�ֲ���
template<class ElemType>
Node<ElemType> *SimpleLinkListWithoutHeadNode<ElemType>::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	Node<ElemType> *tmpPtr = first;		// ��tmpPtr�������Ա��Բ��ҵ�position�����
	int curPosition = 1;				// tmpPtr��ָ����λ�� 

	while (tmpPtr != NULL && curPosition < position)
	// ˳ָ�������ң�ֱ��tmpPtrָ���position�����
	{
		tmpPtr = tmpPtr->next;
		curPosition++;
	}

	if (tmpPtr != NULL && curPosition == position)
	{	// ���ҳɹ�
		return tmpPtr;	
	}
	else
	{	// ����ʧ��
		return NULL;	
	}

}

template <class ElemType>
void SimpleLinkListWithoutHeadNode<ElemType>::Init()
// �����������ʼ�����Ա�
{
	first = NULL;		// ������ָ����Ԫ�ؽṹ��ָ��Ϊ��
}

template <class ElemType>
SimpleLinkListWithoutHeadNode<ElemType>::SimpleLinkListWithoutHeadNode()
// �������������һ��������
{
	Init();
}

template <class ElemType>
SimpleLinkListWithoutHeadNode<ElemType>::~SimpleLinkListWithoutHeadNode()
// ����������������Ա�
{
	Clear();			// ������Ա�
}

template <class ElemType>
int SimpleLinkListWithoutHeadNode<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	int count = 0;		// ������ 
	for (Node<ElemType> *tmpPtr = first; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;	// �����Ա��ÿ��Ԫ�ؽ��м���
	}
	return count;
}

template <class ElemType>
bool SimpleLinkListWithoutHeadNode<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return first == NULL;
}

template <class ElemType>
void SimpleLinkListWithoutHeadNode<ElemType>::Clear()
// ���������������Ա�
{

	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (Length() > 0)
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void SimpleLinkListWithoutHeadNode<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node<ElemType> *tmpPtr = first; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		(*Visit)(tmpPtr->data);	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template <class ElemType>
StatusCode SimpleLinkListWithoutHeadNode<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ����������RANGE_ERROR,
//	����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return RANGE_ERROR;
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
StatusCode SimpleLinkListWithoutHeadNode<ElemType>::SetElem(int position, const ElemType &e)
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
StatusCode SimpleLinkListWithoutHeadNode<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ����e������ֵ,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return NOT_PRESENT;	// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		if (position > 1)
		{	// ɾ���ǵ�1��Ԫ��
			tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position-1������ָ��
			Node<ElemType> *nextPtr = tmpPtr->next;	// nextPtrΪtmpPtr�ĺ��
			tmpPtr->next = nextPtr->next;			// ɾ�����
			e = nextPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ	
			delete nextPtr;							// �ͷű�ɾ���
		}
		else
		{	// ɾ����1��Ԫ��
			tmpPtr = first;							// �ݴ�first
			first = first->next;					// firstָ����
			delete tmpPtr;							// �ͷű�ɾ�����
		}
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode SimpleLinkListWithoutHeadNode<ElemType>::Insert(int position, const ElemType &e)
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
		Node<ElemType> *newPtr;				// ָ�򱻲�����
		if (position > 1)
		{	// ����Ԫ�ز�Ϊ��1��Ԫ��
			Node<ElemType> *tmpPtr = GetElemPtr(position - 1);	
				// ȡ��ָ���position-1������ָ��
			newPtr = new Node<ElemType>(e, tmpPtr->next);// �����½��
			tmpPtr->next = newPtr;			// ��tmpPtr���뵽������
		}
		else
		{	// ����Ԫ��Ϊ��1��Ԫ��
			newPtr = new Node<ElemType>(e, first);// �����½��
			first = newPtr;					// newPtrΪ�µĵ�1��Ԫ�صĽ��
		}
		return SUCCESS;
	}
}

template <class ElemType>
SimpleLinkListWithoutHeadNode<ElemType>::
	SimpleLinkListWithoutHeadNode(const SimpleLinkListWithoutHeadNode<ElemType> &copy)
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
SimpleLinkListWithoutHeadNode<ElemType> &SimpleLinkListWithoutHeadNode<ElemType>::
	operator =(const SimpleLinkListWithoutHeadNode<ElemType> &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա�����ֵ���������
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
