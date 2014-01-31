#include <stdio.h>
#include <iostream>
using namespace std;

const int max = 100;

struct node
{
    node *lchild;
    node *rchild;
    char data;
};

struct node *S[100];

struct node * Create()
{
    int i, j;
    char ch;
    struct node *bt, *p;
    cin >> ch;
    i=0;
    while(ch!='0')
    {
        i++;
        if (ch!='#')
        {
            p = new node;
            p->lchild = NULL;
            p->rchild = NULL;
            p->data = ch;
            S[i] = p;

            if (i==1) bt = p;
            else
            {

                j = i/2;
                if (i%2==0)
                    S[j]->lchild = p;
                else
                    S[j]->rchild = p;

            }
        }
        cin >> ch;
    }
    return bt;
}

void Traverse(struct node * bt)
{

    if (bt->lchild!=NULL)
        Traverse(bt->lchild);
    cout << bt->data;
    if (bt->rchild!=NULL)
        Traverse(bt->rchild);
}

int main()
{
    Traverse(Create());
    return 0;
}
    /* 1
   2   3
    4 5 6
*/

