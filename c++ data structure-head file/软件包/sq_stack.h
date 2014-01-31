#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__


// ˳��ջ��
template<class ElemType>
class SqStack
{
protected:
//  ˳��ջ�����ݳ�Ա:
	int count;										// Ԫ�ظ���
	int maxSize;									// ջ���Ԫ�ظ���
	ElemType *elems;								// Ԫ�ش洢�ռ�

// ��������
	bool Full() const;								// �ж�ջ�Ƿ�����
	void Init(int size);							// ��ʼ��ջ

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SqStack(int size = DEFAULT_SIZE);				// ���캯��
	virtual ~SqStack();								// ��������
	int Length() const;								// ��ջ����
	bool Empty() const;								// �ж�ջ�Ƿ�Ϊ��
	void Clear();									// ��ջ���
	void Traverse(void (*Visit)(const ElemType &)) const;	// ����ջ
	StatusCode Push(const ElemType &e);				// ��ջ
	StatusCode Top(ElemType &e) const;				// ����ջ��Ԫ��
	StatusCode Pop(ElemType &e);					// ��ջ
	SqStack(const SqStack<ElemType> &copy);			// ���ƹ��캯��
	SqStack<ElemType> &operator =(const SqStack<ElemType> &copy); // ��ֵ�������
};


// ˳��ջ���ʵ�ֲ���

template <class ElemType>
bool SqStack<ElemType>::Full() const
// �����������ջ�������򷵻�true�����򷵻�false
{
	return count == maxSize;
}


template <class ElemType>
void SqStack<ElemType>::Init(int size)
// �����������ʼ��ջΪ���Ԫ�ظ���Ϊsize�Ŀ�ջ
{
	maxSize = size;						// ���Ԫ�ظ���
	if (elems != NULL) delete []elems;	// �ͷŴ洢�ռ�
	elems = new ElemType[maxSize];		// ����洢�ռ�
	count = 0;							// ��ջԪ�ظ���Ϊ0
}

template<class ElemType>
SqStack<ElemType>::SqStack(int size)
// �������������һ�����Ԫ�ظ���Ϊsize�Ŀ�ջ
{
	elems = NULL;						// δ����洢�ռ�ǰ,elemsΪ��
	Init(size);							// ��ʼ��ջ
}

template<class ElemType>
SqStack<ElemType>::~SqStack()
// �������������ջ
{
	delete []elems;					// �ͷŴ洢�ռ�
}

template <class ElemType>
int SqStack<ElemType>::Length() const
// �������������ջԪ�ظ���
{
	return count;
}

template<class ElemType>
bool SqStack<ElemType>::Empty() const
// �����������ջΪ�գ��򷵻�true�����򷵻�false
{
	return count == 0;
}

template<class ElemType>
void SqStack<ElemType>::Clear()
// ������������ջ
{
	count = 0;
}

template <class ElemType>
void SqStack<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// �����������ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)
{
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// ��ջ�׵�ջ����ջ��ÿ��Ԫ�ص��ú���(*visit)
		(*Visit)(elems[curPosition - 1]);
	}
}

template<class ElemType>
StatusCode SqStack<ElemType>::Push(const ElemType &e)
// �����������Ԫ��e׷�ӵ�ջ��,��ɹ��򷵼�SUCCESS,��ջ����������OVER_FLOW
{
	if (Full())
	{	// ջ����
		return OVER_FLOW;
	}
	else
	{	// �����ɹ�
		elems[count++] = e;	// ��Ԫ��e׷�ӵ�ջ��
		return SUCCESS;
	}
}

template<class ElemType>
StatusCode SqStack<ElemType>::Top(ElemType &e) const
// �����������ջ�ǿ�,��e����ջ��Ԫ��,��������SUCCESS,����������UNDER_FLOW
{
	if(Empty())
	{	// ջ��
		return UNDER_FLOW;
	}
	else
	{	// ջ�ǿ�,�����ɹ�
		e = elems[count - 1];				// ��e����ջ��Ԫ��
		return SUCCESS;
	}
}

template<class ElemType>
StatusCode SqStack<ElemType>::Pop(ElemType &e)
// �����������ջ�ǿ�,ɾ��ջ��Ԫ��,����e����ջ��Ԫ��,��������SUCCESS,����
//	��������UNDER_FLOW
{
	if (Empty())
	{	// ջ��
		return UNDER_FLOW;
	}
	else
	{	// �����ɹ�
		e = elems[count - 1];				// ��e����ջ��Ԫ��
		count--;                               // �����������������дΪһ�����ӣ�Ӧ����ôд e = elems[--count];
		return SUCCESS;
	}
}

template<class ElemType>
SqStack<ElemType>::SqStack(const SqStack<ElemType> &copy)
// �����������ջcopy������ջ--���ƹ��캯��
{
	elems = NULL;							// δ����洢�ռ�ǰ,elemsΪ��
	Init(copy.maxSize);						// ��ʼ����ջ
	count = copy.count;						// ջԪ�ظ���
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// ��ջ�׵�ջ����ջcopy��ÿ��Ԫ�ؽ��и���
		elems[curPosition - 1] = copy.elems[curPosition - 1];
	}
}

template<class ElemType>
SqStack<ElemType> &SqStack<ElemType>::operator = (const SqStack<ElemType> &copy)
// �����������ջcopy��ֵ����ǰջ--��ֵ�������
{
	if (&copy != this)
	{
		Init(copy.maxSize);					// ��ʼ����ǰջ
		count = copy.count;					// ����ջԪ�ظ���
		for (int curPosition = 1; curPosition <= Length(); curPosition++)
		{	// ��ջ�׵�ջ����ջcopy��ÿ��Ԫ�ؽ��и���
			elems[curPosition - 1] = copy.elems[curPosition - 1];
		}
	}
	return *this;
}

#endif
