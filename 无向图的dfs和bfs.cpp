/******************************************Program Description*****************************************
purpose : 将一个无向图储存在邻接矩阵中，对其分别实现DFS和BFS.
author : Dong-ong-Yan
created : 2012-12-15(14:22:34)
version : codeblocks 10.05 编译通过
******************************************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

#define max 100

/// 定义简单队列类
class queue
{
    protected:
        int arr[max];
        int front, rear;
    public:
        queue();
        void inQueue(const int m);
        void outQueue();
        int getFront();
        int length();
        bool empty();
};

queue::queue()
{
    front = rear = 0;
}

void queue::inQueue(const int m)
{
    arr[rear] = m;
    rear = (rear+1) % max;
}

void queue::outQueue()
{
    front = (front+1) % max;
    return;
}

int queue::getFront()
{
    return arr[front];
}

bool queue::empty()
{
    return (rear-front+max)%max == max-1;
}

int queue::length()
{
    return (rear-front+max)%max;
}

/// 定义图类
class map
{
    protected :
        int num, side, count;
        int edge[max][max];
        int v[max];
    public :
        map();
        void init();
        void dfs(int x);
        void bfs(int x);
};

map::map()
{
    for (int i=0; i<max; i++)
        for (int j=0; j<max; j++)
            v[i] = 0;
    for (int i=0; i<max; i++)
        v[i] = 0;
    count = 0;
}

void map::init()
{
    cout << "请输入图顶点的个数和边的个数:\n";
    cin >> num >> side;

    cout << "请输入任意边的两个顶点坐标:\n";
    int m, n;
    for (int i=1; i<=side; i++)
    {
        cin >> m >> n;
        edge[m][n] = edge[n][m] = 1;
    }
    cout << "邻接矩阵初始化结束!\n";
}

void map::dfs(int x)
{
    count++;
    v[x] = 1;

    cout << "访问顶点" << x << endl;
    if (count == num)
    {
        return;
    }
    for (int i=1; i<=num; i++)
    {
        if (edge[x][i] && !v[i])
        {
            dfs(i);
        }
    }

    return;
}

void map::bfs(int x)
{
    queue q;
    int t;
    q.inQueue(x);

    for (int i=0; i<max; i++)
        v[i] = 0;
    v[x] = 1;
    while (q.length())
    {
        t = q.getFront();
        cout << "访问顶点" << t << endl;
        for (int i=1; i<=num; i++)
        {
            if (edge[x][i] && !v[i])
            {
                q.inQueue(i);
                v[i] = 1;
            }
        }
        q.outQueue();
    }

    return;
}

int main()
{
    map m;
    m.init();

    cout << "这里是dfs遍历\n";
    m.dfs(1);

    cout << "\n\n这里是bfs遍历\n";
    m.bfs(1);

    return 0;
}
/**
测试用例：
Sample input:
4 6

1 2
1 3
1 4
2 3
2 4
3 4
Sample output:
这里是dfs遍历
访问顶点1
访问顶点2
访问顶点3
访问顶点4


这里是bfs遍历
访问顶点1
访问顶点2
访问顶点3
访问顶点4
*/
