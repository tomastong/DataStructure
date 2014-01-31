#ifndef __IN_THREAD_BINARY_TREE_H__
#define __IN_THREAD_BINARY_TREE_H__

#include "binary_tree.h"			// ��������
#include "thread_bin_tree_node.h"	// ���������������

// ����������������
template <class ElemType>
class InThreadBinTree
{
protected:
//  ���������������ݳ�Ա:
	ThreadBinTreeNode<ElemType> *root;

//	��������:
	void InThreadHelp(ThreadBinTreeNode<ElemType> *cur, ThreadBinTreeNode<ElemType> *&pre);
		// ������������curΪ���Ķ�����
	ThreadBinTreeNode<ElemType> *TransformHelp(BinTreeNode<ElemType> *r);
		// btΪ���Ķ�����ת�����µ�δ����������������������,�����¶������ĸ�
	ThreadBinTreeNode<ElemType> *CopyTreeHelp(ThreadBinTreeNode<ElemType> *copy);	
		// ��������������
	void DestroyHelp(ThreadBinTreeNode<ElemType> * &r);		// ������rΪ��������

public:
//  �����������������������ر���ϵͳĬ�Ϸ�������:
	InThreadBinTree(const BinaryTree<ElemType> &bt);		
		// �ɶ���������������������������ת�����캯��
	virtual ~InThreadBinTree();								// ��������
	ThreadBinTreeNode<ElemType> *GetRoot() const;			// ���������������ĸ�
	void InThread();										// ����������������
	void InOrder(void (*Visit)(const ElemType &)) const;	// ���������������	
	InThreadBinTree(const InThreadBinTree<ElemType> &copy);	// ���ƹ��캯��
	InThreadBinTree<ElemType> &operator=(const InThreadBinTree<ElemType>& copy);
		// ��ֵ���������
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(ThreadBinTreeNode<ElemType> *r, int level);
	//	����״��ʽ��ʾ��rΪ����������������levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayBTWithTreeShape(InThreadBinTree<ElemType> &bt);
	//	��״��ʽ��ʾ���������� 


// ���������ʵ�ֲ���
template <class ElemType>
void InThreadBinTree<ElemType>::InThreadHelp(ThreadBinTreeNode<ElemType> *cur, 
	ThreadBinTreeNode<ElemType> *&pre)
// ���������������������curΪ���Ķ�����,pre��ʾcur��ǰ��
{
	if (cur != NULL)
	{	// �����������ʽ����������
		if (cur->leftTag == CHILD_PTR)		
			InThreadHelp(cur->leftChild, pre);	// ������������
		
		if(cur->leftChild == NULL)
		{	// cur������,������ 
			cur->leftChild = pre;				// curǰ��Ϊpre
			cur->leftTag = THREAD_PTR;			// ������־
		}
		else
		{	// cur������, �޸ı�־ 
			cur->leftTag = CHILD_PTR;			// ����ָ���־
		}
		
		if(pre != NULL && pre->rightChild == NULL)
		{	// pre���Һ���, ������
			pre->rightChild = cur;				// pre���Ϊcur
			pre->rightTag = THREAD_PTR;			// ������־ 
  		}
  		else if (pre != NULL)
		{	// cur���Һ���, �޸ı�־ 
			pre->rightTag = CHILD_PTR;			// ����ָ���־
		}
		pre = cur;								// ������һ���ʱ,curΪ��һ����ǰ��
		
		if (cur->rightTag == CHILD_PTR)		
			InThreadHelp(cur->rightChild, pre);	// ������������
	}
}

template <class ElemType>
void InThreadBinTree<ElemType>::InThread()
// �������������������������
{
	ThreadBinTreeNode<ElemType> *pre = NULL;	// ��ʼ������ʱǰ��Ϊ��
	InThreadHelp(root, pre);					// ������������rootΪ���Ķ�����
	if (pre->rightChild == NULL)				// preΪ�������������һ�����
		pre->rightTag = THREAD_PTR;				// �����Һ���,����������
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *InThreadBinTree<ElemType>::TransformHelp(BinTreeNode<ElemType> *r)
// ���������rΪ���Ķ�����ת�����µ�δ����������������������,�����¶������ĸ�
{
	if (r == NULL)
	{	// �ն�����ת�����µĿ�����������
		return NULL;							// ��������������Ϊ��	
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
InThreadBinTree<ElemType>::InThreadBinTree(const BinaryTree<ElemType> &bt)
// ����������ɶ���������������������������ת�����캯��
{
	root = TransformHelp(bt.GetRoot());			// ת����δ�������Ķ�����
	InThread();									// ������������
}

template <class ElemType>
void InThreadBinTree<ElemType>::DestroyHelp(ThreadBinTreeNode<ElemType> * &r)
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
InThreadBinTree<ElemType>::~InThreadBinTree()
// �����������������������--��������
{
	DestroyHelp(root);
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *InThreadBinTree<ElemType>::GetRoot() const
// ������������������������ĸ�
{	
	return root;
}

template <class ElemType>
void InThreadBinTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// ������������������������	
{
	if (root != NULL)
	{
		ThreadBinTreeNode<ElemType> *cur = root;	// �Ӹ���ʼ����
		
		while (cur->leftTag == CHILD_PTR)			// ���������Ľ�㣬�˽� 
			cur = cur->leftChild;					// ��Ϊ�������еĵ�һ�����
		while (cur != NULL)
		{
			(*Visit)(cur->data);					// ���ʵ�ǰ���

			if (cur->rightTag == THREAD_PTR)
			{	// ����Ϊ���������Ϊcur->rightChild
				cur = cur->rightChild;
			} 
			else
			{	// ����Ϊ���ӣ�cur�����������Ľ��Ϊ���
 				cur = cur->rightChild;				// curָ���Һ���	
				while (cur->leftTag == CHILD_PTR) 
					cur = cur->leftChild;			// ����ԭcur�����������Ľ��
			}
		}
	}
}

template <class ElemType>
ThreadBinTreeNode<ElemType> *InThreadBinTree<ElemType>::CopyTreeHelp(ThreadBinTreeNode<ElemType> *copy)	
// �������������copyΪ�����������������Ƴ��µ�δ�������Ķ�����,�����¶������ĸ�
{
	if (copy == NULL)
	{	// ���ƿ�����������
		return NULL;								// ��������������Ϊ��	
	}
	else
	{	// ���Ʒǿ�����������
		ThreadBinTreeNode<ElemType> *lChild;
		ThreadBinTreeNode<ElemType> *rChild;
		if (copy->leftTag == CHILD_PTR)
			lChild = CopyTreeHelp(copy->leftChild);	// ����������
		else lChild = NULL;							// ������Ϊ��
		if (copy->rightTag == CHILD_PTR)
			rChild = CopyTreeHelp(copy->rightChild);// ����������
		else rChild = NULL;							// ������Ϊ��
		ThreadBinTreeNode<ElemType> *r = new ThreadBinTreeNode<ElemType>(copy->data, lChild, rChild);
			// ���Ƹ����
		return r;
	}
}

template <class ElemType>
InThreadBinTree<ElemType>::InThreadBinTree(const InThreadBinTree<ElemType> &copy)
// �������������֪���������������������������������ƹ��캯��
{
	root = CopyTreeHelp(copy.root);					// ��������������
	InThread();										// ����������������
}

template <class ElemType>
InThreadBinTree<ElemType> &InThreadBinTree<ElemType>::operator=(const InThreadBinTree<ElemType> &copy)
// �������������֪����������copy���Ƶ���ǰ����������--��ֵ���������
{
	if (&copy != this)
	{
		DestroyHelp(root);							// �ͷ�ԭ������������ռ�ÿռ�
		root = CopyTreeHelp(copy.root);				// ��������������
		InThread();									// ����������������
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
		cout << endl;								//��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout << " ";							//ȷ���ڵ�level����ʾ���
		cout << r->data;							//��ʾ���
		if (r->leftTag == CHILD_PTR)
			DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//��ʾ������
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(InThreadBinTree<ElemType> &bt)
//	�����������״��ʽ��ʾ���������� 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// ��״��ʾ��bt.GetRoot()Ϊ��������������
	cout << endl;
}

#endif
