#ifndef __PRE_THREAD_BINARY_TREE_H__
#define __PRE_THREAD_BINARY_TREE_H__

#include "binary_tree.h"			// ��������
#include "thread_bin_tree_node.h"	// ���������������

// ����������������
template <class ElemType>
class PreThreadBinTree
{
protected:
//  ���������������ݳ�Ա:
	ThreadBinTreeNode<ElemType> *root;

//	��������:
	void PreThreadHelp(ThreadBinTreeNode<ElemType> *cur, ThreadBinTreeNode<ElemType> *&pre);
		// ������������curΪ���Ķ�����
	ThreadBinTreeNode<ElemType> *TransformHelp(BinTreeNode<ElemType> *r);
		// btΪ���Ķ�����ת�����µ�δ����������������������,�����¶������ĸ�
	ThreadBinTreeNode<ElemType> *CopyTreeHelp(ThreadBinTreeNode<ElemType> *copy);	
		// ��������������
	void DestroyHelp(ThreadBinTreeNode<ElemType> * &r);		// ������rΪ��������

public:
//  �����������������������ر���ϵͳĬ�Ϸ�������:
	PreThreadBinTree(const BinaryTree<ElemType> &bt);		// �ɶ���������������������������ת�����캯��
	virtual ~PreThreadBinTree();							// ���캯��
	ThreadBinTreeNode<ElemType> *GetRoot() const;			// ���������������ĸ�
	void PreThread();										// ����������������
	void PreOrder(void (*Visit)(const ElemType &)) const ;	// ���������������	
	PreThreadBinTree(const PreThreadBinTree<ElemType> &copy);	// ���ƹ��캯��
	PreThreadBinTree<ElemType> &operator=(const PreThreadBinTree<ElemType>& copy);// ��ֵ���������
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(ThreadBinTreeNode<ElemType> *r, int level);
	//	����״��ʽ��ʾ��rΪ����������������levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayBTWithTreeShape(PreThreadBinTree<ElemType> &bt);
	//	��״��ʽ��ʾ���������� 

// ���������ʵ�ֲ���
template <class ElemType>
void PreThreadBinTree<ElemType>::PreThreadHelp(ThreadBinTreeNode<ElemType> *cur, ThreadBinTreeNode<ElemType> *&pre)
// ���������������������curΪ���Ķ�����,pre��ʾcur��ǰ��
{
	if (cur != NULL)
	{	// �����������ʽ����������
		if(cur->leftChild == NULL)
		{	// cur������,������ 
			cur->leftChild = pre;				// curǰ��Ϊpre
			cur->leftTag = THREAD_PTR;			// ������־
		}
		
		if(pre != NULL && pre->rightChild == NULL)
		{	// pre���Һ���, ������
			pre->rightChild = cur;				// pre���Ϊcur
			pre->rightTag = THREAD_PTR;			// ������־ 
  		}

		pre = cur;								// ������һ���ʱ,curΪ��һ����ǰ��

		if (cur->leftTag == CHILD_PTR)		
			PreThreadHelp(cur->leftChild, pre);	// ������������
		if (cur->rightTag == CHILD_PTR)		
			PreThreadHelp(cur->rightChild, pre);// ������������
	}
}

template <class ElemType>
void PreThreadBinTree<ElemType>::PreThread()
// �������������������������
{
	ThreadBinTreeNode<ElemType> *pre = NULL;	// ��ʼ������ʱǰ��Ϊ��
	PreThreadHelp(root, pre);					// ������������rootΪ���Ķ�����
	if (pre->rightChild == NULL)				// preΪǰ�����������һ�����
		pre->rightTag = THREAD_PTR;				// �����Һ���,����������
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *PreThreadBinTree<ElemType>::TransformHelp(BinTreeNode<ElemType> *r)
// ���������rΪ���Ķ�����ת�����µ�δ����������������������,�����¶������ĸ�
{
	if (r == NULL)
	{	// �ն�����ת�����µĿ�����������
		return NULL;					// ��������������Ϊ��	
	}
	else
	{	// ת���ǿն�����
		ThreadBinTreeNode<ElemType> *lChild = TransformHelp(r->leftChild);	// ת��������
		ThreadBinTreeNode<ElemType> *rChild = TransformHelp(r->rightChild);	// ת��������
		ThreadBinTreeNode<ElemType> *rt = new ThreadBinTreeNode<ElemType>(r->data, lChild, rChild);
			// ת�������
		return rt;															// ���ظ����
	}
}

template <class ElemType>
PreThreadBinTree<ElemType>::PreThreadBinTree(const BinaryTree<ElemType> &bt)
// ����������ɶ���������������������������ת�����캯��
{
	root = TransformHelp(bt.GetRoot());			// ת����δ�������Ķ�����
	PreThread();								// ������������
}

template <class ElemType>
void PreThreadBinTree<ElemType>::DestroyHelp(ThreadBinTreeNode<ElemType> * &r)
// ���������������rΪ��������������
{
	if(r != NULL)
	{	// r�ǿ�,ʵʩ����
		if (r->leftTag == CHILD_PTR) DestroyHelp(r->leftChild);		// ����������
		if (r->rightTag == CHILD_PTR) DestroyHelp(r->rightChild);	// ����������
		delete r;													// ���ٸ����
		r = NULL;					
	}
}

template <class ElemType>
PreThreadBinTree<ElemType>::~PreThreadBinTree()
// �����������������������--���캯��
{
	DestroyHelp(root);
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *PreThreadBinTree<ElemType>::GetRoot() const
// ������������������������ĸ�
{	
	return root;
}

template <class ElemType>
void PreThreadBinTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// ������������������������	
{
	if (root != NULL)
	{
		ThreadBinTreeNode<ElemType> *cur = root;	
			// �Ӹ���ʼ����,�����Ϊ���������еĵ�һ�����
		
		while (cur != NULL)
		{
			(*Visit)(cur->data);					// ���ʵ�ǰ���

			if (cur->rightTag == THREAD_PTR)
			{	// ����Ϊ���������Ϊcur->rightChild
				cur = cur->rightChild;
			} 
			else
			{	// ����Ϊ����
				if (cur->rightTag == CHILD_PTR)
 					cur = cur->leftChild;			// cur������,������Ϊ���
				else
 					cur = cur->rightChild;			// cur������,���Һ���Ϊ���
			}
		}
	}
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *PreThreadBinTree<ElemType>::CopyTreeHelp(ThreadBinTreeNode<ElemType> *copy)	
// �������������copyΪ�����������������Ƴ��µ�δ�������Ķ�����,�����¶������ĸ�
{
	if (copy == NULL)
	{	// ���ƿ�����������
		return NULL;									// ��������������Ϊ��	
	}
	else
	{	// ���Ʒǿ�����������
		ThreadBinTreeNode<ElemType> *lChild;
		ThreadBinTreeNode<ElemType> *rChild;
		if (copy->leftTag == CHILD_PTR)
			lChild = CopyTreeHelp(copy->leftChild);		// ����������
		else lChild = NULL;								// ������Ϊ��
		if (copy->rightTag == CHILD_PTR)
			rChild = CopyTreeHelp(copy->rightChild);	// ����������
		else rChild = NULL;								// ������Ϊ��
		ThreadBinTreeNode<ElemType> *r = new ThreadBinTreeNode<ElemType>(copy->data, lChild, rChild);
			// ���Ƹ����
		return r;
	}
}

template <class ElemType>
PreThreadBinTree<ElemType>::PreThreadBinTree(const PreThreadBinTree<ElemType> &copy)
// �������������֪���������������������������������ƹ��캯��
{
	root = CopyTreeHelp(copy.root);						// ��������������
	PreThread();										// ����������������
}

template <class ElemType>
PreThreadBinTree<ElemType> &PreThreadBinTree<ElemType>::operator=(const PreThreadBinTree<ElemType> &copy)
// �������������֪����������copy���Ƶ���ǰ����������--��ֵ���������
{
	if (&copy != this)
	{
		DestroyHelp(root);								// �ͷ�ԭ������������ռ�ÿռ�
		root = CopyTreeHelp(copy.root);					// ��������������
		PreThread();									// ����������������
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(ThreadBinTreeNode<ElemType> *r, int level)
//	�������������״��ʽ��ʾ��rΪ����������������levelΪ���������������Ĳ����Ϊ1
{
	if(r != NULL)
	{	//��������ʽ��ֻ��ʽ�ǿ���
		if (r->rightTag == CHILD_PTR)
			DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//��ʾ������
		cout << endl;					//��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout << " ";				//ȷ���ڵ�level����ʾ���
		cout << r->data;				//��ʾ���
		if (r->leftTag == CHILD_PTR)
			DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//��ʾ������
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(PreThreadBinTree<ElemType> &bt)
//	�����������״��ʽ��ʾ���������� 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// ��״��ʾ��bt.GetRoot()Ϊ��������������
	cout << endl;
}

#endif
