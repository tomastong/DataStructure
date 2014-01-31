#ifndef __DBL_NODE_H__
#define __DBL_NODE_H__


// ˫����������
template <class ElemType>
struct DblNode 
{
// ���ݳ�Ա:
	ElemType data;				// ������
	DblNode<ElemType> *back;	// ָ��ǰ����ָ����
	DblNode<ElemType> *next;	// ָ���̵�ָ����

// ���캯��:
	DblNode();						// �����ݵĹ��캯��
	DblNode(ElemType item, 
	DblNode<ElemType> *linkBack = NULL,
	DblNode<ElemType> *linkNext = NULL);// ��֪�������ָ�������ṹ
};


// ˫�����������ʵ�ֲ���

template<class ElemType>
DblNode<ElemType>::DblNode()
// �������������ָ����Ϊ�յĽ��
{
   next = NULL;
}

template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item,
			DblNode<ElemType> *linkBack,
			DblNode<ElemType> *linkNext)
// �������������һ��������Ϊitem��ָ����ΪlinkBack��linkNext�Ľ��
{
   data = item;
   back = linkBack;
   next = linkNext;
}


#endif