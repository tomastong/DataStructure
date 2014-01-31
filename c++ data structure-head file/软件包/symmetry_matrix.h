#ifndef __SYMMETRY_MATRIX_H__
#define __SYMMETRY_MATRIX_H__

// �Գƾ�����
template<class ElemType>
class SymmtryMatrix
{
protected:
//  �Գƾ�������ݳ�Ա:
	ElemType *elems;			// �洢����Ԫ��
	int n;						// �Գƾ������

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SymmtryMatrix(int sz);		// ����һ��sz��sz�еĶԳƾ���
	~SymmtryMatrix();			// ��������
	int GetSize() const;		// ���ضԳƾ������
	ElemType &operator()(int i, int j);	// ���غ��������
	SymmtryMatrix(const SymmtryMatrix<ElemType> &copy);		// ���ƹ��캯��
	SymmtryMatrix<ElemType> &operator =(const SymmtryMatrix<ElemType> &copy); 
		// ��ֵ�������
};

// �Գƾ������ʵ�ֲ���
template <class ElemType>
SymmtryMatrix<ElemType>::SymmtryMatrix(int sz)
// �������������һ��sz��sz�еĶԳƾ���
{
	if (sz < 1)							
		throw Error("������������Ч!");	// �׳��쳣
	n = sz;								// szΪ�������
	elems = new ElemType[n * (n + 1) / 2];	// ����洢�ռ�
}

template <class ElemType>
SymmtryMatrix<ElemType>::~SymmtryMatrix()
// ����������ͷŶԳƾ�����ռ�ÿռ�
{
	if (elems != NULL) delete []elems; 
}

template <class ElemType>
int SymmtryMatrix<ElemType>::GetSize() const
// ������������ضԳƾ������
{
	return n;
}

template <class ElemType>
ElemType &SymmtryMatrix<ElemType>::operator()(int i, int j)
// ������������غ��������
{
	if (i < 1 || i > n || j < 1 || j > n)	
		throw Error("�±����!");						// �׳��쳣
	if (i >= j)	return elems[i * (i - 1) / 2 + j - 1];	// Ԫ������������
	else return elems[j * (j - 1) / 2 + i - 1];			// Ԫ������������
}

template <class ElemType>
SymmtryMatrix<ElemType>::SymmtryMatrix(const SymmtryMatrix<ElemType> &copy)
// ������������¶Գƾ���copy����Գƾ�����󡪡����ƹ��캯��
{
	n = copy.n;							// ���ƶԳƾ���������
	elems = new ElemType[n * (n + 1) / 2];	// Ϊ����Ԫ�ط���洢�ռ�
	for (int i = 0; i < n * (n + 1) / 2; i++)
	{	// ��������Ԫ��ֵ
		elems[i] = copy.elems[i];
	}
}

template <class ElemType>
SymmtryMatrix<ElemType> &SymmtryMatrix<ElemType>::operator =(const SymmtryMatrix<ElemType> &copy)
// ������������Գƾ���copy��ֵ����ǰ�Գƾ�����󡪡���ֵ�������
{
	if (&copy != this)
	{
		if (elems != NULL) delete []elems;	// �ͷ�����Ԫ�ؿռ�

		n = copy.n;							// ���ƶԳƾ���������
		elems = new ElemType[n * (n + 1) / 2];	// Ϊ����Ԫ�ط���洢�ռ�
		for (int i = 0; i < n * (n + 1) / 2; i++)
		{	// ��������Ԫ��ֵ
			elems[i] = copy.elems[i];
		}
	}
	return *this;
}

#endif