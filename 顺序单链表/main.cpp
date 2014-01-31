#include <iostream>
#include "sq_list.h"

using namespace std;

int main()
{
	SqList a;
	int num;

	cout << "线性表是否为空:(1为空，0为非空):  " << a.Empty() << endl;

	for(int i=0; i<=10; i++)
	{
		a.Insert(i, 2*i+1);
	}
    
	cout << "线性表的所有元素:\n";
	a.Traverse();
	cout << endl;
	a.Length();

	a.GetElem(4, num);
	a.Delete(4, num);

	cout << "删除第四个位置后的，线性表的所有元素:\n";
	a.Traverse();
	cout << endl;
	a.Length();

	return 0;

}