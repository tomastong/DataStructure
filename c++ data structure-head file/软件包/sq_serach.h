#ifndef __SQ_SERACH_H__
#define __SQ_SERACH_H__

template <class ElemType, class KeyType>
int SqSerach(ElemType elem[], int n, KeyType key)
// �������: ��˳����в��ҹؼ��ֵ�ֵ����key�ļ�¼,����ҳɹ�,�򷵻ش˼�¼�����,���򷵻�-1
{
	int i;					// ��ʱ���� 
	for (i = 0; i < n && elem[i] != key; i++);
	if (i < n)
	{	// ���ҳɹ�
		return i;
	}
	else
	{	// ����ʧ��
		return -1;
	}
}

#endif
