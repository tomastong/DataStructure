#ifndef __ADJ_LIST_NETWORK_VEX_NODE_H__
#define __ADJ_LIST_NETWORK_VEX_NODE_H__

// �ڽӱ�ͼ��������
template <class ElemType>
class AdjListGraphVexNode
{
public:
// ���ݳ�Ա:
	ElemType data;							// ����Ԫ��ֵ
	LinkList<int> *adjLink;					// �ڽ�����

// ���캯��:
	AdjListGraphVexNode();					// �޲����Ĺ��캯��
	AdjListGraphVexNode(ElemType item, LinkList<int> *adj = NULL);
		// ���춥������Ϊitem,ָ���ڽ������ָ��Ϊadj�Ľṹ
};

// �ڽӱ�ͼ���������ʵ�ֲ���
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode()
// �������������һ���ն����㡪���޲ι��캯��
{
	adjLink = NULL;							// �ڽ�����Ϊ��
}

template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType item, LinkList<int> *adj)
// �����������������Ϊitem,ָ���ڽ�����Ϊadj�Ķ���
{
	data = item;							// ��������
	adjLink = adj;							// �ڽ�����
}

#endif