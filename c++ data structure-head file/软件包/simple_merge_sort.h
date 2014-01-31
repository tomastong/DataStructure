#ifndef __SIMPLE_MERGE_SORT_H__
#define __SIMPLE_MERGE_SORT_H__

template <class ElemType>
void SimpleMerge(ElemType elem[], int low, int mid, int high)
// �������:������������elem[low .. mid]��elem[mid + 1 .. midhigh]�鲢Ϊ�µ�
//	��������elem[low .. high]
{
	ElemType *tmpElem = new ElemType[high + 1]; // ������ʱ����
	
	int i, j, k;								// ��ʱ���� 
	for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++)
	{	// iΪ�鲢ʱelem[low .. mid]��ǰԪ�ص��±�,jΪ�鲢ʱelem[mid + 1 .. high]��ǰԪ��
		// ���±�,kΪtmpElem�е�ǰԪ�ص��±�
		if (elem[i] <= elem[j])
		{	// elem[i]��С,�ȹ鲢
			tmpElem[k] = elem[i];
			i++;
		}
		else
		{	// elem[j]��С,�ȹ鲢
			tmpElem[k] = elem[j];
			j++;
		}
	}

	for (; i <= mid; i++, k++)
	{	// �鲢elem[low .. mid]��ʣ��Ԫ��
		tmpElem[k] = elem[i];
	}

	for (; j <= high; j++, k++)
	{	// �鲢elem[mid + 1 .. high]��ʣ��Ԫ��
		tmpElem[k] = elem[j];
	}

	for (i = low; i <= high; i++)
	{	// ��tmpElem[low .. high]���Ƶ�elem[low .. high]
		elem[i] = tmpElem[i];
	}

	delete []tmpElem;		// �ͷ�tmpElem�����ÿռ�
}

template <class ElemType>
void SimpleMergeSortHelp(ElemType elem[], int low, int high)
// �������:��elem[low .. high]���м򵥹鲢����
{
	if (low < high)
	{	
		int mid = (low + high) / 2;			
			// ��elem[low .. high]ƽ��Ϊelem[low .. mid]��elem[mid + 1 .. high]
		SimpleMergeSortHelp(elem, low, mid);		// ��elem[low .. mid]���м򵥹鲢����
		SimpleMergeSortHelp(elem, mid + 1, high);	// ��elem[mid + 1 .. high]���м򵥹鲢����
		SimpleMerge(elem, low, mid, high);			// ��elem[low .. mid]��elem[mid + 1 .. high]���й鲢
	}
}

template <class ElemType>
void SimpleMergeSort(ElemType elem[], int n)
// �������:��elem���м򵥹鲢����
{
	SimpleMergeSortHelp(elem, 0, n - 1);
}

#endif

