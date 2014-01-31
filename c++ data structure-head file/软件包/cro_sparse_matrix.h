#ifndef __CRO_SPARSE_MATRIX_H__
#define __CRO_SPARSE_MATRIX_H__

#include "cro_node.h"				// ʮ��������Ԫ������
#include "triple.h"					// ��Ԫ����

// ϡ�����ʮ��������
template<class ElemType>
class CLkSparseMatrix
{
protected:
//  ϡ�����ʮ���������ݳ�Ա:
	CLkTriNode<ElemType> **rightHead, **downHead;// ���������ͷ����
	int rows, cols, num;			// ϡ����������,����������Ԫ����

// ��������
	void DestroyHelp();					// ���ϡ�����
	StatusCode InsertHelp(const Triple<ElemType> &e);	// ����ʮ��������Ԫ����

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	CLkSparseMatrix(int rs = DEFAULT_SIZE, int cs = DEFAULT_SIZE);
		// ����һ��rs��cs�еĿ�ϡ�����
	~CLkSparseMatrix();				// ��������
	int GetRows() const;			// ����ϡ���������
    int GetCols() const;			// ����ϡ���������
    int GetNum() const;				// ����ϡ��������Ԫ����
	StatusCode SetElem(int r, int c, const ElemType &v);	// ����ָ��λ�õ�Ԫ��ֵ
	StatusCode GetElem(int r, int c, ElemType &v);			// ��ָ��λ�õ�Ԫ��ֵ
	CLkSparseMatrix(const CLkSparseMatrix<ElemType> &copy);	// ���ƹ��캯��
	CLkSparseMatrix<ElemType> &operator =(const CLkSparseMatrix<ElemType> &copy); 
		// ��ֵ�������
};

// ϡ�����ʮ���������ʵ�ֲ���
template <class ElemType>
CLkSparseMatrix<ElemType>::CLkSparseMatrix(int rs, int cs)
// �������������һ��rs��cs�еĿ�ϡ�����
{
	if (rs < 1 || cs < 1)							
		throw Error("������������Ч!");	// �׳��쳣
	rows = rs;							// ����
	cols = cs;							// ����
	num = 0;							// ����Ԫ����
	rightHead = new CLkTriNode<ElemType> *[rows + 1];	// �����������ͷ����洢�ռ�
	downHead = new CLkTriNode<ElemType> *[cols + 1];	// �����������ͷ����洢�ռ�
	for (int row = 1; row <= rows; row++) 
		rightHead[row] = NULL;			// ��ʼ���������ͷ����
	for (int col = 1; col <= cols; col++) 
		downHead[col] = NULL;			// ��ʼ���������ͷ����
}

template <class ElemType>
void CLkSparseMatrix<ElemType>::DestroyHelp()
// ������������ϡ�����
{
	for (int row = 1; row <= rows; row++)
	{	// �ͷŵ�row�еĽ�������ÿռ�
		if (rightHead[row] != NULL)
		{
			CLkTriNode<ElemType> *tmpPtr =  rightHead[row];	// ָ���row�е��׽��	
			rightHead[row] = tmpPtr->right;					// ��row���׽���ΪtmpPtr���
			delete tmpPtr;				// �ͷ�ԭ��row���׽��
		}
	}

	delete []rightHead;					// �ͷ��������ͷ����
	delete []downHead;					// �ͷ��������ͷ����
}

template <class ElemType>
CLkSparseMatrix<ElemType>::~CLkSparseMatrix()
// ���������ϡ�������ռ�ÿռ�
{
	DestroyHelp();
}

template <class ElemType>
int CLkSparseMatrix<ElemType>::GetRows() const
// �������������ϡ���������
{
	return rows;						// ��������
}

template <class ElemType>
int CLkSparseMatrix<ElemType>::GetCols() const
// �������������ϡ���������
{
	return cols;						// ��������
}

template <class ElemType>
int CLkSparseMatrix<ElemType>::GetNum() const
// �������������ϡ��������Ԫ����
{
	return num;							// ���ط���Ԫ����
}

template <class ElemType>
StatusCode CLkSparseMatrix<ElemType>::SetElem(int r, int c, const ElemType &v)
// �������������±귶Χ��,�򷵻�RANGE_ERROR,���򷵻�SUCCESS
{
	if (r > rows || c > cols || r < 1 || c < 1)
		return RANGE_ERROR;				// �±귶Χ��
	
	CLkTriNode<ElemType> *pre, *p;
	Triple<ElemType> e(r, c, v);		// ��Ԫ��

	CLkTriNode<ElemType> *ePtr = new CLkTriNode<ElemType>(e);//���ɽ��

	if (rightHead[r] == NULL ||  rightHead[r]->triElem.col >= c)
	{	// ePtr���ڵ�row������ı�ͷ��
		ePtr->right = rightHead[r];	 
		rightHead[r] = ePtr;
	}
	else
	{	// Ѱ���ڵ�r�������е���Ԫ��λ��
		pre = NULL; p=rightHead[r];	// ��ʼ��p��pre
		while (p != NULL && p->triElem.col < c)
		{	// p��pre����
			pre = p;	p = p->right;
		}

		if (p != NULL && p->triElem.row == r && p->triElem.col == c)
		{	// �ҵ���Ԫ��
			if (v != 0)
			{	// ���÷���Ԫ��ֵ
				p->triElem.value = v;
				delete ePtr;			// �ͷ�ePtr
				return SUCCESS;
			}
			else
			{	// ɾ�����
				pre->right = p->right;
			}
		}
		else
		{	// ��ePtr������p��pre֮��
			pre->right = ePtr;	ePtr->right = p;	
		}
	}

	if (downHead[c] == NULL || downHead[c]->triElem.row >= r)
	{	// ePtr���ڵ�c������ı�ͷ��
		ePtr->down = downHead[c];	 
		downHead[c] = ePtr;
		num++;							// ������,����Ԫ�ظ����Լ�1
	}
	else
	{	// Ѱ���ڵ�col�������е���Ԫ��λ��
		pre = NULL; p=downHead[c];	// ��ʼ��p��pre
		while (p != NULL && p->triElem.row < r)
		{	// p��pre����
			pre = p;	p = p->down;
		}
		if (p != NULL && p->triElem.row == r && p->triElem.col == c)
		{	// �ҵ���Ԫ��
			if (v != 0)
			{	// ���÷���Ԫ��ֵ
				p->triElem.value = v;
				delete ePtr;			// �ͷ�ePtr
			}
			else
			{	// ɾ�����
				pre->down = p->down;
				delete p; delete ePtr;	// �ͷŴ洢�ռ�
				num++;					// ɾ�����,����Ԫ�ظ����Լ�1
			}
		}
		else
		{	// ��ePtr������p��pre֮��
			pre->down = ePtr;	ePtr->down = p;	
		}
		num++;							// ������,����Ԫ�ظ����Լ�1
	}

	return SUCCESS;							// �ɹ�
}

template <class ElemType>
StatusCode CLkSparseMatrix<ElemType>::GetElem(int r, int c, ElemType &v)
// �������������±귶Χ��,�򷵻�RANGE_ERROR,���򷵻�SUCCESS,����v����ָ��λ��Ԫ��ֵ
{
	if (r > rows || c > cols || r < 1 || c < 1)
		return RANGE_ERROR;			// �±귶Χ��
	
	CLkTriNode<ElemType> *p;
	for (p=rightHead[r]; p != NULL && p->triElem.col < c; p = p->right);
		// Ѱ���ڵ�r�������е���Ԫ��λ��
	if (p != NULL && p->triElem.row == r && p->triElem.col == c)
	{	// �ҵ���Ԫ��
		v = p->triElem.value;
	}
	else
	{	// δ�ҵ���Ԫ��
		v = 0;						// ������ָ��λ��(r, c)����Ԫ��,��ʾ0Ԫ��
	}

	return SUCCESS;					// �ɹ�
}

template <class ElemType>
StatusCode CLkSparseMatrix<ElemType>::InsertHelp(const Triple<ElemType> &e)
// �������������±귶Χ��,�򷵻�RANGE_ERROR,�����Ԫ���±��ظ�,�򷵻�
//	DUPLICATE_ERROR,�������ɹ�,�򷵻�SUCCESS
{
	if (e.row > rows || e.col > cols || e.row < 1 || e.col < 1)
		return RANGE_ERROR;				// �±귶Χ��
		return RANGE_ERROR;				// �±귶Χ��
	
	CLkTriNode<ElemType> *pre, *p;
	int row = e.row, col = e.col;

	CLkTriNode<ElemType> *ePtr = new CLkTriNode<ElemType>(e);

	// ��ePtr�����row��������ʵ�λ��
	if (rightHead[row] == NULL ||  rightHead[row]->triElem.col >= col)
	{	// ePtr���ڵ�row������ı�ͷ��
		ePtr->right = rightHead[row];	 
		rightHead[row] = ePtr;
	}
	else
	{	// Ѱ���ڵ�row�������еĲ���λ��
		pre = NULL; p=rightHead[row];	// ��ʼ��p��pre
		while (p != NULL && p->triElem.col < col)
		{	// p��pre����
			pre = p;	p = p->right;
		}
		if (p != NULL && p->triElem.row == row && p->triElem.col == col)
		{	// ��Ԫ���±��ظ�
			return DUPLICATE_ERROR;			
		}
		pre->right = ePtr;	ePtr->right = p;	// ��ePtr������p��pre֮��
	}

	// ��ePtr�����ڵ�col��������ʵ�λ��
	if (downHead[col] == NULL || downHead[col]->triElem.row >= row)
	{	// ePtr���ڵ�col������ı�ͷ��
		ePtr->down = downHead[col];	 
		downHead[col] = ePtr;
	}
	else
	{	// Ѱ���ڵ�col�������еĲ���λ��
		pre = NULL; p=downHead[col];	// ��ʼ��p��pre
		while (p != NULL && p->triElem.row < row)
		{	// p��pre����
			pre = p;	p = p->down;
		}
		if (p != NULL && p->triElem.row == row && p->triElem.col == col)
		{	// ��Ԫ���±��ظ�
			return DUPLICATE_ERROR;			
		}
		pre->down = ePtr;	ePtr->down = p;	// ��ePtr������p��pre֮��
	}

	num++;								// ����Ԫ�ظ����Լ�1
	return SUCCESS;						// ����ɹ�
}

template <class ElemType>
CLkSparseMatrix<ElemType>::CLkSparseMatrix(const CLkSparseMatrix<ElemType> &copy)
// �����������ϡ�����copy������ϡ����󡪡����ƹ��캯��
{
	rows = copy.rows;					// ��������
	cols = copy.cols;					// ��������
	num = 0;							// ��ʼ������Ԫ����
	rightHead = new CLkTriNode<ElemType> *[rows + 1];	// �����������ͷ����洢�ռ�
	downHead = new CLkTriNode<ElemType> *[cols + 1];	// �����������ͷ����洢�ռ�
	int row;											// �� 
	int col;											// �� 
	for (row = 1; row <= rows; row++) 
		rightHead[row] = NULL;			// ��ʼ���������ͷ����
	for (col = 1; col <= cols; col++) 
		downHead[col] = NULL;			// ��ʼ���������ͷ����
	
	for (row = 1; row <= rows; row++)
	{	// ���Ƶ�row�е���Ԫ��
		for (CLkTriNode<ElemType> *p = copy.rightHead[row]; p != NULL; p = p->right)
		{	// ���Ƶ�row�е���Ԫ��
			InsertHelp(p->triElem);
		}
	}
}

template <class ElemType>
CLkSparseMatrix<ElemType> &CLkSparseMatrix<ElemType>::operator =(const CLkSparseMatrix<ElemType> &copy)
// �����������ϡ�����copy��ֵ����ǰϡ����󡪡���ֵ�������
{
	if (&copy != this)
	{
		DestroyHelp();						// ���ϡ�����

		rows = copy.rows;				// ��������
		cols = copy.cols;				// ��������
		num = 0;						// ��ʼ������Ԫ����
		rightHead = new CLkTriNode<ElemType> *[rows + 1];	// �����������ͷ����洢�ռ�
		downHead = new CLkTriNode<ElemType> *[cols + 1];	// �����������ͷ����洢�ռ�
		int row;											// �� 
		int col;											// �� 
		for (row = 1; row <= rows; row++) 
			rightHead[row] = NULL;			// ��ʼ���������ͷ����
		for (col = 1; col <= cols; col++) 
			downHead[col] = NULL;			// ��ʼ���������ͷ����

		for (row = 1; row <= rows; row++)
		{	// ���Ƶ�row�е���Ԫ��
			for (CLkTriNode<ElemType> *p = copy.rightHead[row]; p != NULL; p = p->right)
			{	// ���Ƶ�row�е���Ԫ��
				InsertHelp(p->triElem);
			}
		}
	}
	return *this;
}
#endif
