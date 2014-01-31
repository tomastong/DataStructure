#ifndef __SQ_QUEUE_H__
#define __SQ_QUEUE_H__


// ѭ��������

template<class ElemType>
class SqQueue 
{
protected:
	int front, rear;									// ��ͷ��β
	int maxSize;										// �������Ԫ�ظ���
	ElemType *elems;									// Ԫ�ش洢�ռ�

// ��������:
	bool Full() const;									// �ж�ջ�Ƿ�����
	void Init(int size);								// ��ʼ������

public:
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	SqQueue(int size = DEFAULT_SIZE);					// ���캯��
	virtual ~SqQueue();									// ��������
	int Length() const;									// ����г���			 
	bool Empty() const;									// �ж϶����Ƿ�Ϊ��
	void Clear();										// ���������
	void Traverse(void (*Visit)(const ElemType &)) const;	// ��������
	StatusCode OutQueue(ElemType &e);					// ���Ӳ���
	StatusCode GetHead(ElemType &e) const;				// ȡ��ͷ����
	StatusCode InQueue(const ElemType &e);				// ��Ӳ���
	SqQueue(const SqQueue<ElemType> &copy);				// ���ƹ��캯��
	SqQueue<ElemType> &operator =(const SqQueue<ElemType> &copy);// ��ֵ�������
};



// ѭ���������ʵ�ֲ���


template <class ElemType>
bool SqQueue<ElemType>::Full() const
// ���������������������򷵻�true�����򷵻�false
{
	return Length() == maxSize - 1;
}

template <class ElemType>
void SqQueue<ElemType>::Init(int size)
// �����������ʼ������Ϊ���Ԫ�ظ���Ϊsize�Ŀն���
{
	maxSize = size;							// ���Ԫ�ظ���
	if (elems != NULL) delete []elems;		// �ͷŴ洢�ռ�
	elems = new ElemType[maxSize];			// ����洢�ռ�
	rear = front = 0;						// �ն��ж�ͷ���β���
}

template<class ElemType>
SqQueue<ElemType>::SqQueue(int size)
// �������������һ�����Ԫ�ظ���Ϊsize�Ŀ�ѭ������
{
	elems = NULL;							// δ����洢�ռ�ǰ,elemsΪ��
	Init(size);								// ��ʼ������
}

template <class ElemType>
SqQueue<ElemType>::~SqQueue()
// ������������ٶ���
{
	delete []elems;							// �ͷŴ洢�ռ�
}

template<class ElemType>
int SqQueue<ElemType>::Length() const
// ������������ض��г���			 
{
	return (rear - front + maxSize) % maxSize;
}

template<class ElemType>
bool SqQueue<ElemType>::Empty() const
// ��������������Ϊ�գ��򷵻�true�����򷵻�false
{
   return rear == front;
}

template<class ElemType>
void SqQueue<ElemType>::Clear() 
// �����������ն���
{
	rear = front = 0;
}

template <class ElemType>
void SqQueue<ElemType>::Traverse(void (*Visit)(const ElemType &)) const
// ������������ζԶ��е�ÿ��Ԫ�ص��ú���(*visit)
{
	for (int curPosition = front; curPosition != rear; 
		curPosition = (curPosition + 1) % maxSize)
	{	// �Զ���ÿ��Ԫ�ص��ú���(*visit)
		(*Visit)(elems[curPosition]);
	}
}


template<class ElemType>
StatusCode SqQueue<ElemType>::OutQueue(ElemType &e)
// ���������������зǿգ���ôɾ����ͷԪ�أ�����e������ֵ����������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!Empty()) 
	{	// ���зǿ�
		e = elems[front];					// ��e���ض�ͷԪ��
		front = (front + 1) % maxSize;		// frontָ����һԪ��
		return SUCCESS;
	}
	else
	{	// ����Ϊ��
		return UNDER_FLOW;
	}
}

template<class ElemType>
StatusCode SqQueue<ElemType>::GetHead(ElemType &e) const
// ���������������зǿգ���ô��e���ض�ͷԪ�أ���������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!Empty()) 
	{	// ���зǿ�
		e = elems[front];					// ��e���ض�ͷԪ��
		return SUCCESS;
	}
	else
	{	// ����Ϊ��
		return UNDER_FLOW;
	}
}

template<class ElemType>
StatusCode SqQueue<ElemType>::InQueue(const ElemType &e)
// ��������������������������OVER_FLOW,
//	�������Ԫ��eΪ�µĶ�β������SUCCESS
{
	if (Full())
	{	// ��������
		return OVER_FLOW;
	}
	else
	{	// ����δ������ӳɹ�
		elems[rear] = e;					// ����eΪ�¶�β
		rear = (rear + 1) % maxSize;		// rearָ���¶�β
		return SUCCESS;
	}
}

template<class ElemType>
SqQueue<ElemType>::SqQueue(const SqQueue<ElemType> &copy)
// ����������ɶ���copy�����¶���--���ƹ��캯��
{
	elems = NULL;							// δ����洢�ռ�ǰ,elemsΪ��
	Init(copy.maxSize);						// ��ʼ���¶���
	front = copy.front;						// ���ƶ�ͷλ��	
	rear = copy.rear;						// ���ƶ�βλ��
	for (int curPosition = front; curPosition != rear; 
		curPosition = (curPosition + 1) % maxSize)
	{	// ����ѭ������Ԫ��
		elems[curPosition] = copy.elems[curPosition];
	}
}

template<class ElemType>
SqQueue<ElemType> &SqQueue<ElemType>::operator =(const SqQueue<ElemType> &copy)
// ���������������copy��ֵ����ǰ����--��ֵ�������
{
	if (&copy != this)
	{
		Init(copy.maxSize);			 		// ��ʼ����ǰ����
		front = copy.front;					// ���ƶ�ͷλ��	
		rear = copy.rear;					// ���ƶ�βλ��
		for (int curPosition = front; curPosition != rear; 
			curPosition = (curPosition + 1) % maxSize)
		{	// ����ѭ������Ԫ��
			elems[curPosition] = copy.elems[curPosition];
		}
	}
	return *this;
}

#endif
