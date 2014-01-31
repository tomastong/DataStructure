#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__


// 顺序栈类

class SqStack
{
protected:
//  顺序栈的数据成员:
	int count;										// 元素个数
	int maxSize;									// 栈最大元素个数
	char *elems;								// 元素存储空间

// 辅助函数
	bool Full() const;								// 判断栈是否已满
	void Init(int size);							// 初始化栈

public:
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	SqStack(int size = 1000);				// 构造函数
	virtual ~SqStack();								// 析构函数
	int Length() const;								// 求栈长度
	bool Empty() const;								// 判断栈是否为空
	void Clear();									// 将栈清空
//	void Traverse(void (*Visit)(const ElemType &)) const;	// 遍历栈
	void Push(const char &e);				// 入栈
	void Top(char &e) const;				// 返回栈顶元素
	void Pop(char &e);					// 出栈
	SqStack(const SqStack &copy);			// 复制构造函数
	SqStack &operator =(const SqStack &copy); // 赋值语句重载
};


// 顺序栈类的实现部分

bool SqStack::Full() const
// 操作结果：如栈已满，则返回true，否则返回false
{
	return count == maxSize;
}


void SqStack::Init(int size)
// 操作结果：初始化栈为最大元素个数为size的空栈
{
	maxSize = size;						// 最大元素个数
	if (elems != NULL) delete []elems;	// 释放存储空间
	elems = new char[maxSize];		// 分配存储空间
	count = 0;							// 空栈元素个数为0
}

SqStack ::SqStack(int size)
// 操作结果：构造一个最大元素个数为size的空栈
{
	elems = NULL;						// 未分配存储空间前,elems为空
	Init(size);							// 初始化栈
}

SqStack ::~SqStack()
// 操作结果：销毁栈
{
	delete []elems;					// 释放存储空间
}

int SqStack ::Length() const
// 操作结果：返回栈元素个数
{
	return count;
}

bool SqStack ::Empty() const
// 操作结果：如栈为空，则返回true，否则返回false
{
	return count == 0;
}

void SqStack ::Clear()
// 操作结果：清空栈
{
	count = 0;
}

/*void SqStack ::Traverse(void (*Visit)(const ElemType &)) const
// 操作结果：从栈底到栈顶依次对栈的每个元素调用函数(*visit)
{
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// 从栈底到栈顶对栈的每个元素调用函数(*visit)
		(*Visit)(elems[curPosition - 1]);
	}
}
*/
void SqStack ::Push(const char &e)
// 操作结果：将元素e追加到栈顶,如成功则返加SUCCESS,如栈已满将返回OVER_FLOW
{
	if (Full())
	{	// 栈已满
	//	return OVER_FLOW;
	}
	else
	{	// 操作成功
		elems[count++] = e;	// 将元素e追加到栈顶
	//	return SUCCESS;
	}
}

void SqStack ::Top(char &e) const
// 操作结果：如栈非空,用e返回栈顶元素,函数返回SUCCESS,否则函数返回UNDER_FLOW
{
	if(Empty())
	{	// 栈空
	//	return UNDER_FLOW;
	}
	else
	{	// 栈非空,操作成功
		e = elems[count - 1];				// 用e返回栈顶元素
//		return SUCCESS;
	}
}

void SqStack ::Pop(char &e)
// 操作结果：如栈非空,删除栈顶元素,并用e返回栈顶元素,函数返回SUCCESS,否则
//	函数返回UNDER_FLOW
{
	if (Empty())
	{	// 栈空
	//	return UNDER_FLOW;
	}
	else
	{	// 操作成功
		e = elems[count - 1];				// 用e返回栈顶元素
		count--;                               // 这里如果将两个语句合写为一个句子，应该这么写 e = elems[--count];
		//return SUCCESS;
	}
}

SqStack ::SqStack(const SqStack  &copy)
// 操作结果：由栈copy构造新栈--复制构造函数
{
	elems = NULL;							// 未分配存储空间前,elems为空
	Init(copy.maxSize);						// 初始化新栈
	count = copy.count;						// 栈元素个数
	for (int curPosition = 1; curPosition <= Length(); curPosition++)
	{	// 从栈底到栈顶对栈copy的每个元素进行复制
		elems[curPosition - 1] = copy.elems[curPosition - 1];
	}
}

SqStack  &SqStack ::operator = (const SqStack  &copy)
// 操作结果：将栈copy赋值给当前栈--赋值语句重载
{
	if (&copy != this)
	{
		Init(copy.maxSize);					// 初始化当前栈
		count = copy.count;					// 复制栈元素个数
		for (int curPosition = 1; curPosition <= Length(); curPosition++)
		{	// 从栈底到栈顶对栈copy的每个元素进行复制
			elems[curPosition - 1] = copy.elems[curPosition - 1];
		}
	}
	return *this;
}

#endif
