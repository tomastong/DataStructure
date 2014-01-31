#include <iostream>
using namespace std;

#define max 10             /// 严重区分这里，宏定义和const的区别，好好用吧

class queue
{
    protected:
        int arr[max];
        int front, rear;
    public:
        queue();
        void inQueue(const int m);
        void outQueue();
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
    cout << arr[front];
    front = (front+1) % max;
}

bool queue::empty()
{
    return (rear-front+max)%max == max-1;
}


int main()
{
    queue q;
    for (int i=1; i<=9; i++)
    {
        q.inQueue(i);
    }
    cout << q.empty() << endl;
    for (int i=1; i<=8; i++)
    {
        q.outQueue();
    }
    cout << endl << q.empty() << endl;
    return 0;
}
