#include <iostream>
#include "lk_queue.h"
using namespace std;

int main()
{
	LinkQueue list;
	int e;
	if(list.Empty())
	{
		cout << "��������˳��\n";
		for(int i=1; i<=10; i++)
		{
			list.InQueue(2*i-1);
			cout << 2*i-1 << "  ";
		}
	}
	cout << endl;
	//list.Traverse();            // ��ʽ���У�����ǿ�����ǡ��Ƚ��ȳ�����������

	cout << "\n���ǳ���˳��:\n";
	while(!list.Empty())
	{
		list.OutQueue(e);      // ���ǳ���˳��
		cout << e << "  ";
	}
	cout << endl;

	//list.Traverse();

	return 0;
}