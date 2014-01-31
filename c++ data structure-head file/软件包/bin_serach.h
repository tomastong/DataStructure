#ifndef __BIN_SERACH_H__
#define __BIN_SERACH_H__

template <class ElemType, class KeyType>
int BinSerach(ElemType elem[], int n, KeyType key)
// �������: ��������в�����ؼ��ֵ�ֵ����key�ļ�¼,����ҳɹ�,�򷵻ش˼�¼�����,����
//	����-1
{
	int low = 0, high = n -1;		// ���������ֵ
	
	while (low <= high)
	{
		int mid = (low + high) / 2;	// ���������м�λ��
		if (key == elem[mid])
		{	// ���ҳɹ�
			return mid;
		}
		else if (key <= elem[mid])
		{	// ���������������в���
			high = mid - 1;
		}
		else
		{	// �������Ұ�������в���
			low = mid + 1;
		}
	}

	return -1;	// ����ʧ��
}

#endif