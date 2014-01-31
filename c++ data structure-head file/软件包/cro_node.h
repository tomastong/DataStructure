#ifndef __CRO_NODE_H__
#define __CRO_NODE_H__

#include "triple.h"						// ��Ԫ����

// ʮ��������Ԫ������
template<class ElemType>
struct CLkTriNode
{
// ���ݳ�Ա:
	Triple<ElemType> triElem;				// ��Ԫ��
	CLkTriNode<ElemType> *right, *down;		// ����Ԫ�������б����б�ĺ��ָ����

// ���캯��:
	CLkTriNode();							// �޲����Ĺ��캯��
	CLkTriNode(const Triple<ElemType> &e,	// ��֪��Ԫ���ָ���������
		CLkTriNode<ElemType> *rLink = NULL, CLkTriNode<ElemType> *dLink = NULL);	
};

// ʮ��������Ԫ�������ʵ�ֲ���
template<class ElemType>
CLkTriNode<ElemType>::CLkTriNode()
// �������������ָ����Ϊ�յĽ��
{
	right = NULL;						// ��ָ����Ϊ��
	down = NULL;						// ��ָ����Ϊ��
}

template<class ElemType>
CLkTriNode<ElemType>::CLkTriNode(const Triple<ElemType> &e,
		CLkTriNode<ElemType> *rLink, CLkTriNode<ElemType> *dLink)
// �����������֪��Ԫ���ָ���������
{
	triElem.row = e.row;						// ��Ԫ��
	triElem.col = e.col;						// ��Ԫ��
	triElem.value = e.value;						// ��Ԫ��
	right = rLink;						// ��ָ����
	down = dLink;						// ��ָ����
}

#endif
