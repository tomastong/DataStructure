#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

// ˳�����
template <class ElemType>
class SqList 
{
protected:
// ˳���ʵ�ֵ����ݳ�Ա:
	int count;					// Ԫ�ظ���
	int maxSize;				// ˳������Ԫ�ظ���
	ElemType *elems;			// Ԫ�ش洢�ռ�

// ��������
	bool Full() const;			// �ж����Ա��Ƿ�����
	void Init(int size);		// ��ʼ�����Ա�

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SqList(int size = DEFAULT_SIZE);	// ���캯��
	virtual ~SqList();			// ��������
	int Length() const;			// �����Ա���			 
	bool Empty() const;			// �ж����Ա��Ƿ�Ϊ��
	void Clear();				// �����Ա����
	void Traverse(void (*Visit)(const ElemType &)) const;	// �������Ա�
	StatusCode GetElem(int position, ElemType &e) const;	// ��ָ��λ�õ�Ԫ��	
	StatusCode SetElem(int position, const ElemType &e);	// ����ָ��λ�õ�Ԫ��ֵ
	StatusCode Delete(int position, ElemType &e);// ɾ��Ԫ��		
	StatusCode Insert(int position, const ElemType &e); // ����Ԫ��
	SqList(const SqList<ElemType> &copy); // ���ƹ��캯��
	SqList<ElemType> &operator =(const SqList<ElemType> &copy); // ��ֵ�������
};


// ˳������ʵ�ֲ���

template <class ElemType>
bool SqList<ElemType>::Full() const
// ��������������Ա��������򷵻�true�����򷵻�false
{
	return count == maxSize;
}

template <class ElemType>
void SqList<ElemType>::Init(int size)
// �����������ʼ�����Ա�Ϊ���Ԫ�ظ���Ϊsize�Ŀ����Ա�
{
	maxSize = size;						// ���Ԫ�ظ���
	if (elems != NULL) delete []elems;	// �ͷŴ洢�ռ�
	elems = new ElemType[maxSize];		// ����洢�ռ�
	count = 0;							// �����Ա�Ԫ�ظ���Ϊ0
}

template <class ElemType>
SqList<ElemType>::SqList(int size)
// �������������һ�����Ԫ�ظ���Ϊsize�Ŀ�˳���
{
	elems = NULL;						// δ����洢�ռ�ǰ,elemsΪ��
	Init(size);							// ��ʼ�����Ա�
}

template <class ElemType>
SqList<ElemType>::~SqList()
// ����������������Ա�
{
	delete []elems;						// �ͷŴ洢�ռ�
}

template <class ElemType>
int SqList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	return count;
}

template <class ElemType>
bool SqList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return count == 0;
}

template <class ElemType>
void SqList<ElemType>::Clear()
// ���������������Ա�
{
	count = 0;
}

template <class ElemType>
void SqList<ElemType>::Traverse(void (*visit)(const ElemType &)) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
		(*visit)(elems[curPosition - 1]);
	}
}

template <class ElemType>
StatusCode SqList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,
//	����������NOT_PRESENT
{
	if(position < 1 || position > Length())
	{	// position��Χ��
		return NOT_PRESENT;	// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		e = elems[position - 1];
		return ENTRY_FOUND;	// Ԫ�ش���
	}
}

template <class ElemType>
StatusCode SqList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return RANGE_ERROR;	// λ�ô�
	}
	else
	{	// position�Ϸ�
		elems[position - 1] = e;
		return SUCCESS;		// �ɹ�
	}
}

template <class ElemType>
StatusCode SqList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ��ǰ��e������ֵ,
//	position�ĵ�ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	int len = Length();
	ElemType tmp;

	if (position < 1 || position >= len)
	{	// position��Χ��
		return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		GetElem(position, e);	// ��e���ر�ɾ��Ԫ�ص�ֵ
		for (int curPosition = position + 1; curPosition <= len; curPosition++)
		// ��ɾ��Ԫ��֮���Ԫ����������
		{
			GetElem(curPosition, tmp); SetElem(curPosition - 1, tmp); 
		}
		count--;				// ɾ����Ԫ�ظ������Լ�1
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode SqList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e,
//	position�ĵ�ȡֵ��ΧΪ1��position��Length()+1
//	�����Ա�����,�򷵻�OVER_FLOW,
//	��position�Ϸ�, �򷵻�SUCCESS, ����������RANGE_ERROR
{
	int len = Length();
	ElemType tmp;
	if (Full())
	{	// ���Ա���������OVER_FLOW
		return OVER_FLOW;	
	}
	else if (position < 1 || position > len + 1)
	{	// position��Χ��
		return RANGE_ERROR;
	}
	else
	{	// �ɹ�
		count++;				// �����Ԫ�ظ���������1
		for (int curPosition = len; curPosition >= position; curPosition--)
		{	// ����λ��֮���Ԫ������
			GetElem(curPosition, tmp); SetElem(curPosition + 1, tmp); 
		}

		SetElem(position, e);	// ��e��ֵ��positionλ�ô�	
		return SUCCESS;			// ����ɹ�
	}
}

template <class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType> &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��
{
	int copyLength = copy.Length();			// copy�ĳ���
	ElemType e;

	elems = NULL;							// δ����洢�ռ�ǰ,elemsΪ��
	Init(copy.maxSize);						// ��ʼ�������Ա�
	for (int curPosition = 1; curPosition <= copyLength; curPosition++)
	{	// ��������Ԫ��
		copy.GetElem(curPosition, e);		// ȡ����curPosition��Ԫ��
		Insert(Length() + 1, e);			// ��e���뵽��ǰ���Ա�
	}
}

template <class ElemType>
SqList<ElemType> &SqList<ElemType>::operator =(const SqList<ElemType> &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա�����ֵ�������
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy�ĳ���
		ElemType e;

		Init(copy.maxSize);					// ��ʼ����ǰ���Ա�
		for (int curPosition = 1; curPosition <= copyLength; curPosition++)
		{	// ��������Ԫ��
			copy.GetElem(curPosition, e);	// ȡ����curPosition��Ԫ��
			Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
		}
	}
	return *this;
}

#endif