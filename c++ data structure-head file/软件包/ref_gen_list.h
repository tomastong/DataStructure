#ifndef __GEN_LIST_H__
#define __GEN_LIST_H__

#include "ref_gen_node.h"					// �����������������

// ���������������
template<class ElemType>
class RefGenList
{
protected:
// �������������������ݳ�Ա:
	RefGenListNode<ElemType> *head;			// �������������ͷָ��
	
// ��������
	void ShowHelp(RefGenListNode<ElemType> *hd) const;	
		// ��ʾ��hdΪͷ�����������������
	int DepthHelp(const RefGenListNode<ElemType> *hd);	
		// ������hdΪ��ͷ�������������������
	void ClearHelp(RefGenListNode<ElemType> *hd);		
		// �ͷ���hdΪ��ͷ���������������ṹ
	void CopyHelp(const RefGenListNode<ElemType> *sourceHead, 
		 RefGenListNode<ElemType> *&destHead);	
		// ����destHeadΪͷ������������������Ƴ���sourceHeadΪͷ������������
		// �����
	static void CreateHelp(RefGenListNode<ElemType> *&first);
		// ������firstΪͷ�����������������

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	RefGenList();								// �޲����Ĺ��캯��
	RefGenList(RefGenListNode<ElemType> *hd);	// ��ͷ���ָ�빹���������������
	~RefGenList();								// ��������
	RefGenListNode<ElemType> *First() const;	// �����������������ĵ�һ��Ԫ��
	RefGenListNode<ElemType> *Next(RefGenListNode<ElemType> *elemPtr) const;	                                                                               
		// ����elemPtrָ����������������Ԫ�صĺ��
	bool Empty() const;						// �ж���������������Ƿ�Ϊ��
	void Push(const ElemType &e);			// ��ԭ��Ԫ��e��Ϊ��ͷ���뵽���������������ǰ��
	void Push(RefGenList<ElemType> &subList);	
		// ���ӱ�subList��Ϊ��ͷ���뵽���������������ǰ��
	int Depth();							// ��������������������
	RefGenList(const RefGenList<ElemType> &copy);	// ���ƹ��캯��
	RefGenList<ElemType> &operator =(const RefGenList<ElemType> &copy);// ��ֵ�������
	void Input(void);						// ��������	
	void Show(void);						// ��ʾ�����	
};

// ����������������ʵ�ֲ���
template <class ElemType>
RefGenList<ElemType>::RefGenList()
// �������������һ�����������������
{
	head = new RefGenListNode<ElemType>(HEAD);
	head->ref = 1;							// ������
}

template <class ElemType>
RefGenList<ElemType>::RefGenList(RefGenListNode<ElemType> *hd)
// �����������ͷ���ָ�빹���������������
{
	head = hd;								// ͷ���
}

template <class ElemType>
RefGenListNode<ElemType> *RefGenList<ElemType>::First() const
// ��������������������������ĵ�һ��Ԫ��
{
	return head->nextLink;
}

template <class ElemType>
RefGenListNode<ElemType> *RefGenList<ElemType>::Next(RefGenListNode<ElemType> *elemPtr) const
// �������������elemPtrָ����������������Ԫ�صĺ��
{
	return elemPtr->nextLink;
}

template <class ElemType>
bool RefGenList<ElemType>::Empty() const
// ������������������������Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->nextLink == NULL;
}

template <class ElemType>
void RefGenList<ElemType>::Push(const ElemType &e)
// �����������ԭ��Ԫ��e��Ϊ��ͷ���뵽���������������ǰ��
{
	RefGenListNode<ElemType> *tmpPtr = new RefGenListNode<ElemType>(ATOM, head->nextLink);
	tmpPtr->atom = e;					// ������
	head->nextLink = tmpPtr;			// ��tmpPtr������head��head->nextLink֮�� 
}

template <class ElemType>
void RefGenList<ElemType>::Push(RefGenList<ElemType> &subList)
// ������������ӱ�subList��Ϊ��ͷ���뵽���������������ǰ��
{
	RefGenListNode<ElemType> *tmpPtr = new RefGenListNode<ElemType>(LIST, head->nextLink);
	tmpPtr->subLink = subList.head;		// �ӱ�
	subList.head->ref++;				// subList�������Լ�1
	head->nextLink = tmpPtr;			// ��tmpPtr������head��head->nextLink֮�� 
}

template <class ElemType>
void RefGenList<ElemType>::ShowHelp(RefGenListNode<ElemType> *hd) const
// �����������ʾ��hdΪͷ�����������������
{
	bool frist = true;
	cout << "(";						// ���������������(��ʼ
	for (RefGenListNode<ElemType> *tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink)
	{	// ���δ�����������������Ԫ�� 
		if (frist) frist = false;		// ��һ��Ԫ��
		else cout << ",";				// ��ͬԪ������ö��Ÿ���
		if (tmpPtr->tag == ATOM)
		{	// ԭ�ӽ��
			cout << tmpPtr->atom;
		}
		else
		{	// ����
			ShowHelp(tmpPtr->subLink);
		}
	}
	cout << ")";						// ���������������)����
}

template <class ElemType>
void RefGenList<ElemType>::Show(void)
// �����������ʾ�����	
{
	ShowHelp(head);					// ���ø���������ʾ�����
}


template <class ElemType>
int RefGenList<ElemType>::DepthHelp(const RefGenListNode<ElemType> *hd)
// ���������������hdΪ��ͷ�������������������
{
	if (hd->nextLink == NULL) return 1;// �������������������Ϊ1
	
	int subMaxDepth = 0;				// �ӱ�������
	for (RefGenListNode<ElemType> *tmpPtr = hd->nextLink; tmpPtr != NULL; 
		tmpPtr = tmpPtr->nextLink)
	{	// ���ӱ��������
		if (tmpPtr->tag == LIST)
		{	// �ӱ�
			int curSubDepth = DepthHelp(tmpPtr->subLink);	// �ӱ����
			if (subMaxDepth < curSubDepth) subMaxDepth = curSubDepth;
		}
	}
	return subMaxDepth + 1;				// ����������������Ϊ�ӱ������ȼ�1
}

template <class ElemType>
int RefGenList<ElemType>::Depth()
// �����������������������������
{
	return DepthHelp(head);
}

template <class ElemType>
void RefGenList<ElemType>::ClearHelp(RefGenListNode<ElemType> *hd)
// ����������ͷ���hdΪ��ͷ���������������ṹ
{
	hd->ref--;								// �������Լ�1
	
	if (hd->ref == 0)
	{	// ������Ϊ0,�ͷŽ����ռ�ÿռ�
		RefGenListNode<ElemType> *tmpPre, *tmpPtr;	// ��ʱ���� 
		for (tmpPre = hd, tmpPtr = hd->nextLink; 
			tmpPtr != NULL; tmpPre = tmpPtr, tmpPtr = tmpPtr->nextLink)
		{	// ɨ���������������hd�Ķ���
			delete tmpPre;					// �ͷ�tmpPre
			if (tmpPtr->tag == LIST)
			{	// tmpPtrΪ�ӱ�
				ClearHelp(tmpPtr->subLink);	// �ͷ��ӱ�
			}
		}
		delete tmpPre;						// �ͷ�β���tmpPre
	}
}

template <class ElemType>
RefGenList<ElemType>::~RefGenList()
// ����������ͷ��������������ṹ������������
{
	ClearHelp(head);
}

template <class ElemType>
void RefGenList<ElemType>::CopyHelp(const RefGenListNode<ElemType> *sourceHead, 
	RefGenListNode<ElemType> *&destHead)	
// ��ʼ����: ��sourceHeadΪͷ�����������������Ϊ�ǵݹ��������������
// �������: ����sourceHeadΪͷ������������������Ƴ���destHeadΪͷ������������
//	�����
{
	destHead = new RefGenListNode<ElemType>(HEAD);		// ����ͷ���
	RefGenListNode<ElemType> *destPtr = destHead;		// destHead�ĵ�ǰ���
	destHead->ref = 1;									// ������Ϊ1
	for (RefGenListNode<ElemType> *tmpPtr = sourceHead->nextLink; tmpPtr != NULL; 
		tmpPtr = tmpPtr->nextLink)
	{	// ɨ���������������sourceHead�Ķ���
		destPtr = destPtr->nextLink = new RefGenListNode<ElemType>(tmpPtr->tag);	
			// �����½��
		if (tmpPtr->tag == LIST)
		{	// �ӱ�
			CopyHelp(tmpPtr->subLink, destPtr->subLink);// �����ӱ�
		}
		else
		{	// ԭ�ӽ��
			destPtr->atom = tmpPtr->atom;				// ����ԭ�ӽ��
		}
	}
}

template <class ElemType>
RefGenList<ElemType>::RefGenList(const RefGenList<ElemType> &copy)
// ������������������������copy�������������������--���ƹ��캯��
{
	CopyHelp(copy.head, head);
}

template<class ElemType>
RefGenList<ElemType> &RefGenList<ElemType>::operator =(const RefGenList<ElemType> &copy)
// ������������������������copy��ֵ����ǰ�������������--��ֵ�������
{
	if (&copy != this)
	{
		ClearHelp(head);				// ��յ�ǰ�������������
		CopyHelp(copy.head, head);		// �����������������
	}
	return *this;
}

template<class ElemType>
void RefGenList<ElemType>::CreateHelp(RefGenListNode<ElemType> *&first)
// ���������������firstΪͷ�����������������
{
	char ch = GetChar();					// �����ַ�
	switch (ch)
	{
	case ')':								// ������������������
		return;								// ����
	case '(':								// �ӱ�
		// ��ͷΪ�ӱ�
		first = new RefGenListNode<ElemType>(LIST);// ���ɱ���
		
		RefGenListNode<ElemType> *subHead;	// �ӱ�ָ��
		subHead = new RefGenListNode<ElemType>(HEAD);// �����ӱ��ͷ���
		subHead->ref = 1;					// ������Ϊ1	
		first->subLink = subHead;			// subHeadΪ�ӱ�
		CreateHelp(subHead->nextLink);		// �ݹ齨���ӱ�
		
		ch = GetChar();						// ����','
		if (ch != ',') cin.putback(ch);		// �粻��','����ch���˵�������
		CreateHelp(first->nextLink);		// �������������������һ���
		break;
	default:								// ԭ��
		// ��ͷΪԭ��
		cin.putback(ch);					// ��ch���˵�������
		ElemType amData;					// ԭ�ӽ������
		cin >> amData;						// ����ԭ�ӽ������
		first = new RefGenListNode<ElemType>(ATOM);// ����ԭ����
		first->atom = amData;				// ԭ�ӽ������
		
		ch = GetChar();						// ����','
		if (ch != ',') cin.putback(ch);		// �粻��','����ch���˵�������
		CreateHelp(first->nextLink);		// �������������������һ���
		break;
	}
}

template<class ElemType>
void RefGenList<ElemType>::Input(void)
// �����������������
{
	head = new RefGenListNode<ElemType>(HEAD);	// �����������������ͷ���
	head->ref = 1;								// ������Ϊ1
	
	GetChar();									// �����һ��'('
	RefGenList<ElemType>::CreateHelp(head->nextLink);
		// ������head->nextLinkΪ��ͷ���������������
}

#endif
