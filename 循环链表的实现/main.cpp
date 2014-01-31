#include <iostream>
#include "simple_circ_lk_list.h"
using namespace std;

int main()
{
	SimpleCircLinkList a;
	for (int i=1; i<=10; i++)
	{
		a.Insert(i, i);
	}

	a.Traverse(3);

	return 0;
}