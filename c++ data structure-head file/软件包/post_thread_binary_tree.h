#ifndef __POST_THREAD_BINARY_TREE_H__
#define __POST_THREAD_BINARY_TREE_H__

#include "tri_lk_binary_tree.h"			// ���������������
#include "post_thread_bin_tree_node.h"	// �������������������

// ����������������
template <class ElemType>
class PostThreadBinTree
{
protected:
//  ���������������ݳ�Ա:
	PostThreadBinTreeNode<ElemType> *root;

//	��������:
	void PostThreadHelp(PostThreadBinTreeNode<ElemType> *cur, PostThreadBinTreeNode<ElemType> *&pre);
		// ������������curΪ���Ķ�����
	PostThreadBinTreeNode<ElemType> *TransformHelp(TriLkBinTreeNode<ElemType> *r);
		// btΪ���Ķ�����ת�����µ�δ�������ĺ�������������,�����¶������ĸ�
	PostThreadBinTreeNode<ElemType> *CopyTreeHelp(PostThreadBinTreeNode<ElemType> *copy);	
		// ��������������
	void DestroyHelp(PostThreadBinTreeNode<ElemType> * &r);		// ������rΪ��������

public:
//  �����������������������ر���ϵͳĬ�Ϸ�������:
	PostThreadBinTree(const TriLkBinaryTree<ElemType> &bt);		// �ɶ��������������������������ת�����캯��
	virtual ~PostThreadBinTree();								// ���캯��
	PostThreadBinTreeNode<ElemType> *GetRoot() const;			// ���������������ĸ�
	void PostThread();											// ����������������
	void PostOrder(void (*Visit)(const ElemType &)) const;		// �������ĺ������	
	PostThreadBinTree(const PostThreadBinTree<ElemType> &copy);	// ���ƹ��캯��
	PostThreadBinTree<ElemType> &operator=(const PostThreadBinTree<ElemType>& copy);// ��ֵ���������
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(PostThreadBinTreeNode<ElemType> *r, int level);
	//	����״��ʽ��ʾ��rΪ����������������levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayBTWithTreeShape(PostThreadBinTree<ElemType> &bt);
	//	��״��ʽ��ʾ���������� 

// ���������ʵ�ֲ���
template <class ElemType>
void PostThreadBinTree<ElemType>::PostThreadHelp(PostThreadBinTreeNode<ElemType> *cur, PostThreadBinTreeNode<ElemType> *&pre)
// ���������������������curΪ���Ķ�����,pre��ʾcur��ǰ��
{
	if (cur != NULL)
	{	// �����������ʽ����������
		if (cur->leftTag == CHILD_PTR)		
			PostThreadHelp(cur->leftChild, pre);// ������������
		if (cur->rightTag == CHILD_PTR)		
			PostThreadHelp(cur->rightChild, pre);// ������������

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
	}
}

template <class ElemType>
void PostThreadBinTree<ElemType>::PostThread()
// �������������������������
{
	PostThreadBinTreeNode<ElemType> *pre = NULL;// ��ʼ������ʱǰ��Ϊ��
	PostThreadHelp(root, pre);					// ������������rootΪ���Ķ�����
	if (pre->rightChild == NULL)				// preΪ�������������һ�����
		pre->rightTag = THREAD_PTR;				// �����Һ���,����������
}

template <class ElemType>
PostThreadBinTreeNode<ElemType> *PostThreadBinTree<ElemType>::TransformHelp(TriLkBinTreeNode<ElemType> *r)
// ���������rΪ���Ķ�����ת�����µ�δ�������ĺ�������������,�����¶������ĸ�
{
	if (r == NULL)
	{	// �ն�����ת�����µĿ�����������
		return NULL;					// ��������������Ϊ��	
	}
	else
	{	// ת���ǿն�����
		PostThreadBinTreeNode<ElemType> *lChild = TransformHelp(r->leftChild);	// ת��������
		PostThreadBinTreeNode<ElemType> *rChild = TransformHelp(r->rightChild);	// ת��������
		PostThreadBinTreeNode<ElemType> *rt = new PostThreadBinTreeNode<ElemType>(r->data, lChild, rChild);
			// ת�������
		if (lChild != NULL) lChild->parent = rt;	// lChild˫��Ϊrt
		if (rChild != NULL) rChild->parent = rt;	// rChild˫��Ϊrt
		return rt;															// ���ظ����
	}
}

template <class ElemType>
PostThreadBinTree<ElemType>::PostThreadBinTree(const TriLkBinaryTree<ElemType> &bt)
// ����������ɶ��������������������������ת�����캯��
{
	root = TransformHelp(bt.GetRoot());			// ת����δ�������Ķ�����
	PostThread();								// ������������
}

template <class ElemType>
void PostThreadBinTree<ElemType>::DestroyHelp(PostThreadBinTreeNode<ElemType> * &r)
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
PostThreadBinTree<ElemType>::~PostThreadBinTree()
// �����������������������--���캯��
{
	DestroyHelp(root);
}

template <class ElemType>
PostThreadBinTreeNode<ElemType> *PostThreadBinTree<ElemType>::GetRoot() const
// ������������������������ĸ�
{	
	return root;
}

template <class ElemType>
void PostThreadBinTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// ����������������ĺ������	
{
	if (root != NULL)
	{
		PostThreadBinTreeNode<ElemType> *cur = root;		// �Ӹ���ʼ����
		while (cur->leftTag == CHILD_PTR || cur->rightTag == CHILD_PTR)
		{	// ���������µĽ��,�˽��Ϊ�������е�һ�����
			if (cur->leftTag == CHILD_PTR) cur = cur->leftChild;	// ��������
			else cur = cur->rightChild;						// ������,�������Һ���
		}
		
		while (cur != NULL)
		{
			(*Visit)(cur->data);							// ���ʵ�ǰ���

			PostThreadBinTreeNode<ElemType> *pt = cur->parent;	// ��ǰ����˫�� 
			if (cur->rightTag == THREAD_PTR)
			{	// ������Ϊ����, ���Ϊcur->rightChild
				cur = cur->rightChild; 
			}
			else if (cur == root)
			{	// ���cur�Ƕ������ĸ�������Ϊ��
				cur = NULL;
			}
			else if (pt->rightChild == cur || pt->leftChild == cur && pt->rightTag == THREAD_PTR)
			{	// ���cur����˫�׵��Һ��ӻ�����˫�׵���������˫��û������������
				// ���̼�Ϊ˫�׽��
				cur = pt;
			}
			else 
			{	// ���cur����˫�׵����ӣ�����˫������������������Ϊ˫�׵���
				// �����а����������г��ĵ�һ����㣬����˫�׵��������������µĽ��
				cur = pt->rightChild;						// curָ��˫�׵��Һ���
				while (cur->leftTag == CHILD_PTR || cur->rightTag == CHILD_PTR)
				{	// ���������µĽ��,�˽��Ϊ�������е�һ�����
					if (cur->leftTag == CHILD_PTR) cur = cur->leftChild;	// ��������
					else cur = cur->rightChild;				// ������,�������Һ���
				}
			}
		}
	}
}

template <class ElemType>
PostThreadBinTreeNode<ElemType> *PostThreadBinTree<ElemType>::CopyTreeHelp(PostThreadBinTreeNode<ElemType> *copy)	
// �������������copyΪ�����������������Ƴ��µ�δ�������Ķ�����,�����¶������ĸ�
{
	if (copy == NULL)
	{	// ���ƿ�����������
		return NULL;									// ��������������Ϊ��	
	}
	else
	{	// ���Ʒǿ�����������
		PostThreadBinTreeNode<ElemType> *lChild;
		PostThreadBinTreeNode<ElemType> *rChild;
		
		if (copy->leftTag == CHILD_PTR)
			lChild = CopyTreeHelp(copy->leftChild);		// ����������
		else lChild = NULL;								// ������Ϊ��
		
		if (copy->rightTag == CHILD_PTR)
			rChild = CopyTreeHelp(copy->rightChild);	// ����������
		else rChild = NULL;								// ������Ϊ��
		
		PostThreadBinTreeNode<ElemType> *r = new PostThreadBinTreeNode<ElemType>(copy->data, lChild, rChild);
			// ���Ƹ����
		if (lChild != NULL) lChild->parent = r;			// lChild˫��Ϊr
		if (rChild != NULL) rChild->parent = r;			// rChild˫��Ϊr

		return r;
	}
}

template <class ElemType>
PostThreadBinTree<ElemType>::PostThreadBinTree(const PostThreadBinTree<ElemType> &copy)
// �������������֪���������������������������������ƹ��캯��
{
	root = CopyTreeHelp(copy.root);						// ��������������
	PostThread();										// ����������������
}

template <class ElemType>
PostThreadBinTree<ElemType> &PostThreadBinTree<ElemType>::operator=(const PostThreadBinTree<ElemType> &copy)
// �������������֪����������copy���Ƶ���ǰ����������--��ֵ���������
{
	if (&copy != this)
	{
		DestroyHelp(root);								// �ͷ�ԭ������������ռ�ÿռ�
		root = CopyTreeHelp(copy.root);					// ��������������
		PostThread();									// ����������������
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(PostThreadBinTreeNode<ElemType> *r, int level)
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
void DisplayBTWithTreeShape(PostThreadBinTree<ElemType> &bt)
//	�����������״��ʽ��ʾ���������� 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// ��״��ʾ��bt.GetRoot()Ϊ��������������
	cout << endl;
}

#endif
