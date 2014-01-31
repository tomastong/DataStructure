#ifndef __NODE_H__
#define __NODE_H__

struct Node
{
    //数据成员：
    int data;             //数据域
    Node * next;          //指针域

    //构造函数模板
    Node();
    Node(int item, Node * link = NULL);
};

Node::Node()
{
    next = NULL;
}

Node::Node(int item, Node * link)
{
    data = item;
    next = link;
}


#endif   // __NODE_H__