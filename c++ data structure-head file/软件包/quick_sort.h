#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

template <class ElemType>
int Partition(ElemType elem[], int low, int high)
// �������:����elem[low .. high]�е�Ԫ��,ʹ�����ƶ����ʵ���,Ҫ��������֮ǰ��Ԫ��
//	����������,������֮���Ԫ�ز�С�������,�����������λ��

{
	while (low < high)
	{
		while (low < high && elem[high] >= elem[low])
		{	// elem[low]Ϊ����,ʹhigh�ұߵ�Ԫ�ز�С��elem[low]
			high--;
		}
		Swap(elem[low], elem[high]);

		while (low < high && elem[low] <= elem[high])
		{	// elem[high]Ϊ����,ʹlow��ߵ�Ԫ�ز�����elem[high]
			low++;
		}
		Swap(elem[low], elem[high]);
	}
	return low;	// ��������λ��
}

template <class ElemType>
void QuickSortHelp(ElemType elem[], int low, int high)
// �������:������elem[low .. high]�еļ�¼���п�������
{
	if (low < high)
	{	// ������elem[low .. high]���ȴ���1
		int pivotLoc = Partition(elem, low, high);	// ����һ���ҷ�
		QuickSortHelp(elem, low, pivotLoc - 1);		// ���ӱ�elem[low, pivotLoc - 1]�ݹ�����
		QuickSortHelp(elem, pivotLoc + 1, high);	// ���ӱ�elem[pivotLoc + 1, high]�ݹ�����
	}
}

template <class ElemType>
void QuickSort(ElemType elem[], int n)
// �������:������elem���п�������
{
	QuickSortHelp(elem, 0, n - 1);
}

#endif

