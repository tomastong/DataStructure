#include <iostream>
#include "sq_stack.h"
using namespace std;

int main()
{
	SqStack list;
	int e;
	if(list.Empty())
	{
		for(int i=1; i<=10; i++)
		{
			list.Push(2*i-1);
		}
	}
	list.Traverse();          // ����ֻ�Ǳ���,�൱��ѹջ˳��
	cout << endl;
	while(!list.Empty())
	{
		list.Pop(e);          // �����ǳ�ջ˳��
		cout << e << "  ";
	}

	return 0;
}