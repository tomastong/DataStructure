// �ļ�·����: stat_char\stat_char.h
#ifndef __STAT_CHAR_H__
#define __STAT_CHAR_H__

#include "binary_sort_tree.h"				// ������������

// Ԫ����
struct ElemType
{
// ���ݳ�Ա:
	char ch;								// �ַ�
	int num;								// ���ִ���

// ��Ա����:
	ElemType(){};							// �޲����Ĺ��캯�� 
	virtual ~ElemType(){};					// ��������
	ElemType(char c, int n = 1);			// ���캯�� 
	operator char() const;					// ������ת������
};

// ������Ԫ���༰��غ�����ʵ�ֲ���
ElemType::ElemType(char c, int n)
// ������������ַ�c����ִ���n����Ԫ��
{
	ch = c;									// �ַ�
	num = n;								// ���ִ���
}

ElemType::operator char() const
// ���������������Ԫ������ת��Ϊ�ַ�����--������ת������
{
	return ch;								// �����ַ�
}

void DisplayElem(const ElemType &e)
// �������: ��ʾԪ��
{
	cout << e.ch << ":" << e.num << endl;	// ����Ԫ���������ַ������ִ���
}

void StatChar(char *str)
// �������: ͳ�Ʋ���ʾ�ַ���str�и��ַ����ֵĴ���
{
	BinarySortTree<ElemType, char> t;		// ����������
	for (unsigned int i = 0; i < strlen(str); i++)
	{	// ����ͳ�Ƹ��ַ����ֵĴ���
		BinTreeNode<ElemType> *p = t.Search(str[i]);	// �����ַ�str[i]
		if (p != NULL)
		{	// ���ҳɹ�
			p->data.num++;					// �ַ����ִ����Լ�1 
		}
		else
		{	// ����ʧ��
			ElemType e(str[i]);				// ����Ԫ��
			t.Insert(e);					// ����Ԫ��
		}
	}

	// ��ʾ�ַ�ͳ����Ϣ
	t.InOrder(DisplayElem);					// �����������ʾ���ַ������ִ���
}

#endif





