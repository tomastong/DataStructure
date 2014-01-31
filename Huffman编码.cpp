#include <iostream>
#include <cstring>
using namespace std;
/*
哈夫曼编码示例程序
作者：杨勇
哈夫曼建树算法描述：
将所有权值分别构造一个只有一个结点的二叉树结点，将这些结点加入集合A（哈夫曼森林）
检查集合A成员的个数，如果为1，则算法结束，集合A中唯一的结点为哈夫曼树的根。
从集合A中取出根结点权值最小的两棵树a, b，集合中不再保留这两棵树。
由a和b分别为左、右子树构造一个新的二叉树r, 令r的权值等于a的权值与b的权值之和。
将r加入到集合A中，返回第 2 步。
*/

struct HuffmanNode //哈夫曼树结点类型
{
    char data; //结点上的数据
    int power; //结点的权值
    HuffmanNode *lchild; //左分支(作为二叉树结点时用)
    HuffmanNode *rchild; //右分支(作为二叉树结点时用)
    HuffmanNode *next; //后继指针(作为单链表结点时用)
};

//给Huffman森林（按各树根结点的值升序排列的带头结点的链表）添加一棵Huffman树
//使得链表仍然有序
void AddNode(HuffmanNode *headNode, HuffmanNode *pNode)
{
    HuffmanNode *p = headNode;
    //找到第一个权值小于给定结点的结点，p指定该结点的前一个结点
    while (p->next && p->next->power < pNode->power) p = p->next;
    pNode->next = p->next;
    p->next = pNode;
}
//功能：构造哈夫曼树
//参数说明
//n: 字符的个数
//datas: 要统计的字符
//powers: 字符对应的权值(出现的次数)
HuffmanNode* CreateHuffmanTree(int n, char datas[], int powers[])
{
    HuffmanNode head;
    head.next = NULL; //初始化森林
    for (int i = 0; i < n; i++)
    {
        HuffmanNode *pNode = new HuffmanNode;
        pNode->data = datas[i];
        pNode->power = powers[i];
        pNode->lchild = pNode->rchild = pNode->next = NULL;
        AddNode(&head, pNode);
    }
    //开始构造
    while (head.next)
    {
        if (!head.next->next) //只剩最后一个结点，这就是根
        {
            return head.next;
        }
        //取前两个出来构造一棵新树（因为链表已经按权值升序排列了，前两个就是最小的两个）
        HuffmanNode *pN1, *pN2, *pRoot;
        pN1 = head.next; //第一个结点
        pN2 = pN1->next; //第二个结点
        head.next = pN2->next; //将这两个结点从链表中删除
        pRoot = new HuffmanNode; //为这两个结点建立根结点
        pRoot->power = pN1->power + pN2->power; //权值相加
        pRoot->lchild = pN1; //左分支为第一个结点
        pRoot->rchild = pN2; //右分支为第二个结点
        //将新的根加入哈夫曼森林
        AddNode(&head, pRoot);
    }
    return NULL;
}

//计算哈夫曼树的带权路径长度PWL
//node: 树结点
//level: 当前层数
int GetPWL(HuffmanNode *node, int level)
{
    if (!node) return 0;
    if (!node->lchild && !node->rchild) return node->power * level; //是叶结点
    return GetPWL(node->lchild, level + 1) + GetPWL(node->rchild, level+1);
}

//获取所有叶点的哈夫曼编码
//node: 树结点
//code: 上层前缀
void GetCodes(HuffmanNode *node, const char *code)
{
    if (!node->lchild && !node->rchild)
    {
        //是叶结点，打印编码
        cout << node->data << " " << node->power << " " << code << endl;
        return;
    }

    int len = strlen(code);
    char *newcode = new char[len+2];
    strcpy(newcode, code);
    newcode[len+1] = '/0';
    if (node->lchild) //左分支分配'1'
    {
        newcode[len] = '1';
        GetCodes(node->lchild, newcode);
    }
    if (node->rchild) //右分支分配'0'
    {
        newcode[len] = '0';
        GetCodes(node->rchild, newcode);
    }
    delete[] newcode;
}

//释放所有结点,要按二叉树的方式
void FreeNodes(HuffmanNode *node)
{
    if (!node) return;
    FreeNodes(node->lchild);
    FreeNodes(node->rchild);
    delete node;
}
//请尝试改变主函数，使之能统计指定文本文件中的各字母出现的次数，然后给这些字母编码，并将文本文件的内容编码后输出到out.txt中
int main()
{
    int n, pow;
    char ch;
    do
    {
        cout << "请输入字母个数:";
        cin >> n;
    } while (n < 1);
    char *datas = new char[n];
    int *pows = new int[n];
    for (int i = 0; i < n; i++)
    {
        cout << "请输入第 " << i+1 << " 个字母及权值:";
        cin >> ch >> pow;
        datas[i] = ch;
        pows[i] = pow;
    }
    HuffmanNode *root = CreateHuffmanTree(n, datas, pows);
    cout << "构造出哈夫曼树的权值为：" << GetPWL(root, 0) << endl;
    cout << "所有字母的哈夫曼编码如下：" << endl;
    GetCodes(root, "");
    FreeNodes(root);
    delete[] datas;
    delete[] pows;

    return 0;
}
