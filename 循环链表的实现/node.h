#ifndef __NODE_H__
#define __NODE_H__

struct Node
{
    //���ݳ�Ա��
    int data;             //������
    Node * next;          //ָ����

    //���캯��ģ��
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