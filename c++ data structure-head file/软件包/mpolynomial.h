#ifndef __MPOLYNOMIAL_H__
#define __MPOLYNOMIAL_H__

#include "mpolynomial_node.h"					// mԪ����ʽ�����

// mԪ����ʽ��
template<class CoefType>
class MPolynomial
{
protected:
// mԪ����ʽ������ݳ�Ա:
	MPolynomialNode<CoefType> *head;			// mԪ����ʽͷָ��

// ��������
	void ShowHelp(MPolynomialNode<CoefType> *hd) const;	
		// ��ʾ��hdΪͷ����mԪ����ʽ
	void CopyHelp(const MPolynomialNode<CoefType> *sourceHead, 
		 MPolynomialNode<CoefType> *&destHead);
		// ����destHeadΪͷ����mԪ����ʽ���Ƴ���sourceHeadΪͷ����mԪ����ʽ
	static void CreateHelp(MPolynomialNode<CoefType> *&first);
		// ������firstΪͷ����mԪ����ʽ

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	MPolynomial();								// �޲����Ĺ��캯��
	MPolynomial(MPolynomialNode<CoefType> *hd);	// ��ͷ���ָ�빹��mԪ����ʽ
	~MPolynomial(){};							// ��������
	MPolynomialNode<CoefType> *First() const;	// ����mԪ����ʽ�ĵ�һ�����
	MPolynomialNode<CoefType> *Next(MPolynomialNode<CoefType> *elemPtr) const;	                                                                               
		// ����elemPtrָ���mԪ����ʽ��ĺ��
	bool Empty() const;							// �ж�mԪ����ʽ�Ƿ�Ϊ��(0����ʽ)
	MPolynomial(const MPolynomial<CoefType> &copy);		// ���ƹ��캯��
	MPolynomial<CoefType> &operator =(const MPolynomial<CoefType> &copy);// ��ֵ�������
	void Input(void);						// ��������	
	void Show(void);						// ��ʾ�����	
};

// mԪ����ʽ���ʵ�ֲ���
template <class CoefType>
MPolynomial<CoefType>::MPolynomial()
// �������������һ����mԪ����ʽ
{
	head = new MPolynomialNode<CoefType>(HEAD);
}

template <class CoefType>
MPolynomial<CoefType>::MPolynomial(MPolynomialNode<CoefType> *hd)
// �����������ͷ���ָ�빹��mԪ����ʽ
{
	head = hd;								// ͷ���
}

template <class CoefType>
MPolynomialNode<CoefType> *MPolynomial<CoefType>::First() const
// �������������mԪ����ʽ�ĵ�һ�����
{
	return head->nextLink;
}

template <class CoefType>
MPolynomialNode<CoefType> *MPolynomial<CoefType>::Next(MPolynomialNode<CoefType> *elemPtr) const
// �������������elemPtrָ���mԪ����ʽ��ĺ��
{
	return elemPtr->nextLink;
}

template <class CoefType>
bool MPolynomial<CoefType>::Empty() const
// �����������mԪ����ʽΪ��(0����ʽ)���򷵻�true�����򷵻�false
{
	return head->nextLink == NULL;
}

template <class CoefType>
void MPolynomial<CoefType>::ShowHelp(MPolynomialNode<CoefType> *hd) const
// �����������ʾ��hdΪͷ����mԪ����ʽ
{
	bool frist = true;
	if (hd->nextLink != NULL) cout << hd->var;	// ��ʾ�ǿ�mԪ����ʽ��������
	cout << "(";								// mԪ����ʽ��(��ʼ
	for (MPolynomialNode<CoefType> *tmpPtr = hd->nextLink; tmpPtr != NULL; 
		tmpPtr = tmpPtr->nextLink)
	{	// ���δ���mԪ����ʽ����
		if (frist) frist = false;				// ��һ��
		else cout << ",";						// ��ͬ��֮���ö��Ÿ���
		if (tmpPtr->tag == ATOM)
		{	// ԭ�ӽ��
			cout << tmpPtr->atom.coef;			// ��ʾϵ��
			cout << "^" << tmpPtr->atom.exp;	// ��ʾָ��
		}
		else
		{	// ����
			ShowHelp(tmpPtr->list.subLink);		// ��ʾ�ӱ�
			cout << "^" << tmpPtr->list.exp;	// ��ʾָ��
		}
	}
	cout << ")";								// mԪ����ʽ��)����
}

template <class CoefType>
void MPolynomial<CoefType>::Show(void)
// �����������ʾ�����	
{
	ShowHelp(head);						// ���ø���������ʾ�����
}

template <class CoefType>
void MPolynomial<CoefType>::CopyHelp(const MPolynomialNode<CoefType> *sourceHead, MPolynomialNode<CoefType> *&destHead)	
// ��ʼ����: ��sourceHeadΪͷ����mԪ����ʽΪ�ǵݹ�mԪ����ʽ
// �������������sourceHeadΪͷ����mԪ����ʽ���Ƴ���destHeadΪͷ����mԪ����ʽ
{
	destHead = new MPolynomialNode<CoefType>(HEAD);			// ����ͷ���
	destHead->var = sourceHead->var;						// ����ͷ����������
	MPolynomialNode<CoefType> *destPtr = destHead;			// destHead�ĵ�ǰ���
	for (MPolynomialNode<CoefType> *tmpPtr = sourceHead->nextLink; tmpPtr != NULL; 
		tmpPtr = tmpPtr->nextLink)
	{	// ɨ��mԪ����ʽsourceHead�Ķ���
		destPtr = destPtr->nextLink = new MPolynomialNode<CoefType>(tmpPtr->tag);	// �����½��
		if (tmpPtr->tag == LIST)
		{	// �ӱ�
			CopyHelp(tmpPtr->list.subLink, destPtr->list.subLink);	// �����ӱ�
			destPtr->list.exp = tmpPtr->list.exp;			// ����ָ��
		}
		else
		{	// ԭ�ӽ��
			destPtr->atom.coef = tmpPtr->atom.coef;			// ����ϵ��
			destPtr->atom.exp = tmpPtr->atom.exp;			// ����ָ��
		}
	}
}

template <class CoefType>
MPolynomial<CoefType>::MPolynomial(const MPolynomial<CoefType> &copy)
// �����������mԪ����ʽcopy������mԪ����ʽ--���ƹ��캯��
{
	CopyHelp(copy.head, head);			// ��mԪ����ʽcopy������mԪ����ʽ
}

template<class CoefType>
MPolynomial<CoefType> &MPolynomial<CoefType>::operator =(const MPolynomial<CoefType> &copy)
// �����������mԪ����ʽcopy��ֵ����ǰmԪ����ʽ--��ֵ�������
{
	if (&copy != this)
	{
		CopyHelp(copy.head, head);		// ����mԪ����ʽ
	}
	return *this;
}

template<class CoefType>
void MPolynomial<CoefType>::CreateHelp(MPolynomialNode<CoefType> *&first)
// ���������������firstΪͷ����mԪ����ʽ
{
	CoefType tmpCoef;							// ԭ�ӽ�����ʱϵ��
	int tmpExp;									// ԭ�ӽ�����ʱָ��
	char ch = tolower(GetChar());				// �����ַ�
	switch (ch)
	{
	case ')':									// mԪ����ʽ�������
		return;									// ����
	case 'a':									// ������
	case 'b':									// ������
	case 'c':									// ������
	case 'd':									// ������
	case 'e':									// ������
	case 'f':									// ������
	case 'g':									// ������
	case 'h':									// ������
	case 'i':									// ������
	case 'j':									// ������
	case 'k':									// ������
	case 'l':									// ������
	case 'm':									// ������
	case 'n':									// ������
	case 'o':									// ������
	case 'p':									// ������
	case 'q':									// ������
	case 'r':									// ������
	case 's':									// ������
	case 't':									// ������
	case 'u':									// ������
	case 'v':									// ������
	case 'w':									// ������
	case 'x':									// ������
	case 'y':									// ������
	case 'z':									// ������
		// ��ͷΪ�ӱ�
		GetChar();								// ����'('
		first = new MPolynomialNode<CoefType>(LIST);// ���ɱ���
		
		MPolynomialNode<CoefType> *subHead;		// �ӱ�ָ��
		subHead = new MPolynomialNode<CoefType>(HEAD);// �����ӱ��ͷ���
		subHead->var = ch;						// �ӱ��������	
		first->list.subLink = subHead;			// subHeadΪ�ӱ�
		CreateHelp(subHead->nextLink);			// �ݹ齨���ӱ�
		GetChar();								// ����'^'
		cin >> tmpExp;							// ��������ָ��
		first->list.exp = tmpExp;				// �����ָ��
		
		ch = GetChar();							// ����','
		if (ch != ',') cin.putback(ch);			// �粻��','����ch���˵�������
		CreateHelp(first->nextLink);			// ����mԪ����ʽ��һ���
		break;
	default:									// ԭ��
		// ��ͷΪԭ��
		cin.putback(ch);						// ��ch���˵�������
		cin >> tmpCoef;							// ����ԭ�ӽ���ϵ��
		GetChar();								// ����'^'
		cin >> tmpExp;							// ����ԭ�ӽ���ָ��
		first = new MPolynomialNode<CoefType>(ATOM);// ����ԭ����
		first->atom.coef = tmpCoef;				// ԭ�ӽ���ϵ��
		first->atom.exp = tmpExp;				// ԭ�ӽ���ָ��
		
		ch = GetChar();							// ����','
		if (ch != ',') cin.putback(ch);			// �粻��','����ch���˵�������
		CreateHelp(first->nextLink);			// ����mԪ����ʽ��һ���
		break;
	}
}

template<class CoefType>
istream &operator >>(istream &inStream, MPolynomial<CoefType> &in)
// ������������������>>
{
	MPolynomialNode<CoefType> *head;			// ͷ���
	head = new MPolynomialNode<CoefType>(HEAD);	// ����mԪ����ʽͷ���
	
	char ch = tolower(GetChar(inStream));		// �������������һ��'('
	if (ch >= 'a' && ch <= 'z') 
	{	// �������������
		head->var = ch;							// ������
		GetChar(inStream);						// �����һ��'('
	}
	MPolynomial<CoefType>::CreateHelp(inStream, head->nextLink);
		// ������head->nextLinkΪ��ͷ��mԪ����ʽ
	
	in = (MPolynomial<CoefType>)head;			// ����mԪ����ʽ
	
	return inStream;
}

template<class CoefType>
void MPolynomial<CoefType>::Input(void)
// �����������������	
{
	head = new MPolynomialNode<CoefType>(HEAD);	// ����mԪ����ʽͷ���
	
	char ch = tolower(GetChar());				// �������������һ��'('
	if (ch >= 'a' && ch <= 'z') 
	{	// �������������
		head->var = ch;							// ������
		GetChar();								// �����һ��'('
	}
	MPolynomial<CoefType>::CreateHelp(head->nextLink);
		// ������head->nextLinkΪ��ͷ��mԪ����ʽ
}


#endif