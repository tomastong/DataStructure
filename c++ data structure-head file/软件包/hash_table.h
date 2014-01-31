#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

// ɢ�б���
template <class ElemType, class KeyType>
class HashTable
{
protected:
//  ɢ�б�ĵ����ݳ�Ա:
	ElemType *ht;								// ɢ�б�
	bool *empty;								// ��Ԫ��
	int m;										// ɢ�б�����
	int p;										// �����������ĳ���

//	��������:
	int H(KeyType key) const;					// ɢ�к���
	int Collision(KeyType key, int i) const;	// �����ͻ�ĺ���
	bool SearchHelp(const KeyType &key, int &pos) const;	// ��Ѱ�ؼ���Ϊkey��Ԫ�ص�λ��

public:
//  �������������������ر���ϵͳĬ�Ϸ�������:
    HashTable(int size, int divisor);			// ���캯��
    ~HashTable();								// ���캯��
    void Traverse(void (*Visit)(const ElemType &)) const;	// ����ɢ�б�
	bool Search(const KeyType &key, ElemType &e) const ;	// ��Ѱ�ؼ���Ϊkey��Ԫ�ص�ֵ
	bool Insert(const ElemType &e);				// ����Ԫ��e
	bool Delete(const KeyType &key);			// ɾ���ؼ���Ϊkey��Ԫ��
    HashTable(const HashTable<ElemType, KeyType> &copy);	// ���ƹ��캯��
    HashTable<ElemType, KeyType> &operator=
		(const HashTable<ElemType, KeyType> &copy);			// ��ֵ�������
};

// ɢ�б����ʵ�ֲ���
template <class ElemType, class KeyType>
int HashTable<ElemType, KeyType>::H(KeyType key) const
//�������: ����ɢ�е�ַ
{
	return key % p;
}

template <class ElemType, class KeyType>
int HashTable<ElemType, KeyType>::Collision(KeyType key, int i) const
//�������: ���ص�i�γ�ͻ��̽���ַ
{
	return (H(key) + i) % m;
}

template <class ElemType, class KeyType>
HashTable<ElemType, KeyType>::HashTable(int size, int divisor)
// �������: ��sizeΪɢ�б�����, divisorΪ�����������ĳ�������һ���յ�ɢ���
{
	m = size;								// ��ֵɢ�б�����
	p = divisor;							// ��ֵ����
	ht = new ElemType[m];					// ����洢�ռ�
	empty = new bool[m];					// ����洢�ռ�

	for (int pos = 0; pos < m; pos++)
	{	// ������Ԫ���ÿ�
		empty[pos] = true;
	}
}

template <class ElemType, class KeyType>
HashTable<ElemType, KeyType>::~HashTable()
// �������: ����ɢ�б�
{
	delete []ht;							// �ͷ�ht
	delete []empty;							// �ͷ�empty
}

template <class ElemType, class KeyType>
void HashTable<ElemType, KeyType>::Traverse(void (*Visit)(const ElemType &)) const
// �������: ���ζ�ɢ�б��ÿ��Ԫ�ص��ú���(*visit)
{
	for (int pos = 0; pos < m; pos++)
	{	// ��ɢ�б��ÿ��Ԫ�ص��ú���(*visit)
		if (!empty[pos])
		{	// ����Ԫ�طǿ�
			(*Visit)(ht[pos]);
		}
	}
}

template <class ElemType, class KeyType>
bool HashTable<ElemType, KeyType>::SearchHelp(const KeyType &key, int &pos) const
// �������: ��Ѱ�ؼ���Ϊkey��Ԫ�ص�λ��,������ҳɹ�,����true,����posָʾ��������
//	Ԫ����ɢ�б��λ��,���򷵻�false
{	
	int c = 0;							// ��ͻ����
	pos = H(key);						// ɢ�б��ַ

	while (c < m &&						// ��ͻ����ӦС��m
		!empty[pos] &&					// Ԫ��ht[pos]�ǿ�
		ht[pos] != key)					// �ؼ���ֵ����
	{	
		pos = Collision(key, ++c);		//�����һ��̽���ַ
	}

	if (c >= m || empty[pos])
	{	// ����ʧ��
		return false;
	}
	else
	{	// ���ҳɹ�
		return true;
	}
}

template <class ElemType, class KeyType>
bool HashTable<ElemType, KeyType>::Search(const KeyType &key, ElemType &e) const
// �������: ��Ѱ�ؼ���Ϊkey��Ԫ�ص�ֵ,������ҳɹ�,����true,����e����Ԫ�ص�ֵ,
//	���򷵻�false
{
	int pos;							// Ԫ�ص�λ��
	if (SearchHelp(key, pos))
	{	// ���ҳɹ�
		e = ht[pos];					// ��e����Ԫ��ֵ
		return true;					// ����true
	}
	else
	{	// ����ʧ��
		return false;					// ����false
	}
}

template <class ElemType, class KeyType>
bool HashTable<ElemType, KeyType>::Insert(const ElemType &e)
// �������: ��ɢ�б��в�������Ԫ��e,����ɹ�����true,���򷵻�false
{
	int pos;							// ����λ��
	if (!SearchHelp(e, pos) && empty[pos])
	{	// ����ɹ�
		ht[pos] = e;					// ����Ԫ��	
		empty[pos] = false;				// ��ʾ�ǿ�
		return true;
	}
	else
	{	// ����ʧ��
		return false;
	}
}

template <class ElemType, class KeyType>
bool HashTable<ElemType, KeyType>::Delete(const KeyType &key)
// �������: ɾ���ؼ���Ϊkey������Ԫ��,ɾ���ɹ�����true,���򷵻�false
{
	int pos;							// ����Ԫ��λ��
	if (SearchHelp(key, pos))
	{	// ɾ���ɹ�
		empty[pos] = true;				// ��ʾԪ��Ϊ��
		return true;
	}
	else
	{	// ɾ��ʧ��
		return false;
	}
}

template <class ElemType, class KeyType>
HashTable<ElemType, KeyType>::HashTable(const HashTable<ElemType, KeyType> &copy)
// �����������ɢ�б�copy������ɢ�б�--���ƹ��캯��
{
	m = copy.m;										// ɢ�б�����
	p = copy.p;										// �����������ĳ���
	ht = new ElemType[m];							// ����洢�ռ�
	empty = new bool[m];							// ����洢�ռ�

	for (int curPosition = 0; curPosition < m; curPosition++)
	{	// ��������Ԫ��
		ht[curPosition] = copy.ht[curPosition];		// ����Ԫ��
		empty[curPosition] = copy.empty[curPosition];// ����Ԫ���Ƿ�Ϊ��ֵ
	}
}

template <class ElemType, class KeyType>
HashTable<ElemType, KeyType> &HashTable<ElemType, KeyType>::
operator=(const HashTable<ElemType, KeyType> &copy)
// �����������ɢ�б�copy��ֵ����ǰɢ�б�--��ֵ�������
{
	if (&copy != this)
	{
		delete []ht;								// �ͷŵ�ǰɢ�б�洢�ռ�
		m = copy.m;									// ɢ�б�����
		p = copy.p;									// �����������ĳ���
		ht = new ElemType[m];						// ����洢�ռ�
		empty = new bool[m];						// ����洢�ռ�

		for (int curPosition = 0; curPosition < m; curPosition++)
		{	// ��������Ԫ��
			ht[curPosition] = copy.ht[curPosition];	// ����Ԫ��
			empty[curPosition] = copy.empty[curPosition];// ����Ԫ���Ƿ�Ϊ��ֵ
		}
	}
	return *this;
}

#endif