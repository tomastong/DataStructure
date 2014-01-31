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
	list.Traverse();          // 这里只是遍历,相当于压栈顺序
	cout << endl;
	while(!list.Empty())
	{
		list.Pop(e);          // 这里是出栈顺序
		cout << e << "  ";
	}

	return 0;
}