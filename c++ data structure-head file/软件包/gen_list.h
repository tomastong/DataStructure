#ifndef __GEN_LIST_H__
#define __GEN_LIST_H__

#include "gen_node.h"						// ���������

// �������
template<class ElemType>
class GenList
{
protected:
// �����������ݳ�Ա:
	GenListNode<ElemType> *head;			// �����ͷָ��
	
// ��������
	void ShowHelp(GenListNode<ElemType> *hd) const;	
		// ��ʾ��hdΪͷ���Ĺ����
	int DepthHelp(const GenListNode<ElemType> *hd);	// ������hdΪ��ͷ�Ĺ��������
	void CopyHelp(const GenListNode<ElemType> *sourceHead, 
		 GenListNode<ElemType> *&destHead);	
		// ����destHeadΪͷ���Ĺ�����Ƴ���sourceHeadΪͷ���Ĺ����
	static void CreateHelp(GenListNode<ElemType> *&first);
		// ������firstΪͷ���Ĺ����

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	GenList();								// �޲����Ĺ��캯��
	GenList(GenListNode<ElemType> *hd);		// ��ͷ���ָ�빹������
	~GenList(){};							// ��������
	GenListNode<ElemType> *First() const;	// ���ع����ĵ�һ��Ԫ��
	GenListNode<ElemType> *Next(GenListNode<ElemType> *elemPtr) const;	                                                                               
		// ����elemPtrָ��Ĺ����Ԫ�صĺ��
	bool Empty() const;						// �жϹ�����Ƿ�Ϊ��
	void Push(const ElemType &e);			// ��ԭ��Ԫ��e��Ϊ��ͷ���뵽�������ǰ��
	void Push(GenList<ElemType> &subList);	// ���ӱ�subList��Ϊ��ͷ���뵽�������ǰ��
	int Depth();							// �����������
	GenList(const GenList<ElemType> &copy);	// ���ƹ��캯��
	GenList<ElemType> &operator =(const GenList<ElemType> &copy);// ��ֵ�������
	void Input(void);						// ��������	
	void Show(void);						// ��ʾ�����	
};

// ��������ʵ�ֲ���
template <class ElemType>
GenList<ElemType>::GenList()
// �������������һ���չ����
{
	head = new GenListNode<ElemType>(HEAD);
}

template <class ElemType>
GenList<ElemType>::GenList(GenListNode<ElemType> *hd)
// �����������ͷ���ָ�빹������
{
	head = hd;								// ͷ���
}

template <class ElemType>
GenListNode<ElemType> *GenList<ElemType>::First() const
// ������������ع����ĵ�һ��Ԫ��
{
	return head->nextLink;
}

template <class ElemType>
GenListNode<ElemType> *GenList<ElemType>::Next(GenListNode<ElemType> *elemPtr) const
// �������������elemPtrָ��Ĺ����Ԫ�صĺ��
{
	return elemPtr->nextLink;
}

template <class ElemType>
bool GenList<ElemType>::Empty() const
// ���������������Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->nextLink == NULL;
}

template <class ElemType>
void GenList<ElemType>::Push(const ElemType &e)
// �����������ԭ��Ԫ��e��Ϊ��ͷ���뵽�������ǰ��
{
	GenListNode<ElemType> *tmpPtr = new GenListNode<ElemType>(ATOM, head->nextLink);
	tmpPtr->atom = e;					// ������
	head->nextLink = tmpPtr;			// ��tmpPtr������head��head->nextLink֮�� 
}

template <class ElemType>
void GenList<ElemType>::Push(GenList<ElemType> &subList)
// ������������ӱ�subList��Ϊ��ͷ���뵽�������ǰ��
{
	GenListNode<ElemType> *tmpPtr = new GenListNode<ElemType>(LIST, head->nextLink);
	tmpPtr->subLink = subList.head;		// �ӱ�
	head->nextLink = tmpPtr;			// ��tmpPtr������head��head->nextLink֮�� 
}

template <class ElemType>
void GenList<ElemType>::ShowHelp(GenListNode<ElemType> *hd) const
// �����������ʾ��hdΪͷ���Ĺ����
{
	bool frist = true;
	cout << "(";						// �������(��ʼ
	for (GenListNode<ElemType> *tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink)
	{	// ���δ��������Ԫ�� 
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
	cout << ")";						// �������)����
}

template <class ElemType>
void GenList<ElemType>::Show(void)
// �����������ʾ�����	
{
	ShowHelp(head);						// ���ø���������ʾ�����
}


template <class ElemType>
int GenList<ElemType>::DepthHelp(const GenListNode<ElemType> *hd)
// ���������������hdΪ��ͷ�Ĺ��������
{
	if (hd->nextLink == NULL) return 1;// �չ��������Ϊ1
	
	int subMaxDepth = 0;				// �ӱ�������
	for (GenListNode<ElemType> *tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink)
	{	// ���ӱ��������
		if (tmpPtr->tag == LIST)
		{	// �ӱ�
			int curSubDepth = DepthHelp(tmpPtr->subLink);	// �ӱ����
			if (subMaxDepth < curSubDepth) subMaxDepth = curSubDepth;
		}
	}
	return subMaxDepth + 1;				// ��������Ϊ�ӱ������ȼ�1
}

template <class ElemType>
int GenList<ElemType>::Depth()
// ������������ع�������
{
	return DepthHelp(head);
}

template <class ElemType>
void GenList<ElemType>::CopyHelp(const GenListNode<ElemType> *sourceHead, GenListNode<ElemType> *&destHead)	
// ��ʼ����: ��sourceHeadΪͷ���Ĺ����Ϊ�ǵݹ�����
// �������: ����sourceHeadΪͷ���Ĺ�����Ƴ���destHeadΪͷ���Ĺ����
{
	destHead = new GenListNode<ElemType>(HEAD);			// ����ͷ���
	GenListNode<ElemType> *destPtr = destHead;			// destHead�ĵ�ǰ���
	for (GenListNode<ElemType> *tmpPtr = sourceHead->nextLink; tmpPtr != NULL; 
		tmpPtr = tmpPtr->nextLink)
	{	// ɨ������sourceHead�Ķ���
		destPtr = destPtr->nextLink = new GenListNode<ElemType>(tmpPtr->tag);	// �����½��
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
GenList<ElemType>::GenList(const GenList<ElemType> &copy)
// ����������ɹ����copy�����¹����--���ƹ��캯��
{
	CopyHelp(copy.head, head);
}

template<class ElemType>
GenList<ElemType> &GenList<ElemType>::operator =(const GenList<ElemType> &copy)
// ����������������copy��ֵ����ǰ�����--��ֵ�������
{
	if (&copy != this)
	{
		CopyHelp(copy.head, head);		// ���ƹ����
	}
	return *this;
}

template<class ElemType>
void GenList<ElemType>::CreateHelp(GenListNode<ElemType> *&first)
// ���������������firstΪͷ���Ĺ����
{
	char ch = GetChar();					// �����ַ�
	switch (ch)
	{
	case ')':								// ����������
		return;								// ����
	case '(':								// �ӱ�
		// ��ͷΪ�ӱ�
		first = new GenListNode<ElemType>(LIST);// ���ɱ���
		
		GenListNode<ElemType> *subHead;		// �ӱ�ָ��
		subHead = new GenListNode<ElemType>(HEAD);// �����ӱ��ͷ���
		first->subLink = subHead;			// subHeadΪ�ӱ�
		CreateHelp(subHead->nextLink);		// �ݹ齨���ӱ�
		
		ch = GetChar();						// ����','
		if (ch != ',') cin.putback(ch);		// �粻��','����ch���˵�������
		CreateHelp(first->nextLink);		// �����������һ���
		break;
	default:								// ԭ��
		// ��ͷΪԭ��
		cin.putback(ch);					// ��ch���˵�������
		ElemType amData;					// ԭ�ӽ������
		cin >> amData;						// ����ԭ�ӽ������
		first = new GenListNode<ElemType>(ATOM);// ����ԭ����
		first->atom = amData;				// ԭ�ӽ������
		
		ch = GetChar();						// ����','
		if (ch != ',') cin.putback(ch);		// �粻��','����ch���˵�������
		CreateHelp(first->nextLink);		// �����������һ���
		break;
	}
}

template<class ElemType>
void GenList<ElemType>::Input(void)
// �����������������	
{
	head = new GenListNode<ElemType>(HEAD);	// ���ɹ����ͷ���
	
	GetChar();								// �����һ��'('
	GenList<ElemType>::CreateHelp(head->nextLink);
		// ������head->nextLinkΪ��ͷ�Ĺ����
}

#endif