#ifndef __LOWER_TRIANGULAR_MATRIX_H__
#define __LOWER_TRIANGULAR_MATRIX_H__

// �����Ǿ�����
template<class ElemType>
class LowerTriangularMatrix
{
protected:
//  �����Ǿ�������ݳ�Ա:
	ElemType *elems;				// �洢����Ԫ��
	int n;							// �����Ǿ������

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	LowerTriangularMatrix(int sz);	// ����һ��sz��sz�е������Ǿ���
	~LowerTriangularMatrix();		// ��������
	int GetSize() const;			//���������Ǿ������
	ElemType &operator()(int i, int j);	// ���غ��������
	LowerTriangularMatrix(const LowerTriangularMatrix<ElemType> &copy);		// ���ƹ��캯��
	LowerTriangularMatrix<ElemType> &operator =(const LowerTriangularMatrix<ElemType> &copy); 
		// ��ֵ�������
};

// �����Ǿ������ʵ�ֲ���
template <class ElemType>
LowerTriangularMatrix<ElemType>::LowerTriangularMatrix(int sz)
// �������������һ��sz��sz�е������Ǿ���
{
	if (sz < 1)							
		throw Error("������������Ч!");	// �׳��쳣
	n = sz;								// szΪ�������
	elems = new ElemType[n * (n + 1) / 2 + 1];	// ����洢�ռ�
}

template <class ElemType>
LowerTriangularMatrix<ElemType>::~LowerTriangularMatrix()
// ����������ͷ������Ǿ�����ռ�ÿռ�
{
	if (elems != NULL) delete []elems; 
}

template <class ElemType>
int LowerTriangularMatrix<ElemType>::GetSize() const
// ������������������Ǿ������
{
	return n;
}

template <class ElemType>
ElemType &LowerTriangularMatrix<ElemType>::operator()(int i, int j)
// ������������غ��������
{
	if (i < 1 || i > n || j < 1 || j > n)	
		throw Error("�±����!");					// �׳��쳣
	if (i >= j)	return elems[i * (i - 1) / 2 + j];	// Ԫ������������
	else return elems[0];							// Ԫ��������λ��
}

template <class ElemType>
LowerTriangularMatrix<ElemType>::LowerTriangularMatrix(const LowerTriangularMatrix<ElemType> &copy)
// ����������������Ǿ���copy�����������ԽǾ��󡪡����ƹ��캯��
{
	n = copy.n;							// ���������ԽǾ������
	elems = new ElemType[n * (n + 1) / 2 + 1];	// Ϊ����Ԫ�ط���洢�ռ�
	for (int i = 0; i < n * (n + 1) / 2 + 1; i++)
	{	// ��������Ԫ��ֵ
		elems[i] = copy.elems[i];
	}
}

template <class ElemType>
LowerTriangularMatrix<ElemType> &LowerTriangularMatrix<ElemType>::operator =(const LowerTriangularMatrix<ElemType> &copy)
// ����������������Ǿ���copy��ֵ����ǰ�����ԽǾ��󡪡���ֵ�������
{
	if (&copy != this)
	{
		if (elems != NULL) delete []elems;	// �ͷ�����Ԫ�ؿռ�

		n = copy.n;							// ���������Ǿ������
		elems = new ElemType[n * (n + 1) / 2 + 1];	// Ϊ����Ԫ�ط���洢�ռ�
		for (int i = 0; i < n * (n + 1) / 2 + 1; i++)
		{	// ��������Ԫ��ֵ
			elems[i] = copy.elems[i];
		}
	}
	return *this;
}

#endif