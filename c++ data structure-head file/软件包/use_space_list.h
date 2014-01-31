#ifndef __USE_SPACE_LIST_H__
#define __USE_SPACE_LIST_H__

#include "node.h"					// �����

// ʹ�ÿռ����
class UseSpaceList
{
protected:
// ���ݳ�Ա:
	Node<void *> *head;				// ʹ�ÿռ��ͷָ��

public:
// ����:
	UseSpaceList();					// �޲����Ĺ��캯��
	~UseSpaceList();				// ��������
	void Push(void *nodePtr);		// ��ָ�����ָ����뵽ʹ�ÿռ����
};

// ʹ�ÿռ�����ʵ�ֲ���
UseSpaceList::UseSpaceList()
// �������������ʹ�ÿռ��
{
	head = NULL;
}

UseSpaceList::~UseSpaceList()
// ����������ͷŽ��ռ�ô洢�ռ�
{
	while (head != NULL)
	{	// ѭ���ͷŽ��ռ�
		delete head->data;			// head->data�洢����ָ�����ָ��
		Node<void *> *tmpPtr = head;// �ݴ�head
		head = head->next;			// �µ�head
		delete tmpPtr;				// �ͷ�tmpPtr
	}
}

void UseSpaceList::Push(void *nodePtr)
// �����������ָ�����ָ����뵽ʹ�ÿռ����
{
	Node<void *> *tmpPtr = new Node<void *>(nodePtr, head);	// ������ʹ�ÿռ����
	head = tmpPtr;					// tmpPtr���±�ͷ	
}

#ifndef __GLOBAL_USE_SPACE_LIST__
#define __GLOBAL_USE_SPACE_LIST__
static UseSpaceList gUseSpaceList;	// ȫ��ʹ�ÿռ�����
#endif


#endif
