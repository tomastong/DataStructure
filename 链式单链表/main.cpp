//main������

#include "simple_lk_list.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    SimpleLinkList line;
	Info stu, InfoValue;

	int num;
    int option;
	bool isNull = line.Empty();
    char ch = 'y';
while(ch == 'Y' || ch == 'y')
	{
    cout << "*****************************************************************\n";
	cout << "                       �˵�ѡ��\n";
	cout << "1> �½�ѧ����Ϣ\n";
	cout << "2> ѧ����Ϣ����\n";
	cout << "3> ѧ����Ϣɾ��\n";
	cout << "4> ѧ����Ϣ����\n";
	cout << "5> ������ݿ�\n";
	cout << "*****************************************************************\n";
    
		
		cout << "���������ѡ��:";
		cin >> option;
	
		switch(option)
		{
			case 1:
			{
				cout << "������ѧ����Ϣ������\n";
				cin >> num;

				if (isNull)
				{

					for(int i=1; i<=num; i++)
					{
						cin >> stu.Age >> stu.Name;
						line.Insert(i, stu);
					}
					cout << "��Ϣ¼��ɹ�! ^_^ \n";
				}
				break;
			}
			case 2:
			{
				int site;
				cout << "������ѧ����Ϣ��λ�ã�\n";
				cin >> site;
			
				cout << "������ѧ����Ϣ��\n";
				cin >> stu.Age >> stu.Name;
		
				line.Insert(site, stu);
				cout << "��Ϣ����ɹ�! ^_^ \n";
			
				break;
			}
			case 3:
			{
				int site;
				cout << "������Ҫɾ����Աλ�ã�\n";
				cin >> site;
				line.Delete(site, InfoValue);
				
				cout << "��Ա" << InfoValue.Age << " " << InfoValue.Name <<  "ɾ���ɹ�! ^_^ \n";
			    break;
			}
			case 4:
			{		
				line.Traverse();
				cout << "��Ϣ�����ɹ�! ^_^ \n";
				break;
			}
			case 5:
			{	
				line.Clear();
				cout << "��Ϣ��ճɹ�! ^_^ \n";
				break;
			}

			default:
				cout << "Sorry, û�и�ѡ��!\n";
		}
		
		cout << "������ y �� Y ���м���:\n";
		cin >> ch;
		system("cls");
		
    }

	return 0;
}