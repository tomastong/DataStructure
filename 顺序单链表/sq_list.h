#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

#define DEFAULT_SIZE 1000			// ȱʡԪ�ظ���
/***
   *�Զ�������(����ͨ��ö�ٱ������к궨�壬�������ﲻ�Ǹù���)��
   *�����StatusCodeö������,ֻ��һ����ע�����۷���1����0����
   *���﷽��ʹ�������ף�����ֵ����ǰ�����ι����Ƿ�ʵ��
   */
enum StatusCode {SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR, DUPLICATE_ERROR,
	NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED};


// ˳�����
class SqList 
{
protected:
// ˳���ʵ�ֵ����ݳ�Ա:
	int count;					// Ԫ�ظ���
	int maxSize;				// ˳������Ԫ�ظ���
	int *elems;			// Ԫ�ش洢�ռ�

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
	void Traverse() const;	// �������Ա�
	bool GetElem(int position, int &e) const;	// ��ָ��λ�õ�Ԫ��	
	bool SetElem(int position, const int &e);	// ����ָ��λ�õ�Ԫ��ֵ
	bool Delete(int position, int &e);// ɾ��Ԫ��		
	bool Insert(int position, const int &e); // ����Ԫ��
	SqList(const SqList &copy); // ���ƹ��캯��
	SqList &operator =(const SqList &copy); // ��ֵ�������
};


// ˳������ʵ�ֲ���

bool SqList::Full() const
// ��������������Ա��������򷵻�true�����򷵻�false
{
	return count == maxSize;
}

void SqList::Init(int size)
// �����������ʼ�����Ա�Ϊ���Ԫ�ظ���Ϊsize�Ŀ����Ա�
{
	maxSize = size;						// ���Ԫ�ظ���
	if (elems != NULL) delete []elems;	// �ͷŴ洢�ռ�
	elems = new int[maxSize];		// ����洢�ռ�
	count = 0;							// �����Ա�Ԫ�ظ���Ϊ0
}

SqList::SqList(int size)
// �������������һ�����Ԫ�ظ���Ϊsize�Ŀ�˳���
{
	elems = NULL;						// δ����洢�ռ�ǰ,elemsΪ��
	Init(size);							// ��ʼ�����Ա�
}

SqList::~SqList()
// ����������������Ա�
{
	delete []elems;						// �ͷŴ洢�ռ�
}

int SqList::Length() const
// ����������������Ա�Ԫ�ظ���
{
	return count;
}

bool SqList::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return count == 0;
}

void SqList::Clear()
// ���������������Ա�
{
	count = 0;
}

void SqList::Traverse() const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	
		std::cout << elems[curPosition - 1] << "  ";
	}
}

bool SqList::GetElem(int position, int &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,
//	����������NOT_PRESENT
{
	if(position < 1 || position > Length())
	{	// position��Χ��
		return false;	// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		e = elems[position - 1];
		return true;	// Ԫ�ش���
	}
}

bool SqList::SetElem(int position, const int &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return false;	// λ�ô�
	}
	else
	{	// position�Ϸ�
		elems[position - 1] = e;
		return true;		// �ɹ�
	}
}

bool SqList::Delete(int position, int &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ��ǰ��e������ֵ,
//	position�ĵ�ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	int len = Length();
	int tmp;

	if (position < 1 || position >= len)
	{	// position��Χ��
		return false;
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
		return true;
	}
}

bool SqList::Insert(int position, const int &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e,
//	position�ĵ�ȡֵ��ΧΪ1��position��Length()+1
//	�����Ա�����,�򷵻�OVER_FLOW,
//	��position�Ϸ�, �򷵻�SUCCESS, ����������RANGE_ERROR
{
	int len = Length();
	int tmp;
	if (Full())
	{	// ���Ա���������OVER_FLOW
		return false;	
	}
	else if (position < 1 || position > len + 1)
	{	// position��Χ��
		return false;
	}
	else
	{	// �ɹ�
		count++;				// �����Ԫ�ظ���������1
		for (int curPosition = len; curPosition >= position; curPosition--)
		{	// ����λ��֮���Ԫ������
			GetElem(curPosition, tmp); SetElem(curPosition + 1, tmp); 
		}

		SetElem(position, e);	// ��e��ֵ��positionλ�ô�	
		return true;			// ����ɹ�
	}
}

SqList::SqList(const SqList &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��
{
	int copyLength = copy.Length();			// copy�ĳ���
	int e;

	elems = NULL;							// δ����洢�ռ�ǰ,elemsΪ��
	Init(copy.maxSize);						// ��ʼ�������Ա�
	for (int curPosition = 1; curPosition <= copyLength; curPosition++)
	{	// ��������Ԫ��
		copy.GetElem(curPosition, e);		// ȡ����curPosition��Ԫ��
		Insert(Length() + 1, e);			// ��e���뵽��ǰ���Ա�
	}
}


SqList &SqList::operator =(const SqList &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա�����ֵ�������
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy�ĳ���
		int e;

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