#ifndef __MIN_PRIORITY_SQ_QUEUE_H__
#define __MIN_PRIORITY_SQ_QUEUE_H__

#include "sq_queue.h"				// ѭ��������

// ��С����ѭ��������
template<class ElemType>
class MinPrioritySqQueue: public SqQueue<ElemType> 
{
public:
//  ������Ӳ�������:
	StatusCode InQueue(const ElemType &e);			// ������Ӳ���
};

// ��С����ѭ���������ʵ�ֲ���
template<class ElemType>
StatusCode MinPrioritySqQueue<ElemType>::InQueue(const ElemType &e)
// ��������������������������OVER_FLOW,
//	�������Ԫ��eΪ�µĶ�β������SUCCESS
{
	if (SqQueue<ElemType>::Full())
	{	// ��������
		return OVER_FLOW;
	}
	else
	{	// ����δ������ӳɹ�
		int curPosition = SqQueue<ElemType>::front;
		while (curPosition != SqQueue<ElemType>::rear && 
			SqQueue<ElemType>::elems[curPosition] <= e)
		{	// �����в�����e��Ԫ����ǰ��һ��λ��
			SqQueue<ElemType>::elems[(curPosition - 1 + SqQueue<ElemType>::maxSize) 
				% SqQueue<ElemType>::maxSize] = SqQueue<ElemType>::elems[curPosition];
				// elems[curPosition]ǰ��һ��λ��
			curPosition = (curPosition + 1) % SqQueue<ElemType>::maxSize;	
				// curPositionָ����һԪ��
		}

		SqQueue<ElemType>::elems[(curPosition - 1 + SqQueue<ElemType>::maxSize) % 
			SqQueue<ElemType>::maxSize] = e;	// curPosition��ǰһλ��Ϊe�Ĳ���λ��
		SqQueue<ElemType>::front = (SqQueue<ElemType>::front - 1 + 
			SqQueue<ElemType>::maxSize) % SqQueue<ElemType>::maxSize;			
			// front����ǰһλ��

		return SUCCESS;
	}
}

#endif
