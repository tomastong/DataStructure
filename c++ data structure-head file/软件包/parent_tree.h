#ifndef __PARENT_TREE_H__
#define __PARENT_TREE_H__

#include "lk_queue.h"				// ������
#include "parent_tree_node.h"		// ˫�ױ�ʾ�������

// ˫����ʾ����
template <class ElemType>
class ParentTree
{
protected:
//  �������ݳ�Ա:
	ParentTreeNode<ElemType> *nodes;				// �洢�����
	int maxSize;									// ����������� 
	int root, num;									// ����λ�ü������

//	��������:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// �ȸ������
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType &)) const;	// ��������
    int HeightHelp(int r) const;					// ������rΪ�������ĸ�
	int DegreeHelp(int r) const;					// ������rΪ�������Ķ�
	void MoveHelp(int from, int to);				// ������from�Ƶ����to
	void DeleteHelp(int r);							// ɾ����rΪ������

public:
//  ���������������ر���ϵͳĬ�Ϸ�������:
	ParentTree();									// ���캯��
	virtual ~ParentTree();							// ��������
	int GetRoot() const;							// �������ĸ�
	bool Empty() const;								// �ж����Ƿ�Ϊ��
	StatusCode GetElem(int cur, ElemType &e) const;	// ��e���ؽ��Ԫ��ֵ
	StatusCode SetElem(int cur, const ElemType &e);	// �����cur��ֵ��Ϊe
	void PreRootOrder(void (*Visit)(const ElemType &)) const ;	// �����������
	void PostRootOrder(void (*Visit)(const ElemType &)) const ;	// ���ĺ������
	void LevelOrder(void (*Visit)(const ElemType &)) const ;	// ���Ĳ�α���
	int NodeCount() const;							// �������Ľ�����
	int NodeDegree(int cur) const;					// ���ؽ��cur�Ķ�
	int Degree() const;								// �������Ķ�
	int FirstChild(int cur) const;					// ���ؽ��cur�ĵ�һ������
	int RightSibling(int cur) const;				// ���ؽ��cur�����ֵ�
	int Parent(int cur) const;						// ���ؽ��cur��˫����
	StatusCode InsertChild(int cur, int i, const ElemType &e);	
		// ������Ԫ�ز���Ϊcur�ĵ�i������
	StatusCode DeleteChild(int cur, int i);			// ɾ��cur�ĵ�i��������
	int	Height() const;								// �������ĸ�
	ParentTree(const ElemType &e, int size = DEFAULT_SIZE);	
		// ����������Ԫ��eΪ������
	ParentTree(const ParentTree<ElemType> &copy);	// ���ƹ��캯��
	ParentTree(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE);
		// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn����
	ParentTree<ElemType> &operator=(const ParentTree<ElemType>& copy);	
		// ��ֵ�������
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ParentTree<ElemType> &t, int r, int level);
	// �������ʾ����ʾ����levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayTWithConcaveShape(const ParentTree<ElemType> &t);
	// �������ʾ����ʾ��

// ˫����ʾ�����ʵ�ֲ���
template <class ElemType>
ParentTree<ElemType>::ParentTree()
// �������������һ�ÿ���
{
	maxSize = DEFAULT_SIZE;							// �����������
	nodes = new ParentTreeNode<ElemType>[maxSize];	// ����洢�ռ�
	root = -1;										// ��ʾ�����ڸ�
	num = 0;										// �����Ľ�����Ϊ0
}

template <class ElemType>
ParentTree<ElemType>::~ParentTree()
// ����������ͷŴ洢�ռ�
{
	delete []nodes;			// �ͷŴ洢�ռ�
}


template <class ElemType>
int ParentTree<ElemType>::GetRoot() const
// ����������������ĸ�
{
	return root;
}

template <class ElemType>
bool ParentTree<ElemType>::Empty() const
// ����������ж����Ƿ�Ϊ��
{
	return num == 0;
}

template <class ElemType>
StatusCode ParentTree<ElemType>::GetElem(int cur, ElemType &e) const
// �����������e���ؽ��curԪ��ֵ,��������ڽ��cur,��������NOT_PRESENT,���򷵻�ENTRY_FOUND
{
	if (cur < 0 || cur >= num)	
	{	// �����ڽ��cur
		return NOT_PRESENT;					// ����NOT_PRESENT
	}
	else
	{	// ���ڽ��cur
		e = nodes[cur].data;				// ��e����Ԫ��ֵ
		return ENTRY_FOUND;					// ����ENTRY_FOUND
	}
}

template <class ElemType>
StatusCode ParentTree<ElemType>::SetElem(int cur, const ElemType &e)
// �����������������ڽ��cur,�򷵻�FAIL,���򷵻�SUCCESS,�������cur��ֵ����Ϊe
{
	if (cur < 0 || cur >= num)	
	{	// �����ڽ��cur
		return FAIL;						// ����FAIL
	}
	else
	{	// ���ڽ��cur
		nodes[cur].data = e;				// �����cur��ֵ����Ϊe
		return SUCCESS;						// ����SUCCESS
	}
}

template <class ElemType>
void ParentTree<ElemType>::PreRootOrderHelp(int r, void (*Visit)(const ElemType &)) const
// ������������ȸ������ζ���rΪ��������ÿ��Ԫ�ص��ú���(*visit)
{
	if (r >=0 && r < num)
	{	// r��Χ�Ϸ�
		(*Visit)(nodes[r].data);			// ���ʸ����
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
		{	// �����ȸ������ÿ������
			PreRootOrderHelp(child, Visit);
		}
	}
}

template <class ElemType>
void ParentTree<ElemType>::PreRootOrder(void (*Visit)(const ElemType &)) const
// ������������ȸ������ζ�����ÿ��Ԫ�ص��ú���(*visit)
{
	PreRootOrderHelp(GetRoot(), Visit);				// ���ø�������ʵ�ֺ��ȸ������
}

template <class ElemType>
void ParentTree<ElemType>::PostRootOrderHelp(int r, void (*Visit)(const ElemType &)) const
// �������������������ζ���rΪ��������ÿ��Ԫ�ص��ú���(*visit)
{
	if (r >=0 && r < num)
	{	// r��Χ�Ϸ�
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
		{	// ���κ�������ÿ������
			PostRootOrderHelp(child, Visit);
		}
		(*Visit)(nodes[r].data);					// ���ʸ����
	}
}

template <class ElemType>
void ParentTree<ElemType>::PostRootOrder(void (*Visit)(const ElemType &)) const
// �������������������ζ�����ÿ��Ԫ�ص��ú���(*visit)
{
	PostRootOrderHelp(GetRoot(), Visit);			// ���ø�������ʵ�ֺ�������
}

template <class ElemType>
void ParentTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// �����������α�����
{
	LinkQueue<int> q;	// ����
	int cur = root;		// �Ӹ���㿪ʼ���в�α���
	
	if (cur >= 0 || cur < num) q.InQueue(cur);	// ������Ϸ�,�����
	while (!q.Empty())
	{	// q�ǿ�,˵�����н��δ����
		q.OutQueue(cur);						// ����
		(*Visit)(nodes[cur].data);				// ���ʵ�ǰ���
		for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
		{	// ���ν�cur�ĺ������
			q.InQueue(child);					// �������
		}
	}
}

template <class ElemType>
int ParentTree<ElemType>::HeightHelp(int r) const
// ���������������rΪ�������ĸ�
{
	if (r < 0 || r >= num)
	{	// ����,��Ϊ0
		return 0;
	}
	else
	{
		int maxSubTreeHeight = 0;
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
		{	// ��������ߵ����ֵ
			int h = HeightHelp(child);			// ��ʱ�����洢��
			maxSubTreeHeight = (maxSubTreeHeight < h) ? h : maxSubTreeHeight;
				// ���������ߵ����ֵ
		}
		return maxSubTreeHeight + 1;			// ����Ϊ�����������ֵ�ټ�1
	}
}

template <class ElemType>
int ParentTree<ElemType>::Height() const
// ����������������ĸ�
{
	return HeightHelp(root);					// ���ø�������ʵ�ַ������ĸ�
}

template <class ElemType>
int ParentTree<ElemType>::NodeCount() const
// ����������������Ľ�����
{
	return num;
}

template <class ElemType>
int ParentTree<ElemType>::NodeDegree(int cur) const
// ������������ؽ��cur�Ķ�
{
	int d = 0;					// ��ʱ����,���ڶԺ��Ӹ������м���
	for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
	{	// �Ҳ�cur�ĺ���
		d++;					// �Ժ��Ӹ������м���
	}
	return d;
}

template <class ElemType>
int ParentTree<ElemType>::DegreeHelp(int r) const
// ���������������rΪ�������Ķ�
{

	int d = 0;					// ��ʱ����,���ڽ��ĺ��Ӹ���
	int maxSubTreeDegree = 0;	// �����ȵ����ֵ
	for (int child = FirstChild(r); child != -1; child = RightSibling(child))
	{	// �Ҳ�r�ĺ���
		d++;					// �Ժ��Ӹ������м���
		int subTreeDegree = DegreeHelp(child);	// �����Ķ�
		maxSubTreeDegree = (maxSubTreeDegree < subTreeDegree) ? subTreeDegree : maxSubTreeDegree;
			// �����������ֵ
	}
	return (d < maxSubTreeDegree) ? maxSubTreeDegree : d;
}

template <class ElemType>
int ParentTree<ElemType>::Degree() const
// ����������������Ķ�
{
	return DegreeHelp(root);
}

template <class ElemType>
int ParentTree<ElemType>::FirstChild(int cur) const
// �����������cur�޺���,�򷵻�-1,���򷵻������cur�ĵ�һ������,
{
	for (int pos = 0; pos < num; pos++)
	{	// �Ҳ��һ������
		if (nodes[pos].parent == cur) return pos;	// posΪ��һ������
	}
	return -1;										// �Ҳ�ʧ��,��ʾ�޺���
}

template <class ElemType>
int ParentTree<ElemType>::RightSibling(int cur) const
// ���������������cur�����ֵ�,�򷵻�-1,���򷵻�cur�����ֵ�
{
	for (int pos = cur + 1; pos < num; pos++)
	{	// ����cur�����ֵ�
		if (nodes[cur].parent == nodes[pos].parent) return pos;	// posΪcur�����ֵ�
	}
	return -1;										// ����ʧ��,��ʾ�����ֵ�
}

template <class ElemType>
int ParentTree<ElemType>::Parent(int cur) const
// ������������ؽ��cur��˫����
{
	if (cur < 0 || cur >= num)						
		return -1;									// ���cur������,����-1��ʾ��˫��
	return nodes[cur].parent;
}

template <class ElemType>
void ParentTree<ElemType>::MoveHelp(int from, int to)
// ���������������from�Ƶ�to
{
	nodes[to] = nodes[from];						// ��nodes[from]��ֵ��nodes[to]
	for (int pos = 0; pos < num; pos++)
	{	// ����fromΪ˫�׵Ľ���Ϊ��toΪ˫�׵Ľ��
		if (from == nodes[pos].parent) nodes[pos].parent = to;
	}
}

template <class ElemType>
StatusCode ParentTree<ElemType>::InsertChild(int cur, int i, const ElemType &e)
// ���������������Ԫ�ز���Ϊcur�ĵ�i������,�������ɹ�,�򷵻�SUCCESS,���򷵻�FAIL
{
	if (cur < 0 || cur >= num) return FAIL;
	if (i < 0 || i > NodeDegree(cur) + 1) return FAIL;
	int n, child;						// ��ʱ���� 
	for (n = 1, child = FirstChild(cur); n < i && child != -1; child = RightSibling(child), n++);
		// ���ҵ�i + 1�����ӵ�λ��
	if (child != -1)
	{	// ���ڵ�i������,��i�����ӵ�λ��Ϊ����λ��
		for (int pos = num - 1; pos >= child; pos--)
		{	// ��num - 1��child�Ľ�����κ���
			MoveHelp(pos, pos + 1);
		}
		nodes[child].data = e;						// �����child�ĵ�����Ԫ��ֵ��Ϊe
		nodes[child].parent = cur;					// ���child��˫��Ϊcur
	}
	else
	{	// �����ڵ�i+1������,�������
		child = num;								// childΪ���λ��
		nodes[child].data = e;						// �����child�ĵ�����Ԫ��ֵ��Ϊe
		nodes[child].parent = cur;					// ���child��˫��Ϊcur
	}
	num++;											// ����ɹ�,������Լ�1
	return SUCCESS;
}

template <class ElemType>
void ParentTree<ElemType>::DeleteHelp(int r)
// ���������ɾ����rΪ������
{
	if (r >= 0 || r < num)
	{	// r�Ϸ�
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
		{	// �Ҳ�r������
			DeleteHelp(child);						// ɾ����child��������
		}
		nodes[r].parent = -2;						// ˫��Ϊ-2,�ر�ʾ�˽���ѱ�ɾ��
	}
}

template <class ElemType>
StatusCode ParentTree<ElemType>::DeleteChild(int cur, int i)
// ���������ɾ��cur�ĵ�i������,,���ɾ���ɹ�,�򷵻�SUCCESS,���򷵻�FAIL
{
	if (i < 0 && i > NodeDegree(cur)) return FAIL;	// ����ʧ��
	int n, child;									// ��ʱ���� 
	for (n = 1, child = FirstChild(cur); n < i && child != -1; child = RightSibling(child), n++);
		// ���ҵ�i�����ӵ�λ��
	
	DeleteHelp(child);								// ɾ����i������
	for (int pos = num - 1; pos >= 0; pos--)
	{	// �����ɾ���Ľ��
		if (Parent(pos) == -2)
		{	// ��ɾ�����
			for (int i = num - 1; i >= pos + 1; i--)
			{	// ��num - 1��pos + 1�Ľ������ǰ��
				MoveHelp(i, i - 1);					// ǰ��
			}
			num--;									// �����ɾ������,�������Լ�1			
		}
	}
	return SUCCESS;									// �����ɹ�
}

template <class ElemType>
ParentTree<ElemType>::ParentTree(const ElemType &e, int size)
// �������������������Ԫ��eΪ������
{
	maxSize = size;									// ��������
	nodes = new ParentTreeNode<ElemType>[maxSize];	// ����洢�ռ�
	root = 0;										// ����λ��
	nodes[root].data = e;							// ����������и�ֵ
	nodes[root].parent = -1;						// ����˫��Ϊ-1
	num = 1;										// ������
}


template <class ElemType>
ParentTree<ElemType>::ParentTree(const ParentTree<ElemType> &copy)
// �������������֪�����������������ƹ��캯��
{
	maxSize = copy.maxSize;							// ��������
	nodes = new ParentTreeNode<ElemType>[maxSize];	// ����洢�ռ�
	for (int pos = 0; pos < copy.num; pos++)
	{	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
		nodes[pos].data = copy.nodes[pos].data;		// ����Ԫ��ֵ
		nodes[pos].parent = copy.nodes[pos].parent;	// ˫��λ��
	}
	root = copy.root;								// ��
	num = copy.num;									// ������
}
  
template <class ElemType>
ParentTree<ElemType>::ParentTree(ElemType items[], int parents[], int r, int n, int size)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn����
{
	maxSize = size;									// ��������
	if (n > maxSize)	
		throw Error("������̫��!");				// �׳��쳣
	nodes = new ParentTreeNode<ElemType>[maxSize];	// ����洢�ռ�
	
	for (int pos = 0; pos < n; pos++)
	{	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
		nodes[pos].data = items[pos];				// ����Ԫ��ֵ
		nodes[pos].parent = parents[pos];			// ˫��λ��
	}
	root = r;										// ��
	num = n;										// ������
}


template <class ElemType>
ParentTree<ElemType> &ParentTree<ElemType>::operator=(const ParentTree<ElemType> &copy)
// �������������֪��copy���Ƶ���ǰ��--��ֵ�������
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;							// ��������
		delete []nodes;									// �ͷŴ洢�ռ�
		nodes = new ParentTreeNode<ElemType>[maxSize];	// ����洢�ռ�
		for (int pos = 0; pos < copy.num; pos++)
		{	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
			nodes[pos].data = copy.nodes[pos].data;		// ����Ԫ��ֵ
			nodes[pos].parent = copy.nodes[pos].parent;	// ˫��λ��
		}
		root = copy.root;								// ��
		num = copy.num;									// ������
	}
	return *this;
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ParentTree<ElemType> &t, int r, int level)
// ����������������ʾ����ʾ����levelΪ���������������Ĳ����Ϊ1
{
	if (r >= 0 && r < t.NodeCount())
	{	// ���ڽ��r,����ʾr����Ϣ
		cout<<endl;									//��ʾ����	
		for(int i = 0; i< level - 1; i++)
			cout<<" ";								//ȷ���ڵ�level����ʾ���
		ElemType e;
		t.GetElem(r, e);							// ȡ�����r��Ԫ��ֵ
		cout << e;									// ��ʾ���Ԫ��ֵ
		for (int child = t.FirstChild(r); child != -1; child = t.RightSibling(child))
		{	// ������ʾ��������
			DisplayTWithConcaveShapeHelp(t, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ParentTree<ElemType> &t)
// ����������������ʾ����ʾ��
{
	DisplayTWithConcaveShapeHelp(t, t.GetRoot(), 1);// ���ø�������ʵ�ְ������ʾ����ʾ��
	cout << endl;									// ����
}

#endif
