#ifndef __CHILD_PARENT_TREE_NODE_H__
#define __CHILD_PARENT_TREE_NODE_H__

#include "lk_list.h"				// ��������

// ����˫����ʾ�������
template <class ElemType>
struct ChildParentTreeNode 
{
// ���ݳ�Ա:
	ElemType data;					// ������
	LinkList<int> childLkList;		// ��������	
	int parent;						// ˫��λ����

// ���캯��:
	ChildParentTreeNode();			// �޲����Ĺ��캯��
	ChildParentTreeNode(ElemType item, int pt = -1);// ��֪������ֵ��˫��λ�ý����ṹ
};

// ����˫����ʾ��������ʵ�ֲ���
template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode()
// �������������˫����Ϊ-1�Ľ��
{
	parent = -1;
}

template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode(ElemType item, int pt)
// �������������һ��������Ϊitem��˫����Ϊpt�Ľ��
{
	data = item;					// ����Ԫ��ֵ
	parent = pt;					// ˫��
}

#endif
