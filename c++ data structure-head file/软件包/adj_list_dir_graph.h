#ifndef __ADJ_LIST_DIR_GRAPH_H__
#define __ADJ_LIST_DIR_GRAPH_H__

#include "lk_list.h"							// ����������
#include "adj_list_graph_vex_node.h"			// �ڽӱ�����ͼ��������

// ����ͼ���ڽӱ���
template <class ElemType>
class AdjListDirGraph
{
protected:
// �ڽӱ�����ݳ�Ա:
	int vexNum, edgeNum;						// ��������ͱ���
	AdjListGraphVexNode<ElemType> *vexTable;	// �����
	mutable StatusCode *tag;					// ָ���־�����ָ��				

// ��������
	void DestroyHelp();							// ��������ͼ,�ͷ�����ͼ���õĿռ�
	int IndexHelp(const LinkList<int> *la, int v) const;
		//��λ����v���ڽ������е�λ��

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);
		// ���춥������Ϊes[],�������ΪvertexNum,����Ϊ0������ͼ
	AdjListDirGraph(int vertexNum = DEFAULT_SIZE);
		// ���춥�����ΪvertexNum,����Ϊ0������ͼ
	~AdjListDirGraph();							// ��������
	StatusCode GetElem(int v, ElemType &e) const;// �󶥵��Ԫ��	
	StatusCode SetElem(int v, const ElemType &e);// ���ö����Ԫ��ֵ
	int GetVexNum() const;						// ���ض������			 
	int GetedgeNum() const;						// ���ر�������			 
	int FirstAdjVex(int v) const;				// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;		// ���ض���v1�������v2����һ���ڽӵ�			 
	void InsertEdge(int v1, int v2);			// ���붥��Ϊv1��v2�ı�			 
	void DeleteEdge(int v1, int v2);			// ɾ������Ϊv1��v2�ı�			 
	StatusCode GetTag(int v) const;			// ���ض���v�ı�־		 
	void SetTag(int v, StatusCode val) const;	// ���ö���v�ı�־Ϊval		 
	AdjListDirGraph(const AdjListDirGraph<ElemType> &copy);	// ���ƹ��캯��
	AdjListDirGraph<ElemType> &operator =(const AdjListDirGraph<ElemType> &copy); 
		// ��ֵ�������
};

template <class ElemType>
void Display(const AdjListDirGraph<ElemType> &g, bool showVexElem);	// ��ʾ�ڽӾ�������ͼ

// ����ͼ���ڽӱ����ʵ�ֲ���
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType es[], int vertexNum)
// ������������춥����ΪnumVex,��������Ϊes[],����Ϊkf,�������ΪvertexNum,����Ϊ0������ͼ
{
	if (vertexNum < 0)	throw Error("�����������Ϊ��!");// �׳��쳣

	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	tag = new StatusCode[vexNum];				// ���ɱ�־����
	int curPos;									// ��ʱ���� 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ��ʼ����־����
		tag[curPos] = UNVISITED;
	}

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// �����ڽӱ�
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ��ʼ����������
		vexTable[curPos].data = es[curPos];
	}
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexNum)
// ������������춥����ΪnumVex,����Ϊkf,�������ΪvertexNum,����Ϊ0������ͼ
{
	if (vertexNum < 0)	throw Error("�����������Ϊ��!");// �׳��쳣

	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	tag = new StatusCode[vexNum];				// ���ɱ�־����
	int curPos;									// ��ʱ���� 
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ��ʼ����־����
		tag[curPos] = UNVISITED;
	}

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// �����ڽӱ�
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DestroyHelp()
// �����������������ͼ,�ͷ�����ͼ���õĿռ�
{
	delete []tag;								// �ͷű�־
	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// �ͷ�����
		if (vexTable[iPos].adjLink != NULL)
			delete vexTable[iPos].adjLink;
	}
	delete []vexTable;							// �ͷ��ڽӱ�
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph()
// ����������ͷ��ڽӱ�����ͼ��ռ�ÿռ�
{
	DestroyHelp();
}

template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetElem(int v, ElemType &e) const
// ����������󶥵�v��Ԫ��, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return NOT_PRESENT;			// Ԫ�ز�����
	}
	else
	{	// v�Ϸ�
		e = vexTable[v].data;		// ������v��Ԫ��ֵ����e
		return ENTRY_FOUND;			// Ԫ�ش���
	}
}	

template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::SetElem(int v, const ElemType &e)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return RANGE_ERROR;			// λ�ô�
	}
	else
	{	// v�Ϸ�
		vexTable[v].data = e;		// ����Ԫ��
		return SUCCESS;				// �ɹ�
	}
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetedgeNum() const
// ������������ر�������
{
	return edgeNum;
}		 

template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�һ���ڽӵ�			 
{
	if (v < 0 || v >= vexNum) throw Error("v���Ϸ�!");// �׳��쳣

	if (vexTable[v].adjLink == NULL)
	{	// ���ڽ��������ڽӵ�
		return -1; 
	}
	else
	{	// �ǿ��ڽ����������ڽӵ�
		int adjVex;
		vexTable[v].adjLink->GetElem(1, adjVex);
		return adjVex;
	}
}

template <class ElemType>
int AdjListDirGraph<ElemType>::IndexHelp(const LinkList<int> *la, int v) const
// �����������λ����v���ڽ������е�λ��
{
	int curPos, adjVex;
	curPos = la->GetCurPosition();

	la->GetElem(curPos, adjVex);					// ȡ���ڽӵ���Ϣ
	if (adjVex == v) return curPos;					// vΪ��������ĵ�ǰλ�ô� 
	
	curPos = 1;
	for (curPos = 1; curPos <= la->Length(); curPos++)
	{	// ѭ������
		la->GetElem(curPos, adjVex);				// ȡ�ñ���Ϣ
		if (adjVex == v) break;						// ��λ�ɹ�
	}
	
	return curPos;									// curPos = la.Length() + 1 ��ʾ��λʧ��
}

template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw Error("v1���ܵ���v2!");				// �׳��쳣
	
	if (vexTable[v1].adjLink == NULL) return -1;			// �ڽ�����vexTable[v1].adjListΪ��,����-1

	int curPos = IndexHelp(vexTable[v1].adjLink, v2);	// ȡ��v2���ڽ������е�λ��
	if (curPos < vexTable[v1].adjLink->Length())
	{	// ������1���ڽӵ�
		int adjVex;
		vexTable[v1].adjLink->GetElem(curPos + 1, adjVex);// ȡ�����
		return adjVex;
	}
	else
	{	// ��������һ���ڽӵ�
		return -1;
	}
}

template <class ElemType>
void AdjListDirGraph<ElemType>::InsertEdge(int v1, int v2)
// ������������붥��Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw Error("v1���ܵ���v2!");				// �׳��쳣

	if (vexTable[v1].adjLink == NULL)
	{	// ������
		vexTable[v1].adjLink = new LinkList<int>;
	}

	int curPos = IndexHelp(vexTable[v1].adjLink, v2);		// ȡ��v2���ڽ������е�λ��
	if (curPos > vexTable[v1].adjLink->Length())
	{	// �����ڱ�<v1, v2>
		vexTable[v1].adjLink->Insert(curPos, v2);			// �����<v1, v2>
		edgeNum++;											// ��������1
	}
}

template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteEdge(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw Error("v1���ܵ���v2!");				// �׳��쳣

	int curPos = IndexHelp(vexTable[v1].adjLink, v2);	// ȡ��v2���ڽ������е�λ��
	if (curPos <= vexTable[v1].adjLink->Length())
	{	// ���ڱ�<v1, v2>
		vexTable[v1].adjLink->Delete(curPos, v2);		// ɾ��<v1,v2>
 		edgeNum--;										// �����Լ�1
	}
}

template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum) throw Error("v���Ϸ�!");	// �׳��쳣

	return tag[v];
}

template <class ElemType>
void AdjListDirGraph<ElemType>::SetTag(int v, StatusCode val) const
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum) throw Error("v���Ϸ�!");		// �׳��쳣

	tag[v] = val;
}

template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(const AdjListDirGraph<ElemType> &copy)
// ���������������ͼ���ڽӾ���copy����������ͼ���ڽӾ���copy�������ƹ��캯��
{
	int curPos;									// ��ʱ����
	vexNum = copy.vexNum;						// ���ƶ�����
	edgeNum = copy.edgeNum;						// ���Ʊ���

	tag = new StatusCode[vexNum];				// ���ɱ�־����
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// ���Ʊ�־����
		tag[curPos] = copy.tag[curPos];
	}

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// �����ڽӱ�
	for (curPos = 0; curPos < vexNum; curPos++)
	{	// �����ڽ�����
		vexTable[curPos].data = copy.vexTable[curPos].data;	// ���ƶ�������
		vexTable[curPos].adjLink = new LinkList<int>(*copy.vexTable[curPos].adjLink);	
	}
}

template <class ElemType>
AdjListDirGraph<ElemType> &AdjListDirGraph<ElemType>::operator =(const AdjListDirGraph<ElemType> &copy)
// ���������������ͼ���ڽӾ���copy��ֵ����ǰ����ͼ���ڽӾ��󡪡���ֵ�������
{
	if (&copy != this)
	{
		DestroyHelp();								// �ͷŵ�ǰ����ͼռ�ÿռ�

		int curPos;									// ��ʱ����
		vexNum = copy.vexNum;						// ���ƶ�����
		edgeNum = copy.edgeNum;						// ���Ʊ���

		tag = new StatusCode[vexNum];				// ���ɱ�־����
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// ���Ʊ�־����
			tag[curPos] = copy.tag[curPos];
		}

		vexTable = new AdjListGraphVexNode<ElemType>[vexNum];// �����ڽӱ�
		for (curPos = 0; curPos < vexNum; curPos++)
		{	// �����ڽ�����
			vexTable[curPos].data = copy.vexTable[curPos].data;	// ���ƶ�������
			vexTable[curPos].adjLink = new LinkList<int>(*copy.vexTable[curPos].adjLink);	
		}
	}
	return *this;
}

template <class ElemType>
void Display(const AdjListDirGraph<ElemType> &g, bool showVexElem = true)
// �������: ��ʾ�ڽӾ�������ͼ
{
	for (int v = 0; v < g.GetVexNum(); v++)
	{	// ��ʾ��v���ڽ�����
		cout << endl << v << "  ";							// ��ʾ�����
		if (showVexElem)
		{	// ��ʾ����Ԫ��
			ElemType e;										// ����Ԫ��
			g.GetElem(v, e);								// ȡ��Ԫ��ֵ
			cout << e << "  ";								// ��ʾ����Ԫ��
		}

		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
		{	// ��ʾ��v���ڽ������һ����㣨��ʾһ���ڽӵ㣩
			cout << "-->" << u; 
		}
		cout << endl; 
	}
}

#endif
