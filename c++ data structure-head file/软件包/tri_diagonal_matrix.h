#ifndef __TRI_DIAGONAL_H__
#define __TRI_DIAGONAL_H__

// ���ԽǾ�����
template<class ElemType>
class TriDiagonalMatrix
{
protected:
//  ���ԽǾ�������ݳ�Ա:
	ElemType *elems;			// �洢����Ԫ��
	int n;						// ���ԽǾ������

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	TriDiagonalMatrix(int sz);	// ����һ��sz��sz�е����ԽǾ���
	~TriDiagonalMatrix();		// ��������
    int GetSize() const;		// �������ԽǾ������
	ElemType &operator()(int i, int j);	// ���غ��������
	TriDiagonalMatrix(const TriDiagonalMatrix<ElemType> &copy);		// ���ƹ��캯��
	TriDiagonalMatrix<ElemType> &operator =(const TriDiagonalMatrix<ElemType> &copy); 
		// ��ֵ�������
};

// ���ԽǾ������ʵ�ֲ���
template <class ElemType>
TriDiagonalMatrix<ElemType>::TriDiagonalMatrix(int sz)
// �������������һ��sz��sz�е����ԽǾ���
{
	if (sz < 1)							
		throw Error("������������Ч!");	// �׳��쳣
	n = sz;								// szΪ�������
	elems = new ElemType[3 * n - 1];	// ����洢�ռ�
}

template <class ElemType>
TriDiagonalMatrix<ElemType>::~TriDiagonalMatrix()
// ����������ͷ����ԽǾ�����ռ�ÿռ�
{
	if (elems != NULL) delete []elems; 
}

template <class ElemType>
int TriDiagonalMatrix<ElemType>::GetSize() const
// ����������������ԽǾ������
{
	return n;
}

template <class ElemType>
ElemType &TriDiagonalMatrix<ElemType>::operator()(int i, int j)
// ������������غ��������
{
	if (i < 1 || i > n || j < 1 || j > n)
		throw Error("�±����!");					// �׳��쳣
	if (i - j == 1)	return elems[2 * n + i - 2];	// Ԫ���ڵͶ�������
	else if (i - j == 0) return elems[n + i - 1];	// Ԫ��������������
	else if (i - j == -1) return elems[i];			// Ԫ���ڸ߶�������
	else return elems[0];							// Ԫ��������λ��
}

template <class ElemType>
TriDiagonalMatrix<ElemType>::TriDiagonalMatrix(const TriDiagonalMatrix<ElemType> &copy)
// ��������������ԽǾ���copy���������ԽǾ��󡪡����ƹ��캯��
{
	n = copy.n;							// �������ԽǾ������
	elems = new ElemType[3 * n - 1];	// Ϊ����Ԫ�ط���洢�ռ�
	for (int i = 0; i < 3 * n - 1; i++)
	{	// ��������Ԫ��ֵ
		elems[i] = copy.elems[i];
	}
}

template <class ElemType>
TriDiagonalMatrix<ElemType> &TriDiagonalMatrix<ElemType>::operator =(const TriDiagonalMatrix<ElemType> &copy)
// ��������������ԽǾ���copy��ֵ����ǰ���ԽǾ��󡪡���ֵ�������
{
	if (&copy != this)
	{
		if (elems != NULL) delete []elems;	// �ͷ�����Ԫ�ؿռ�

		n = copy.n;							// �������ԽǾ������
		elems = new ElemType[3 * n - 1];	// Ϊ����Ԫ�ط���洢�ռ�
		for (int i = 0; i < 3 * n - 1; i++)
		{	// ��������Ԫ��ֵ
			elems[i] = copy.elems[i];
		}
	}
	return *this;
}

#endif