#ifndef __SIMPLE_LK_LIST_H__
#define __SIMPLE_LK_LIST_H__

#include <iostream>
#include "node.h"
using namespace std;

enum StatusCode {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED};

// ������������
class SimpleLinkList 
{
protected:
//  ����ʵ�ֵ����ݳ�Ա:
	Node *head;		// ͷ���ָ��

// ��������
	Node  *GetElemPtr(int position) const;	// ����ָ���position������ָ��
	void Init();				// ��ʼ�����Ա�

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SimpleLinkList();			// �޲����Ĺ��캯��
	virtual ~SimpleLinkList();	// ��������
	int Length() const;			// �����Ա���			 
	bool Empty() const;			// �ж����Ա��Ƿ�Ϊ��
	void Clear();				// �����Ա����
	void Traverse() const;	// �������Ա�
	StatusCode GetElem(int position, Info &e) const;	// ��ָ��λ�õ�Ԫ��	
	StatusCode SetElem(int position, const Info &e);	// ����ָ��λ�õ�Ԫ��ֵ
	StatusCode Delete(int position, Info &e);			// ɾ��Ԫ��		
	StatusCode Insert(int position, const Info &e);		// ����Ԫ��
	SimpleLinkList(const SimpleLinkList &copy);	// ���ƹ��캯��
	SimpleLinkList  &operator =(const SimpleLinkList  &copy); // ��ֵ�������
		
};


// �������������ʵ�ֲ���
Node *SimpleLinkList::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	Node *tmpPtr = head;		// ��tmpPtr�������Ա��Բ��ҵ�position�����
	int curPosition = 0;				// tmpPtr��ָ����λ�� 

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


void SimpleLinkList::Init()
// �����������ʼ�����Ա�
{
	head = new Node;		// ����ͷָ��
}

SimpleLinkList::SimpleLinkList()
// �������������һ��������
{
	Init();
}

SimpleLinkList::~SimpleLinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�������ռ�
}

int SimpleLinkList::Length() const
// ����������������Ա�Ԫ�ظ���
{
	int count = 0;		// ������ 
	for (Node *tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;	// �����Ա��ÿ��Ԫ�ؽ��м���
	}
	return count;
}

bool SimpleLinkList::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == NULL;
}

void SimpleLinkList::Clear()
// ���������������Ա�
{

	Info tmpElem;	// ��ʱԪ��ֵ
	while (Length() > 0)
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}


void SimpleLinkList::Traverse() const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node *tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		cout << tmpPtr->data.Age << " " << tmpPtr->data.Name << endl;	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
}

StatusCode SimpleLinkList::GetElem(int position, Info &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,
//	����������NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return NOT_PRESENT;	// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		Node  *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��	
		e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
		return ENTRY_FOUND;
	}
}

 
StatusCode SimpleLinkList::SetElem(int position, const Info &e)
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
		Node  *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
		return SUCCESS;
	}
}


StatusCode SimpleLinkList::Delete(int position, Info &e)
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
		Node  *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position-1������ָ��
		Node  *nextPtr = tmpPtr->next;	// nextPtrΪtmpPtr�ĺ��
		tmpPtr->next = nextPtr->next;			// ɾ�����
		e = nextPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ	
		delete nextPtr;							// �ͷű�ɾ���
		return SUCCESS;
	}
}

 
StatusCode SimpleLinkList::Insert(int position, const Info &e)
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
		Node  *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
		Node  *newPtr;
		newPtr = new Node (e, tmpPtr->next);// �����½��
		tmpPtr->next = newPtr;			// ��tmpPtr���뵽������
		return SUCCESS;
	}
}

 
SimpleLinkList::SimpleLinkList(const SimpleLinkList  &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��
{
	int copyLength = copy.Length();		// copy�ĳ���
    Info e;
	Init();								// ��ʼ�����Ա�

	for (int curPosition = 1; curPosition <= copyLength; curPosition++)
	{	// ��������Ԫ��
		copy.GetElem(curPosition, e);	// ȡ����curPosition��Ԫ��
		Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
	}
}

 
SimpleLinkList  &SimpleLinkList ::operator =(const SimpleLinkList  &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա�����ֵ�������
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy�ĳ���
		Info e;
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
