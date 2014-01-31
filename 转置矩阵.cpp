#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXSIZE 12500
typedef int datatype;



struct node
{
	int i, j;      // Ԫ�ص�����������λ��
	datatype v;    // Ԫ�ص�ֵ
}data[MAXSIZE];

int cmp(const void *a, const void *b)
{
	return ((struct node *)a)->i - ((struct node *)b)->i;
}

int main()
{
	int num,
	//int m=0, k=0, s=0;
	int col, row;
	int count;
	//memset(data, 0, sizeof(data));
	printf("���������Ԫ�ĸ���,��������������� : \n");
    scanf("%d %d %d", &row, &col, &num);

    //p = (node *)malloc(num*sizeof(node));
	for ( m=0; m<num; m++)
	{
		scanf("%d %d %d", &data[m].i, &data[m].j, &data[m].v);
	}
    printf("\nת��ǰ,��ӡ�������״����:\n");

	for (int s=0; s<row; s++)
	{
		for (int k=0; k<col; k++)
		{
			for (int m=0; m<num; m++)
			{   count = 0;
				if (s==data[m].i && k==data[m].j)
				{
					printf("%d ", data[m].v);
					count = 1;
					break;
				}
			}
			if (count == 0)
				printf("0 ");
		}
		printf("\n");
	}
	printf("\nת�ú�,��ӡ�������״����:\n");
	qsort(data, num, sizeof(data[0]), cmp);

	for (s=0; s<row; s++)
	{
		for (k=0; k<col; k++)
		{
			for (m=0; m<num; m++)
			{   count = 0;
				if (s==data[m].j && k==data[m].i)
				{
					printf("%d ", data[m].v);
					count = 1;
					break;
				}
			}
			if (count == 0)
				printf("0 ");
		}
		printf("\n");
	}

    return 0;
}
