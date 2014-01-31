#ifndef __SIMPLE_EQUIVALENCE_H__				// ���û�ж���__SIMPLE_EQUIVALENCE_H__
#define __SIMPLE_EQUIVALENCE_H__				// ��ô����__SIMPLE_EQUIVALENCE_H__

// �ȼ���
class SimpleEquivalence
{
protected:
// �ȼ�������ݳ�Ա:
	int *parent;								// �洢����˫��
	int size;									// ������

// ��������
int Find(int cur) const;						// ���ҽ��cur�������ĸ�

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SimpleEquivalence(int sz);					// ����sz���������(�ȼ���)
	virtual ~SimpleEquivalence();				// ��������
	void Union(int a, int b);					// �ϲ�a��b���ڵĵȼ���
	bool Differ(int a, int b);					// ���a��b����ͬһ�����ϣ�����true�����򷵻�false
	SimpleEquivalence(const SimpleEquivalence &copy);				// ���ƹ��캯��
	SimpleEquivalence &operator =(const SimpleEquivalence &copy);	// ��ֵ�����
};

                                                                                                                                       
// �ȼ����ʵ�ֲ���
SimpleEquivalence::SimpleEquivalence(int sz)
// �������������sz���������(�ȼ���)
{
	size = sz;									// ����
	parent = new int[size];						// ����ռ�
	for (int i = 0; i < size; i++) 
		parent[i] = -1;							// ÿ����㹹�ɵ�������γɵĵȼ���
}

int SimpleEquivalence::Find(int cur) const
// ������������ҽ��cur�������ĸ�
{
	if (cur < 0 || cur >= size)
		throw Error("��Χ��!");					// �׳��쳣
	while (parent[cur] != -1) cur = parent[cur];// ���Ҹ�
	return cur;									// ���ظ�
}

SimpleEquivalence::~SimpleEquivalence()
// ����������ͷŶ���ռ�õĿռ䡪����������
{
	delete []parent;							// �ͷ�����parent
}

void SimpleEquivalence::Union(int a, int b)
// ����������ϲ�a��b���ڵĵȼ���
{
	if (a < 0 || a >= size || b < 0 || b >= size)
		throw Error("��Χ��!");					// �׳��쳣
	int root1 = Find(a);						// ����a������(�ȼ���)�ĸ�		
	int root2 = Find(b);						// ����b������(�ȼ���)�ĸ�		
	if (root1 != root2) parent[root2] = root1;	// �ϲ���(�ȼ���)
}

bool SimpleEquivalence::Differ(int a, int b)
// ������������a��b����ͬһ�����ϣ�����true�����򷵻�false
{
	if (a < 0 || a >= size || b < 0 || b >= size)
		throw Error("��Χ��!");					// �׳��쳣
	int root1 = Find(a);						// ����a������(�ȼ���)�ĸ�		
	int root2 = Find(b);						// ����b������(�ȼ���)�ĸ�		
	return root1 != root2;						// �Ƚ���(�ȼ���)�ĸ�
}

SimpleEquivalence::SimpleEquivalence(const SimpleEquivalence &copy)
// �����������copy�����¶��󡪡����ƹ��캯��
{
	size = copy.size;							// ����
	parent = new int[size];						// ����ռ�
	for (int i = 0; i < size; i++) 
		parent[i] = copy.parent[i];				// ����parent��ÿ��Ԫ��

}

SimpleEquivalence &SimpleEquivalence::operator =(const SimpleEquivalence &copy)
// �����������copy��ֵ����ǰ���󡪡���ֵ�����
{
	if (&copy != this)
	{
		size = copy.size;						// ����
		delete []parent;						// �ͷſռ�
		parent = new int[size];					// ����ռ�
		for (int i = 0; i < size; i++) 
			parent[i] = copy.parent[i];			// ����parent��ÿ��Ԫ��
	}
	return *this;
}

#endif
