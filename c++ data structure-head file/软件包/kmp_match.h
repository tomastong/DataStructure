#ifndef __KMP_MATCH_H__
#define __KMP_MATCH_H__

#include "string.h"				// ����

// KMPƥ���㷨
void getNext(const String &P, int next[])
// �������: ��ģʽ��P��next�����Ԫ��ֵ
{
	next[0] = -1;				// ��next[0] = -1��ʼ���е���
	int j = 0, k = -1;			// next[j] = k�����ĳ�ʼ���
	while (j < P.Length() - 1)		
	{	// ����next���±귶ΧΪ0 ~ P.Length() - 1, ͨ�����Ʒ�ʽ���next[j+1]��ֵ
		if (k == -1)
		{	// k == -1ֻ��j == 0ʱ����
			next[j+1]=0;		// next[j+1]=next[1] = 0
			j=1; k = 0;			// ���������next[1] = 0,����j = 1, k = 0
		}
		else if (P[k] == P[j])
		{	// ��ʱnext[j+1] = next[j]+1
			next[j+1]=k+1;		// ����P[k] == P[j],����next[j+1] = next[j]+1 = k + 1
			j++; k++;			// ���������next[j+1]=k+1,����j����Ϊ++j,k����Ϊ++k
		}
		else
		{	// P[k]��P[j]��ƥ��
			k = next[k];		// Ѱ���µ�ƥ���ַ�
		}
	}
}


int KMPIndexHelp(const String &T, const String &P, int pos, int next[])
// �������: ͨ��next�������ģʽ��P��һ����Ŀ�괮T�дӵ�pos���ַ���ʼ���ֵ�λ��
{
	int i = pos, j = 0;			// iΪĿ�괮T�еĵ�ǰ�ַ�λ��,jΪģʽ��P�ĵ�ǰ�ַ�λ��
	while (i < T.Length() && j < P.Length())
	{	
		if (j == -1)
		{	// ��ʱ����P���κ��ַ���������T[i]���бȽ�,�´�P[0]��T[i+1]��ʼ���бȽ�
			i++; j = 0;
		}
		else if (P[j] == T[i])
		{	// P[j]��T[i]ƥ��
			i++; j++;			// ģʽ��P��Ŀ�괮T�ĵ�ǰλ�������
		}
		else
		{	// P[j]��T[i]��ƥ��
			j = next[j];		// Ѱ���µ�ģʽ��P��ƥ���ַ�λ��
		}
	}

	if (j < P.Length()) return -1;			// ƥ��ʧ��
	else return i - j;						// ƥ��ɹ�
}

int KMPIndex(const String &T, const String &P, int pos = 0)
// �������: ����ģʽ��P��һ����Ŀ�괮T�дӵ�pos���ַ���ʼ���ֵ�λ��
{
	int *next = new int[P.Length()];		// Ϊ����next����ռ�
	getNext(P, next);						// ��ģʽ��P��next�����Ԫ��ֵ
	int result = KMPIndexHelp(T, P, pos, next);	
		// ����ģʽ��P��һ����Ŀ�괮T�дӵ�pos���ַ���ʼ���ֵ�λ��
	delete []next;							// ��next��ռ�õĴ洢�ռ�
	return result;
}

#endif

