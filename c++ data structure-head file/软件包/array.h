#ifndef __ARRAY_H__
#define __ARRAY_H__

// ������
template<class ElemType>
class Array
{
protected:
//  ��������ݳ�Ա:
	ElemType *base;			// ����Ԫ�ػ�ַ
	int dim;				// ����ά��
	int *bounds;			// �����ά����
	int *constants;			// ����ӳ��������

// ��������
	int Locate(int sub0, va_list &va) const;// ��Ԫ����˳��洢�е�λ��

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	Array(int d, ...);		// ��ά��d�����ĸ�ά���ȹ�������
	~Array();				// ��������
	ElemType &operator()(int sub0, ...);	// ���غ��������
	Array(const Array<ElemType> &copy);		// ���ƹ��캯��
	Array<ElemType> &operator =(const Array<ElemType> &copy); // ��ֵ�������
};

// �������ʵ�ֲ���
template <class ElemType>
Array<ElemType>::Array(int d, ...)
// �����������ά��d�����ĸ�ά���ȹ�������
{
	if (d < 1)				
		throw Error("ά������С��1!");// �׳��쳣
	dim = d;				// ����ά��Ϊd
	bounds = new int[dim];	// ���������ά���ȴ洢�ռ�
	va_list va;				// �䳤��������
	int elemTotal =	1;		// Ԫ������
	int i;					// ��ʱ����
	
	va_start(va, d);						
		// ��ʼ������va,���ڴ洢�䳤������Ϣ,dΪʡ�Ժ�������ұߵĲ�����ʶ��
	for (i = 0; i < dim; i++)
	{	// Ϊ��ά���ȸ�ֵ������������Ԫ�ظ���
		bounds[i] = va_arg(va, int);		// ȡ���䳤������Ϊ��ά����
		elemTotal = elemTotal * bounds[i];	// ͳ��������Ԫ�ظ���
	}
	va_end(va);				// �����䳤����������

	base = new ElemType[elemTotal];	// ��������Ԫ�ؿռ�
	constants = new int[dim];		// ��������ӳ��������
	constants[dim - 1] = 1;
	for (i = dim - 2; i >= 0; --i)
		constants[i] = bounds[i + 1] * constants[i + 1]; // ��������ӳ��������
}

template <class ElemType>
Array<ElemType>::~Array()
// ����������ͷ�������ռ�ÿռ�
{
	if (base != NULL) delete []base;				// �ͷ�����Ԫ�ؿռ�
	if (bounds != NULL) delete []bounds;			// �ͷŸ�ά���ȿռ�
	if (constants != NULL) delete []constants;		// �ͷ�ӳ���������ռ�
}

template <class ElemType>
int Array<ElemType>::Locate(int sub0, va_list &va) const
// �����������Ԫ����˳��洢�е�λ��
{	
	if (!(sub0 >= 0 && sub0 < bounds[0]))	
		throw Error("�±����!");			// �׳��쳣		
	int off = constants[0] * sub0;			// ��ʼ��Ԫ����˳��洢�е�λ��	
	for (int i = 1; i < dim; i++)
	{
		int sub = va_arg(va, int);			// ȡ������Ԫ���±�
		if (!(sub >= 0 && sub < bounds[i]))	// �׳��쳣
			throw Error("�±����!");			
		off += constants[i] * sub;			// �ۼӳ˻���Ԫ����˳��洢�е�λ��
	}
	return off;
}

template <class ElemType>
ElemType &Array<ElemType>::operator()(int sub0, ...)
// ������������غ��������
{
	va_list va;								// �䳤��������
	va_start(va, sub0);						
		// ��ʼ������va,���ڴ洢�䳤������Ϣ,sub0Ϊʡ�Ժ�������ұߵĲ�����ʶ��
	int off = Locate(sub0, va);
	va_end(va);
	return *(base + off);					// ����Ԫ��
}

template <class ElemType>
Array<ElemType>::Array(const Array<ElemType> &copy)
// ���������������copy���������顪�����ƹ��캯��
{
	dim = copy.dim;			// ����ά��

	int elemTotal =	1;		// Ԫ������
	int i;					// ��ʱ����
	for (i = 0; i < dim; i++)
	{	// ͳ��������Ԫ�ظ���
		elemTotal = elemTotal * copy.bounds[i];	// ����������Ԫ�ظ���
	}
	base = new ElemType[elemTotal];	// Ϊ����Ԫ�ط���洢�ռ�
	for (i = 0; i < elemTotal; i++)
	{	// ��������Ԫ��
		base[i] = copy.base[i];
	}
	
	bounds = new int[dim];			// Ϊ�����ά���ȷ���洢�ռ�
	constants =  new int[dim];		// Ϊ����ӳ������������洢�ռ�
	for (i = 0; i < dim; i++)
	{	// ���������ά������ӳ��������
		bounds[i] = copy.bounds[i];			// ��ά����	
		constants[i] = copy.constants[i];	// ӳ��������
	}
}

template <class ElemType>
Array<ElemType> &Array<ElemType>::operator =(const Array<ElemType> &copy)
// ���������������copy��ֵ����ǰ���顪����ֵ�������
{
	if (&copy != this)
	{
		if (base != NULL) delete []base;				// �ͷ�����Ԫ�ؿռ�
		if (bounds != NULL) delete []bounds;			// �ͷŸ�ά���ȿռ�
		if (constants != NULL) delete []constants;		// �ͷ�ӳ���������ռ�

		dim = copy.dim;			// ����ά��

		int elemTotal =	1;		// Ԫ������
		int i;					// ��ʱ����
		for (i = 0; i < dim; i++)
		{	// ͳ��������Ԫ�ظ���
			elemTotal = elemTotal * copy.bounds[i];		// ����������Ԫ�ظ���
		}
		base = new ElemType[elemTotal];		// Ϊ����Ԫ�ط���洢�ռ�
		for (i = 0; i < elemTotal; i++)
		{	// ��������Ԫ��
			base[i] = copy.base[i];
		}
		
		bounds = new int[dim];				// Ϊ�����ά���ȷ���洢�ռ�
		constants =  new int[dim];			// Ϊ����ӳ������������洢�ռ�
		for (i = 0; i < dim; i++)
		{	// ���������ά������ӳ��������
			bounds[i] = copy.bounds[i];			// ��ά����	
			constants[i] = copy.constants[i];	// ӳ��������
		}
	}
	return *this;
}

#endif