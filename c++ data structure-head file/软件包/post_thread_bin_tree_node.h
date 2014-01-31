#ifndef __POST_THREAD_BIN_TREE_NODE_H__
#define __POST_THREAD_BIN_TREE_NODE_H__

#ifndef __POINTER_TAG_TYPE__
#define __POINTER_TAG_TYPE__
enum PointerTagType {CHILD_PTR, THREAD_PTR};	
	// ָ���־����,CHILD_PTR(0):ָ���ӵ�ָ��,THREAD_PTR(1):ָ��������ָ��
#endif

// �������������������
template <class ElemType>
struct PostThreadBinTreeNode
{
// ���ݳ�Ա:
	ElemType data;								// ������
	PostThreadBinTreeNode<ElemType> *leftChild;	// ����ָ����
	PostThreadBinTreeNode<ElemType> *rightChild;// �Һ���ָ����
	PostThreadBinTreeNode<ElemType> *parent;	// ˫��ָ����
	PointerTagType leftTag, rightTag;			// ���ұ�����

//	���캯��:
	PostThreadBinTreeNode();					// �޲����Ĺ��캯�� 
	PostThreadBinTreeNode(const ElemType &val,	// ������Ԫ��ֵ,ָ�뼰��־������
		PostThreadBinTreeNode<ElemType> *lChild = NULL, 
		PostThreadBinTreeNode<ElemType> *rChild = NULL,
		PostThreadBinTreeNode<ElemType> *pt = NULL,
		PointerTagType leftTag = CHILD_PTR,
		PointerTagType rightTag = CHILD_PTR);
};

// ��������������������ʵ�ֲ���
template <class ElemType>
PostThreadBinTreeNode<ElemType>::PostThreadBinTreeNode()
// �������������һ��Ҷ���
{
	leftChild = rightChild = parent = NULL;		// ָ����Ϊ��
	leftTag = rightTag = CHILD_PTR;				// ��־��
}

template <class ElemType>
PostThreadBinTreeNode<ElemType>::PostThreadBinTreeNode(const ElemType &val, 
		PostThreadBinTreeNode<ElemType> *lChild, 
		PostThreadBinTreeNode<ElemType> *rChild,
		PostThreadBinTreeNode<ElemType> *pt,
		PointerTagType lTag,
		PointerTagType rTag)
// �������������һ��������Ϊval,����ΪlChild,�Һ���ΪrChild�Ľ��,˫��Ϊ
//	pt,���־ΪlTag,�ұ�־ΪrTag�Ľ��
{	
	data = val;									// ����Ԫ��ֵ
	leftChild = lChild;							// ����
	rightChild = rChild;						// �Һ���
	parent = pt;								// ˫��
	leftTag = lTag;								// ���־
	rightTag = rTag;							// �ұ�־
}

#endif

