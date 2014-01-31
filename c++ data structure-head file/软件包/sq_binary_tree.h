#ifndef __SQ_BINNARY_TREE_H__
#define __SQ_BINNARY_TREE_H__

#include "lk_queue.h"										// ������
#include "sq_bin_tree_node.h"								// ˳��洢�����������

// ˳��洢��������
template <class ElemType>
class SqBinaryTree
{
protected:
//  �����������ݳ�Ա:
	int maxSize;											// ����������������
	SqBinTreeNode<ElemType> *elems;							// ���洢�ռ�
	int root;												// �������ĸ�

//	��������:
	int NodeCountHelp(int r) const;							// ���ض������Ľ�����
	void SetNodeEmpty(int cur);								// �����cur�ÿ�
	void DestroyHelp(int r);								// ������rΪ��������
	void PreOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// �������
	void InOrderHelp(int r, void (*Visit)(const ElemType &)) const;		// �������
	void PostOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// �������
    int HeightHelp(int r) const;							// ���ض������ĸ�

public:
//  �������������������ر���ϵͳĬ�Ϸ�������:
	SqBinaryTree();											// �޲����Ĺ��캯��
	virtual ~SqBinaryTree();								// ��������
	int GetRoot() const;									// ���ض������ĸ�
	bool NodeEmpty(int cur) const;							// �жϽ��cur�Ƿ�Ϊ��
	StatusCode GetItem(int cur, ElemType &e);				// ���ؽ��cur��Ԫ��ֵ
	StatusCode SetElem(int cur, const ElemType &e);			// �����cur��ֵ��Ϊe
	bool Empty() const;										// �ж϶������Ƿ�Ϊ��
	void InOrder(void (*Visit)(const ElemType &)) const;	// ���������������	
	void PreOrder(void (*Visit)(const ElemType &)) const;	// ���������������
	void PostOrder(void (*Visit)(const ElemType &)) const;	// �������ĺ������
	void LevelOrder(void (*Visit)(const ElemType &)) const;	// �������Ĳ�α���
	int NodeCount() const;									// ��������Ľ�����
	int LeftChild(const int cur) const;						// ���ض��������cur������
	int RightChild(const int cur) const;					// ���ض��������cur���Һ���
	int Parent(const int cur) const;						// ���ض��������cur��˫��
	void InsertLeftChild(int cur, const ElemType &e);		// ��������
	void InsertRightChild(int cur, const ElemType &e);		// �����Һ���
	void DeleteLeftChild(int cur);							// ɾ��������
	void DeleteRightChild(int cur);							// ɾ�����Ӵ�
	int	Height() const;										// ��������ĸ�
	SqBinaryTree(const ElemType &e, int size = DEFAULT_SIZE);	// ������eΪ���Ķ�����
	SqBinaryTree(const SqBinaryTree<ElemType> &copy);		// ���ƹ��캯��
	SqBinaryTree(SqBinTreeNode<ElemType> es[], int r, int size = DEFAULT_SIZE);	
		// ��es[]��r��size���������
	SqBinaryTree<ElemType> &operator=(const SqBinaryTree<ElemType>& copy);		
		// ��ֵ���������
};


template <class ElemType>
void DisplayBTWithTreeShapeHelp(int r, int level);
	//	����״��ʽ��ʾ��rΪ���Ķ�������levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayBTWithTreeShape(SqBinaryTree<ElemType> &bt);
	//	��״��ʽ��ʾ������ 
template <class ElemType>
void CreateBinaryTreeHelp(SqBinTreeNode<ElemType> es, int r, ElemType pre[], ElemType in[], 
	int preLeft, int preRight, int inLeft, int inRight);	
	// ��֪����������������pre[preLeft..preRight]����������in[inLeft..inRight]������rΪ���Ķ�����
template <class ElemType>
SqBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n);
	// ��֪������������й��������

// ���������ʵ�ֲ���
template <class ElemType>
bool SqBinaryTree<ElemType>::NodeEmpty(int cur) const
// ���������������curΪ��,�򷵻�true,���򷵻�false
{
	if(cur <1 || cur > maxSize || elems[cur].tag == EMPTY_NODE) return true;	// ��ʱ���Ϊ��
	else return false;
}

template <class ElemType>
StatusCode SqBinaryTree<ElemType>::GetItem(int cur, ElemType &e)
// �����������e���ؽ��cur��Ԫ��ֵ,������ɹ�,��������SUCCESS,���򷵻�FAIL
{
	if (NodeEmpty(cur)) return FAIL;		// ����ʧ��
	else
	{
		e = elems[cur].data;				// ��e���ؽ��cur��Ԫ��ֵ
		return SUCCESS;						// �����ɹ�
	}
}

template <class ElemType>
StatusCode SqBinaryTree<ElemType>::SetElem(int cur, const ElemType &e)
// �����������������ڽ��cur,�򷵻�FAIL,���򷵻�SUCCESS,�������cur��ֵ����Ϊe
{
	if (NodeEmpty(cur)) return FAIL;		// ����ʧ��
	else
	{	// ���ڽ��cur
		elems[cur].data = e;				// �����cur��ֵ����Ϊe
		return SUCCESS;						// ����SUCCESS
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::SetNodeEmpty(int cur)
// ��������������cur�ÿ�
{
	if (cur > 0 && cur <= maxSize) elems[cur].tag = EMPTY_NODE;	// ��cur�ÿ�
}

template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree()
// �������������һ�ÿն�����
{
	maxSize = DEFAULT_SIZE;			// ��������
	elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// ����洢�ռ�, δʹ��elems[0]
	for (int i = 1; i <=maxSize; i++)
	{	// �����н���ʶΪ��
		elems[i].tag = EMPTY_NODE;
	}
	root = 1;						// elems[1]�洢��
}

template <class ElemType>
SqBinaryTree<ElemType>::~SqBinaryTree()
// ������������ٶ�����
{
	delete []elems;					// �ͷŴ洢�ռ�
}

template <class ElemType>
int SqBinaryTree<ElemType>::GetRoot() const
// ������������ض������ĸ�
{
	return root;						// rootΪ��
}

template <class ElemType>
bool SqBinaryTree<ElemType>::Empty() const
// ����������ж϶������Ƿ�Ϊ��
{
	return NodeEmpty(root);
}

template <class ElemType>
void SqBinaryTree<ElemType>::PreOrderHelp(int r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ�����
{
	if (!NodeEmpty(r)) 
	{	// ���ǿ�
		(*Visit)(elems[r].data);			// ���ʸ����
		PreOrderHelp(LeftChild(r), Visit);			// ����������
		PreOrderHelp(RightChild(r), Visit);		// ����������
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// ����������������������
{
	PreOrderHelp(root, Visit);	
}	

template <class ElemType>
void SqBinaryTree<ElemType>::InOrderHelp(int r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ�����
{
	if (!NodeEmpty(r)) 
	{	// ���ǿ�
		InOrderHelp(LeftChild(r), Visit);			// ����������
		(*Visit)(elems[r].data);					// ���ʸ����
		InOrderHelp(RightChild(r), Visit);			// ����������
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// ����������������������
{
	InOrderHelp(root, Visit);	
}	

template <class ElemType>
void SqBinaryTree<ElemType>::PostOrderHelp(int r, void (*Visit)(const ElemType &)) const
// ������������������rΪ���Ķ�����
{
	if (!NodeEmpty(r)) 
	{	// ���ǿ�
		PostOrderHelp(LeftChild(r), Visit);		// ����������
		PostOrderHelp(RightChild(r), Visit);	// ����������
		(*Visit)(elems[r].data);					// ���ʸ����
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::PostOrder(void (*Visit)(const ElemType &)) const
// ����������������������
{
	PostOrderHelp(root, Visit);	
}	

template <class ElemType>
void SqBinaryTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// �����������α���������
{
	LinkQueue<int > q;						// ����
	int t = root;							// �Ӹ���㿪ʼ���в�α���
	
	if (!NodeEmpty(t)) q.InQueue(t);		// ������ǿ�,�����
	while (!q.Empty())
	{	// q�ǿ�,˵�����н��δ����
		q.OutQueue(t);     
		(*Visit)(elems[t].data);
		if (!NodeEmpty(LeftChild(t)))				// ���ӷǿ�
			q.InQueue(LeftChild(t));				// �������
		if (!NodeEmpty(RightChild(t)))			// �Һ��ӷǿ�
			q.InQueue(RightChild(t));			// �Һ������
	}
}

template <class ElemType>
int SqBinaryTree<ElemType>::HeightHelp(int r) const
// ���������������rΪ���Ķ������ĸ�
{
	if(NodeEmpty(r))
	{	// �ն�������Ϊ0
		return 0;
	}
	else
	{	// �ǿն�������Ϊ���������ĸߵ����ֵ�ټ�1
		int lHeight, rHeight;
		lHeight = HeightHelp(LeftChild(r));		// �������ĸ�
		rHeight = HeightHelp(RightChild(r));	// �������ĸ�
		return 1 + (lHeight > rHeight ? lHeight : rHeight);
			// �ǿն�������Ϊ���������ĸߵ����ֵ�ټ�1
	}
}

template <class ElemType>
int SqBinaryTree<ElemType>::Height() const
// ������������ض������ĸ�
{
	return HeightHelp(root);
}

template <class ElemType>
int SqBinaryTree<ElemType>::NodeCountHelp(int r) const
// ���������������rΪ���Ķ������Ľ�����
{
	if (NodeEmpty(r)) return 0;	// �ն�����������Ϊ0
	else return 1 + NodeCountHelp(LeftChild(r)) + NodeCountHelp(RightChild(r));
		// �ǿն���������Ϊ���������Ľ�����֮���ټ�1
}

template <class ElemType>
int SqBinaryTree<ElemType>::NodeCount() const
// ������������ض������Ľ�����
{
	return NodeCountHelp(root);
}

template <class ElemType>
int SqBinaryTree<ElemType>::LeftChild(const int cur) const
// ������������ض��������cur������
{
	return 2 * cur;				// 2 * curΪ���� 
}

template <class ElemType>
int SqBinaryTree<ElemType>::RightChild(const int cur) const
// ������������ض��������cur���Һ���
{
	return 2 * cur + 1;			// 2 * cur + 1Ϊ�Һ��� 
}

template <class ElemType>
int SqBinaryTree<ElemType>::Parent(const int cur) const
// ������������ض��������cur��˫��
{
	return cur / 2;				// cur / 2Ϊ˫��
}

template <class ElemType>
void SqBinaryTree<ElemType>::InsertLeftChild(int cur, const ElemType &e)
// ��ʼ������cur��cur���ӷǿ�
// �������������eΪcur�����ӣ����cur�����ӷǿգ�������ʧ��
{
	if (NodeEmpty(cur))
	{	// curΪ�գ�����
		return;
	}
	else 
	{	// ��������    
		if (NodeEmpty(LeftChild(cur)) && LeftChild(cur) <= maxSize && LeftChild(cur) > 0)
		{	// cur����Ϊ��,�ҺϷ�
			elems[LeftChild(cur)].data = e;				// ����Ԫ��ֵ
			elems[LeftChild(cur)].tag = USED_NODE;		// ���ӱ�־
		}
		return;
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::InsertRightChild(int cur, const ElemType &e)
// ��ʼ������cur��cur�Һ��ӷǿ�
// �������������eΪcur���Һ��ӣ����cur���Һ��ӷǿգ�������ʧ��
{
	if (NodeEmpty(cur))
	{	//  curΪ�գ�����
		return;
	}
	else
	{	// �����Һ���
		if (NodeEmpty(RightChild(cur)) && RightChild(cur) <= maxSize && RightChild(cur) > 0)
		{	// cur�Һ���Ϊ��,�ҺϷ�
			elems[RightChild(cur)].data = e;				// �Һ���Ԫ��ֵ
			elems[RightChild(cur)].tag = USED_NODE;		// �Һ��ӱ�־
		}
		return;
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::DeleteLeftChild(int cur)
// ��ʼ������cur�ǿ�
// ���������ɾ��cur������
{
	if (NodeEmpty(cur))
	{	// curΪ��
		return;
	}
	else
	{	// cur�ǿ�
		DestroyHelp(LeftChild(cur));	// ɾ��cur������
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::DeleteRightChild(int cur)
// ��ʼ������cur�ǿ�
// ���������ɾ��cur������
{
	if (NodeEmpty(cur))
	{	// curΪ��
		return;
	}
	else
	{	// cur�ǿ�
		DestroyHelp(RightChild(cur));	// ɾ��cur������
	}
}

template <class ElemType>
void SqBinaryTree<ElemType>::DestroyHelp(int r)
// ���������������r�Ķ�����
{
	if(!NodeEmpty(r))
	{	// r�ǿ�,ʵʩ����
		DestroyHelp(LeftChild(r));		// ����������
		DestroyHelp(RightChild(r));		// ����������
		SetNodeEmpty(r);				// ��r�ÿ�
	}
}

template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(const ElemType &e, int size)
// ���������������eΪ������������Ϊsize�Ķ�����
{
	maxSize = size;					// ��������
	elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// ����洢�ռ�, δʹ��elems[0]
	for (int i = 2; i <=maxSize; i++)
	{	// �����н���ʶΪ��
		elems[i].tag = EMPTY_NODE;
	}
	root = 1;						// elems[1]�洢��
	elems[root].tag = USED_NODE;	// ����־
	elems[root].data = e;			// ��������Ԫ��ֵ
}


template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(const SqBinaryTree<ElemType> &copy)
// �������������֪�����������¶������������ƹ��캯��
{
	maxSize = copy.maxSize;							// ��������
	elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// ����洢�ռ�, δʹ��elems[0]
	for (int i = 1; i <=maxSize; i++)
	{	// ���ƽ��
		elems[i] = copy.elems[i];
	}
	root = copy.GetRoot();							// ���ƶ�������
}

template <class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(SqBinTreeNode<ElemType> es[], int r, int size)
// �����������es[]��r������������Ϊsize�Ķ�����, 
{
	maxSize = size;									// ��������
	elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// ����洢�ռ�, δʹ��elems[0]
	for (int i = 1; i <=maxSize; i++)
	{	// ���ƽ��
		elems[i] = es[i];
	}
	root = r;			// ���ƶ�������
}

template <class ElemType>
SqBinaryTree<ElemType> &SqBinaryTree<ElemType>::operator=(const SqBinaryTree<ElemType> &copy)
// �������������֪������copy���Ƶ���ǰ������--��ֵ���������
{
	if (&copy != this)
	{
		delete []elems;					// �ͷŴ洢�ռ�
		maxSize = copy.maxSize;							// ��������
		elems = new SqBinTreeNode<ElemType>[maxSize + 1];	// ����洢�ռ�, δʹ��elems[0]

		for (int i = 1; i <=maxSize; i++)
		{	// ���ƽ��
			elems[i] = copy.elems[i];
		}
		root = copy.GetRoot();			// ���ƶ�������
	}
	return *this;
}

template <class ElemType>
void DisplayBTWithTreeShapeHelp(SqBinaryTree<ElemType> &bt, int r, int level)
//	�������������״��ʽ��ʾ��rΪ���Ķ�������levelΪ���������������Ĳ����Ϊ1
{
	if(!bt.NodeEmpty(r))
	{	//��������ʽ��ֻ��ʽ�ǿ���
		DisplayBTWithTreeShapeHelp<ElemType>(bt, bt.RightChild(r), level + 1);//��ʾ������
		cout << endl;					//��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout << " ";				//ȷ���ڵ�level����ʾ���
		ElemType e;
		bt.GetItem(r, e);
		cout << e;						//��ʾ���
		DisplayBTWithTreeShapeHelp<ElemType>(bt, bt.LeftChild(r), level + 1);//��ʾ������
	}
}

template <class ElemType>
void DisplayBTWithTreeShape(SqBinaryTree<ElemType> &bt)
//	�����������״��ʽ��ʾ������ 
{
	DisplayBTWithTreeShapeHelp<ElemType>(bt, bt.GetRoot(), 1);	
		// ��״��ʾ��bt.GetRoot()Ϊ���Ķ�����
	cout << endl;
}

template <class ElemType>
void CreateBinaryTreeHelp(SqBinTreeNode<ElemType> es[], int r, ElemType pre[], ElemType in[], 
	int preLeft, int preRight, int inLeft, int inRight)	
// �����������֪����������������pre[preLeft..preRight]����������in[inLeft..inRight]����
//	��rΪ���Ķ�����
{
	if (inLeft > inRight)
	{	// �������޽��,�ն�����
		r = 0;							// �ն�������Ϊ��
	}
	else
	{	// �������н��,�ǿն�����
		es[r].data = pre[preLeft];es[r].tag = USED_NODE; // ���ɸ����
		int mid = inLeft;
		while (in[mid] != pre[preLeft]) 
		{	// ����pre[preLeft]��in[]�е�λ��,Ҳ�������������и���λ��
			mid++;
		}
		CreateBinaryTreeHelp(es, 2 * r, pre, in, preLeft+1, preLeft + mid - inLeft, inLeft, mid - 1);
			// ����������
		CreateBinaryTreeHelp(es, 2 * r + 1, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, 
			inRight);					// ����������
	}
} 

template <class ElemType>
SqBinaryTree<ElemType> &CreateBinaryTree(ElemType pre[], ElemType in[], int n)
// �����������֪������������й��������
{
	SqBinTreeNode<ElemType> *es = new SqBinTreeNode<ElemType>[n + 1];	// �洢��������Ϣ
	int r = 1;											// �������ĸ�
	CreateBinaryTreeHelp<ElemType>(es, r, pre, in, 0, n - 1, 0, n - 1);
		// ��������������й�����rΪ���Ķ����� 
	SqBinaryTree<ElemType> *bt = new SqBinaryTree<ElemType>(es, r, n);	// ���ɶ�����
	delete []es;										// �ͷŴ洢�ռ�
	return *bt;
}

#endif
