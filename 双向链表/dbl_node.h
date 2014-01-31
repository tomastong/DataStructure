#ifndef __DBL_NODE_H__
#define __DBL_NODE_H__


// ˫����������
struct DblNode
{
// ���ݳ�Ա:
	int data;				// ������
	DblNode *back;	// ָ��ǰ����ָ����
	DblNode *next;	// ָ���̵�ָ����

// ���캯��:
	DblNode();						// �����ݵĹ��캯��
	DblNode(int item,
	DblNode *linkBack = NULL,
	DblNode *linkNext = NULL);// ��֪�������ָ�������ṹ
};


// ˫�����������ʵ�ֲ���

DblNode::DblNode()
// �������������ָ����Ϊ�յĽ��
{
   next = NULL;
}

DblNode::DblNode(int item,
			DblNode *linkBack,
			DblNode *linkNext)
// �������������һ��������Ϊitem��ָ����ΪlinkBack��linkNext�Ľ��
{
   data = item;
   back = linkBack;
   next = linkNext;
}


#endif
