#ifndef __RADIX_SORT_H__
#define __RADIX_SORT_H__

#include "lk_list.h"			// ��������

template <class ElemType>
void Distribute(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[])
// ��ʼ����: rΪ����,dΪ�ؼ���λ��,list[0 .. r - 1]Ϊ����������Ա�����
// �������: ���е�i�˷���
{
	for (int power = (int)pow((double)r, i - 1), j = 0; j < n; j++)
	{	// ���е�i�����
		int index = (elem[j] / power) % r;		
		list[index].Insert(list[index].Length() + 1, elem[j]); 
	}
}

template <class ElemType>
void Colect(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[])
// ��ʼ����: rΪ����,dΪ�ؼ���λ��,list[0 .. r - 1]Ϊ����������Ա�����
// �������: ���е�i���ռ�
{
	for (int k = 0, j = 0; j < r; j++)
	{	// ���е�i�����
		ElemType tmpElem;
		while (!list[j].Empty())
		{	// �ռ�list[j]
			list[j].Delete(1, tmpElem);
			elem[k++] = tmpElem;
		}
	}
}

template <class ElemType>
void RadixSort(ElemType elem[], int n, int r, int d)
// ��ʼ����: rΪ����,dΪ�ؼ���λ��
// �������: ��elem���л�������
{
	LinkList<ElemType> *list;	// ���ڴ洢����������Ա�����
	list = new LinkList<ElemType>[r];
	for (int i = 1; i <= d; i++)
	{	// ��i�˷������ռ�
		Distribute(elem, n, r, d, i, list);	// ����
		Colect(elem, n, r, d, i, list);		// �ռ�
	}
	delete []list;
}

#endif

