#include <iostream>
#include "sq_list.h"

using namespace std;

int main()
{
	SqList a;
	int num;

	cout << "���Ա��Ƿ�Ϊ��:(1Ϊ�գ�0Ϊ�ǿ�):  " << a.Empty() << endl;

	for(int i=0; i<=10; i++)
	{
		a.Insert(i, 2*i+1);
	}
    
	cout << "���Ա������Ԫ��:\n";
	a.Traverse();
	cout << endl;
	a.Length();

	a.GetElem(4, num);
	a.Delete(4, num);

	cout << "ɾ�����ĸ�λ�ú�ģ����Ա������Ԫ��:\n";
	a.Traverse();
	cout << endl;
	a.Length();

	return 0;

}