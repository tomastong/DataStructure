#include <iostream>
#include "dbl_lk_list.h"
using namespace std;

int main()
{
	DblLinkList list;
	int e;
	if(list.Empty())
	{
		for(int i=0; i<=10; i++)
		{
			list.Insert(i, 2*i-1);
		}
	}
	list.Traverse(2);
	cout << list.Length();
	
	list.Insert(4, 888);
	list.Delete(5, e);

	cout << "\n删除元素值为" << e << endl;
	list.Traverse(4);
	cout << list.Length();
	cout << endl;

	return 0;
}

// 在第四个元素7，之前插入888，则7为敌五个元素，再删除7 