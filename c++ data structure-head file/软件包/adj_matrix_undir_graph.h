#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__

// ����ͼ���ڽӾ�����
template <class ElemType>
class AdjMatrixUndirGraph 
{
protected:
// �ڽӾ�������ݳ�Ա:
	int vexNum, edgeNum;						// ��������ͱ���
	int **Matrix;								// �ڽӾ���
	ElemType *elems;							// ��������
	mutable StatusCode *tag;					// ָ���־�����ָ��

// ��������
	void DestroyHelp();							// ��������ͼ,�ͷ�����ͼռ�õĿռ�

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	AdjMatrixUndirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);	
		// ��������Ԫ��es[],�������ΪvertexNum,����Ϊ0������ͼ
	AdjMatrixUndirGraph(int vertexNum = DEFAULT_SIZE);	
		// ���춥�����ΪvertexNum,����Ϊ0������ͼ
	~AdjMatrixUndirGraph();						// ��������
	StatusCode GetElem(int v, ElemType &e) const;// �󶥵��Ԫ��	
	StatusCode SetElem(int v, const ElemType &e);// ���ö����Ԫ��ֵ
	int GetVexNum() const;						// ���ض������			 
	int GetEdgeNum() const;						// ���ر���			 
	int FirstAdjVex(int v) const;				// ���ض���v�ĵ�һ���ڽӵ�			 
	int NextAdjVex(int v1, int v2) const;		// ���ض���v1�������v2����һ���ڽӵ�			 
	void InsertEdge(int v1, int v2);			// ���붥��Ϊv1��v2�ı�			 
	void DeleteEdge(int v1, int v2);			// ɾ������Ϊv1��v2�ı�			 
	StatusCode GetTag(int v) const;				// ���ض���v�ı�־		 
	void SetTag(int v, StatusCode val) const;	// ���ö���v�ı�־Ϊval		 
	AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &copy);	// ���ƹ��캯��
	AdjMatrixUndirGraph<ElemType> &operator =(const AdjMatrixUndirGraph<ElemType> &copy); 
		// ��ֵ�������
};

template <class ElemType>
void Display(const AdjMatrixUndirGraph<ElemType> &g, bool showVexElem);	// ��ʾ�ڽӾ�������ͼ


// ����ͼ���ڽӾ������ʵ�ֲ���
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum)
// �����������������Ԫ��es[],�������ΪvertexNum,����Ϊ0������ͼ
{
	if (vertexNum < 0)	throw Error("�����������Ϊ��!");// �׳��쳣

	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	elems = new ElemType[vexNum];				// ���ɶ������ݱ�����
	
	int u, v;									// ��ʱ���� 
	for (v = 0; v < vexNum; v++)
	{	// ��ʼ����־����
		elems[v] = es[v];
	}

	tag = new StatusCode[vexNum];				// ���ɱ�־����
	for (v = 0; v < vexNum; v++)
	{	// ��ʼ����־����
		tag[v] = UNVISITED;
	}

	Matrix = (int **)new int *[vexNum];// �����ڽӾ���
	for (v = 0; v < vexNum; v++)
	{	// �����ڽӾ������
		Matrix[v] = new int[vexNum];	
	}

	for (u = 0; u < vexNum; u++)
	{
		for (v = 0; v < vexNum; v++)
		{	// Ϊ�ڽӾ���Ԫ�ظ�ֵ
			Matrix[u][v] = 0;
		}
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(int vertexNum)
// ������������춥�����ΪvertexNum,����Ϊ0������ͼ
{
	if (vertexNum < 0)	throw Error("�����������Ϊ��!");// �׳��쳣

	vexNum = vertexNum;							// ������ΪvertexNum
	edgeNum = 0;								// ����Ϊ0

	elems = new ElemType[vexNum];				// ���ɶ������ݱ�����

	int u, v;									// ��ʱ���� 
	tag = new StatusCode[vexNum];				// ���ɱ�־����
	for (v = 0; v < vexNum; v++)
	{	// ��ʼ����־����
		tag[v] = UNVISITED;
	}

	Matrix = (int **)new int *[vexNum];// �����ڽӾ���
	for (v = 0; v < vexNum; v++)
	{	// �����ڽӾ������
		Matrix[v] = new int[vexNum];	
	}

	for (u = 0; u < vexNum; u++)
	{
		for (v = 0; v < vexNum; v++)
		{	// Ϊ�ڽӾ���Ԫ�ظ�ֵ
			Matrix[u][v] = 0;
		}
	}
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DestroyHelp()
// �����������������ͼ,�ͷ�����ͼռ�õĿռ�
{
	delete []elems;							// �ͷŶ�������
	delete []tag;								// �ͷű�־

	for (int iPos = 0; iPos < vexNum; iPos++)
	{	// �ͷ��ڽӾ������
		delete []Matrix[iPos];
	}
	delete []Matrix;							// �ͷ��ڽӾ���
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph()
// ����������ͷŶ�����ռ�ÿռ�
{
	DestroyHelp();
}

template <class ElemType>
StatusCode AdjMatrixUndirGraph<ElemType>::GetElem(int v, ElemType &e) const
// ����������󶥵�v��Ԫ��, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return NOT_PRESENT;	// Ԫ�ز�����
	}
	else
	{	// v�Ϸ�
		e = elems[v];		// ������v��Ԫ��ֵ����e
		return ENTRY_FOUND;	// Ԫ�ش���
	}
}	

template <class ElemType>
StatusCode AdjMatrixUndirGraph<ElemType>::SetElem(int v, const ElemType &e)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
	{	// v��Χ��
		return RANGE_ERROR;	// λ�ô�
	}
	else
	{	// v�Ϸ�
		elems[v] = e;		// ����Ԫ��
		return SUCCESS;		// �ɹ�
	}
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetVexNum() const
// ������������ض������			 
{
	return vexNum;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetEdgeNum() const
// ������������ر�������
{
	return edgeNum;
}		 

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�1���ڽӵ�			 
{
	if (v < 0 || v >= vexNum) throw Error("v���Ϸ�!");// �׳��쳣

	for (int cur = 0; cur < vexNum; cur++)
	{	// �����ڽӵ�
		if (Matrix[v][cur] != 0) return cur;
	}

	return -1;									// ����-1��ʾ���ڽӵ�
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����1���ڽӵ�			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw Error("v1���ܵ���v2!");				// �׳��쳣

	for (int cur = v2 + 1; cur < vexNum; cur++)
	{	// �����ڽӵ�
		if (Matrix[v1][cur] != 0) return cur;
	}

	return -1;									// ����-1��ʾ���ڽӵ�
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertEdge(int v1, int v2)
// ������������붥��Ϊv1��v2,ȨΪw�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw Error("v1���ܵ���v2!");				// �׳��쳣

	if (Matrix[v1][v2] == 0 && Matrix[v2][v1] == 0)
	{	// ԭ����ͼ�ޱ�(v1, v2),������������1
		edgeNum++;
	}
	Matrix[v1][v2] = 1;				// �޸�<v1, v2>��Ӧ���ڽӾ���Ԫ��ֵ
	Matrix[v2][v1] = 1;				// �޸�<v2, v1>��Ӧ���ڽӾ���Ԫ��ֵ
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteEdge(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�			 
{
	if (v1 < 0 || v1 >= vexNum) throw Error("v1���Ϸ�!");	// �׳��쳣
	if (v2 < 0 || v2 >= vexNum) throw Error("v2���Ϸ�!");	// �׳��쳣
	if (v1 == v2) throw Error("v1���ܵ���v2!");				// �׳��쳣

	if (Matrix[v1][v2] != 0 && Matrix[v2][v1] != 0)
	{	// ԭ����ͼ���ڱ�(v1, v2),ɾ��������Լ�1
		edgeNum--;
	}
	Matrix[v1][v2] = 0;				// �޸�<v1, v2>��Ӧ���ڽӾ���Ԫ��ֵ
	Matrix[v2][v1] = 0;				// �޸�<v2, v1>��Ӧ���ڽӾ���Ԫ��ֵ
}

template <class ElemType>
StatusCode AdjMatrixUndirGraph<ElemType>::GetTag(int v) const
// ������������ض���v�ı�־		 
{
	if (v < 0 || v >= vexNum) throw Error("v���Ϸ�!");	// �׳��쳣

	return tag[v];
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::SetTag(int v, StatusCode val) const 
// ������������ö���v�ı�־Ϊval		 
{
	if (v < 0 || v >= vexNum) throw Error("v���Ϸ�!");	// �׳��쳣

	tag[v] = val;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &copy)
// ���������������ͼ���ڽӾ���copy����������ͼ���ڽӾ���copy�������ƹ��캯��
{
	int iPos, jPos;								// ��ʱ����
	vexNum = copy.vexNum;						// ���ƶ�����
	edgeNum = copy.edgeNum;						// ���Ʊ���

	elems = new ElemType[vexNum];			// ���ɶ�����������
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// ���ƶ�����������
		elems[iPos] = copy.elems[iPos];
	}

	tag = new StatusCode[vexNum];				// ���ɱ�־����
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// ���Ʊ�־����
		tag[iPos] = copy.tag[iPos];
	}

	Matrix = (int **)new int *[vexNum];	// �����ڽӾ���
	for (iPos = 0; iPos < vexNum; iPos++)
	{	// �����ڽӾ������
		Matrix[iPos] = new int[vexNum];	
	}

	for (iPos = 0; iPos < vexNum; iPos++)
	{
		for (jPos = 0; jPos < vexNum; jPos++)
		{	// �����ڽӾ���Ԫ�ظ�ֵ
			Matrix[iPos][jPos] = copy.Matrix[iPos][jPos];
		}
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType> &AdjMatrixUndirGraph<ElemType>::operator =(const AdjMatrixUndirGraph<ElemType> &copy)
// ���������������ͼ���ڽӾ���copy��ֵ����ǰ����ͼ���ڽӾ��󡪡���ֵ�������
{
	if (&copy != this)
	{
		DestroyHelp();						// �ͷŵ�ǰ����ͼռ�ÿռ�
		int iPos, jPos;						// ��ʱ����
		vexNum = copy.vexNum;				// ���ƶ�����
		edgeNum = copy.edgeNum;				// ���Ʊ���

		elems = new ElemType[vexNum];		// ���ɶ�����������
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// ���ƶ�����������
			elems[iPos] = copy.elems[iPos];
		}

		tag = new StatusCode[vexNum];	// ���ɱ�־����
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// ���Ʊ�־����
			tag[iPos] = copy.tag[iPos];
		}

		Matrix = (int **)new int*[vexNum];	// �����ڽӾ���
		for (iPos = 0; iPos < vexNum; iPos++)
		{	// �����ڽӾ������
			Matrix[iPos] = new int[vexNum];	
		}

		for (iPos = 0; iPos < vexNum; iPos++)
		{
			for (jPos = 0; jPos < vexNum; jPos++)
			{	// �����ڽӾ���Ԫ�ظ�ֵ
				Matrix[iPos][jPos] = copy.Matrix[iPos][jPos];
			}
		}
	}
	return *this;
}

template <class ElemType>
void Display(const AdjMatrixUndirGraph<ElemType> &g, bool showVexElem = true)
// �������: ��ʾ�ڽӾ�������ͼ
{
	int **Matrix;							// �ڽӾ���
	Matrix = (int **)new int *[g.GetVexNum()];		// �����ڽӾ���
	int iPos;										// ��ʱ���� 

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// �����ڽӾ������
		Matrix[iPos] = new int[g.GetVexNum()];	
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{
		for (int jPos = 0; jPos < g.GetVexNum(); jPos++)
		{	// Ϊ�ڽӾ���Ԫ�ظ�ֵ
			Matrix[iPos][jPos] = 0;
		}
	}

	for (int v = 0; v < g.GetVexNum(); v++)
	{	// ��������ͼ��v���ڽӵ�
		for (int u = g.FirstAdjVex(v); u != -1; u = g.NextAdjVex(v, u))
		{	// uΪv���ڽӵ�
			Matrix[v][u] = 1;
		}
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// ��ʾ��
		if (showVexElem)
		{	// ��ʾ����Ԫ��
			ElemType e;					// ����Ԫ��
			g.GetElem(iPos, e);			// ȡ��Ԫ��ֵ
			cout << e;					// ��ʾԪ��ֵ
		}

		for (int jPos = 0; jPos < g.GetVexNum(); jPos++)
		{	// ��ʾԪ��
 			cout << "\t" << Matrix[iPos][jPos];
		}
		cout << endl;					// ���� 
	}

	for (iPos = 0; iPos < g.GetVexNum(); iPos++)
	{	// �ͷ��ڽӾ������
		delete []Matrix[iPos];
	}
	delete []Matrix;					// �ͷ��ڽӾ���
}

#endif
