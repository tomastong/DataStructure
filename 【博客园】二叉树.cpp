#include <iostream>
#include <cstdio>
using namespace std;
struct node
{
    int data;
    node *left;
    node *right;
} root;
struct node *insert(node *r,int a)
{
    if(r==NULL)
    {
        r = new node;
        r->data = a;
        r->left = NULL;
        r->right = NULL;
    }
    else
    {
        if(r->data>a)
        {
            r->left = insert(r->left,a);
        }
        else
        {
            r->right = insert(r->right,a);
        }
    }	return r;
} void preorder(node *r)
{
    if(r!=NULL)
    {
        printf("%d\n",r->data);
        preorder(r->left);
        preorder(r->right);
    }
}
void inorder(node *r)
{
    if(r!=NULL)
    {
        inorder(r->left);
        printf("%d\n",r->data);
        inorder(r->right);
    }
}
void postorder(node *r)
{
    if(r!=NULL)
    {
        postorder(r->left);
        postorder(r->right);
        printf("%d\n",r->data);
    }
}
int main()
{
   // freopen("sum.in","r",stdin);
   // freopen("sum.out","w",stdout);
    int n,t,a;
    cin>>t;
    while(t--)
    {
        node *r = &root;
        r = NULL;
        cin>>n;
        for(int i=1; i<=n; i++)
        {
            cin>>a;
            r = insert(r,a);
        }
        printf("----------------------前序遍历\n");
        preorder(r);
        printf("----------------------中序遍历\n");
        inorder(r);
        printf("----------------------后序遍历\n");
        postorder(r);
    }
    return 0;
}
