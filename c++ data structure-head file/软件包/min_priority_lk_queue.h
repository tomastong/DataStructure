#ifndef __MIN_PRIORITY_LK_QUEUE_H__
#define __MIN_PRIORITY_LK_QUEUE_H__

#include "node.h"					// �����
#include "lk_queue.h"				// ��������

// ��С������������
template<class ElemType>
class MinPriorityLinkQueue: public LinkQueue<ElemType> 
{
public:
//  ������Ӳ�������:
	StatusCode InQueue(const ElemType &e);			// ������Ӳ���
};


// ��С�������������ʵ�ֲ���
template<class ElemType>
StatusCode MinPriorityLinkQueue<ElemType>::InQueue(const ElemType &e)
// �������������Ԫ��eΪ�µĶ�β������SUCCESS
{
	Node<ElemType> *curPtr = LinkQueue<ElemType>::front->next;		// ָ��ǰ���
	Node<ElemType> *curPrePtr = LinkQueue<ElemType>::front;			// ָ��ǰ����ǰ�����
	
	while (curPtr != NULL && curPtr->data <= e)
	{	// curPtr��curPrePtr��ָ����һԪ��
		curPrePtr = curPtr;
		curPtr = curPtr->next; 
	}

	Node<ElemType> *tmpPtr = new Node<ElemType>(e, curPtr);			// �����½��
	curPrePtr->next = tmpPtr;										// ��tmpPtr������curPrePtr��curPtr֮�� 
	
	if (curPrePtr == LinkQueue<ElemType>::rear)
	{	// �½�����rear�ĺ���
		LinkQueue<ElemType>::rear = tmpPtr;							// rearָ���¶�β
	}

	return SUCCESS;
}

#endif
