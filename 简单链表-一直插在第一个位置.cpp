#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;

    node() {}
};

class list
{
    protected:
        node * head;
    public:
        list();
        void insert(const int m);
        void traverse();
};

list::list()
{
    head = new node();
    head->next = NULL;
}

void list::insert(const int m)
{
    node *p;
    p = new node;
    p->data = m;
    p->next = head->next;
    head->next = p;

}

void list::traverse()
{
     node *p = head->next;
     for (; p->next!=NULL; p = p->next)
     {
         cout << p->data << " ";
     }
     cout << p->data;
     cout << endl;
}

int main()
{
    list s;
    for (int i=1; i<=10; i++)
    {
        s.insert(i);
    }
    s.traverse();

    return 0;
}
