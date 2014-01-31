#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__

template <class ElemType>
void BubbleSort(ElemType elem[], int n)
// �������:������elem�������������������
{
	for (int i = n - 1; i > 0; i--)
	{	// ��i����������
		for (int j = 0; j < i; j++)
		{	// �Ƚ�elem[j]��elem[j + 1]
			if (elem[j] > elem[j + 1])
			{	// ���������,�򽻻�elem[j]��elem[j + 1]
				Swap(elem[j], elem[j + 1]);
			}
		}
	}
}



#endif

