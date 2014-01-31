#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__


// ˳��ջ��

class SqStack
{
protected:
//  ˳��ջ�����ݳ�Ա:
	int count;										// Ԫ�ظ���
	int maxSize;									// ջ���Ԫ�ظ���
	char *elems;								// Ԫ�ش洢�ռ�

// ��������
	bool Full() const;								// �ж�ջ�Ƿ�����
	void Init(int size);							// ��ʼ��ջ

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SqStack(int size = 1000);				// ���캯��
	virtual ~SqStack();								// ��������
	int Length() const;								// ��ջ����
	bool Empty() const;								// �ж�ջ�Ƿ�Ϊ��
	void Clear();									// ��ջ���
//	void Traverse(void (*Visit)(const ElemType &)) const;	// ����ջ
	void Push(const char &e);				// ��ջ
	void Top(char &e) const;				// ����ջ��Ԫ��
	void Pop(char &e);					// ��ջ
	SqStack(const SqStack &copy);			// ���ƹ��캯��
	SqStack &operator =(const SqStack &copy); // ��ֵ�������
};


// ˳��ջ���ʵ�ֲ���

bool SqStack::Full() const
// �����������ջ�������򷵻�true�����򷵻�false
{
	return count == maxSize;
}


void SqStack::Init(int size)
// �����������ʼ��ջΪ���Ԫ�ظ���Ϊsize�Ŀ�ջ
{
	maxSize = size;						// ���Ԫ�ظ���
	if (elems != NULL) delete []elems;	// �ͷŴ洢�ռ�
	elems = new char[maxSize];		// ����洢�ռ�
	count = 0;							// ��ջԪ�ظ���Ϊ0
}

SqStack ::SqStack(int size)
// �������������һ�����Ԫ�ظ���Ϊsize�Ŀ�ջ
{
	elems = NULL;						// δ����洢�ռ�ǰ,elemsΪ��
	Init(size);							// ��ʼ��ջ
}

SqStack ::~SqStack()
// �������������ջ
{
	delete []elems;					// �ͷŴ洢�ռ�
}

int SqStack ::Length() const
// �������������ջԪ�ظ���
{
	return count;
}

bool SqStack ::Empty() const
// �����������ջΪ�գ��򷵻�true�����򷵻�false
{
	return count == 0;
}

void SqStack ::Clear()
// ������������ջ
{
	count = 0;
}

/*void SqStack ::Traverse(void (*Visit)(const ElemType &)) const
// �����������ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)
{
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// ��ջ�׵�ջ����ջ��ÿ��Ԫ�ص��ú���(*visit)
		(*Visit)(elems[curPosition - 1]);
	}
}
*/
void SqStack ::Push(const char &e)
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

void SqStack ::Top(char &e) const
// �����������ջ�ǿ�,��e����ջ��Ԫ��,��������SUCCESS,����������UNDER_FLOW
{
	if(Empty())
	{	// ջ��
	//	return UNDER_FLOW;
	}
	else
	{	// ջ�ǿ�,�����ɹ�
		e = elems[count - 1];				// ��e����ջ��Ԫ��
//		return SUCCESS;
	}
}

void SqStack ::Pop(char &e)
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
		//return SUCCESS;
	}
}

SqStack ::SqStack(const SqStack  &copy)
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

SqStack  &SqStack ::operator = (const SqStack  &copy)
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
