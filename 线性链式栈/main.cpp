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
			cout << 2*i-1 << "  ";  // 压入栈的顺序
		}
	}
	cout << endl;
	list.Traverse();                // 这个时候，遍历函数是由栈顶向栈底遍历的
	cout << endl;
	while(!list.Empty())
	{
		list.Pop(e);                // 这个时候，元素的弹出顺序和便利顺序是一致的
		cout << e << "  ";
	}
	cout << endl;

	return 0;
}