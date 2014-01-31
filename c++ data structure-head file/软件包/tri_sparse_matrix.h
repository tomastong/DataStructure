#ifndef __TRI_SPARSE_MATRIX_H__
#define __TRI_SPARSE_MATRIX_H__

#include "triple.h"					// ��Ԫ����

// ϡ�������Ԫ��˳�����
template<class ElemType>
class TriSparseMatrix
{
protected:
// ϡ�������Ԫ��˳�������ݳ�Ա:
	Triple<ElemType> *triElems;		// �洢ϡ��������Ԫ���
	int maxSize;					// ����Ԫ��������
	int rows, cols, num;			// ϡ����������,����������Ԫ����

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	TriSparseMatrix(int rs = DEFAULT_SIZE, int cs = DEFAULT_SIZE, int size = DEFAULT_SIZE);
		// ����һ��rs��cs�з���Ԫ��������Ϊsize�Ŀ�ϡ�����
	~TriSparseMatrix();				// ��������
    int GetRows() const;			// ����ϡ���������
    int GetCols() const;			// ����ϡ���������
    int GetNum() const;				// ����ϡ��������Ԫ����
	StatusCode SetElem(int r, int c, const ElemType &v);	// ����ָ��λ�õ�Ԫ��ֵ
	StatusCode GetElem(int r, int c, ElemType &v);			// ��ָ��λ�õ�Ԫ��ֵ
	TriSparseMatrix(const TriSparseMatrix<ElemType> &copy);	// ���ƹ��캯��
	TriSparseMatrix<ElemType> &operator =(const TriSparseMatrix<ElemType> &copy); 
		// ��ֵ���������
	static void SimpleTranspose(const TriSparseMatrix<ElemType> &source, 
		TriSparseMatrix<ElemType> &dest);// ��ϡ�����sourceת�ó�ϡ�����dest�ļ��㷨
	static void FastTranspose(const TriSparseMatrix<ElemType> &source, 
		TriSparseMatrix<ElemType> &dest);// ��ϡ�����sourceת�ó�ϡ�����dest�Ŀ����㷨
};

// ϡ�������Ԫ��˳������ʵ�ֲ���
template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(int rs, int cs, int size)
// ��������� ����һ��rs��cs�з���Ԫ��������Ϊsize�Ŀ�ϡ�����
{
	if (rs < 1 || cs < 1)							
		throw Error("������������Ч!");	// �׳��쳣
	maxSize = size;						// ����Ԫ��������
	rows = rs;							// ����
	cols = cs;							// ����
	num = 0;							// ����Ԫ�ظ���
	triElems = new Triple<ElemType>[maxSize];	// ����洢�ռ�
} 

template <class ElemType>
TriSparseMatrix<ElemType>::~TriSparseMatrix()
// ���������ϡ�������ռ�ÿռ�
{
	if (triElems != NULL) delete []triElems; // �ͷŴ洢�ռ�
}

template <class ElemType>
int TriSparseMatrix<ElemType>::GetRows() const
// �������������ϡ���������
{
	return rows;					// ��������
}

template <class ElemType>
int TriSparseMatrix<ElemType>::GetCols() const
// �������������ϡ���������
{
	return cols;					// ��������
}

template <class ElemType>
int TriSparseMatrix<ElemType>::GetNum() const
// �������������ϡ��������Ԫ����
{
	return num;						// ���ط���Ԫ����
}

template <class ElemType>
StatusCode TriSparseMatrix<ElemType>::SetElem(int r, int c, const ElemType &v)
// �������������±귶Χ��,�򷵻�RANGE_ERROR,������,�򷵻�OVER_FLOW,����
//	��SUCCESS
{
	if (r > rows || c > cols || r < 1 || c < 1)
		return RANGE_ERROR;					// �±귶Χ��
	
	int i, j;								// ��������
	for (j = num - 1; j >= 0 && 
		(r < triElems[j].row || r == triElems[j].row && c < triElems[j].col); j--);// ������Ԫ��λ��

	if (j >= 0 && triElems[j].row == r && triElems[j].col == c)
	{	// �ҵ���Ԫ��
		if (v == 0)
		{	// ɾ����Ԫ��
			for (i = j + 1; i < num; i++)
				triElems[i - 1] = triElems[i];	// ǰ�ƴ�j+1��ʼ����Ԫ��
			num--;								// ɾ����Ԫ���,����Ԫ�����Լ�1
		}
		else
		{	// �޸�Ԫ��ֵ
			triElems[j].value = v;
		}
		return SUCCESS;						// �ɹ�
	}
	else if (v != 0)
	{	
		if (num < maxSize)
		{	// ����Ԫ��(r, c, v)���뵽��Ԫ�����
			for (i = num - 1; i > j; i--)
			{	// ����Ԫ��	
				triElems[i + 1] = triElems[i];
			}
			// j + 1Ϊ�ճ��Ĳ���λ��
			triElems[j + 1].row = r;		// ��
			triElems[j + 1].col = c;		// ��
			triElems[j + 1].value = v;		// ����Ԫ��ֵ
			num++;							// ������Ԫ���,����Ԫ�����Լ�1
			return SUCCESS;					// �ɹ�
		}
		else
		{	// ���
			return OVER_FLOW;				// ���ʱ����OVER_FLOW
		}
	}
	return SUCCESS;							// �ɹ�
}

template <class ElemType>
StatusCode TriSparseMatrix<ElemType>::GetElem(int r, int c, ElemType &v)
// �������������±귶Χ��,�򷵻�RANGE_ERROR,���򷵻�SUCCESS,����v����ָ��λ��Ԫ��ֵ
{
	if (r > rows || c > cols || r < 1 || c < 1)
		return RANGE_ERROR;			// �±귶Χ��

	int j;							// ��������

	
	for (j = num - 1; j >= 0 && 
		(r < triElems[j].row || r == triElems[j].row && c < triElems[j].col); j--);// ����ָ��λ�õ���Ԫ��
	
	if (j >= 0 && triElems[j].row == r && triElems[j].col == c)
	{	// �ҵ���Ԫ��
		v = triElems[j].value;		// ��v����ָ��λ��Ԫ��ֵ
	}
	else
	{	// δ�ҵ���Ԫ��
		v = 0;						// δ�ҵ���Ԫ��,��ʾ0Ԫ��ֵ
	}
	return SUCCESS;					// �ɹ�
}

template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(const TriSparseMatrix<ElemType> &copy)
// �����������ϡ�����copy������ϡ����󡪡����ƹ��캯��
{
	maxSize = copy.maxSize;							// ������Ԫ�ظ���
	triElems = new Triple<ElemType>[maxSize];		// ����洢�ռ�
	rows = copy.rows;								// ��������
	cols = copy.cols;								// ��������
	num = copy.num;									// ���Ʒ���Ԫ�ظ���
	triElems = new Triple<ElemType>[maxSize];		// Ϊ��Ԫ�����洢�ռ�
	for (int i = 0; i < num; i++)
	{	// ������Ԫ��
		triElems[i] = copy.triElems[i];
	}
}

template <class ElemType>
TriSparseMatrix<ElemType> &TriSparseMatrix<ElemType>::operator =(const TriSparseMatrix<ElemType> &copy)
// �����������ϡ�����copy��ֵ����ǰϡ����󡪡���ֵ���������
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;						// ������Ԫ�ظ���
		if (triElems != NULL) delete []triElems;	// �ͷŴ洢�ռ�
		triElems = new Triple<ElemType>[maxSize];	// ����洢�ռ�
		rows = copy.rows;							// ��������
		cols = copy.cols;							// ��������
		num = copy.num;								// ���Ʒ���Ԫ�ظ���

		for (int i = 0; i < num; i++)
		{	// ������Ԫ��
			triElems[i] = copy.triElems[i];
		}
	}
	return *this;
}

template<class ElemType>
void TriSparseMatrix<ElemType>::SimpleTranspose(const TriSparseMatrix<ElemType> &source, 
	TriSparseMatrix<ElemType> &dest)
// �����������ϡ�����sourceת�ó�ϡ�����dest�ļ��㷨
{
	dest.rows = source.cols;							// ����
	dest.cols = source.rows;							// ����
	dest.num = source.num;								// ����Ԫ�ظ���
	dest.maxSize = source.maxSize;						// ������Ԫ�ظ���
	delete []dest.triElems;								// �ͷŴ洢�ռ�
	dest.triElems = new Triple<ElemType>[dest.maxSize];	// ����洢�ռ�

	if (dest.num > 0)
	{
		int destPos = 0;								// ϡ�����dest����һ����Ԫ��Ĵ��λ��
		for (int col = 1; col <= source.cols; col++)
		{	// ת��ǰ���б�Ϊת�ú����
			for (int sourcePos = 0; sourcePos < source.num; sourcePos++)
			{	// ���ҵ�col�е���Ԫ��
				if (source.triElems[sourcePos].col == col)
				{	// �ҵ���col�е�һ����Ԫ��,ת�ú����dest
					dest.triElems[destPos].row = source.triElems[sourcePos].col;	// �б���
					dest.triElems[destPos].col = source.triElems[sourcePos].row;	// �б���
					dest.triElems[destPos].value = source.triElems[sourcePos].value;
						// ����Ԫ��ֵ����
					destPos++;														// ����һ��Ԫ�صĴ��λ��
				}
			}
		}
	}
}

template<class ElemType>
void TriSparseMatrix<ElemType>::FastTranspose(const TriSparseMatrix<ElemType> &source, 
	TriSparseMatrix<ElemType> &dest)
// �����������ϡ�����sourceת�ó�ϡ�����dest�Ŀ����㷨
{
	dest.rows = source.cols;							// ����
	dest.cols = source.rows;							// ����
	dest.num = source.num;								// ����Ԫ�ظ���
	dest.maxSize = source.maxSize;						// ������Ԫ�ظ���
	delete []dest.triElems;								// �ͷŴ洢�ռ�
	dest.triElems = new Triple<ElemType>[dest.maxSize];	// ����洢�ռ�

	int *cNum = new int[source.cols + 1];				// sourceÿһ�еķ���Ԫ����
	int *cPos = new int[source.cols + 1];				// sourceÿһ�еĵ�һ������Ԫ��dest�еĴ洢λ��
	int col;											// ��
	int sourcePos;										// ϡ�����source��Ԫ��ı��λ��

	if (dest.num > 0)
	{
		for (col = 1; col <= source.cols; col++) cNum[col] = 0;	// ��ʼ��cNum
		for (sourcePos = 0; sourcePos < source.num; sourcePos++)
			++cNum[source.triElems[sourcePos].col];		// ͳ��sourceÿһ�еķ���Ԫ����
		cPos[1] = 0;									// ��һ�еĵ�һ������Ԫ��dest�洢����ʼλ��
		for (col = 2; col <= source.cols; col++)
		{	// ѭ����ÿһ�еĵ�һ������Ԫ��dest�洢����ʼλ��
			cPos[col] = cPos[col - 1] + cNum[col - 1];	
		}

		for (sourcePos = 0; sourcePos < source.num; sourcePos++)
		{	// ѭ������source����Ԫ��
			int destPos = cPos[source.triElems[sourcePos].col];	
				// ���ڱ�ʾdest��ǰ�е���һ������Ԫ��Ԫ��Ĵ洢λ��
			dest.triElems[destPos].row = source.triElems[sourcePos].col;		// �б���
			dest.triElems[destPos].col = source.triElems[sourcePos].row;		// �б���
			dest.triElems[destPos].value = source.triElems[sourcePos].value;	// ����Ԫ��ֵ����
			++cPos[source.triElems[sourcePos].col];				
				// dest��ǰ�е���һ������Ԫ��Ԫ��Ĵ洢��λ��
		}
	}

	delete []cNum;										// �ͷ�cNum
	delete []cPos;										// �ͷ�cPos
}


#endif
