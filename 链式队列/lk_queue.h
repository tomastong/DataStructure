#ifndef __LK_QUEUE_H__
#define __LK_QUEUE_H__

#include "node.h"				// 结点类

// 链队列类

class LinkQueue
{
protected:
//  链队列实现的数据成员:
	Node *front, *rear;					// 队头队尾指指

// 辅助函数:
	//void Init();									// 初始化队列

public:
//  抽象数据类型方法声明及重载编译系统默认方法声明:
	LinkQueue();									// 无参数的构造函数
	virtual ~LinkQueue();							// 析构函数
	int Length() const;								// 求队列长度
	bool Empty() const;								// 判断队列是否为空
	void Clear();									// 将队列清空
	void Traverse() const ;	// 遍历队列
    void OutQueue(int &e);				// 出队操作
	void GetHead(int &e) const;			// 取队头操作
    void InQueue(const int &e);			// 入队操作
	LinkQueue(const LinkQueue &copy);		// 复制构造函数
	LinkQueue &operator =(const LinkQueue &copy);// 赋值语句重载
};

// 链队列类的实现部分
/*
void LinkQueue::Init()
// 操作结果：初始化队列
{
	rear = front = new Node;	// 生成头结点
}*/

LinkQueue::LinkQueue()
// 操作结果：构造一个空队列
{
    rear = front = new Node;	// 生成头结点
}

LinkQueue::~LinkQueue()
// 操作结果：销毁队列
{
	Clear();
}

int LinkQueue::Length() const
// 操作结果：返回队列长度
{
	int count = 0;		// 计数器
	for (Node *tmpPtr = front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// 用tmpPtr依次指向每个元素
		count++;		// 对栈每个元素进行计数
	}
	return count;
}

bool LinkQueue::Empty() const
// 操作结果：如队列为空，则返回true，否则返回false
{
   return rear == front;
}

void LinkQueue::Clear()
// 操作结果：清空队列
{
	int tmpElem;	// 临时元素值
	while (Length() > 0)
	{	// 队列非空，则出列
		OutQueue(tmpElem);                   // 晴空用出列来表示，效果同删除
	}
}

void LinkQueue::Traverse() const
// 操作结果：依次对队列的每个元素调用函数(*visit)
{
	for (Node *tmpPtr = front->next; tmpPtr != NULL;
		tmpPtr = tmpPtr->next)
	{	// 对队列每个元素调用函数(*visit)
        std::cout << tmpPtr->data << "  ";
	}
}


void LinkQueue::OutQueue(int &e)
// 操作结果：如果队列非空，那么删除队头元素，并用e返回其值，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty())
	{	// 队列非空
		Node *tmpPtr = front->next;	// 指向队列头素
		e = tmpPtr->data;						// 用e返回队头元素
		front->next = tmpPtr->next;				// front指向下一元素
		if (rear == tmpPtr)
		{	// 表示出队前队列中只有一个元素，出队后为空队列
			rear = front;
		}
		delete tmpPtr;							// 释放出队的结点
		//return SUCCESS;
	}
	else
	{	// 队列为空
		//return UNDER_FLOW;
	}
}

void LinkQueue::GetHead(int &e) const
// 操作结果：如果队列非空，那么用e返回队头元素，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!Empty())
	{	// 队列非空
		Node *tmpPtr = front->next;	// 指向队列头素
		e = tmpPtr->data;						// 用e返回队头元素
		//return SUCCESS;
	}
	else
	{	// 队列为空
		//return UNDER_FLOW;
	}
}

void LinkQueue::InQueue(const int &e)
// 操作结果：插入元素e为新的队尾，返回SUCCESS
{
	Node *tmpPtr = new Node(e);	// 生成新结点
	rear->next = tmpPtr;							// 新结点追加在队尾
	rear = tmpPtr;									// rear指向新队尾
	//return SUCCESS;
}


LinkQueue::LinkQueue(const LinkQueue &copy)
// 操作结果：由队列copy构造新队列--复制构造函数
{
//	Init();
	rear = front = new Node;	// 生成头结点
	for (Node *tmpPtr = copy.front->next; tmpPtr != NULL;
		tmpPtr = tmpPtr->next)
	{	// 对copy队列每个元素对当前队列作入队列操作
		InQueue(tmpPtr->data);
	}
}

LinkQueue &LinkQueue::operator =(const LinkQueue &copy)
// 操作结果：将队列copy赋值给当前队列--赋值语句重载
{
	if (&copy != this)
	{
		Clear();
		for (Node *tmpPtr = copy.front->next; tmpPtr != NULL;
			tmpPtr = tmpPtr->next)
		{	// 对copy队列每个元素对当前队列作入队列操作
			InQueue(tmpPtr->data);
		}
	}
	return *this;
}

#endif
