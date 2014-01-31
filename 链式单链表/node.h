#ifndef __NODE_H__
#define __NODE_H__

#include <string>

struct Info
{
	int Age;
	std::string Name;
};

// �����
struct Node 
{
// ���ݳ�Ա:
	Info data;				// ������
	Node *next;		// ָ����

// ���캯��:
	Node();						// �޲����Ĺ��캯��
	Node(Info item, Node *link = NULL);	// ��֪������Ԫ��ֵ��ָ�뽨���ṹ
};

// ������ʵ�ֲ���
Node::Node()
// �������������ָ����Ϊ�յĽ��
{
   next = NULL;
}
Node::Node(Info item, Node *link)
// �������������һ��������Ϊitem��ָ����Ϊlink�Ľ��
{
   data = item;
   next = link;
}

#endif
