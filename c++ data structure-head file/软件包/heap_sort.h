#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__

template <class ElemType>
void SiftAdjust(ElemType elem[], int low, int high)
// �������:elem[low .. high]�м�¼��elem[low]���ⶼ����Ѷ���,��
//	��elem[low]ʹ��elem[low .. high]��Ϊһ���󶥶�
{
	for (int f = low, i = 2 * low + 1; i <= high; i = 2 * i + 1)
	{	// fΪ���������,iΪf�������
		if (i < high && elem[i] < elem[i + 1])
		{	// �Һ��Ӹ���, iָ���Һ���
			i++;
		}
		if (elem[f] >= elem[i])
		{	// �ѳ�Ϊ�󶥶�
			break;
		}
		Swap(elem[f], elem[i]);	// ����elem[f], elem[i]
		f = i;					// ��Ϊ�µĵ������		
	}
}


template <class ElemType>
void HeapSort(ElemType elem[], int n)
// �������:������elem���ж�����
{
	int i;
	for (i = (n-2)/2; i >= 0; --i) 
	{	// ��elem[0 .. n - 1]�����ɴ󶥶�
		SiftAdjust(elem, i, n - 1);
	};

	for (i = n - 1; i > 0; --i)
	{	// ��i�˶�����
		Swap(elem[0], elem[i]);		
			// ���Ѷ�Ԫ�غ͵�ǰδ�������������elem[0 .. i]�����һ��Ԫ�ؽ���
		SiftAdjust(elem, 0, i - 1);	// ��elem[0 .. i - 1]���µ���Ϊ�󶥶�
	}
}

#endif

