#ifndef __TRI_LK_BINNARY_TREE_H__
#define __TRI_LK_BINNARY_TREE_H__

#include "lk_queue.h"				// ������
#include "tri_lk_bin_tree_node.h"	// ������������������

// ���������������
template <class ElemType>
class TriLkBinaryTree
{
protected:
//  �����������ݳ�Ա:
	TriLkBinTreeNode<ElemType> *root;

//	��������:
	TriLkBinTreeNode<ElemType> *CopyTreeHelp(TriLkBinTreeNode<ElemType> *copy);	// ���ƶ�����
	void DestroyHelp(TriLkBinTreeNode<ElemType> * &r);						// ������rΪ��������
	void PreOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// �������
	void InOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;		// �������
	void PostOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// �������
    int HeightHelp(const TriLkBinTreeNode<ElemType> *r) const;				// ���ض������ĸ�
	int NodeCountHelp(const TriLkBinTreeNode<ElemType> *r) const;			// ���ض������Ľ�����

public:
//  �������������������ر���ϵͳĬ�Ϸ�������:
	TriLkBinaryTree();											// �޲����Ĺ��캯��
	virtual ~TriLkBinaryTree();									// ��������
	TriLkBinTreeNode<ElemType> *GetRoot() const;				// ���ض������ĸ�
	bool Empty() const;											// �ж϶������Ƿ�Ϊ��
	StatusCode GetElem(TriLkBinTreeNode<ElemType> *cur, ElemType &e) const;
		// ��e���ؽ��Ԫ��ֵ
	StatusCode SetElem(TriLkBinTreeNode<ElemType> *cur, const ElemType &e);
		// ����cur��ֵ��Ϊe
	void InOrder(void (*Visit)(const ElemType &)) const;		// ���������������	
	void PreOrder(void (*Visit)(const ElemType &)) const;		// ���������������
	void PostOrder(void (*Visit)(const ElemType &)) const;		// �������ĺ������
	void LevelOrder(void (*Visit)(const ElemType &)) const;		// �������Ĳ�α���
	int NodeCount() const;										// ��������Ľ�����
	TriLkBinTreeNode<ElemType> *LeftChild(const TriLkBinTreeNode<ElemType> *cur) const;
		// ���ض��������cur������
	TriLkBinTreeNode<ElemType> *RightChild(const TriLkBinTreeNode<ElemType> *cur) const;
		// ���ض��������cur���Һ���
	TriLkBinTreeNode<ElemType> *Parent(const TriLkBinTreeNode<ElemType> *cur) const;
		// ���ض��������cur��˫��
	void InsertLeftChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e);	// ��������
	void InsertRightChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e);// �����Һ���
	void DeleteLeftChild(TriLkBinTreeNode<ElemType> *cur);		// ɾ��������
	void DeleteRightChild(TriLkBinTreeNode<ElemType> *cur);		// ɾ�����Ӵ�
	int	Height() const;											// ��������ĸ�
	TriLkBinaryTree(const ElemType &e);							// ������eΪ���Ķ�����
	TriLkBinaryTree(const TriLkBinaryTree<ElemType> &copy);		// ���ƹ��캯��
	TriLkBinaryTree(TriLkBinTreeNode<ElemType> *r);				// ������rΪ���Ķ�����
	TriLkBinaryTree<ElemType> &operator=(const TriLkBinaryTree<ElemType>& copy);	// ��ֵ���������
};

template <class ElemType>
void DisplayBTWithTreeShapeHelp(TriLkBinTreeNode<ElemType> *r, int level);
	//	����״��ʽ��ʾ��rΪ���Ķ�������levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayBTWithTreeShape(TriLkBinaryTree<ElemType> &bt);
	//	��״��ʽ��ʾ������ 
template <class ElemType>
void CreateBinaryTreeHelp(TriLkBinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
							int preLeft, int preRight, int inLeft, int inRight);	
	// ��֪����������������pre[preLeft..preRight]����������in[inLeft..inRight]������rΪ����
	// ������
template <class ElemType>
TriLkBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n);
	// ��֪������������й��������



// ���������ʵ�ֲ���
template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree()
// �������������һ���ն�����
{
	root = NULL;
}

template <class ElemType>
TriLkBinaryTree<ElemType>::~TriLkBinaryTree()
// ������������ٶ�����--���캯��
{
	DestroyHelp(root);
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::GetRoot() const
// ������������ض������ĸ�
{
	return root;
}

template <class ElemType>
bool TriLkBinaryTree<ElemType>::Empty() const
// ����������ж϶������Ƿ�Ϊ��
{
	return root == NULL;
}

template <class ElemType>
StatusCode TriLkBinaryTree<ElemType>::GetElem(TriLkBinTreeNode<ElemType> *cur, ElemType &e) const
// �����������e���ؽ��curԪ��ֵ,��������ڽ��cur,��������NOT_PRESENT,���򷵻�ENTRY_FOUND
{
	if (cur == NULL)	
	{	// �����ڽ��cur
		return NOT_PRESENT;			// ����NOT_PRESENT
	}
	else
	{	// ���ڽ��cur
		e = cur->data;				// ��e����Ԫ��ֵ
		return ENTRY_FOUND;			// ����ENTRY_FOUND
	}
}

template <class ElemType>
StatusCode TriLkBinaryTree<ElemType>::SetElem(TriLkBinTreeNode<ElemType> *cur, const ElemType &e)
// �����������������ڽ��cur,�򷵻�FAIL,���򷵻�SUCCESS,�������cur��ֵ����Ϊe
{
	if (cur == NULL)	
	{	// �����ڽ��cur
		return FAIL;				// ����FAIL
	}
	else
	{	// ���ڽ��cur
		cur->data = e;				// �����cur��ֵ����Ϊe
		return SUCCESS;				// ����SUCCESS
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::PreOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &))const
// ������������������rΪ���Ķ�����
{
	if (r != NULL) 
	{
		(*Visit)(r->data);					// ���ʸ����
		PreOrderHelp(r->leftChild, Visit);	// ����������
		PreOrderHelp(r->rightChild, Visit);	// ����������
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// ����������������������
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType>
void TriLkBinaryTree<ElemType>::InOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ�����
{
	if (r != NULL) 
	{
		InOrderHelp(r->leftChild, Visit);	// ����������
		(*Visit)(r->data);					// ���ʸ����
		InOrderHelp(r->rightChild, Visit);	// ����������
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// ����������������������
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType>
void TriLkBinaryTree<ElemType>::PostOrderHelp(TriLkBinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ�����
{
	if (r != NULL) 
	{
		PostOrderHelp(r->leftChild, Visit);	// ����������
		PostOrderHelp(r->rightChild, Visit);// ����������
		(*Visit)(r->data);					// ���ʸ����
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// ����������������������
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType>
void TriLkBinaryTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// �����������α���������
{
	LinkQueue<TriLkBinTreeNode<ElemType> *> q;	// ����
	TriLkBinTreeNode<ElemType> *t = root;		// �Ӹ���㿪ʼ���в�α���
	
	if (t != NULL) q.InQueue(t);				// ������ǿ�,�����
	while (!q.Empty())
	{	// q�ǿ�,˵�����н��δ����
		q.OutQueue(t);     
		(*Visit)(t->data);
		if (t->leftChild != NULL)				// ���ӷǿ�
			q.InQueue(t->leftChild);			// �������
		if (t->rightChild != NULL)				// �Һ��ӷǿ�
			q.InQueue(t->rightChild);			// �Һ������
	}
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::HeightHelp(const TriLkBinTreeNode<ElemType> *r) const
// ���������������rΪ���Ķ������ĸ�
{
	if(r == NULL)
	{	// �ն�������Ϊ0
		return 0;
	}
	else
	{	// �ǿն�������Ϊ���������ĸߵ����ֵ�ټ�1
		int lHeight, rHeight;
		lHeight = HeightHelp(r->leftChild);		// �������ĸ�
		rHeight = HeightHelp(r->rightChild);	// �������ĸ�
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// �ǿն�������Ϊ���������ĸߵ����ֵ�ټ�1
	}
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::Height() const
// ������������ض������ĸ�
{
	return HeightHelp(root);
}

template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree(const ElemType &e)
// ���������������eΪ���Ķ�����
{
	root = new TriLkBinTreeNode<ElemType>(e);
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::NodeCountHelp(const TriLkBinTreeNode<ElemType> *r) const
// ���������������rΪ���Ķ������Ľ�����
{
	if (r ==NULL) return 0;						// �ն�����������Ϊ0
	else return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
		// �ǿն���������Ϊ���������Ľ�����֮���ټ�1
}

template <class ElemType>
int TriLkBinaryTree<ElemType>::NodeCount() const
// ������������ض������Ľ�����
{
	return NodeCountHelp(root);
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::LeftChild(const TriLkBinTreeNode<ElemType> *cur) const
// ������������ض��������cur������
{
	return cur->leftChild;
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::RightChild(const TriLkBinTreeNode<ElemType> *cur) const
// ������������ض��������cur���Һ���
{
	return cur->rightChild;
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::Parent(const TriLkBinTreeNode<ElemType> *cur) const
// ������������ض��������cur��˫��
{
	return cur->parent;
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::InsertLeftChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e)
// ��ʼ������cur�ǿգ�
// �������������Ԫ��ֵΪe�Ľ��Ϊcur�����ӣ����cur�����ӷǿգ���curԭ����������Ϊe��������
{
	if (cur == NULL)
	{	// curΪ�գ�����
		return;
	}
	else 
	{	// ��������
		TriLkBinTreeNode<ElemType> *child =  new TriLkBinTreeNode<ElemType>(e);// Ԫ��ֵΪe���
		if (cur->leftChild != NULL)
		{	// cur�����ӷǿ�
			child->leftChild = cur->leftChild;	// curԭ����������Ϊe��������
			cur->leftChild->parent = child;		// curԭ���������ĸ���˫��Ϊe
		}
		cur->leftChild = child;					// e��Ϊcur������
		child->parent = cur;					// e��˫��Ϊcur
		return;
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::InsertRightChild(TriLkBinTreeNode<ElemType> *cur, const ElemType &e)
// ��ʼ������cur�ǿ�
// �������������Ԫ��ֵΪe�Ľ��Ϊcur���Һ��ӣ����cur���Һ��ӷǿգ���curԭ����������Ϊe��������
{
	if (cur == NULL)
	{	// curΪ�գ�����
		return;
	}
	else
	{	// �����Һ���
		TriLkBinTreeNode<ElemType> *child =  new TriLkBinTreeNode<ElemType>(e);// Ԫ��ֵΪe���
		if (cur->rightChild != NULL)
		{	// cur���Һ��ӷǿ�
			child->rightChild = cur->rightChild;// curԭ����������Ϊe��������
			cur->rightChild->parent = child;	// curԭ���������ɵĸ���˫��Ϊchild
		}
		cur->rightChild = child;				// e��Ϊcur���Һ���
		child->parent= cur;						// e��˫��Ϊcur
		return;
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::DeleteLeftChild(TriLkBinTreeNode<ElemType> *cur)
// ��ʼ������cur�ǿ�
// ���������ɾ��cur������
{
	if (cur == NULL)
	{	// curΪ��
		return;
	}
	else
	{	// cur�ǿ�
		DestroyHelp(cur->leftChild);		// ɾ��cur������
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::DeleteRightChild(TriLkBinTreeNode<ElemType> *cur)
// ��ʼ������cur�ǿ�
// ���������ɾ��cur������
{
	if (cur == NULL)
	{	// curΪ��
		return;
	}
	else
	{	// cur�ǿ�
		DestroyHelp(cur->rightChild);		// ɾ��cur������
	}
}

template <class ElemType>
void TriLkBinaryTree<ElemType>::DestroyHelp(TriLkBinTreeNode<ElemType> *&r)
// ���������������r�Ķ�����
{
	if(r != NULL)
	{	// r�ǿ�,ʵʩ����
		DestroyHelp(r->leftChild);			// ����������
		DestroyHelp(r->rightChild);			// ����������
		delete r;							// ���ٸ����
		r = NULL;
	}
}

template <class ElemType>
TriLkBinTreeNode<ElemType> *TriLkBinaryTree<ElemType>::CopyTreeHelp(TriLkBinTreeNode<ElemType> *copy)
// �������������copyΪ���Ķ��������Ƴ��µĶ�����,�����¶������ĸ�
{
	if (copy == NULL)
	{	// ���ƿն�����
		return NULL;						// �ն�������Ϊ��	
	}
	else
	{	// ���Ʒǿն�����
		TriLkBinTreeNode<ElemType> *lChild = CopyTreeHelp(copy->leftChild);	// ����������
		TriLkBinTreeNode<ElemType> *rChild = CopyTreeHelp(copy->rightChild);// ����������
		TriLkBinTreeNode<ElemType> *r = new TriLkBinTreeNode<ElemType>(copy->data, lChild, rChild);
			// ���Ƹ����
		if (lChild != NULL) lChild->parent = r;		// lChild˫��Ϊr
		if (rChild != NULL) rChild->parent = r;		// rChild˫��Ϊr
		return r;
	}
}

template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree(const TriLkBinaryTree<ElemType> &copy)
// �������������֪�����������¶������������ƹ��캯��
{
	root = CopyTreeHelp(copy.root);				// ���ƶ�����
}

template <class ElemType>
TriLkBinaryTree<ElemType>::TriLkBinaryTree(TriLkBinTreeNode<ElemType> *r)
// ���������������rΪ���Ķ�����
{	
	root = r;								// ���ƶ�����
}

template <class ElemType>
TriLkBinaryTree<ElemType> &TriLkBinaryTree<ElemType>::operator=(const TriLkBinaryTree<ElemType> &copy)
// �������������֪������copy���Ƶ���ǰ������--��ֵ���������
{
	if (&copy != this)
	{
		DestroyHelp(root);					// �ͷ�ԭ��������ռ�ÿռ�
		root = CopyTreeHelp(copy.root);			// ���ƶ�����
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(TriLkBinTreeNode<ElemType> *r, int level)
//	�������������״��ʽ��ʾ��rΪ���Ķ�������levelΪ���������������Ĳ����Ϊ1
{
	if(r != NULL)
	{	//��������ʽ��ֻ��ʽ�ǿ���
		DisplayBTWithTreeShapeHelp<ElemType>(r->rightChild, level + 1);//��ʾ������
		cout << endl;						// ��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout << " ";					// ȷ���ڵ�level����ʾ���
		cout << r->data;					// ��ʾ���
		DisplayBTWithTreeShapeHelp<ElemType>(r->leftChild, level + 1);//��ʾ������
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(TriLkBinaryTree<ElemType> &bt)
//	�����������״��ʽ��ʾ������ 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt.GetRoot(), 1);	
		// ��״��ʾ��bt.GetRoot()Ϊ���Ķ�����
	cout << endl;
}

template <class ElemType>
void CreateBinaryTreeHelp(TriLkBinTreeNode<ElemType> *&r, ElemType pre[], ElemType in[], 
							int preLeft, int preRight, int inLeft, int inRight)	
// �����������֪����������������pre[preLeft..preRight]����������in[inLeft..inRight]����
//	��rΪ���Ķ�����
{
	if (inLeft > inRight)
	{	// �������޽��,�ն�����
		r = NULL;							// �ն�������Ϊ��
	}
	else
	{	// �������н��,�ǿն�����
		r = new TriLkBinTreeNode<ElemType>(pre[preLeft]);		// ���ɸ����
		int mid = inLeft;
		while (in[mid] != pre[preLeft]) 
		{	// ����pre[preLeft]��in[]�е�λ��,Ҳ�������������и���λ��
			mid++;
		}
		CreateBinaryTreeHelp(r->leftChild, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid - 1);
			// ����������
		if (r->leftChild != NULL) r->leftChild->parent = r;		// ���ӵ�˫��Ϊr
		CreateBinaryTreeHelp(r->rightChild, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, 
			inRight);											// ����������
		if (r->rightChild != NULL) r->rightChild->parent = r;	// �Һ��ӵ�˫��Ϊr
	}
} 

template <class ElemType>
TriLkBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n)
// �����������֪������������й��������
{
	TriLkBinTreeNode<ElemType> *r;								// �������ĸ�
	CreateBinaryTreeHelp<ElemType>(r, pre, in, 0, n - 1, 0, n - 1);
		// ��������������й�����rΪ���Ķ����� 
	TriLkBinaryTree<ElemType> *bt = new TriLkBinaryTree<ElemType>(r);// ���ɶ�����
	return *bt;
}

#endif
