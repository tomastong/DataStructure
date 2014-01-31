#ifndef __BINNARY_TREE_H__
#define __BINNARY_TREE_H__

#include "lk_queue.h"				// ������
#include "bin_tree_node.h"			// �����������

// ������������
template <class ElemType, class KeyType>
class BinarySortTree
{
protected:
//  ���������������ݳ�Ա:
	BinTreeNode<ElemType> *root;

//	��������:
	BinTreeNode<ElemType> *CopyTreeHelp(BinTreeNode<ElemType> *copy);	// ���ƶ���������
	void DestroyHelp(BinTreeNode<ElemType> * &r);						// ������rΪ������������
	void PreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// �������
	void InOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	// �������
	void PostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;// �������
    int HeightHelp(const BinTreeNode<ElemType> *r) const;	// ���ض����������ĸ�
	int NodeCountHelp(const BinTreeNode<ElemType> *r) const;// ���ض����������Ľ�����
	BinTreeNode<ElemType> *ParentHelp(BinTreeNode<ElemType> *r, 
		const BinTreeNode<ElemType> *cur) const;			// ����cur��˫��
	BinTreeNode<ElemType> *SearchHelp(const KeyType &key, BinTreeNode<ElemType> *&f) const;	
		// ���ҹؼ���Ϊkey������Ԫ��
	void DeleteHelp(BinTreeNode<ElemType> *&p);				// ɾ��pָ��Ľ��

public:
//  �����������������������ر���ϵͳĬ�Ϸ�������:
	BinarySortTree();										// �޲����Ĺ��캯��
	virtual ~BinarySortTree();								// ��������
	BinTreeNode<ElemType> *GetRoot() const;					// ���ض����������ĸ�
	bool Empty() const;										// �ж϶����������Ƿ�Ϊ��
	StatusCode GetElem(BinTreeNode<ElemType> *cur, ElemType &e) const;
		// ��e���ؽ������Ԫ��ֵ
	StatusCode SetElem(BinTreeNode<ElemType> *cur, const ElemType &e);
		// ����cur��ֵ��Ϊe
	void InOrder(void (*Visit)(const ElemType &)) const;	// �������������������	
	void PreOrder(void (*Visit)(const ElemType &)) const;	// �������������������
	void PostOrder(void (*Visit)(const ElemType &)) const;	// �����������ĺ������
	void LevelOrder(void (*Visit)(const ElemType &)) const;	// �����������Ĳ�α���
	int NodeCount() const;									// ������������Ľ�����
	BinTreeNode<ElemType> *Search(const KeyType &key) const;// ���ҹؼ���Ϊkey������Ԫ��
	bool Insert(const ElemType &e);							// ��������Ԫ��e
	bool Delete(const KeyType &key);						// ɾ���ؼ���Ϊkey������Ԫ��
	BinTreeNode<ElemType> *LeftChild(const BinTreeNode<ElemType> *cur) const;
		// ���ض������������cur������
	BinTreeNode<ElemType> *RightChild(const BinTreeNode<ElemType> *cur) const;
		// ���ض������������cur���Һ���
	BinTreeNode<ElemType> *Parent(const BinTreeNode<ElemType> *cur) const;
		// ���ض������������cur��˫��
	int	Height() const;										// ������������ĸ�
	BinarySortTree(const ElemType &e);						// ������eΪ���Ķ���������
	BinarySortTree(const BinarySortTree<ElemType, KeyType> &copy);	// ���ƹ��캯��
	BinarySortTree(BinTreeNode<ElemType> *r);				// ������rΪ���Ķ���������
	BinarySortTree<ElemType, KeyType> &operator=
		(const BinarySortTree<ElemType, KeyType>& copy);	// ��ֵ�������
};

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level);
	//	����״��ʽ��ʾ��rΪ���Ķ�����������levelΪ���������������Ĳ����Ϊ1
template <class ElemType, class KeyType>
void DisplayBTWithTreeShape(const BinarySortTree<ElemType, KeyType> &bt);
	//	��״��ʽ��ʾ���������� 

// �������������ʵ�ֲ���
template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree()
// �������������һ���ն���������
{
	root = NULL;
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::~BinarySortTree()
// ������������ٶ���������--���캯��
{
	DestroyHelp(root);
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::GetRoot() const
// ������������ض����������ĸ�
{
	return root;
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::Empty() const
// ����������ж϶����������Ƿ�Ϊ��
{
	return root == NULL;
}

template <class ElemType, class KeyType>
StatusCode BinarySortTree<ElemType, KeyType>::GetElem(BinTreeNode<ElemType> *cur, ElemType &e) const
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
StatusCode BinarySortTree<ElemType, KeyType>::SetElem(BinTreeNode<ElemType> *cur, const ElemType &e)
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
void BinarySortTree<ElemType, KeyType>::PreOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ���������
{
	if (r != NULL) 
	{
		(*Visit)(r->data);					// ���ʸ����
		PreOrderHelp(r->leftChild, Visit);	// ����������
		PreOrderHelp(r->rightChild, Visit);	// ����������
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PreOrder(void (*Visit)(const ElemType &)) const
// ��������������������������
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::InOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ���������
{
	if (r != NULL) 
	{
		InOrderHelp(r->leftChild, Visit);	// ����������
		(*Visit)(r->data);					// ���ʸ����
		InOrderHelp(r->rightChild, Visit);	// ����������
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::InOrder(void (*Visit)(const ElemType &)) const
// ��������������������������
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PostOrderHelp(BinTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ���������
{
	if (r != NULL) 
	{
		PostOrderHelp(r->leftChild, Visit);	// ����������
		PostOrderHelp(r->rightChild, Visit);// ����������
		(*Visit)(r->data);					// ���ʸ����
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::PostOrder(void (*Visit)(const ElemType &)) const
// ��������������������������
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::LevelOrder(void (*Visit)(const ElemType &)) const
// �����������α�������������
{
	LinkQueue<BinTreeNode<ElemType> *> q;	// ����
	BinTreeNode<ElemType> *t = root;		// �Ӹ���㿪ʼ���в�α���
	
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
int BinarySortTree<ElemType, KeyType>::HeightHelp(const BinTreeNode<ElemType> *r) const
// ���������������rΪ���Ķ����������ĸ�
{
	if(r == NULL)
	{	// �ն�����������Ϊ0
		return 0;
	}
	else
	{	// �ǿն�����������Ϊ���������ĸߵ����ֵ�ټ�1
		int lHeight, rHeight;
		lHeight = HeightHelp(r->leftChild);		// �������ĸ�
		rHeight = HeightHelp(r->rightChild);	// �������ĸ�
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// �ǿն�����������Ϊ���������ĸߵ����ֵ�ټ�1
	}
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::Height() const
// ������������ض����������ĸ�
{
	return HeightHelp(root);
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree(const ElemType &e)
// ���������������eΪ���Ķ���������
{
	root = new BinTreeNode<ElemType>(e);
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::NodeCountHelp(const BinTreeNode<ElemType> *r) const
// ���������������rΪ���Ķ����������Ľ�����
{
	if (r ==NULL) return 0;			// �ն���������������Ϊ0
	else return 1 + NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild);
		// �ǿն�������������Ϊ���������Ľ�����֮���ټ�1
}

template <class ElemType, class KeyType>
int BinarySortTree<ElemType, KeyType>::NodeCount() const
// ������������ض����������Ľ�����
{
	return NodeCountHelp(root);
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::LeftChild(const BinTreeNode<ElemType> *cur) const
// ������������ض������������cur������
{
	return cur->leftChild;
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::RightChild(const BinTreeNode<ElemType> *cur) const
// ������������ض������������cur���Һ���
{
	return cur->rightChild;
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> * BinarySortTree<ElemType, KeyType>::ParentHelp(BinTreeNode<ElemType> *r, const BinTreeNode<ElemType> *cur) const
// ���������������rΪ���Ķ���������, ���cur��˫��
{
	if (r == NULL) return NULL;		// �ն���������
	else if (r->leftChild == cur || r->rightChild == cur) return r; // rΪcur��˫��
	else
	{	// ����������˫��
		BinTreeNode<ElemType> *tmp;
		
		tmp = ParentHelp(r->leftChild, cur);	// ������������cur��˫��	
		if (tmp != NULL) return tmp;			// ˫������������

		tmp = ParentHelp(r->rightChild, cur);	// ������������cur��˫��	
		if (tmp != NULL) return tmp;			// ˫������������
		else return NULL;						// ��ʾcur��˫��
	}
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::Parent(const BinTreeNode<ElemType> *cur) const
// ������������ض������������cur��˫��
{
	return ParentHelp(root, cur);
}

template <class ElemType, class KeyType>
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::SearchHelp(const KeyType &key, 
	BinTreeNode<ElemType> *&f) const
// �������: ����ָ��ؼ���Ϊkey������Ԫ�ص�ָ��,��f������˫��
{
	BinTreeNode< ElemType> *p = GetRoot();	// ָ��ǰ���
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
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::Search(const KeyType &key)	const 
// �������: ����ָ��ؼ���Ϊkey������Ԫ�ص�ָ��
{
	BinTreeNode<ElemType> *f;			// ָ�򱻲��ҽ���˫��
	return SearchHelp(key, f);
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::Insert(const ElemType &e)
// �������: ��������Ԫ��e
{
	BinTreeNode<ElemType> *f;			// ָ�򱻲��ҽ���˫��

	if (SearchHelp(e, f) == NULL)
	{	// ����ʧ��, ����ɹ�
		BinTreeNode<ElemType> *p;		// ������½��
		p = new BinTreeNode<ElemType>(e);
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

		return true;		
	}
	else
	{	// ���ҳɹ�, ����ʧ��
		return false;
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::DeleteHelp(BinTreeNode<ElemType> *&p)
// �������: ɾ��pָ��Ľ��
{
	BinTreeNode<ElemType> *tmpPtr, *tmpF;  
	if (p->leftChild == NULL && p->rightChild == NULL)
	{	// pΪҶ���
		delete p;
		p = NULL;
	}
	else if (p->leftChild == NULL)
	{	// pֻ��������Ϊ��
		tmpPtr = p;
		p = p->rightChild;
		delete tmpPtr;
	}
	else if (p->rightChild == NULL)
	{	// pֻ���������ǿ�
		tmpPtr = p;
		p = p->leftChild;
		delete tmpPtr;
	}
	else
	{	// p�����ӷǿ�
		tmpF = p;
		tmpPtr = p->leftChild;
		while (tmpPtr->rightChild != NULL)
		{	// ����p������������ֱ��ǰ��tmpPtr����˫��tmpF,ֱ��tmpPtr������Ϊ��
			tmpF = tmpPtr;
			tmpPtr = tmpPtr->rightChild;
		}
		p->data = tmpPtr->data;
			// ��tmpPtrָ���������Ԫ��ֵ��ֵ��tmpFָ���������Ԫ��ֵ

		// ɾ��tmpPtrָ��Ľ��
		if (tmpF->rightChild == tmpPtr)
		{	// ɾ��tmpF���Һ���
			DeleteHelp(tmpF->rightChild);
		}
		else
		{	// ɾ��tmpF������
			DeleteHelp(tmpF->leftChild);
		}
	}
}

template <class ElemType, class KeyType>
bool BinarySortTree<ElemType, KeyType>::Delete(const KeyType &key)
// �������: ɾ���ؼ���Ϊkey������Ԫ��
{
	BinTreeNode<ElemType> *p, *f;
	p = SearchHelp(key, f);
	if ( p == NULL)
	{	// ����ʧ��, ɾ��ʧ��
		return false;
	}
	else
	{	// ���ҳɹ�, ����ʧ��
		if (f == NULL)
		{	// ��ɾ�����Ϊ�����
			DeleteHelp(root);
		}
		else if (key < f->data)
		{	// elem.key��С,ɾ��f������
			DeleteHelp(f->leftChild);
		}
		else
		{	// elem.key����, ɾ��f���Һ���
			DeleteHelp(f->rightChild);
		}
		return true;		
	}
}

template <class ElemType, class KeyType>
void BinarySortTree<ElemType, KeyType>::DestroyHelp(BinTreeNode<ElemType> *&r)
// ���������������r�Ķ���������
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
BinTreeNode<ElemType> *BinarySortTree<ElemType, KeyType>::CopyTreeHelp(BinTreeNode<ElemType> *copy)
// �������������copyΪ���Ķ������������Ƴ��µĶ���������,�����¶����������ĸ�
{
	if (copy == NULL)
	{	// ���ƿն���������
		return NULL;					// �ն�����������Ϊ��	
	}
	else
	{	// ���Ʒǿն���������
		BinTreeNode<ElemType> *lChild = CopyTreeHelp(copy->leftChild);	// ����������
		BinTreeNode<ElemType> *rChild = CopyTreeHelp(copy->rightChild);	// ����������
		BinTreeNode<ElemType> *r = new BinTreeNode<ElemType>(copy->data, lChild, rChild);
			// ���Ƹ����
		return r;
	}
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree(const BinarySortTree<ElemType, KeyType> &copy)
// �������������֪���������������¶����������������ƹ��캯��
{
	root = CopyTreeHelp(copy.root);	// ���ƶ���������
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType>::BinarySortTree(BinTreeNode<ElemType> *r)
// ���������������rΪ���Ķ���������
{	
	root = r;	// ���ƶ���������
}

template <class ElemType, class KeyType>
BinarySortTree<ElemType, KeyType> &BinarySortTree<ElemType, KeyType>::operator=(const BinarySortTree<ElemType, KeyType> &copy)
// �������������֪����������copy���Ƶ���ǰ����������--��ֵ�������
{
	if (&copy != this)
	{
		DestroyHelp(root);				// �ͷ�ԭ������������ռ�ÿռ�
		root = CopyTreeHelp(copy.root);	// ���ƶ���������
	}
	return *this;
}

template <class ElemType, class KeyType>
void DisplayBTWithTreeShapeHelp(const BinTreeNode<ElemType> *r, int level)
//	�������������״��ʽ��ʾ��rΪ���Ķ�����������levelΪ���������������Ĳ����Ϊ1
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
void DisplayBTWithTreeShape(const BinarySortTree<ElemType, KeyType> &bt)
//	�����������״��ʽ��ʾ���������� 
{
	DisplayBTWithTreeShapeHelp<ElemType, KeyType>(bt.GetRoot(), 1);	
		// ��״��ʾ��bt.GetRoot()Ϊ���Ķ���������
	cout << endl;
}

#endif
