#ifndef __DBL_LK_LIST_H__
#define __DBL_LK_LIST_H__

#include "dbl_node.h"				// ˫����������

// ˫��������
class DblLinkList
{
protected:
//  ѭ������ʵ�ֵ����ݳ�Ա:
	DblNode *head;			// ͷ���ָ��
	mutable int curPosition;			// ��ǰλ�õ����
	mutable DblNode * curPtr;	// ָ��ǰλ�õ�ָ��
	int count;							// Ԫ�ظ���

// ��������
	DblNode *GetElemPtr(int position) const;	// ����ָ���position������ָ��
	void Init();				// ��ʼ�����Ա�

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	DblLinkList();				// �޲����Ĺ��캯��
	virtual ~DblLinkList();		// ��������
	int Length() const;			// �����Ա���
	bool Empty() const;			// �ж����Ա��Ƿ�Ϊ��
	void Clear();				// �����Ա����
	void Traverse(int position) const;	// �������Ա�
	int GetCurPosition() const;								// ���ص�ǰλ��
	void GetElem(int position, int &e) const;	// ��ָ��λ�õ�Ԫ��
	void SetElem(int position, const int &e);	// ����ָ��λ�õ�Ԫ��ֵ
	void Delete(int position, int &e);			// ɾ��Ԫ��
	void Insert(int position, const int &e);		// ����Ԫ��
	DblLinkList(const DblLinkList &copy);			// ���ƹ��캯��
	DblLinkList &operator =(const DblLinkList &copy); // ��ֵ�������
};


// �������ʵ�ֲ���

DblNode *DblLinkList::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	if (curPosition < position)
	{	// ��ǰλ����������λ��֮ǰ,������
		for (; curPosition < position; curPosition++)
			curPtr = curPtr->next;			// ����λ��position
	}
	else if (curPosition > position)
	{	// ��ǰλ����������λ��֮��,��ǰ����
		for (; curPosition > position; curPosition--)
			curPtr = curPtr->back;			// ����λ��position
	}

	return curPtr;

}

void DblLinkList::Init()
// �����������ʼ�����Ա�
{
	head = new DblNode; 	// ����ͷָ�� ��ͷ������ʽ��
	head->next = head;				// ��ѭ�������ͷ�����Ϊͷ��㱾��
	curPtr = head;	curPosition = 0;// ��ʼ����ǰλ��
	count = 0;						// ��ʼ��Ԫ�ظ���
}

DblLinkList::DblLinkList()
// �������������һ��������
{
	Init();
}

DblLinkList::~DblLinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�������ռ�
}

int DblLinkList::Length() const
// ����������������Ա�Ԫ�ظ���
{
	return count;
}

bool DblLinkList::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == head;
}

void DblLinkList::Clear()
// ���������������Ա�
{

	int tmpElem;	// ��ʱԪ��ֵ
	while (Length() > 0)
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

void DblLinkList::Traverse(int position) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	// ����˫������Ҳ����for (DblNode *tmpPtr = GetElemPtr(position); tmpPtr != GetElemPtr(position1+1); tmpPtr = tmpPtr->back)
	for (DblNode *tmpPtr = GetElemPtr(position); tmpPtr != GetElemPtr(position1-1); tmpPtr = tmpPtr->back)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		if(tmpPtr != head)
		std::cout << tmpPtr->data << "  ";	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
	std::cout << tmpPtr->data << "  ";
	std::cout << std::endl;
}

int DblLinkList::GetCurPosition() const
// ������������ص�ǰλ��
{
	return curPosition;
}

void DblLinkList::GetElem(int position, int &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,
//	����������NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position��Χ��
	//	return NOT_PRESENT;				// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		DblNode *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
		//return ENTRY_FOUND;
	}
}

void DblLinkList::SetElem(int position, const int &e)
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
		DblNode *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
		//return SUCCESS;
	}
}

void DblLinkList::Delete(int position, int &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ����e������ֵ,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
	//	return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		DblNode *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position - 1������ָ��
		tmpPtr = tmpPtr->next;					// tmpPtrָ���position �����
		tmpPtr->back->next = tmpPtr->next;		// �޸����ҵ�ָ��
		tmpPtr->next->back = tmpPtr->back;		// �޸������ָ��
		e = tmpPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ
		if (position == Length())
		{	// ɾ��β���,��ǰ����Ϊͷ���
			curPosition = 0;					// ���õ�ǰλ�õ����
			curPtr = head;						// ����ָ��ǰλ�õ�ָ��
		}
		else
		{	// ɾ����β���,��ǰ����Ϊ��position�����
			curPosition = position;				// ���õ�ǰλ�õ����
			curPtr = tmpPtr->next;				// ����ָ��ǰλ�õ�ָ��
		}
		count--;								// ɾ���ɹ���Ԫ�ظ�����1
		delete tmpPtr;							// �ͷű�ɾ���

//		return SUCCESS;
	}
}

void DblLinkList::Insert(int position, const int &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e
//	position��ȡֵ��ΧΪ1��position��Length()+1
//	position�Ϸ�ʱ����SUCCESS, ����������RANGE_ERROR
{
	if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		//return RANGE_ERROR; // λ�ò��Ϸ�
	}
	else
	{	// position�Ϸ�
		DblNode *tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
		nextPtr = tmpPtr->next;				// nextPtrָ���position�����
		newPtr = new DblNode(e, tmpPtr, nextPtr);// �����½��
		tmpPtr->next = newPtr;				// �޸����ҵ�ָ��
		nextPtr->back = newPtr;				// �޸������ָ��
		curPosition = position;				// ���õ�ǰλ�õ����
		curPtr = newPtr;					// ����ָ��ǰλ�õ�ָ��
		count++;							// ����ɹ���Ԫ�ظ�����1
	//	return SUCCESS;
	}
}

DblLinkList::DblLinkList(const DblLinkList &copy)
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

DblLinkList &DblLinkList::operator =(const DblLinkList &copy)
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
