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

	cout << "\nɾ��Ԫ��ֵΪ" << e << endl;
	list.Traverse(4);
	cout << list.Length();
	cout << endl;

	return 0;
}

// �ڵ��ĸ�Ԫ��7��֮ǰ����888����7Ϊ�����Ԫ�أ���ɾ��7 