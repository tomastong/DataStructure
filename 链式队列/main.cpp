#include <iostream>
#include "lk_queue.h"
using namespace std;

int main()
{
	LinkQueue list;
	int e;
	if(list.Empty())
	{
		cout << "这是入列顺序：\n";
		for(int i=1; i<=10; i++)
		{
			list.InQueue(2*i-1);
			cout << 2*i-1 << "  ";
		}
	}
	cout << endl;
	//list.Traverse();            // 链式队列，这里强调就是“先进先出，后进后出”

	cout << "\n这是出列顺序:\n";
	while(!list.Empty())
	{
		list.OutQueue(e);      // 这是出列顺序
		cout << e << "  ";
	}
	cout << endl;

	//list.Traverse();

	return 0;
}