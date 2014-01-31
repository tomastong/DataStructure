#ifndef __INSERT_SORT_H__
#define __INSERT_SORT_H__

template <class ElemType>
void StraightInsertSort(ElemType elem[], int n)
// �������:������elem��ֱ�Ӳ���������
{
	for ( int i = 1; i < n; i++)
	{	// ��i��ֱ�Ӳ�������
		ElemType e = elem[i];			// �ݴ�elem[i]
		int j;							// ��ʱ����
		for (j = i - 1; j >= 0 && e < elem[j]; j--)
		{	// ����e��ļ�¼������
			elem[j + 1] = elem[j];		// ����
		}
		elem[j + 1] = e;				// j+1Ϊ����λ��
	}
}

#endif

