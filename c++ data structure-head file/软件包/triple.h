#ifndef __TRIPLE_H__
#define __TRIPLE_H__

// ��Ԫ����
template<class ElemType>
struct Triple
{
// ���ݳ�Ա:
	int row, col;						// ����Ԫ�ص����±������±�
	ElemType value;						// ����Ԫ�ص�ֵ

// ���캯��:
	Triple();							// �޲����Ĺ��캯��
	Triple(int r, int c, ElemType v);	// ��֪����������Ԫ��
};

// ��Ԫ�����ʵ�ֲ���
template<class ElemType>
Triple<ElemType>::Triple()
// ����������������Ԫ��
{
}

template<class ElemType>
Triple<ElemType>::Triple(int r, int c, ElemType v)
// �������������֪������������Ԫ��
{
	row = r;							// �к�
	col = c;							// �к�
	value = v;							// ����Ԫ��ֵ
}

#endif

