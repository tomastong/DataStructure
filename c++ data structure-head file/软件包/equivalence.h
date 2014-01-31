#ifndef __EQUIVALENCE_H__				// ���û�ж���__EQUIVALENCE_H__
#define __EQUIVALENCE_H__				// ��ô����__EQUIVALENCE_H__

// �ȼ���
class Equivalence
{
protected:
// �ȼ�������ݳ�Ա:
	int *parent;								// �洢����˫��
	int size;									// ������

// ��������
int Find(int cur) const;						// ���ҽ��cur�������ĸ�

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	Equivalence(int sz);						// ����sz���������(�ȼ���)
	virtual ~Equivalence();						// ��������
	void Union(int a, int b);					// �ϲ�a��b���ڵĵȼ���
	bool Differ(int a, int b);					// ���a��b����ͬһ�����ϣ�����true�����򷵻�false
	Equivalence(const Equivalence &copy);				// ���ƹ��캯��
	Equivalence &operator =(const Equivalence &copy);	// ��ֵ�������
};


// �ȼ����ʵ�ֲ���
Equivalence::Equivalence(int sz)
// �������������sz���������(�ȼ���)
{
	size = sz;									// ����
	parent = new int[size];						// ����ռ�
	for (int i = 0; i < size; i++) 
		parent[i] = -1;							// ÿ����㹹�ɵ������(�ȼ���)
}

int Equivalence::Find(int cur) const
// ������������ҽ��cur�������ĸ�
{
	if (cur < 0 || cur >= size)
		throw Error("��Χ��!");					// �׳��쳣
	int root = cur;								// ��
	while (parent[root] > 0) root = parent[root];// ���Ҹ�
	for (int p, i = cur; i != root; i = p)
	{	// ����cur����·���ϵ����н�㶼��ɸ��ĺ��ӽ��
		p = parent[i];							// ��p�ݴ�i��˫��
		parent[i] = root;						// ��i��Ϊroot�ĺ���
	}
	return root;								// ���ظ�
}

Equivalence::~Equivalence()
// ����������ͷŶ�����õĿռ䡪����������
{
	delete []parent;							// �ͷ�����parent
}

void Equivalence::Union(int a, int b)
// ����������ϲ�a��b���ڵĵȼ���
{
	if (a < 0 || a >= size || b < 0 || b >= size)
		throw Error("��Χ��!");					// �׳��쳣
	int root1 = Find(a);						// ����a������(�ȼ���)�ĸ�		
	int root2 = Find(b);						// ����b������(�ȼ���)�ĸ�		
	if (parent[root1] < parent[root2])
	{	// root1����������϶�,��root2�ϲ���root1
		parent[root1] = parent[root1] + parent[root2];
			// root1�Ľ�����Ϊԭroot1��root2������֮��
		parent[root2] = root1;					// ��root2�ϲ���root1
	}
	else
	{	// root2����������϶�,��root1�ϲ���root2
		parent[root2] = parent[root1] + parent[root2];
			// root2�Ľ�����Ϊԭroot1��root2������֮��
		parent[root1] = root2;					// ��root1�ϲ���root2
	}
}

bool Equivalence::Differ(int a, int b)
// ������������a��b����ͬһ�����ϣ�����true�����򷵻�false
{
	if (a < 0 || a >= size || b < 0 || b >= size)
		throw Error("��Χ��!");					// �׳��쳣
	int root1 = Find(a);						// ����a������(�ȼ���)�ĸ�		
	int root2 = Find(b);						// ����b������(�ȼ���)�ĸ�		
	return root1 != root2;						// �Ƚ���(�ȼ���)�ĸ�
}

Equivalence::Equivalence(const Equivalence &copy)
// �����������copy�����¶��󡪡����ƹ��캯��
{
	size = copy.size;							// ����
	parent = new int[size];						// ����ռ�
	for (int i = 0; i < size; i++) 
		parent[i] = copy.parent[i];				// ����parent��ÿ��Ԫ��

}

Equivalence &Equivalence::operator =(const Equivalence &copy)
// �����������copy��ֵ����ǰ���󡪡���ֵ�������
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
