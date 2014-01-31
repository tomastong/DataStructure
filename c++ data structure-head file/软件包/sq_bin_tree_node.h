#ifndef __SQ_BIN_TREE_NODE_H__
#define __SQ_BIN_TREE_NODE_H__

#ifndef __SQ_BIN_TREE_NODE_TAG_TYPE__
#define __SQ_BIN_TREE_NODE_TAG_TYPE__
enum SqBinTreeNodeTagType {EMPTY_NODE, USED_NODE};
#endif

// ˳��洢�����������
template <class ElemType>
struct SqBinTreeNode 
{
// ���ݳ�Ա:
	ElemType data;				// ������
	SqBinTreeNodeTagType tag;	// ���ʹ�ñ�־

// ���캯��:
	SqBinTreeNode();						// �޲����Ĺ��캯��
	SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg = EMPTY_NODE);	
		// ��֪�������ʹ�ñ�־�����ṹ
};

// ˳��洢������������ʵ�ֲ���
template<class ElemType>
SqBinTreeNode<ElemType>::SqBinTreeNode()
// �������������ָ����Ϊ�յĽ��
{
   tag = EMPTY_NODE;			// ��һ���ս��
}

template<class ElemType>
SqBinTreeNode<ElemType>::SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg)
// �������������һ��������Ϊitem�ͱ�־��Ϊtg�Ľ��
{
   data = item;					// ������
   tag = tg;					// ��־��
}

#endif
