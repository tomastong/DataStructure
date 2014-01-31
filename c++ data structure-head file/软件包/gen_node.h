#ifndef __GEN_NODE_H__
#define __GEN_NODE_H__

#ifndef __GEN_LIST_NODE_TYPE__
#define __GEN_LIST_NODE_TYPE__
enum GenListNodeType {HEAD, ATOM, LIST};
#endif

#include "use_space_list.h"				// �����ʹ�ÿռ����

// ���������
template<class ElemType>
struct GenListNode
{
// ���ݳ�Ա:
	GenListNodeType tag;				// ��־��,HEAD(0):ͷ���, ATOM(1):ԭ�ӽṹ, LIST(2):����
	GenListNode<ElemType> *nextLink;	// ָ��ͬһ���е���һ�����ָ����
	union
	{
		ElemType atom;					// tag=ATOM,���ԭ�ӽ���������
		GenListNode<ElemType> *subLink;	// tag=LISK,���ָ���ӱ��ָ����
	}; 

// ���캯��:
	GenListNode(GenListNodeType tg = HEAD, GenListNode<ElemType> *next = NULL);
		// �ɱ�־tg��ָ��next����������
};

// ����������ʵ�ֲ���
template<class ElemType>
GenListNode<ElemType>::GenListNode(GenListNodeType tg, GenListNode<ElemType> *next)
// ����������ɱ�־tg��ָ��next����������
{
	tag = tg;							// ��־
	nextLink = next;					// ���
	gUseSpaceList.Push(this);			// ��ָ��ǰ����ָ����뵽�����ʹ�ÿռ����
}


#endif
