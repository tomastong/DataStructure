/******************************************Program Description*****************************************
purpose : ��һ������ͼ�������ڽӾ����У�����ֱ�ʵ��DFS��BFS.
author : Dong-ong-Yan
created : 2012-12-15(14:22:34)
version : codeblocks 10.05 ����ͨ��
******************************************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

#define max 100

/// ����򵥶�����
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

/// ����ͼ��
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
    cout << "������ͼ����ĸ����ͱߵĸ���:\n";
    cin >> num >> side;

    cout << "����������ߵ�������������:\n";
    int m, n;
    for (int i=1; i<=side; i++)
    {
        cin >> m >> n;
        edge[m][n] = edge[n][m] = 1;
    }
    cout << "�ڽӾ����ʼ������!\n";
}

void map::dfs(int x)
{
    count++;
    v[x] = 1;

    cout << "���ʶ���" << x << endl;
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
        cout << "���ʶ���" << t << endl;
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

    cout << "������dfs����\n";
    m.dfs(1);

    cout << "\n\n������bfs����\n";
    m.bfs(1);

    return 0;
}
/**
����������
Sample input:
4 6

1 2
1 3
1 4
2 3
2 4
3 4
Sample output:
������dfs����
���ʶ���1
���ʶ���2
���ʶ���3
���ʶ���4


������bfs����
���ʶ���1
���ʶ���2
���ʶ���3
���ʶ���4
*/
