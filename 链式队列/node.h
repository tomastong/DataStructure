#ifndef __NODE_H__
#define __NODE_H__

// 结点类
struct Node
{
// 数据成员:
	int data;				// 数据域
	Node *next;		// 指针域

// 构造函数:
	Node();						// 无参数的构造函数
	Node(int item, Node *link = NULL);	// 已知数数据元素值和指针建立结构
};

// 结点类的实现部分
Node::Node()
// 操作结果：构造指针域为空的结点
{
   next = NULL;
}

Node::Node(int item, Node *link)
// 操作结果：构造一个数据域为item和指针域为link的结点
{
   data = item;
   next = link;
}

#endif
