#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "lk_queue.h"					// ������
#include "lk_stack.h"					// ��ջ
#include "bin_avl_tree_node.h"			// ����ƽ���������

// ����ƽ������
template <class ElemType, class KeyType>
class BinaryAVLTree
{
protected:
//  ����ƽ���������ݳ�Ա:
	BinAVLTreeNode<ElemType> *root;

//	��������:
	BinAVLTreeNode<ElemType> *CopyTreeHelp(BinAVLTreeNode<ElemType> *copy);	// ���ƶ���ƽ����
	void DestroyHelp(BinAVLTreeNode<ElemType> * &r);						// ������rΪ������ƽ����
	void PreOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// �������
	void InOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// �������
	void PostOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// �������
    int HeightHelp(const BinAVLTreeNode<ElemType> *r) const;	// ���ض���ƽ�����ĸ�
	int NodeCountHelp(const BinAVLTreeNode<ElemType> *r) const;// ���ض���ƽ�����Ľ�����
	BinAVLTreeNode<ElemType> *ParentHelp(BinAVLTreeNode<ElemType> *r, 
		const BinAVLTreeNode<ElemType> *cur) const;			// ����cur��˫��
	BinAVLTreeNode<ElemType> *SearchHelp(const KeyType &key, BinAVLTreeNode<ElemType> *&f) const;	
		// ���ҹؼ���Ϊkey������Ԫ��

	BinAVLTreeNode<ElemType> *SearchHelp(const KeyType &key, BinAVLTreeNode<ElemType> *&f,
		LinkStack<BinAVLTreeNode<ElemType> *> &s); // ����ָ��ؼ���Ϊkey��Ԫ�ص�ָ��,��f������˫��
	void LeftRotate(BinAVLTreeNode<ElemType> *&subRoot);
		// ����subRootΪ���Ķ���������������,����֮��subRootָ���µ��������,Ҳ������ת����ǰ������
		// ���ĸ����
	void RightRotate(BinAVLTreeNode<ElemType> *&subRoot);
		// ����subRootΪ���Ķ���������������,����֮��subRootָ���µ��������,Ҳ������ת����ǰ������
		// ���ĸ����
	void InsertLeftBalance(BinAVLTreeNode<ElemType> *&subRoot);
		// ����subRootΪ���Ķ���������ʱ����ƽ�⴦��,�����subRootָ���µ��������
	void InsertRightBalance(BinAVLTreeNode<ElemType> *&subRoot);
		// ����subRootΪ���Ķ���������ʱ����ƽ�⴦��,�����subRootָ���µ��������
	void InsertBalance(const ElemType &elem, LinkStack< BinAVLTreeNode<ElemType> *> &s);
		// �Ӳ�����elem���ݲ���·�����л���,����ƽ�⴦��
	void DeleteLeftBalance(BinAVLTreeNode<ElemType> *&subRoot, bool &isShorter);
		// ����subRootΪ���Ķ�����ɾ��ʱ����ƽ�⴦��,�����subRootָ���µ��������
	void DeleteRightBalance(BinAVLTreeNode<ElemType> *&subRoot, bool &isShorter);
		// ����subRootΪ���Ķ�����ɾ��ʱ����ƽ�⴦��,�����subRootָ���µ��������
	void DeleteBalance(const KeyType &key, LinkStack<BinAVLTreeNode<ElemType> *> &s);
		// ��ɾ�������ݲ���·�����л���,����ƽ�⴦��
	void DeleteHelp(const KeyType &key, BinAVLTreeNode<ElemType> *&p,
		LinkStack< BinAVLTreeNode<ElemType> *> &s);		// ɾ��pָ��Ľ��

public:
//  ����ƽ�����������������ر���ϵͳĬ�Ϸ�������:
	BinaryAVLTree();										// �޲����Ĺ��캯��
	virtual ~BinaryAVLTree();								// ��������
	BinAVLTreeNode<ElemType> *GetRoot() const;				// ���ض���ƽ�����ĸ�
	bool Empty() const;										// �ж϶���ƽ�����Ƿ�Ϊ��
	StatusCode GetElem(BinAVLTreeNode<ElemType> *cur, ElemType &e) const;
		// ��e���ؽ������Ԫ��ֵ
	StatusCode SetElem(BinAVLTreeNode<ElemType> *cur, const ElemType &e);
		// ����cur��ֵ��Ϊe
	void InOrder(void (*Visit)(const ElemType &)) const;	// ����ƽ�������������	
	void PreOrder(void (*Visit)(const ElemType &)) const;	// ����ƽ�������������
	void PostOrder(void (*Visit)(const ElemType &)) const;	// ����ƽ�����ĺ������
	void LevelOrder(void (*Visit)(const ElemType &)) const;	// ����ƽ�����Ĳ�α���
	int NodeCount() const;									// �����ƽ�����Ľ�����
	BinAVLTreeNode<ElemType> *Search(const KeyType &key) const;// ���ҹؼ���Ϊkey������Ԫ��
	bool Insert(const ElemType &e);							// ��������Ԫ��e
	bool Delete(const KeyType &key);						// ɾ���ؼ���Ϊkey������Ԫ��
	BinAVLTreeNode<ElemType> *LeftChild(const BinAVLTreeNode<ElemType> *cur) const;
		// ���ض���ƽ�������cur������
	BinAVLTreeNode<ElemType> *RightChild(const BinAVLTreeNode<ElemType> *cur) const;
		// ���ض���ƽ�������cur���Һ���
	BinAVLTreeNode<ElemType> *Parent(const BinAVLTreeNode<ElemType> *cur) const;
		// ���ض���ƽ�������cur��˫��
	int	Height() const;										// �����ƽ�����ĸ�
	BinaryAVLTree(const ElemType &e);						// ������eΪ���Ķ���ƽ����
	BinaryAVLTree(const BinaryAVLTree<ElemType, KeyType> &copy);	// ���ƹ��캯��
	BinaryAVLTree(BinAVLTreeNode<ElemType> *r);				// ������rΪ���Ķ���ƽ����
	BinaryAVLTree<ElemType, KeyType> &operator=(const BinaryAVLTree<ElemType, KeyType>& copy);	// ��ֵ�������
};

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinAVLTreeNode<ElemType> *r, int level);
	//	����״��ʽ��ʾ��rΪ���Ķ���ƽ������levelΪ���������������Ĳ����Ϊ1
template <class ElemType, class KeyType>
void DisplayBTWithTreeShape(const BinaryAVLTree<ElemType, KeyType> &bt);
	//	��״��ʽ��ʾ����ƽ���� 

// ����ƽ�������ʵ�ֲ���
template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::BinaryAVLTree()
// �������������һ���ն���ƽ����
{
	root = NULL;
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::~BinaryAVLTree()
// ������������ٶ���ƽ����--���캯��
{
	DestroyHelp(root);
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::GetRoot() const
// ������������ض���ƽ�����ĸ�
{
	return root;
}

template <class ElemType, class KeyType>
bool BinaryAVLTree<ElemType, KeyType>::Empty() const
// ����������ж϶���ƽ�����Ƿ�Ϊ��
{
	return root == NULL;
}

template <class ElemType, class KeyType>
StatusCode BinaryAVLTree<ElemType, KeyType>::GetElem(BinAVLTreeNode<ElemType> *cur, ElemType &e) const
// �����������e���ؽ��cur����Ԫ��ֵ,��������ڽ��cur,��������NOT_PRESENT,���򷵻�ENTRY_FOUND
{
	if (cur == NULL)	
	{	// �����ڽ��cur
		return NOT_PRESENT;			// ����NOT_PRESENT
	}
	else
	{	// ���ڽ��cur
		e = cur->data;				// ��e��������Ԫ��ֵ
		return ENTRY_FOUND;			// ����ENTRY_FOUND
	}
}

template <class ElemType, class KeyType>
StatusCode BinaryAVLTree<ElemType, KeyType>::SetElem(BinAVLTreeNode<ElemType> *cur, const ElemType &e)
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

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::PreOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ���ƽ����
{
	if (r != NULL) 
	{
		(*Visit)(r->data);					// ���ʸ����
		PreOrderHelp(r->leftChild, Visit);	// ����������
		PreOrderHelp(r->rightChild, Visit);	// ����������
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::PreOrder(void (*Visit)(const ElemType &)) const
// ��������������������ƽ����
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ���ƽ����
{
	if (r != NULL) 
	{
		InOrderHelp(r->leftChild, Visit);	// ����������
		(*Visit)(r->data);					// ���ʸ����
		InOrderHelp(r->rightChild, Visit);	// ����������
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InOrder(void (*Visit)(const ElemType &)) const
// ��������������������ƽ����
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::PostOrderHelp(BinAVLTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ���ƽ����
{
	if (r != NULL) 
	{
		PostOrderHelp(r->leftChild, Visit);	// ����������
		PostOrderHelp(r->rightChild, Visit);// ����������
		(*Visit)(r->data);					// ���ʸ����
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::PostOrder(void (*Visit)(const ElemType &)) const
// ��������������������ƽ����
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::LevelOrder(void (*Visit)(const ElemType &)) const
// �����������α�������ƽ����
{
	LinkQueue<BinAVLTreeNode<ElemType> *> q;	// ����
	BinAVLTreeNode<ElemType> *t = root;		// �Ӹ���㿪ʼ���в�α���
	
	if (t != NULL) q.InQueue(t);			// ������ǿ�,�����
	while (!q.Empty())
	{	// q�ǿ�,˵�����н��δ����
		q.OutQueue(t);     
		(*Visit)(t->data);
		if (t->leftChild != NULL)			// ���ӷǿ�
			q.InQueue(t->leftChild);		// �������
		if (t->rightChild != NULL)			// �Һ��ӷǿ�
			q.InQueue(t->rightChild);		// �Һ������
	}
}

template <class ElemType, class KeyType>
int BinaryAVLTree<ElemType, KeyType>::HeightHelp(const BinAVLTreeNode<ElemType> *r) const
// ���������������rΪ���Ķ���ƽ�����ĸ�
{
	if(r == NULL)
	{	// �ն���ƽ������Ϊ0
		return 0;
	}
	else
	{	// �ǿն���ƽ������Ϊ���������ĸߵ����ֵ�ټ�1
		int lHeight, rHeight;
		lHeight = HeightHelp(r->leftChild);		// �������ĸ�
		rHeight = HeightHelp(r->rightChild);	// �������ĸ�
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// �ǿն���ƽ������Ϊ���������ĸߵ����ֵ�ټ�1
	}
}

template <class ElemType, class KeyType>
int BinaryAVLTree<ElemType, KeyType>::Height() const
// ������������ض���ƽ�����ĸ�
{
	return HeightHelp(root);
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::BinaryAVLTree(const ElemType &e)
// ���������������eΪ���Ķ���ƽ����
{
	root = new BinAVLTreeNode<ElemType>(e);
}

template <class ElemType, class KeyType>
int BinaryAVLTree<ElemType, KeyType>::NodeCountHelp(const BinAVLTreeNode<ElemType> *r) const
// ���������������rΪ���Ķ���ƽ�����Ľ�����
{
	if (r ==NULL) return 0;			// �ն���ƽ����������Ϊ0
	else return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
		// �ǿն���ƽ��������Ϊ���������Ľ�����֮���ټ�1
}

template <class ElemType, class KeyType>
int BinaryAVLTree<ElemType, KeyType>::NodeCount() const
// ������������ض���ƽ�����Ľ�����
{
	return NodeCountHelp(root);
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::LeftChild(const BinAVLTreeNode<ElemType> *cur) const
// ������������ض���ƽ�������cur������
{
	return cur->leftChild;
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::RightChild(const BinAVLTreeNode<ElemType> *cur) const
// ������������ض���ƽ�������cur���Һ���
{
	return cur->rightChild;
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> * BinaryAVLTree<ElemType, KeyType>::ParentHelp(BinAVLTreeNode<ElemType> *r, const BinAVLTreeNode<ElemType> *cur) const
// ���������������rΪ���Ķ���ƽ����, ���cur��˫��
{
	if (r == NULL) return NULL;		// �ն���ƽ����
	else if (r->leftChild == cur || r->rightChild == cur) return r; // rΪcur��˫��
	else
	{	// ����������˫��
		BinAVLTreeNode<ElemType> *tmp;
		
		tmp = ParentHelp(r->leftChild, cur);	// ������������cur��˫��	
		if (tmp != NULL) return tmp;			// ˫������������

		tmp = ParentHelp(r->rightChild, cur);	// ������������cur��˫��	
		if (tmp != NULL) return tmp;			// ˫������������
		else return NULL;						// ��ʾcur��˫��
	}
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::Parent(const BinAVLTreeNode<ElemType> *cur) const
// ������������ض���ƽ�������cur��˫��
{
	return ParentHelp(root, cur);
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::SearchHelp(const KeyType &key, BinAVLTreeNode<ElemType> *&f) const
// �������: ����ָ��ؼ���Ϊkey������Ԫ�ص�ָ��,��f������˫��,ջs�洢����·��
{
	BinAVLTreeNode< ElemType> *p = GetRoot();	// ָ��ǰ���
	f = NULL;								// ָ��p��˫��
	
	while (p != NULL && p->data != key)
	{	// ���ҹؼ���Ϊkey�Ľ��
		if (key < p->data)
		{	// key��С,���������Ͻ��в���
			f = p;
			p = p->leftChild;
		}
		else
		{	// key����,���������Ͻ��в���
			f = p;
			p = p->rightChild;
		}
	}
	
	return p;
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::Search(const KeyType &key)	const 
// �������: ����ָ��ؼ���Ϊkey������Ԫ�ص�ָ��
{
	BinAVLTreeNode<ElemType> *f;			// ָ�򱻲��ҽ���˫��
	return SearchHelp(key, f);
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::SearchHelp(
	const KeyType &key,	BinAVLTreeNode<ElemType> *&f,
	LinkStack<BinAVLTreeNode<ElemType> *> &s) 
// �������: ����ָ��ؼ���Ϊkey��Ԫ�ص�ָ��,��f������˫��
{
	BinAVLTreeNode<ElemType> *p = GetRoot();	// ָ��ǰ���
	f = NULL;		// ָ��p��˫��
	while (p != NULL && p->data != key)
	{	// ��Ѱ�ؼ���Ϊkey�Ľ��
		if (key < p->data)
		{	// key��С,���������Ͻ��в���
			f = p;
			s.Push(p);
			p = p->leftChild;
		}
		else
		{	// key����,���������Ͻ��в���
			f = p;
			s.Push(p);
			p = p->rightChild;
		}
	}
	return p;
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::LeftRotate(BinAVLTreeNode<ElemType> *&subRoot)
// �������: ����subRootΪ���Ķ���������������,����֮��subRootָ���µ��������,
//	Ҳ������ת����ǰ���������ĸ����
{
	BinAVLTreeNode<ElemType> *ptrRChild;
	ptrRChild = subRoot->rightChild;			// ptrRChildָ��subRoot�Һ���
	subRoot->rightChild = ptrRChild->leftChild;	// ptrRChild������������ΪsubRoot��������
	ptrRChild->leftChild = subRoot;				// subRoot����ΪptrRChild������
	subRoot = ptrRChild;						// subRootָ���µĸ����
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::RightRotate(BinAVLTreeNode<ElemType> *&subRoot)
// �������: ����subRootΪ���Ķ���������������,����֮��subRootָ���µ��������,
//	Ҳ������ת����ǰ���������ĸ����
{
	BinAVLTreeNode<ElemType> *pLChild;
	pLChild = subRoot->leftChild;				// pLChildָ��subRoot����
	subRoot->leftChild = pLChild->rightChild;	// pLChild������������ΪsubRoot��������
	pLChild->rightChild = subRoot;				// subRoot����ΪpLChild���Һ���
	subRoot = pLChild;							// subRootָ���µĸ����
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InsertLeftBalance(BinAVLTreeNode<ElemType> *&subRoot)
// �������: ����subRootΪ���Ķ���������ʱ����ƽ�⴦��,��������subRoot��������,�����
//	subRootָ���µ��������
{
	BinAVLTreeNode<ElemType> *ptrLChild, *ptrLRChild;	
	ptrLChild  = subRoot->leftChild;	// ptrLChildָ��subRoot����
	switch (ptrLChild->bf)
	{	// ����subRoot����������ƽ����������Ӧ��ƽ�⴦��
	case LH:							// ��������subRoot�����ӵ���������,������������
		subRoot->bf = ptrLChild->bf = EH;// ƽ�����Ӷ�Ϊ0
		RightRotate(subRoot);			// ����
		break;
	case RH:							// ��������subRoot�����ӵ���������,������������������
		ptrLRChild = ptrLChild->rightChild;// ptrLRChildָ��subRoot�����ӵ��������ĸ�
		switch (ptrLRChild->bf)
		{	// �޸�subRoot�����ӵ�ƽ������
		case LH:						// ��������ptrLRChild����������
			subRoot->bf = RH;
			ptrLChild->bf = EH;
			break;
		case EH:						// ����ǰptrLRChildΪ��,ptrLRChildָ�������
			subRoot->bf = ptrLChild->bf = EH;
			break;
		case RH:						// ��������ptrLRChild����������
			subRoot->bf = EH;
			ptrLChild->bf = LH;
			break;
		}
		ptrLRChild->bf = 0;
		LeftRotate(subRoot->leftChild);	// ��subRoot����������������
		RightRotate(subRoot);			// ��subRoot����������
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InsertRightBalance(BinAVLTreeNode<ElemType> *&subRoot)
// �������: ����subRootΪ���Ķ���������ʱ����ƽ�⴦��,��������subRoot��������,�����
//	subRootָ���µ��������
{
	BinAVLTreeNode<ElemType> *ptrRChild, *ptrRLChild;	
	ptrRChild  = subRoot->rightChild;	// ptrRChildָ��subRoot�Һ���
	switch (ptrRChild->bf)
	{	// ����subRoot����������ƽ����������Ӧ��ƽ�⴦��
	case RH:							// ��������subRoot���Һ��ӵ���������,������������
		subRoot->bf = ptrRChild->bf = EH;// ƽ�����Ӷ�Ϊ0
		LeftRotate(subRoot);			// ����
		break;
	case LH:							// ��������subRoot���Һ��ӵ���������,������������������
		ptrRLChild = ptrRChild->leftChild;// ptrRLChildָ��subRoot���Һ��ӵ��������ĸ�
		switch (ptrRLChild->bf)
		{	// �޸�subRoot���Һ��ӵ�ƽ������
		case RH:						// ��������ptrRLChild����������
			subRoot->bf = LH;
			ptrRChild->bf = EH;
			break;
		case EH:						// ����ǰptrRLChildΪ��,ptrRLChildָ�������
			subRoot->bf = ptrRChild->bf = EH;
			break;
		case LH:						// ��������ptrRLChild����������
			subRoot->bf = EH;
			ptrRChild->bf = RH;
			break;
		}
		ptrRLChild->bf = 0;
		RightRotate(subRoot->rightChild);// ��subRoot����������������
		LeftRotate(subRoot);			// ��subRoot����������
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::InsertBalance(const ElemType &e,
	LinkStack<BinAVLTreeNode<ElemType> *> &s)
// �������: �Ӳ���Ԫ��e���ݲ���·�����л���,����ƽ�⴦��
{
	bool isTaller = true;
	while (!s.Empty() && isTaller)
	{
		BinAVLTreeNode<ElemType> *ptrCurNode, *ptrParent;
		s.Pop(ptrCurNode);			// ȡ����ƽ��Ľ��
		if (s.Empty())
		{	// ptrCurNode��Ϊ�����,ptrParentΪ��
			ptrParent = NULL;
		}
		else
		{	// ptrCurNode��Ϊ�����,ȡ��˫��ptrParent
			s.Top(ptrParent);
		}

		if (e < ptrCurNode->data)
		{	// e������ptrCurNode����������
			switch (ptrCurNode->bf)
			{	// ���ptrCurNode��ƽ���
			case LH:						// �����ptrCurNode->bf=2, ����ƽ�⴦��
				if (ptrParent == NULL)
				{	// �ѻ��ݵ������
					InsertLeftBalance(ptrCurNode);	
					root = ptrCurNode;		// ת����ptrCurNodeΪ�¸�
				}
				else if (ptrParent->leftChild == ptrCurNode)
				{	// ptrParent��������ƽ�⴦��
					InsertLeftBalance(ptrParent->leftChild);
				}
				else
				{	// ptrParent��������ƽ�⴦��
					InsertLeftBalance(ptrParent->rightChild);
				}
				isTaller = false;
				break;
			case EH:					// �����ptrCurNode->bf=LH
				ptrCurNode->bf = LH;
				break;	
			case RH:					// �����ptrCurNode->bf=EH
				ptrCurNode->bf = EH;
				isTaller = false;
				break;
			}
		}
		else
		{	// e������ptrCurNode����������
			switch (ptrCurNode->bf)
			{	// ���ptrCurNode��ƽ���
			case RH:						// �����ptrCurNode->bf=-2, ����ƽ�⴦��
				if (ptrParent == NULL)
				{	// �ѻ��ݵ������
					InsertRightBalance(ptrCurNode);
					root = ptrCurNode;		// ת����ptrCurNodeΪ�¸�
				}
				else if (ptrParent->leftChild == ptrCurNode)
				{	// ptrParent��������ƽ�⴦��
					InsertRightBalance(ptrParent->leftChild);
				}
				else
				{	// ptrParent��������ƽ�⴦��
					InsertRightBalance(ptrParent->rightChild);
				}
				isTaller = false;
				break;
			case EH:						// �����ptrCurNode->bf=RH
				ptrCurNode->bf = RH;
				break;
			case LH:						// �����ptrCurNode->bf=EH
				ptrCurNode->bf = EH;
				isTaller = false;
				break;
			}
		}
	}
}

template <class ElemType, class KeyType>
bool BinaryAVLTree<ElemType, KeyType>::Insert(const ElemType &e)
// �������: ��������Ԫ��e
{
	BinAVLTreeNode<ElemType> *f;
	LinkStack< BinAVLTreeNode<ElemType> *> s;
	if (SearchHelp(e, f, s) == NULL)
	{	// ����ʧ��, ����ɹ�
		BinAVLTreeNode<ElemType> *p;		// ������½��
		p = new BinAVLTreeNode<ElemType>(e);// ���ɲ�����
		p->bf = 0;
		if (Empty())
		{	// �ն�����,�½��Ϊ�����
			root = p;
		}
		else if (e < f->data)
		{	// e��С,������Ϊf������
			f->leftChild = p;
		}
		else
		{	// e����,������Ϊf���Һ���
			f->rightChild = p;
		}

		InsertBalance(e, s);// ���������ƽ�⴦��
		return true;		
	}
	else
	{	// ���ҳɹ�, ����ʧ��
		return false;
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DeleteLeftBalance(BinAVLTreeNode<ElemType> *&
subRoot, bool &isShorter)
// �������: ����subRootΪ���Ķ�����ɾ��ʱ����ƽ�⴦��, ɾ��subRoot���������ϵĽ�㣬��
//	���subRootָ���µ��������
{
	BinAVLTreeNode<ElemType> *ptrRChild, *ptrRLChild;	
	ptrRChild  = subRoot->rightChild;		// ptrRChildָ��subRoot�Һ���
	switch (ptrRChild->bf)
	{	// ����subRoot����������ƽ����������Ӧ��ƽ�⴦��
	case RH:								// �Ҹߣ���������ת
		subRoot->bf = ptrRChild->bf = EH;	// ƽ�����Ӷ�Ϊ0
		LeftRotate(subRoot);				// ����
		isShorter = true;
		break;
	case EH:								// �ȸߣ���������ת
		subRoot->bf = RH;
		ptrRChild->bf = LH;		
		LeftRotate(subRoot);				// ����
		isShorter = false;
		break;
	case LH:								// ���,������������
		ptrRLChild = ptrRChild->leftChild;	// ptrRLChildָ��subRoot���Һ��ӵ��������ĸ�
		switch (ptrRLChild->bf)
		{	// �޸�subRoot���Һ��ӵ�ƽ������
		case LH:
			subRoot->bf = EH;
			ptrRChild->bf = RH;
			isShorter = true;
			break;
		case EH:
			subRoot->bf = ptrRChild->bf = EH;
			isShorter = false;
			break;
		case RH:
			subRoot->bf = LH;
			ptrRChild->bf = EH;
			isShorter = true;
			break;
		}
		ptrRLChild->bf = 0;
		RightRotate(subRoot->rightChild);	// ��subRoot����������������
		LeftRotate(subRoot);				// ��subRoot����������
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DeleteRightBalance(BinAVLTreeNode<ElemType> *
&subRoot, bool &isShorter)
// �������: ����subRootΪ���Ķ�����ɾ��ʱ����ƽ�⴦��, ɾ��subRoot���������ϵĽ�㣬��
//	���subRootָ���µ��������
{
	BinAVLTreeNode<ElemType> *ptrLChild, *ptrLRChild;	
	ptrLChild  = subRoot->leftChild;	// ptrLChildָ��subRoot����
	switch (ptrLChild->bf)
	{	// ����subRoot����������ƽ����������Ӧ��ƽ�⴦��
	case LH:						// �Ҹߣ���������ת
		subRoot->bf = ptrLChild->bf = EH;// ƽ�����Ӷ�Ϊ0
		RightRotate(subRoot);			// ����
		isShorter = true;
		break;
	case EH:						// �ȸߣ���������ת
		subRoot->bf = LH;
		ptrLChild->bf = RH;			// ƽ�����Ӷ�Ϊ0
		RightRotate(subRoot);			// ����
		isShorter = false;
		break;
	case RH:						// ���,������������
		ptrLRChild = ptrLChild->rightChild;// ptrLRChildָ��subRoot�����ӵ��������ĸ�
		switch (ptrLRChild->bf)
		{	// �޸�subRoot�����ӵ�ƽ������
		case LH:
			subRoot->bf = RH;
			ptrLChild->bf = EH;
			isShorter = true;
			break;
		case EH:
			subRoot->bf = ptrLChild->bf = EH;
			isShorter = false;
			break;
		case RH:
			subRoot->bf = EH;
			ptrLChild->bf = LH;
			isShorter = true;
			break;
		}
		ptrLRChild->bf = 0;
		LeftRotate(subRoot->leftChild);	// ��subRoot����������������
		RightRotate(subRoot);			// ��subRoot����������
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DeleteBalance(const KeyType &key, 
LinkStack<BinAVLTreeNode<ElemType> *> &s)
// �������: ��ɾ�������ݲ���·�����л���,����ƽ�⴦��
{
	bool isShorter = true;
	while (!s.Empty() && isShorter)
	{
		BinAVLTreeNode<ElemType> *ptrCurNode, *ptrParent;
		s.Pop(ptrCurNode);					// ȡ����ƽ��Ľ��
		if (s.Empty())
		{	// ptrCurNode��Ϊ�����,ptrParentΪ��
			ptrParent = NULL;
		}
		else
		{	// ptrCurNode��Ϊ�����,ȡ��˫��ptrParent
			s.Top(ptrParent);
		}

		if (key < ptrCurNode->data)
		{	// ɾ��ptrCurNode���������ϵĽ��
			switch (ptrCurNode->bf)
			{	// ���ptrCurNode��ƽ���
			case LH:						// ���
				ptrCurNode->bf = EH;
				break;
			case EH:						// �ȸ�
				ptrCurNode->bf = RH;
				isShorter = false;
				break;
			case RH:						// �Ҹ�
				if (ptrParent == NULL)
				{	// �ѻ��ݵ������
					DeleteLeftBalance(ptrCurNode, isShorter);
					root = ptrCurNode;		// ת����ptrCurNodeΪ�¸�
				}
				else if (ptrParent->leftChild == ptrCurNode)
				{	// ptrParent��������ƽ�⴦��
					DeleteLeftBalance(ptrParent->leftChild, isShorter);
				}
				else
				{	// ptrParent��������ƽ�⴦��
					DeleteLeftBalance(ptrParent->rightChild, isShorter);
				}
				break;
			}
		}
		else
		{	// ɾ��ptrCurNode���������ϵĽ��
			switch (ptrCurNode->bf)
			{	// ���ptrCurNode��ƽ���
			case RH: 						// �Ҹ�
				ptrCurNode->bf = EH;
				break;
			case EH: 						// �ȸ�
				ptrCurNode->bf = LH;
				isShorter = false;
				break;
			case LH: 						// ���
				if (ptrParent == NULL)
				{	// �ѻ��ݵ������
					DeleteLeftBalance(ptrCurNode, isShorter);
					root = ptrCurNode;		// ת����ptrCurNodeΪ�¸�
				}
				else if (ptrParent->leftChild == ptrCurNode)
				{	// ptrParent��������ƽ�⴦��
					DeleteLeftBalance(ptrParent->leftChild, isShorter);
				}
				else
				{	// ptrParent��������ƽ�⴦��
					DeleteLeftBalance(ptrParent->rightChild, isShorter);
				}
				break;
			}
		}
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DeleteHelp(const KeyType &key, 
BinAVLTreeNode<ElemType> *&p, LinkStack< BinAVLTreeNode<ElemType> *> &s)
// �������: ɾ��pָ��Ľ��
{
	BinAVLTreeNode<ElemType> *tmpPtr, *tmpF;  
	if (p->leftChild == NULL && p->rightChild == NULL)
	{	// pΪҶ���
		delete p;
		p = NULL;
		DeleteBalance(key, s);
	}
	else if (p->leftChild == NULL)
	{	// pֻ��������Ϊ��
		tmpPtr = p;
		p = p->rightChild;
		delete tmpPtr;
		DeleteBalance(key, s);
	}
	else if (p->rightChild == NULL)
	{	// pֻ���������ǿ�
		tmpPtr = p;
		p = p->leftChild;
		delete tmpPtr;
		DeleteBalance(key, s);
	}
	else
	{	// p�����ӷǿ�
		tmpF = p;
		s.Push(tmpF);
		tmpPtr = p->leftChild;
		while (tmpPtr->rightChild != NULL)
		{	// ����p������������ֱ��ǰ��tmpPtr����˫��tmpF,tmpPtr��������Ϊ��
			tmpF = tmpPtr;
			s.Push(tmpF);
			tmpPtr = tmpPtr->rightChild;
		}
		p->data = tmpPtr->data;// ��tmpPtrָ�����Ԫ��ֵ��ֵ��tmpFָ�����Ԫ��ֵ

		// ɾ��tmpPtrָ��Ľ��
		if (tmpF->rightChild == tmpPtr)
		{	// ɾ��tmpF���Һ���
			DeleteHelp(key, tmpF->rightChild, s);
		}
		else
		{	// ɾ��tmpF������
			DeleteHelp(key, tmpF->leftChild, s);
		}
	}
}

template <class ElemType, class KeyType>
bool BinaryAVLTree<ElemType, KeyType>::Delete(const KeyType &key)
// �������: ɾ���ؼ���Ϊkey�Ľ��
{
	BinAVLTreeNode<ElemType> *p, *f;
	LinkStack< BinAVLTreeNode<ElemType> *> s;
	p = SearchHelp(key, f, s);
	if ( p == NULL)
	{	// ����ʧ��, ɾ��ʧ��
		return false;
	}
	else
	{	// ���ҳɹ�, ����ʧ��
		if (f == NULL)
		{	// ��ɾ�����Ϊ�����
			DeleteHelp(key, root, s);
		}
		else if (key < f->data)
		{	// key��С,ɾ��f������
			DeleteHelp(key, f->leftChild, s);
		}
		else
		{	// key����,����f���Һ���
			DeleteHelp(key, f->rightChild, s);
		}
		return true;		
	}
}

template <class ElemType, class KeyType>
void BinaryAVLTree<ElemType, KeyType>::DestroyHelp(BinAVLTreeNode<ElemType> *&r)
// ���������������r�Ķ���ƽ����
{
	if(r != NULL)
	{	// r�ǿ�,ʵʩ����
		DestroyHelp(r->leftChild);		// ����������
		DestroyHelp(r->rightChild);		// ����������
		delete r;						// ���ٸ����
		r = NULL;
	}
}

template <class ElemType, class KeyType>
BinAVLTreeNode<ElemType> *BinaryAVLTree<ElemType, KeyType>::CopyTreeHelp(BinAVLTreeNode<ElemType> *copy)
// �������������copyΪ���Ķ���ƽ�������Ƴ��µĶ���ƽ����,�����¶���ƽ�����ĸ�
{
	if (copy == NULL)
	{	// ���ƿն���ƽ����
		return NULL;					// �ն���ƽ������Ϊ��	
	}
	else
	{	// ���Ʒǿն���ƽ����
		BinAVLTreeNode<ElemType> *lChild = CopyTreeHelp(copy->leftChild);	// ����������
		BinAVLTreeNode<ElemType> *rChild = CopyTreeHelp(copy->rightChild);	// ����������
		BinAVLTreeNode<ElemType> *r = new BinAVLTreeNode<ElemType>(copy->data, copy->bf, lChild, rChild);
			// ���Ƹ����
		return r;
	}
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::BinaryAVLTree(const BinaryAVLTree<ElemType, KeyType> &copy)
// �������������֪����ƽ���������¶���ƽ�����������ƹ��캯��
{
	root = CopyTreeHelp(copy.root);	// ���ƶ���ƽ����
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType>::BinaryAVLTree(BinAVLTreeNode<ElemType> *r)
// ���������������rΪ���Ķ���ƽ����
{	
	root = r;	// ���ƶ���ƽ����
}

template <class ElemType, class KeyType>
BinaryAVLTree<ElemType, KeyType> &BinaryAVLTree<ElemType, KeyType>::operator=(const BinaryAVLTree<ElemType, KeyType> &copy)
// �������������֪����ƽ����copy���Ƶ���ǰ����ƽ����--��ֵ�������
{
	if (&copy != this)
	{
		DestroyHelp(root);				// �ͷ�ԭ����ƽ������ռ�ÿռ�
		root = CopyTreeHelp(copy.root);	// ���ƶ���ƽ����
	}
	return *this;
}

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinAVLTreeNode<ElemType> *r, int level)
//	�������������״��ʽ��ʾ��rΪ���Ķ���ƽ������levelΪ���������������Ĳ����Ϊ1
{
	if(r != NULL)
	{	//��������ʽ��ֻ��ʽ�ǿ���
		DisplayBTWithTreeShapeHelp<ElemType, KeyType>(r->rightChild, level + 1);//��ʾ������
		cout << endl;					//��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout << " ";				//ȷ���ڵ�level����ʾ���
		cout << r->data;				//��ʾ���
		DisplayBTWithTreeShapeHelp<ElemType, KeyType>(r->leftChild, level + 1);//��ʾ������
	}
}

template <class ElemType, class KeyType>
void DisplayBTWithTreeShape(const BinaryAVLTree<ElemType, KeyType> &bt)
//	�����������״��ʽ��ʾ����ƽ���� 
{
	DisplayBTWithTreeShapeHelp<ElemType, KeyType>(bt.GetRoot(), 1);	
		// ��״��ʾ��bt.GetRoot()Ϊ���Ķ���ƽ����
	cout << endl;
}

#endif
