#ifndef __CHILD_SIBLING_FOREST_H__
#define __CHILD_SIBLING_FOREST_H__

#include "lk_queue.h"							// ������
#include "child_sibling_tree_node.h"			// �����ֵܱ�ʾ�������

// �����ֵܱ�ʾɭ����
template <class ElemType>
class ChildSiblingForest
{
protected:
//  ɭ�ֵ����ݳ�Ա:
	ChildSiblingTreeNode<ElemType> *root;		// ɭ�ֵ�һ�����ĸ�

//	��������:
	void DestroyHelp(ChildSiblingTreeNode<ElemType> * &r);		// ������rΪ��һ��������ɭ��
	void PreOrderHelp(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;
		// ���������rΪ��һ�����ĸ���ɭ��
	void InOrderHelp(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;	
		// ���������rΪ��һ�����ĸ���ɭ��
	int NodeCountHelp(ChildSiblingTreeNode<ElemType> *r) const;	// ���ؽ�����
	void DeleteHelp(ChildSiblingTreeNode<ElemType> *r);	// ɾ����rΪ��һ�����ĸ���ɭ��
	ChildSiblingTreeNode<ElemType> *ParentHelp(ChildSiblingTreeNode<ElemType> *r, 
		const ChildSiblingTreeNode<ElemType> *cur) const;	// ����cur��˫��
	ChildSiblingTreeNode<ElemType> *CopyTreeHelp(ChildSiblingTreeNode<ElemType> *copy);	
		// ����ɭ��
	ChildSiblingTreeNode<ElemType> *CreateForestHelp(ElemType items[], int parents[], int r, int n);
		// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],��һ���������λ��Ϊr,������
		// Ϊn��ɭ�֣�������ɭ�ֵĸ�

public:
//  ɭ�ַ������������ر���ϵͳĬ�Ϸ�������:
	ChildSiblingForest();									// �޲����Ĺ��캯��
	virtual ~ChildSiblingForest();							// ��������
	ChildSiblingTreeNode<ElemType> *GetFirstRoot() const;	// ����ɭ�ֵĵ�һ�����ĸ�
	bool Empty() const;								// �ж�ɭ���Ƿ�Ϊ��
	StatusCode GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const;
		// ��e���ؽ��Ԫ��ֵ
	StatusCode SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e);
		// �����cur��ֵ��Ϊe
	void PreOrder(void (*Visit)(const ElemType &)) const;		// ɭ�ֵ��������
	void InOrder(void (*Visit)(const ElemType &)) const;		// ɭ�ֵ��������
	void LevelOrder(void (*Visit)(const ElemType &)) const;		// ɭ�ֵĲ�α���
	int NodeCount() const;							// ��ɭ�ֵĽ�����
	int NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const;	// ����cur�Ķ�
	ChildSiblingTreeNode<ElemType> *FirstChild(ChildSiblingTreeNode<ElemType> *cur) const;	
		// ����ɭ�ֽ��cur�ĵ�һ������
	ChildSiblingTreeNode<ElemType> *RightSibling(ChildSiblingTreeNode<ElemType> *cur) const;				
		// ����ɭ�ֽ��cur�����ֵ�
	ChildSiblingTreeNode<ElemType> *Parent(ChildSiblingTreeNode<ElemType> *cur) const;
		// ����ɭ�ֽ��cur��˫��
	StatusCode InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e);	
		// ������Ԫ�ز���Ϊcur�ĵ�i������
	StatusCode DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i);		// ɾ��cur�ĵ�i������ɭ��
	ChildSiblingForest(const ElemType &e);					// ����������Ԫ��eΪ�����������ɵ�ֻ��һ������ɭ��
	ChildSiblingForest(const ChildSiblingForest<ElemType> &copy);	// ���ƹ��캯��
	ChildSiblingForest(ElemType items[], int parents[], int n);
		// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],������Ϊn��ɭ��
	ChildSiblingForest(ChildSiblingTreeNode<ElemType> *r);// ������rΪ��һ�����ĸ���ɭ��
	ChildSiblingForest<ElemType> &operator=(const ChildSiblingForest<ElemType>& copy);	
		// ��ֵ�������
};

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildSiblingForest<ElemType> &t, ChildSiblingTreeNode<ElemType> *r, int level);
	// �������ʾ����ʾɭ�֣�levelΪ���������������Ĳ����Ϊ1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingForest<ElemType> &f);
	// �������ʾ����ʾɭ��

// �����ֵܱ�ʾɭ�����ʵ�ֲ���
template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest()
// �������������һ����ɭ��
{
	root = NULL;						// ��ʾɭ��Ϊ��
}

template <class ElemType>
void ChildSiblingForest<ElemType>::DestroyHelp(ChildSiblingTreeNode<ElemType> * &r)
// ���������������rΪ��һ��������ɭ��
{
	if (r != NULL)
	{	// r�ǿ�,ʵʩ����
		ChildSiblingTreeNode<ElemType> *fChild = FirstChild(r);		// �׺���
		ChildSiblingTreeNode<ElemType> *rSibling = RightSibling(r);	// ���ֵ�
		DestroyHelp(fChild);			// ���ٵ�һ����������ɭ��
		DestroyHelp(rSibling);			// ���ٳ�ȥ��һ������ʣ��������ɵ�ɭ��
		delete r;						// ���ٸ����
		r = NULL;
	}
}

template <class ElemType>
ChildSiblingForest<ElemType>::~ChildSiblingForest()
// �������������ɭ��--���캯��
{
	DestroyHelp(root);				// ����ɭ��
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::GetFirstRoot() const
// �������������ɭ�ֵĵ�һ�����ĸ�
{
	return root;
}

template <class ElemType>
bool ChildSiblingForest<ElemType>::Empty() const
// ����������ж�ɭ���Ƿ�Ϊ��
{
	return root == NULL;			// rootΪ�ձ�ʾɭ��Ϊ��
}

template <class ElemType>
StatusCode ChildSiblingForest<ElemType>::GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const
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
StatusCode ChildSiblingForest<ElemType>::SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e)
// ���������������ڽ��cur,�򷵻�FAIL,���򷵻�SUCCESS,�������cur��ֵ����Ϊe
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
void ChildSiblingForest<ElemType>::PreOrderHelp(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const
// ��ʼ����: rΪɭ���е�һ�����ĸ�
// �����������ɭ������������ζ�ÿ��Ԫ�ص��ú���(*visit)
{
	if (r != NULL)
	{	// r�ǿ�
		(*Visit)(r->data);							// ���ʵ�һ�����ĸ����
		PreOrderHelp(FirstChild(r), Visit);			// ���������һ����������ɭ��
		PreOrderHelp(RightSibling(r), Visit);		// ���������ȥ��һ������ʣ��������ɵ�ɭ��
	}
}

template <class ElemType>
void ChildSiblingForest<ElemType>::PreOrder(void (*Visit)(const ElemType &)) const
// ������������������ζ�ɭ�ֵ�ÿ��Ԫ�ص��ú���(*visit)
{
	PreOrderHelp(GetFirstRoot(), Visit);	// GetFirstRoot()Ϊ��һ�����ĸ�
}

template <class ElemType>
void ChildSiblingForest<ElemType>::InOrderHelp(ChildSiblingTreeNode<ElemType> *r, 
	void (*Visit)(const ElemType &)) const
// ��ʼ����: rΪɭ���е�һ�����ĸ�
// �����������ɭ������������ζ�ÿ��Ԫ�ص��ú���(*visit)
{
	if (r != NULL)
	{	// r�ǿ�
		InOrderHelp(FirstChild(r), Visit);			// ���������һ����������ɭ��
		(*Visit)(r->data);							// ���ʵ�һ�����ĸ����
		InOrderHelp(RightSibling(r), Visit);		// ���������ȥ��һ������ʣ��������ɵ�ɭ��
	}
}

template <class ElemType>
void ChildSiblingForest<ElemType>::InOrder(void (*Visit)(const ElemType &)) const
// ������������������ζ�ɭ�ֵ�ÿ��Ԫ�ص��ú���(*visit)
{
	InOrderHelp(GetFirstRoot(), Visit);			// GetFirstRoot()Ϊ��һ�����ĸ�
}

template <class ElemType>
void ChildSiblingForest<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
// �����������α���ɭ��
{
	for (ChildSiblingTreeNode<ElemType> *treeRoot = root; treeRoot != NULL; 
		treeRoot = RightSibling(treeRoot))
	{	// ���β�α���ɭ����ÿ����
		LinkQueue<ChildSiblingTreeNode<ElemType> *> q;	// ����
		ChildSiblingTreeNode<ElemType> *cur = treeRoot;	// �Ӹ���㿪ʼ���в�α���
		
		if (cur != NULL) q.InQueue(cur);			// ������ǿ�,�����
		while (!q.Empty())
		{	// q�ǿ�,˵�����н��δ����
			q.OutQueue(cur);						// ����
			(*Visit)(cur->data);				// ���ʵ�ǰ���
			for (ChildSiblingTreeNode<ElemType> *child = FirstChild(cur); child != NULL;
				child = RightSibling(child))
			{	// ���ν�cur�ĺ�������
				q.InQueue(child);					// �������
			}
		}
	}
}

template <class ElemType>
int ChildSiblingForest<ElemType>::NodeCountHelp(ChildSiblingTreeNode<ElemType> *r) const
// ���������������rΪ����ɭ�ֵĽ�����
{
	if (r == NULL) return 0;			// ��ɭ�ֽ�����Ϊ0
	else
	{	// ����ɭ�ֵĽ�����֮��
		int forestNodeCountSum = 0;		// ɭ�ֽ�����֮��
		forestNodeCountSum += NodeCountHelp(FirstChild(r));	// ��һ����������ɭ�ֽ�����
		forestNodeCountSum += NodeCountHelp(RightSibling(r));	// ��ȥ��һ������ʣ��������ɵ�ɭ�ֽ�����
		return 1 + forestNodeCountSum;	
			// �ǿ�ɭ�ֽ���Ϊÿһ��������ɭ�ֵĽ��������ϳ�ȥ��һ������ʣ��������ɵ�ɭ�ֽ�����֮���ټ�1
	}
}

template <class ElemType>
int ChildSiblingForest<ElemType>::NodeCount() const
// �������������ɭ�ֵĽ�����
{
	return NodeCountHelp(root);			// �ø�������ʵ����ɭ�ֽ�����
}

template <class ElemType>
int ChildSiblingForest<ElemType>::NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const
// ������������ؽ��cur�Ķ�
{
	int d = 0;					// ��ʱ����,���ڶԺ��Ӹ������м���
	for (ChildSiblingTreeNode<ElemType> *child = FirstChild(cur); child != NULL;
		child = RightSibling(child))
	{	// �Ҳ�cur�ĺ���
		d++;					// �Ժ��Ӹ������м���
	}
	return d;
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::FirstChild(ChildSiblingTreeNode<ElemType> *cur) const
// �����������ΪNULL,�򷵻ص�һ�����ĸ�,���򷵻�ɭ�ֽ��cur�ĵ�һ������,
{
	if (cur == NULL)
	{	// cur��,���ĸ���˫��ΪNULL,��ɭ����ÿ�����ĸ�������ΪNULL�ĺ���
		return root;			
	}
	else
	{	// cur�ǿ�
		return cur->firstChild;			// firstChildΪ��һ������
	}
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::RightSibling(ChildSiblingTreeNode<ElemType> *cur) const
// ���������������cur�����ֵ�,�򷵻�NULL,���򷵻�cur�����ֵ�
{
	if (cur == NULL)
	{	// curΪ��
		return NULL;					// �ս�����ֵ�
	}
	else
	{	// cur�ǿ�
		return cur->rightSibling;		// rightSiblingΪ���ֵ�
	}
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::ParentHelp(ChildSiblingTreeNode<ElemType> *r, 
	const ChildSiblingTreeNode<ElemType> *cur) const
// ���������������rΪ��һ��������ɭ����, ���cur��˫��
{
	if (r == NULL) return NULL;				// ��ɭ��

	if (FirstChild(r) == cur)
	{	// rΪcur�ĵ�һ�����ӵ�˫��
		return r;
	}

	ChildSiblingTreeNode<ElemType> *tmp;
	tmp = ParentHelp(FirstChild(r), cur);	// �ڵ�һ����������ɭ������˫��
	if (tmp != NULL) return tmp;			// ����˫��,�򷵻�˫��
	
	tmp = ParentHelp(RightSibling(r), cur);	// �ڳ�ȥ��һ������ʣ��������ɵ�ɭ������˫��
	if (tmp != NULL) return tmp;			// ����˫��,�򷵻�˫��

	return NULL;							// δ�ҵ�˫��
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::Parent(ChildSiblingTreeNode<ElemType> *cur) const
// �������������ɭ���н��cur��˫��
{
	return ParentHelp(root, cur);			// �ø���������ɭ���н���˫��
}

template <class ElemType>
StatusCode ChildSiblingForest<ElemType>::InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e)
// ���������������Ԫ�ز���Ϊcur�ĵ�i������,�������ɹ�,�򷵻�SUCCESS,���򷵻�FAIL
{
	if (cur == NULL) return FAIL;
	if (i < 0 || i > NodeDegree(cur) + 1) return FAIL;

	ChildSiblingTreeNode<ElemType> *newNodePtr = new ChildSiblingTreeNode<ElemType>(e);	// �½��
	if (i == 1)
	{	// ��������׺���
		ChildSiblingTreeNode<ElemType> *tmp = cur->firstChild;	// �ݴ�cur���׺���
		cur->firstChild = newNodePtr;		// newNodePtr����Ϊcur���׺���
		newNodePtr->rightSibling = tmp;		// ԭcur���׺��ӱ�ΪnewNodePtr�����ֵ�
	}
	else
	{
		int n = 1;
		ChildSiblingTreeNode<ElemType> *child;		// ���� 
		for (child = FirstChild(cur); n < i - 1 && child != NULL;
			child = RightSibling(child), n++);
			// ���ҵ�i-1������

		newNodePtr->rightSibling = child->rightSibling; child->rightSibling = newNodePtr;
			// ��tmp������Ϊ��i������
	}
	return SUCCESS;
}

template <class ElemType>
void ChildSiblingForest<ElemType>::DeleteHelp(ChildSiblingTreeNode<ElemType> *r)
// ���������ɾ����rΪ��һ�õĸ���ɭ��
{
	if (r != NULL)
	{	// r�ǿ�
		DeleteHelp(FirstChild(r));			// ɾ����һ����������ɭ��
		DeleteHelp(RightSibling(r));		// ɾ����ȥ��һ������ʣ��������ɵ�ɭ��
		delete r;							// �ͷ�r
		r = NULL;
	}
}

template <class ElemType>
StatusCode ChildSiblingForest<ElemType>::DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i)
// ���������ɾ��cur�ĵ�i������ɭ��,���ɾ���ɹ�,�򷵻�SUCCESS,���򷵻�FAIL
{
	if (i < 0 && i > NodeDegree(cur)) return FAIL;	// ����ʧ��
	if (i == 1)
	{
		ChildSiblingTreeNode<ElemType> *tmp = cur->firstChild;	// �ݴ��1����ɭ�ֵĸ�
		cur->firstChild = tmp->rightSibling;		// ���߼���ɾ����1����ɭ��
		DeleteHelp(tmp);							// ������ɾ����1����ɭ��
	}
	else
	{
		int n = 1;
		ChildSiblingTreeNode<ElemType> *child;		// ���� 
		for (child = FirstChild(cur); n < i - 1 && child != NULL; 
			child = RightSibling(child), n++);
 			// ���ҵ�i - 1������

		ChildSiblingTreeNode<ElemType> *tmp = child->rightSibling;	// �ݴ��i����ɭ�ֵĸ�
		child->rightSibling = tmp->rightSibling;		// ������ɾ����i������ɭ��
		DeleteHelp(tmp);								// ������ɾ����i����ɭ��
		return SUCCESS;									// �����ɹ�
	}
	return SUCCESS;										// �����ɹ�
}

template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest(const ElemType &e)
// �������������������Ԫ��eΪ�����������ɵ�ֻ��һ������ɭ��
{
	root = new ChildSiblingTreeNode<ElemType>(e);	// ���ɸ����
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::CopyTreeHelp(ChildSiblingTreeNode<ElemType> *copy)
// �������������copyΪ��һ�����ĸ���ɭ�ָ��Ƴ��µ�ɭ��,������ɭ�ֵ�һ�����ĸ�
{
	if (copy == NULL)
	{	// ���ƿ�ɭ��
		return NULL;					// ��ɭ�ֵ�һ�������ĸ�Ϊ��	
	}
	else
	{	// ���Ʒǿ�ɭ��
		ChildSiblingTreeNode<ElemType> *r = new ChildSiblingTreeNode<ElemType>(copy->data);	// ���Ƶ�һ���������
		r->firstChild = CopyTreeHelp(copy->firstChild);	// ���Ƶ�һ�öԵ�����ɭ��
		r->rightSibling = CopyTreeHelp(copy->rightSibling);	// ���Ƴ�ȥ��һ������ʣ��������ɵ�ɭ��
		return r;
	}	
}

template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest(const ChildSiblingForest<ElemType> &copy)
// �������������֪ɭ�ֹ�����ɭ�֡������ƹ��캯��
{
	root = CopyTreeHelp(copy.FirstChild(NULL));
}
  
template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingForest<ElemType>::CreateForestHelp(ElemType items[], int parents[], int r, int n)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],��һ���������λ��Ϊr,������Ϊn�����������ص�һ�����ĸ�
{
	if (r >= 0 || r < n)
	{
		ChildSiblingTreeNode<ElemType> *rt = new ChildSiblingTreeNode<ElemType>(items[r]);
			// ���Ƶ�һ�����ĸ����

		for (int fChild = 0; fChild < n; fChild++)
		{	// ����r�ĵ�һ������
			if (parents[fChild] == r)
			{	// ������һ����������ɭ��
				rt->firstChild = CreateForestHelp(items, parents, fChild, n);
				break;
			}
		}

		for (int rSibling = r + 1; rSibling < n; rSibling++)
		{	// ����r�����ֵ�
			if (parents[rSibling] == parents[r])
			{	// ������ȥ��һ������ʣ��������ɵ�ɭ��
				rt->rightSibling = CreateForestHelp(items, parents, rSibling, n);
				break;
			}
		}
		return rt;					// ��һ�����ĸ�
	}
	else return NULL;				// ��ɭ��
}

template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest(ElemType items[], int parents[], int n)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],������Ϊn��ɭ��
{
	int r;							// ��ʱ���� 
	for (r = 0; r < n; r++)
	{	// ���ҵ�һ�����ĸ�
		if (parents[r] == -1)
		{	// rΪ��һ�����ĸ�
			root = CreateForestHelp(items, parents, r, n);	// �ø�����������ɭ��
			return;
		}
	}
	if (r >= n) root = NULL;		// δ�ҵ���,��ɭ��
}

template <class ElemType>
ChildSiblingForest<ElemType>::ChildSiblingForest(ChildSiblingTreeNode<ElemType> *r)
// ���������������rΪ��һ�����ĸ���ɭ��
{
	root = r;
}

template <class ElemType>
ChildSiblingForest<ElemType> &ChildSiblingForest<ElemType>::operator=(const ChildSiblingForest<ElemType> &copy)
// �������������֪ɭ��copy���Ƶ���ǰɭ��--��ֵ�������
{
	if (&copy != this)
	{
		DestroyHelp(root);							// ����ɭ��
		root = CopyTreeHelp(copy.FirstChild(NULL));
	}
	return *this;
}

template <class ElemType>
void DisplayTWithConcaveShapeHelp(const ChildSiblingForest<ElemType> &f, ChildSiblingTreeNode<ElemType> *r, int level)
// ����������������ʾ����ʾɭ�֣�levelΪ���������������Ĳ����Ϊ1
{
	if (r != NULL)
	{	// �ǿո�r
		cout<<endl;									//��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout<<" ";								//ȷ���ڵ�level����ʾ���
		ElemType e;
		f.GetElem(r, e);							// ȡ�����r��Ԫ��ֵ
		cout << e;									// ��ʾ���Ԫ��ֵ
		for (ChildSiblingTreeNode<ElemType> *child = f.FirstChild(r); child != NULL;
			child = f.RightSibling(child))
		{	// ������ʾ������ɭ��
			DisplayTWithConcaveShapeHelp(f, child, level + 1);
		}
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingForest<ElemType> &f)
// ����������������ʾ����ʾɭ��
{
	for (ChildSiblingTreeNode<ElemType> *cur = f.GetFirstRoot(); cur != NULL;
		cur = f.RightSibling(cur))
	{	// ����ɭ���и������ĸ����
		DisplayTWithConcaveShapeHelp(f, cur, 1);
			// ���ø�������ʵ�ְ������ʾ����ʾɭ�ֵĸ�����
		cout << endl;								// ����
	}
}

#endif
