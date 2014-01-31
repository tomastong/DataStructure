#ifndef __MATRIX_H__
#define __MATRIX_H__

// ������
template<class ElemType>
class Matrix
{
protected:
//  ��������ݳ�Ա:
	ElemType *elems;		// �洢֪��Ԫ��
	int rows, cols;			// ��������������

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	Matrix(int rs, int cs);	// ����һ��rs��cs�еľ���
	~Matrix();				// ��������
	int GetRows() const;	// ���ؾ�������
	int GetCols() const;	// ���ؾ�������
	ElemType &operator()(int i, int j);			// ���غ��������
	Matrix(const Matrix<ElemType> &copy);		// ���ƹ��캯��
	Matrix<ElemType> &operator =(const Matrix<ElemType> &copy); // ��ֵ�������
};

// ���Խ����ʵ�ֲ���
template <class ElemType>
Matrix<ElemType>::Matrix(int rs, int cs)
// �������������һ��rs��cs�еľ���
{
	if (rs < 1 && cs < 1)	
		throw Error("������������Ч!");	// �׳��쳣
	rows = rs;				// rsΪ����
	cols = cs;				// csΪ����
	elems = new ElemType[rows * cols];	// ����洢�ռ�
}

template <class ElemType>
Matrix<ElemType>::~Matrix()
// ����������ͷž�����ռ�ÿռ�
{
	if (elems != NULL) delete []elems; 
}

template <class ElemType>
int Matrix<ElemType>::GetRows() const
// ������������ؾ�������
{
	return rows;
}

template <class ElemType>
int Matrix<ElemType>::GetCols() const
// ������������ؾ�������
{
	return cols;
}

template <class ElemType>
ElemType &Matrix<ElemType>::operator()(int i, int j)
// ������������غ��������
{
	if (i < 1 || i > rows || j < 1 || j > cols)	
		throw Error("�±����!");			// �׳��쳣
	return elems[(i - 1) * cols + j - 1];	// ����Ԫ��
}

template <class ElemType>
Matrix<ElemType>::Matrix(const Matrix<ElemType> &copy)
// ����������ɾ���copy�����¾��󡪡����ƹ��캯��
{
	rows = copy.rows;		// ��������
	cols = copy.cols;		// ��������
	elems = new ElemType[rows * cols];	// Ϊ����Ԫ�ط���洢�ռ�
	for (int i = 0; i < rows * cols; i++)
	{	// ��������Ԫ��ֵ
		elems[i] = copy.elems[i];
	}
}

template <class ElemType>
Matrix<ElemType> &Matrix<ElemType>::operator =(const Matrix<ElemType> &copy)
// ���������������copy��ֵ����ǰ���󡪡���ֵ�������
{
	if (&copy != this)
	{
		if (elems != NULL) delete []elems;	// �ͷ�����Ԫ�ؿռ�

		rows = copy.rows;		// ��������
		cols = copy.cols;		// ��������
		elems = new ElemType[rows * cols];	// Ϊ����Ԫ�ط���洢�ռ�
		for (int i = 0; i < rows * cols; i++)
		{	// ��������Ԫ��ֵ
			elems[i] = copy.elems[i];
		}
	}
	return *this;
}

#endif