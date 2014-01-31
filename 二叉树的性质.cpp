#include <iostream>
#include <conio.h>
#include <queue>     // ����stl�еĶ��У������Ǽ򵥵ģ��������ȶ���
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
// �ݹ��ж϶����������
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
// �ݹ������Ľ��
int Count(struct node * root)
{
	if (root == NULL) return 0;
	else
	{
		return 1+Count(root->lchild)+Count(root->rchild);
	}
}
// �����������
void Traverse1(struct node *root)
{
	cout << root->data << ' ';
	if (root->lchild != NULL)
		Traverse1(root->lchild);


	if (root->rchild != NULL)
		Traverse1(root->rchild);

}
// �����������
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
// ���պ������
void Traverse3(struct node *root)
{
	if (root->lchild != NULL)
		Traverse3(root->lchild);

	if (root->rchild != NULL)
		Traverse3(root->rchild);

	cout << root->data << ' ';

}

// ���ղ�α���
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
		cout << "*********************�������������*******************\n"
			 << " 1, ����������. \n"
			 << " 2, �����������. \n"
			 << " 3, �����������. \n"
			 << " 4, ���ú������. \n"
			 << " 5, ���ò�α���. \n"
			 << " 6, ��������ĸ߶�. \n"
			 << " 7, ��������Ľ������. \n"
			 << " 8, ��ʾ������. \n"
			 << "******************************************************\n";
		cout << "���������ѡ��: ";
		cin >> num;
		switch(num)
		{
			case 1:
				cout << " \n��������������ÿ�����Ԫ�أ�û�е���'#'�����棡'$'��Ϊ������־\n";
				root = CreateBt(); break;
			case 2:
				if (root == NULL) {cout << "�����봴��������!\n"; break;}
				cout << "����������:\n";
				Traverse1(root);
				cout << "\n�밴���������...\n";
				getch();
				break;    // �������
			case 3:
				if (root == NULL) {cout << "�����봴��������!\n"; break;}
				cout << "����������:\n";
				Traverse2(root);
				cout << "\n�밴���������...\n";
				getch();
				break;    // �������
			case 4:
				if (root == NULL) {cout << "�����봴��������!\n"; break;}
				cout << "����������:\n";
				Traverse3(root);
				cout << "\n�밴���������...\n";
				getch();
				break;    // �������
			case 5:
				if (root == NULL) {cout << "�����봴��������!\n"; break;}
				cout << "��α������:\n";
				Traverse4();
				cout << "\n�밴���������...\n";
				getch();
				break;
			case 6:
				cout << "������������� "<< Height(root) << endl;
				cout << "\n�밴���������...\n";
				getch();
				break;
			case 7:
				cout << "�������Ľ�������� "<< Count(root) << endl;
				cout << "\n�밴���������...\n";
				getch();
				break;
            case 8:
				cout << "��ʾ�������� "<< endl;
				DisplayBt(root, 1);
				cout << "\n�밴���������...\n";
				getch();
				break;
			default:
				cout << "û����˷���!\n";
		}
		//system("cls");
	}
    cout << endl;
	return 0;
}
