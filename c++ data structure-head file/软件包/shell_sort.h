#ifndef __SHELL_SORT_H__
#define __SHELL_SORT_H__

template <class ElemType>
void ShellInsert(ElemType elem[], int n, int incr)
// �������: ������elem��һ������Ϊincr��Shell����,�Բ��������������޸���
//	��������ǰ�����ڼ�¼������Ϊincr,������1
{
	for ( int i = incr ; i < n; i++)
	{	// ��i�˲�������
		ElemType e = elem[i];			// �ݴ�elem[i]
		int j;							// ��ʱ����
		for (j = i - incr; j >= 0 && e < elem[j]; j -= incr)
		{	// ���������б�e��ļ�¼������
			elem[j + incr] = elem[j];	// ����
		}
		elem[j + incr] = e;				// j+incrΪ����λ��
	}
}

template <class ElemType>
void ShellSort(ElemType elem[], int n, int inc[], int t)
// �������: ����������inc[0 .. t -1 ]������elem��Shell����
{
	for ( int k = 0 ; k < t; k++)
	{	// ��k��Shell����
		ShellInsert(elem, n, inc[k]);
	}
}

#endif

