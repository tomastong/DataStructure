#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

template <class ElemType>
void Merge(ElemType elem[], ElemType tmpElem[], int low, int mid, int high)
// �������:������������elem[low .. mid]��elem[mid + 1 .. midhigh]�鲢Ϊ�µ�
//	��������elem[low .. high]
{

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
}

template <class ElemType>
void MergeSortHelp(ElemType elem[], ElemType tmpElem[], int low, int high)
// �������:��elem[low .. high]���й鲢����
{
	if (low < high)
	{	
		int mid = (low + high) / 2;			
			// ��elem[low .. high]ƽ��Ϊelem[low .. mid]��elem[mid + 1 .. high]
		MergeSortHelp(elem, tmpElem, low, mid);		// ��elem[low .. mid]���й鲢����
		MergeSortHelp(elem, tmpElem, mid + 1, high);// ��elem[mid + 1 .. high]���й鲢����
		Merge(elem, tmpElem, low, mid, high);		// ��elem[low .. mid]��elem[mid + 1 .. high]���й鲢
	}
}

template <class ElemType>
void MergeSort(ElemType elem[], int n)
// �������:��elem���й鲢����
{
	ElemType *tmpElem = new ElemType[n]; // ������ʱ����
	MergeSortHelp(elem, tmpElem, 0, n - 1);
	delete []tmpElem;					// �ͷ�tmpElem�����ÿռ�
}

#endif

