#ifndef __NODE_H__
#define __NODE_H__

// �����
struct Node
{
// ���ݳ�Ա:
	int data;				// ������
	Node *next;		// ָ����

// ���캯��:
	Node();						// �޲����Ĺ��캯��
	Node(int item, Node *link = NULL);	// ��֪������Ԫ��ֵ��ָ�뽨���ṹ
};

// ������ʵ�ֲ���
Node::Node()
// �������������ָ����Ϊ�յĽ��
{
   next = NULL;
}

Node::Node(int item, Node *link)
// �������������һ��������Ϊitem��ָ����Ϊlink�Ľ��
{
   data = item;
   next = link;
}

#endif
