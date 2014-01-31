#include <iostream>
#include <cstring>
using namespace std;
/*
����������ʾ������
���ߣ�����
�����������㷨������
������Ȩֵ�ֱ���һ��ֻ��һ�����Ķ�������㣬����Щ�����뼯��A��������ɭ�֣�
��鼯��A��Ա�ĸ��������Ϊ1�����㷨����������A��Ψһ�Ľ��Ϊ���������ĸ���
�Ӽ���A��ȡ�������Ȩֵ��С��������a, b�������в��ٱ�������������
��a��b�ֱ�Ϊ������������һ���µĶ�����r, ��r��Ȩֵ����a��Ȩֵ��b��Ȩֵ֮�͡�
��r���뵽����A�У����ص� 2 ����
*/

struct HuffmanNode //���������������
{
    char data; //����ϵ�����
    int power; //����Ȩֵ
    HuffmanNode *lchild; //���֧(��Ϊ���������ʱ��)
    HuffmanNode *rchild; //�ҷ�֧(��Ϊ���������ʱ��)
    HuffmanNode *next; //���ָ��(��Ϊ��������ʱ��)
};

//��Huffmanɭ�֣�������������ֵ�������еĴ�ͷ�����������һ��Huffman��
//ʹ��������Ȼ����
void AddNode(HuffmanNode *headNode, HuffmanNode *pNode)
{
    HuffmanNode *p = headNode;
    //�ҵ���һ��ȨֵС�ڸ������Ľ�㣬pָ���ý���ǰһ�����
    while (p->next && p->next->power < pNode->power) p = p->next;
    pNode->next = p->next;
    p->next = pNode;
}
//���ܣ������������
//����˵��
//n: �ַ��ĸ���
//datas: Ҫͳ�Ƶ��ַ�
//powers: �ַ���Ӧ��Ȩֵ(���ֵĴ���)
HuffmanNode* CreateHuffmanTree(int n, char datas[], int powers[])
{
    HuffmanNode head;
    head.next = NULL; //��ʼ��ɭ��
    for (int i = 0; i < n; i++)
    {
        HuffmanNode *pNode = new HuffmanNode;
        pNode->data = datas[i];
        pNode->power = powers[i];
        pNode->lchild = pNode->rchild = pNode->next = NULL;
        AddNode(&head, pNode);
    }
    //��ʼ����
    while (head.next)
    {
        if (!head.next->next) //ֻʣ���һ����㣬����Ǹ�
        {
            return head.next;
        }
        //ȡǰ������������һ����������Ϊ�����Ѿ���Ȩֵ���������ˣ�ǰ����������С��������
        HuffmanNode *pN1, *pN2, *pRoot;
        pN1 = head.next; //��һ�����
        pN2 = pN1->next; //�ڶ������
        head.next = pN2->next; //������������������ɾ��
        pRoot = new HuffmanNode; //Ϊ��������㽨�������
        pRoot->power = pN1->power + pN2->power; //Ȩֵ���
        pRoot->lchild = pN1; //���֧Ϊ��һ�����
        pRoot->rchild = pN2; //�ҷ�֧Ϊ�ڶ������
        //���µĸ����������ɭ��
        AddNode(&head, pRoot);
    }
    return NULL;
}

//������������Ĵ�Ȩ·������PWL
//node: �����
//level: ��ǰ����
int GetPWL(HuffmanNode *node, int level)
{
    if (!node) return 0;
    if (!node->lchild && !node->rchild) return node->power * level; //��Ҷ���
    return GetPWL(node->lchild, level + 1) + GetPWL(node->rchild, level+1);
}

//��ȡ����Ҷ��Ĺ���������
//node: �����
//code: �ϲ�ǰ׺
void GetCodes(HuffmanNode *node, const char *code)
{
    if (!node->lchild && !node->rchild)
    {
        //��Ҷ��㣬��ӡ����
        cout << node->data << " " << node->power << " " << code << endl;
        return;
    }

    int len = strlen(code);
    char *newcode = new char[len+2];
    strcpy(newcode, code);
    newcode[len+1] = '/0';
    if (node->lchild) //���֧����'1'
    {
        newcode[len] = '1';
        GetCodes(node->lchild, newcode);
    }
    if (node->rchild) //�ҷ�֧����'0'
    {
        newcode[len] = '0';
        GetCodes(node->rchild, newcode);
    }
    delete[] newcode;
}

//�ͷ����н��,Ҫ���������ķ�ʽ
void FreeNodes(HuffmanNode *node)
{
    if (!node) return;
    FreeNodes(node->lchild);
    FreeNodes(node->rchild);
    delete node;
}
//�볢�Ըı���������ʹ֮��ͳ��ָ���ı��ļ��еĸ���ĸ���ֵĴ�����Ȼ�����Щ��ĸ���룬�����ı��ļ������ݱ���������out.txt��
int main()
{
    int n, pow;
    char ch;
    do
    {
        cout << "��������ĸ����:";
        cin >> n;
    } while (n < 1);
    char *datas = new char[n];
    int *pows = new int[n];
    for (int i = 0; i < n; i++)
    {
        cout << "������� " << i+1 << " ����ĸ��Ȩֵ:";
        cin >> ch >> pow;
        datas[i] = ch;
        pows[i] = pow;
    }
    HuffmanNode *root = CreateHuffmanTree(n, datas, pows);
    cout << "���������������ȨֵΪ��" << GetPWL(root, 0) << endl;
    cout << "������ĸ�Ĺ������������£�" << endl;
    GetCodes(root, "");
    FreeNodes(root);
    delete[] datas;
    delete[] pows;

    return 0;
}
