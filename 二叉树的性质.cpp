#include <iostream>
#include <conio.h>
#include <queue>     // 调用stl中的队列，这里是简单的，不是优先队列
#include <cstdio>
using namespace std;

//#define NULL 0
const int max1 = 1000;

struct node
{
	struct node * lchild;
	struct node * rchild;
	char data;
};

queue<char>que;

struct node * S[max1];

struct node * CreateBt()
{
	int i, j;
	char ch;
	struct node * bt, * p;
	cin >> ch;

	i = 0;
	while (ch != '$')
	{
		i++;
		if(ch != '#')
		{
			p = new node;
			p->lchild = NULL;
			p->rchild = NULL;
			p->data = ch;
		    que.push(ch);
			S[i] = p;

			if (i == 1)
				bt = p;
			else
			{
				j = i/2;
				if (i%2 == 0)
				{
					S[j]->lchild = p;
				}
				else
				{
					S[j]->rchild = p;
				}
			}

		}
		cin >> ch;
	}
	return bt;
}
// 递归判断二叉树的深度
int Height(struct node * root)
{
	if (root == NULL) return 0;
	else
	{
		int depth1 = Height(root->lchild);
		int depth2 = Height(root->rchild);
		return  depth1>depth2 ? (depth1 + 1):(depth2 + 1);
	}
}
// 递归数树的结点
int Count(struct node * root)
{
	if (root == NULL) return 0;
	else
	{
		return 1+Count(root->lchild)+Count(root->rchild);
	}
}
// 按照先序遍历
void Traverse1(struct node *root)
{
	cout << root->data << ' ';
	if (root->lchild != NULL)
		Traverse1(root->lchild);


	if (root->rchild != NULL)
		Traverse1(root->rchild);

}
// 按照中序遍历
void Traverse2(struct node *root)
{
	if (root->lchild != NULL)
		Traverse2(root->lchild);

    cout << root->data << ' ';

	if (root->rchild != NULL)
	{
		Traverse2(root->rchild);
	}
}
// 按照后序遍历
void Traverse3(struct node *root)
{
	if (root->lchild != NULL)
		Traverse3(root->lchild);

	if (root->rchild != NULL)
		Traverse3(root->rchild);

	cout << root->data << ' ';

}

// 按照层次遍历
void Traverse4()
{
	//char ch;
	while (!que.empty())
	{
		cout << que.front() << ' ';
		que.pop();
	}
}

void DisplayBt(struct node *root, int leval)
{
    if (root != NULL)
    {
        DisplayBt(root->rchild, leval+1);

        for (int i=0; i<leval-1; i++)
            cout << " ";
        cout << root->data;
        cout << endl;
        DisplayBt(root->lchild, leval+1);
    }
}

int main()
{


	struct node * root = NULL;
	int num;
	while (1)
	{
		cout << "*********************二叉树相关性质*******************\n"
			 << " 1, 创建二叉树. \n"
			 << " 2, 采用先序遍历. \n"
			 << " 3, 采用中序遍历. \n"
			 << " 4, 采用后序遍历. \n"
			 << " 5, 采用层次遍历. \n"
			 << " 6, 求二叉树的高度. \n"
			 << " 7, 求二叉树的结点总数. \n"
			 << " 8, 显示二叉树. \n"
			 << "******************************************************\n";
		cout << "请输入你的选项: ";
		cin >> num;
		switch(num)
		{
			case 1:
				cout << " \n请依次输入输入每个结点元素，没有的用'#'，代替！'$'作为结束标志\n";
				root = CreateBt(); break;
			case 2:
				if (root == NULL) {cout << "请输入创建二叉树!\n"; break;}
				cout << "先序遍历结果:\n";
				Traverse1(root);
				cout << "\n请按任意键继续...\n";
				getch();
				break;    // 先序遍历
			case 3:
				if (root == NULL) {cout << "请输入创建二叉树!\n"; break;}
				cout << "中序遍历结果:\n";
				Traverse2(root);
				cout << "\n请按任意键继续...\n";
				getch();
				break;    // 中序遍历
			case 4:
				if (root == NULL) {cout << "请输入创建二叉树!\n"; break;}
				cout << "后序遍历结果:\n";
				Traverse3(root);
				cout << "\n请按任意键继续...\n";
				getch();
				break;    // 后序遍历
			case 5:
				if (root == NULL) {cout << "请输入创建二叉树!\n"; break;}
				cout << "层次遍历结果:\n";
				Traverse4();
				cout << "\n请按任意键继续...\n";
				getch();
				break;
			case 6:
				cout << "二叉树的深度是 "<< Height(root) << endl;
				cout << "\n请按任意键继续...\n";
				getch();
				break;
			case 7:
				cout << "二叉树的结点总数是 "<< Count(root) << endl;
				cout << "\n请按任意键继续...\n";
				getch();
				break;
            case 8:
				cout << "显示二叉树是 "<< endl;
				DisplayBt(root, 1);
				cout << "\n请按任意键继续...\n";
				getch();
				break;
			default:
				cout << "没有如此方法!\n";
		}
		//system("cls");
	}
    cout << endl;
	return 0;
}
