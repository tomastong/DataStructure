#ifndef __DBL_NODE_H__
#define __DBL_NODE_H__


// 双向链表结点类
struct DblNode
{
// 数据成员:
	int data;				// 数据域
	DblNode *back;	// 指向前驱的指针域
	DblNode *next;	// 指向后继的指针域

// 构造函数:
	DblNode();						// 无数据的构造函数
	DblNode(int item,
	DblNode *linkBack = NULL,
	DblNode *linkNext = NULL);// 已知数据域和指针域建立结构
};


// 双向链表结点类的实现部分

DblNode::DblNode()
// 操作结果：构造指针域为空的结点
{
   next = NULL;
}

DblNode::DblNode(int item,
			DblNode *linkBack,
			DblNode *linkNext)
// 操作结果：构造一个数据域为item和指针域为linkBack和linkNext的结点
{
   data = item;
   back = linkBack;
   next = linkNext;
}


#endif
