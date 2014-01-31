#include <iostream>
#include <string.h>
using namespace std;

const int maxn=128;
const int maxm = 2*maxn-1;

const int inf = 1<<13;

struct Node
{
    int parent;
    int lchild;
    int rchild;
    int weight;

    Node(int parent=0, int lchild=-1, int rchild=-1, int weight=0)
    {
        this->parent = parent;
        this->lchild = lchild;
        this->rchild = rchild;
        this->weight = weight;
    }
};

struct codeleaf
{
    char ch;
    char bit[129];
};

class Huffman
{
protected:
    int m, n;
    codeleaf H[maxn];
    Node T[maxm];

    void getMin(int &pos, int m);
public:
    Huffman() {}

    void Init();
    void createHT();
    void enCode();
    void deCode();
};

void Huffman::getMin(int &pos, int m)
{
    int minx = inf;

    for (int i=0; i<m; i++)
    {

        if(minx > T[i].weight && !T[i].parent)
        {
            pos = i;
            minx = T[i].weight;
        }

    }
}

void Huffman::Init()
{
    cout << "请输入字符的种类：\n";
    cin >> n;
    cout << "输入每一个字符和它的权重:\n";

    for (int i=0; i<n; i++)
    {
        cin >> H[i].ch >> T[i].weight;
    }
}

void Huffman::createHT()
{
    int j, k;
    m = 2*n-1;
    for (int i=n; i<m; i++)
    {
        getMin(j, i);
        T[j].parent = i;             /// 这点失误太大了，伤心啊啊！！！
        T[i].rchild = j;

        getMin(k, i);
        T[k].parent = i;
        T[i].lchild = k;

        T[i].weight = T[j].weight + T[k].weight;
    }

    T[m-1].parent = -2;
}

void Huffman::enCode()
{
    int child, start, s;
    char temp[n+1];
    temp[n] = '\0';

    for (int p=0; p<n; p++)
    {

        start = n;
        child = p;
        while ((s=T[child].parent)!=-2)       /// 这里必修加上小括号
        {
            temp[--start] = (T[s].lchild == child)? '0':'1';
            child = s;
        }
        strcpy(H[p].bit, &temp[start]);
    }

    cout << "各个字符的编码:\n";
    for (int w=0; w<n; w++)
    {
        cout << H[w].ch << ":"<<H[w].bit<<endl;
    }
}

void Huffman::deCode()
{
    char ch[1000];
    char *p = ch;

    cout << "请输入要译码的信息：\n";
    cin >> ch;

    while(*p!='\0')
    {
        int end = m-1, s;
        s = (*p == '0') ? T[end].lchild : T[end].rchild;

        while (T[s].lchild != -1 && T[s].rchild != -1)
        {
            p++;
            s = (*p == '0') ? T[s].lchild : T[s].rchild;
        }

        cout << H[s].ch;
        p++;
    }
}

int main()
{
    Huffman man;
    man.Init();
    man.createHT();
    man.enCode();
    man.deCode();

    return 0;

}
