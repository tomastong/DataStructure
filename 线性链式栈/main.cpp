#include <iostream>
#include "lk_stack.h"
using namespace std;

int main()
{
	LinkStack list;
	int e;
	
	if(list.Empty())
	{
		for (int i=1; i<=10; i++)
		{
			list.Push(2*i-1);
			cout << 2*i-1 << "  ";  // ѹ��ջ��˳��
		}
	}
	cout << endl;
	list.Traverse();                // ���ʱ�򣬱�����������ջ����ջ�ױ�����
	cout << endl;
	while(!list.Empty())
	{
		list.Pop(e);                // ���ʱ��Ԫ�صĵ���˳��ͱ���˳����һ�µ�
		cout << e << "  ";
	}
	cout << endl;

	return 0;
}