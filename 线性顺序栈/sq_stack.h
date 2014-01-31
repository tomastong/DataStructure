#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__


// ˳��ջ��
class SqStack
{
protected:
//  ˳��ջ�����ݳ�Ա:
	int count;										// Ԫ�ظ���
	int maxSize;									// ջ���Ԫ�ظ���
	int *elems;								// Ԫ�ش洢�ռ�

// ��������
	bool Full() const;								// �ж�ջ�Ƿ�����

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SqStack(int size = 1000);				// ���캯��
	virtual ~SqStack();								// ��������
	int Length() const;								// ��ջ����
	bool Empty() const;								// �ж�ջ�Ƿ�Ϊ��
	void Clear();									// ��ջ���
	void Traverse() const;	// ����ջ
    void Push(const int &e);				// ��ջ
	void Top(int &e) const;				// ����ջ��Ԫ��
	void Pop(int &e);					// ��ջ
	SqStack(const SqStack &copy);			// ���ƹ��캯��
	SqStack &operator =(const SqStack &copy); // ��ֵ�������
};


// ˳��ջ���ʵ�ֲ���

bool SqStack::Full() const
// �����������ջ�������򷵻�true�����򷵻�false
{
	return count == maxSize;
}



SqStack::SqStack(int size)
// �������������һ�����Ԫ�ظ���Ϊsize�Ŀ�ջ
{
	elems = NULL;						// δ����洢�ռ�ǰ,elemsΪ��
	//Init(size);							// ��ʼ��ջ

	elems = new int[maxSize];		// ����洢�ռ�
	count = 0;
}

SqStack::~SqStack()
// �������������ջ
{
	delete []elems;					// �ͷŴ洢�ռ�
}

int SqStack::Length() const
// �������������ջԪ�ظ���
{
	return count;
}

bool SqStack::Empty() const
// �����������ջΪ�գ��򷵻�true�����򷵻�false
{
	return count == 0;
}

void SqStack::Clear()
// ������������ջ
{
	count = 0;
}

void SqStack::Traverse() const
// �����������ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)
{
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// ��ջ�׵�ջ����ջ��ÿ��Ԫ�ص��ú���(*visit)
		std::cout << elems[curPosition - 1] << "  ";
	}
}

void SqStack::Push(const int &e)
// �����������Ԫ��e׷�ӵ�ջ��,��ɹ��򷵼�SUCCESS,��ջ����������OVER_FLOW
{
	if (Full())
	{	// ջ����
	//	return OVER_FLOW;
	}
	else
	{	// �����ɹ�
		elems[count++] = e;	// ��Ԫ��e׷�ӵ�ջ��
	//	return SUCCESS;
	}
}

void SqStack::Top(int &e) const
// �����������ջ�ǿ�,��e����ջ��Ԫ��,��������SUCCESS,����������UNDER_FLOW
{
	if(Empty())
	{	// ջ��
	//	return UNDER_FLOW;
	}
	else
	{	// ջ�ǿ�,�����ɹ�
		e = elems[count - 1];				// ��e����ջ��Ԫ��
	//	return SUCCESS;
	}
}

void SqStack::Pop(int &e)
// �����������ջ�ǿ�,ɾ��ջ��Ԫ��,����e����ջ��Ԫ��,��������SUCCESS,����
//	��������UNDER_FLOW
{
	if (Empty())
	{	// ջ��
	//	return UNDER_FLOW;
	}
	else
	{	// �����ɹ�
		e = elems[count - 1];				// ��e����ջ��Ԫ��
		count--;                               // �����������������дΪһ�����ӣ�Ӧ����ôд e = elems[--count];
	//	return SUCCESS;
	}
}

SqStack::SqStack(const SqStack &copy)
// �����������ջcopy������ջ--���ƹ��캯��
{
	elems = NULL;							// δ����洢�ռ�ǰ,elemsΪ��
	//Init();						// ��ʼ����ջ
	elems = new int[copy.maxSize];		// ����洢�ռ�
	count = 0;
	count = copy.count;						// ջԪ�ظ���
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// ��ջ�׵�ջ����ջcopy��ÿ��Ԫ�ؽ��и���
		elems[curPosition - 1] = copy.elems[curPosition - 1];
	}
}

SqStack &SqStack::operator = (const SqStack &copy)
// �����������ջcopy��ֵ����ǰջ--��ֵ�������
{
	if (&copy != this)
	{
		elems = new int[copy.maxSize];		// ����洢�ռ�
		count = 0;					// ��ʼ����ǰջ
		count = copy.count;					// ����ջԪ�ظ���
		for (int curPosition = 1; curPosition <= Length(); curPosition++)
		{	// ��ջ�׵�ջ����ջcopy��ÿ��Ԫ�ؽ��и���
			elems[curPosition - 1] = copy.elems[curPosition - 1];
		}
	}
	return *this;
}

#endif
