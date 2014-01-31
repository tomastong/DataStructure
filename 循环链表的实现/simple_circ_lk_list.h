#ifndef __SIMPLE_CIRC_LK_LIST_H__
#define __SIMPLE_CIRC_LK_LIST_H__

#include "node.h"					// �����

// ��ѭ��������

class SimpleCircLinkList
{
protected:
//  ѭ������ʵ�ֵ����ݳ�Ա:
	Node *head;			// ͷ���ָ��

// ��������
	Node *GetElemPtr(int position) const;	// ����ָ���position������ָ��
	void Init();					// ��ʼ�����Ա�

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SimpleCircLinkList();			// �޲����Ĺ��캯��
	virtual ~SimpleCircLinkList();	// ��������
	int Length() const;				// �����Ա���
	bool Empty() const;				// �ж����Ա��Ƿ�Ϊ��
	void Clear();					// �����Ա����
	void Traverse(int position) const;	// �������Ա�
	void GetElem(int position, int &e) const;	// ��ָ��λ�õ�Ԫ��
	void SetElem(int position, const &e);	// ����ָ��λ�õ�Ԫ��ֵ
	void Delete(int position, int &e);			// ɾ��Ԫ��
	void Insert(int position, const int &e);		// ����Ԫ��
	SimpleCircLinkList(const SimpleCircLinkList &copy); // ���ƹ��캯��
	SimpleCircLinkList &operator =(const SimpleCircLinkList &copy); // ��ֵ�������
};


// ���������ʵ�ֲ���

Node *SimpleCircLinkList::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	if (position == 0)
	{	// ͷ�������Ϊ0
		return head;
	}

	Node *tmpPtr = head->next;// ��tmpPtr�������Ա��Բ��ҵ�position�����
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


void SimpleCircLinkList::Init()
// �����������ʼ�����Ա�
{
	head = new Node;		// ����ͷָ��
	head->next = head;				// ��ѭ�������ͷ�����Ϊͷ��㱾��
}


SimpleCircLinkList::SimpleCircLinkList()
// �������������һ��������
{
	Init();
}


SimpleCircLinkList::~SimpleCircLinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�������ռ�
}

int SimpleCircLinkList::Length() const
// ����������������Ա�Ԫ�ظ���
{
	int count = 0;		// ������
	for (Node *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		count++;	// �����Ա��ÿ��Ԫ�ؽ��м���
	}
	return count;
}


bool SimpleCircLinkList::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == head;
}


void SimpleCircLinkList::Clear()
// ���������������Ա�
{

	int tmpElem;	// ��ʱԪ��ֵ
	while (Length() > 0)
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

void SimpleCircLinkList::Traverse(int position) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	Node *tmpPtr = GetElemPtr(position);
	for (; tmpPtr != GetElemPtr(position-1); tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		if (tmpPtr!=head)        // ��������жϣ�����ͷָ��
		std::cout << tmpPtr->data << "   ";	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
	if (position !=1)
	std::cout << tmpPtr->data << "   ";                   // �������Ҫ�����һ������	
}


void SimpleCircLinkList::GetElem(int position, int &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,
//	����������NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position��Χ��
	//	return NOT_PRESENT;				// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		Node *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
		//return ENTRY_FOUND;
	}
}


void SimpleCircLinkList::SetElem(int position, const int &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
	//	return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		Node *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
		//return SUCCESS;
	}
}

void SimpleCircLinkList::Delete(int position, int &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ����e������ֵ,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		//return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		Node *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position-1������ָ��
		Node *nextPtr = tmpPtr->next;	// nextPtrΪtmpPtr�ĺ��
		tmpPtr->next = nextPtr->next;			// ɾ�����
		e = nextPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ
		delete nextPtr;							// �ͷű�ɾ���
//		return SUCCESS;
	}
}


void SimpleCircLinkList::Insert(int position, const int &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e
//	position��ȡֵ��ΧΪ1��position��Length()+1
//	position�Ϸ�ʱ����SUCCESS, ����������RANGE_ERROR
{
	if (position < 1 || position > Length() + 1)
	{	// position��Χ��
	//	return RANGE_ERROR; // λ�ò��Ϸ�
	}
	else
	{	// position�Ϸ�
		Node *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
		Node *newPtr;
		newPtr = new Node(e, tmpPtr->next);//  �����ǰ�tmpPtr->nextָ��Ľ�㣨�����½ڵ�֮��Ľ�㣩����ֵ���½ڵ㣬��nextָ����֮��Ľ��
		tmpPtr->next = newPtr;			// ��tmpPtr���뵽������
		//return SUCCESS;
	}
}


SimpleCircLinkList::SimpleCircLinkList(const SimpleCircLinkList &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��
{
	int copyLength = copy.Length();		// copy�ĳ���
	int e;
	Init();								// ��ʼ�����Ա�

	for (int curPosition = 1; curPosition <= copyLength; curPosition++)
	{	// ��������Ԫ��
		copy.GetElem(curPosition, e);	// ȡ����curPosition��Ԫ��
		Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
	}
}


SimpleCircLinkList &SimpleCircLinkList::operator =(const SimpleCircLinkList &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա�����ֵ�������
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy�ĳ���
		int e;
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
