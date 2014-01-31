#ifndef __IN_THREAD_BIN_TREE_NODE_H__
#define __IN_THREAD_BIN_TREE_NODE_H__

#ifndef __POINTER_TAG_TYPE__
#define __POINTER_TAG_TYPE__
enum PointerTagType {CHILD_PTR, THREAD_PTR};
	// ָ���־����,CHILD_PTR(0):ָ���ӵ�ָ��,THREAD_PTR(1):ָ��������ָ��
#endif

// ���������������
template <class ElemType>
struct ThreadBinTreeNode
{
// ���ݳ�Ա:
	ElemType data;							// ������
	ThreadBinTreeNode<ElemType> *leftChild;	// ����ָ����
	ThreadBinTreeNode<ElemType> *rightChild;// �Һ���ָ����
	PointerTagType leftTag, rightTag;		// ���ұ�־��

//	���캯��:
	ThreadBinTreeNode();					// �޲����Ĺ��캯�� 
	ThreadBinTreeNode(const ElemType &val,	// ������Ԫ��ֵ,ָ�뼰��־������
		ThreadBinTreeNode<ElemType> *lChild = NULL, 
		ThreadBinTreeNode<ElemType> *rChild = NULL,
		PointerTagType leftTag = CHILD_PTR,
		PointerTagType rightTag = CHILD_PTR);
};

// ����������������ʵ�ֲ���
template <class ElemType>
ThreadBinTreeNode<ElemType>::ThreadBinTreeNode()
// �������������һ��Ҷ���
{
	leftChild = rightChild = NULL;			// ָ����Ϊ��
	leftTag = rightTag = CHILD_PTR;			// ��־��
}

template <class ElemType>
ThreadBinTreeNode<ElemType>::ThreadBinTreeNode(const ElemType &val, 
		ThreadBinTreeNode<ElemType> *lChild, 
		ThreadBinTreeNode<ElemType> *rChild,
		PointerTagType lTag,
		PointerTagType rTag)
// �������������һ��������Ϊval,����ΪlChild,�Һ���ΪrChild�Ľ��,���
//	־ΪlTag,�ұ�־ΪrTag�Ľ��
{	
	data = val;								// ����Ԫ��ֵ
	leftChild = lChild;						// ����
	rightChild = rChild;					// �Һ���
	leftTag = lTag;							// ���־
	rightTag = rTag;						// �ұ�־
}

#endif

