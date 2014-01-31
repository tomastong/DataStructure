//main主程序

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
	cout << "                       菜单选项\n";
	cout << "1> 新建学生信息\n";
	cout << "2> 学生信息插入\n";
	cout << "3> 学生信息删除\n";
	cout << "4> 学生信息遍历\n";
	cout << "5> 清空数据库\n";
	cout << "*****************************************************************\n";
    
		
		cout << "请输入你的选项:";
		cin >> option;
	
		switch(option)
		{
			case 1:
			{
				cout << "请输入学生信息个数：\n";
				cin >> num;

				if (isNull)
				{

					for(int i=1; i<=num; i++)
					{
						cin >> stu.Age >> stu.Name;
						line.Insert(i, stu);
					}
					cout << "信息录入成功! ^_^ \n";
				}
				break;
			}
			case 2:
			{
				int site;
				cout << "请输入学生信息的位置：\n";
				cin >> site;
			
				cout << "请输入学生信息：\n";
				cin >> stu.Age >> stu.Name;
		
				line.Insert(site, stu);
				cout << "信息插入成功! ^_^ \n";
			
				break;
			}
			case 3:
			{
				int site;
				cout << "请输入要删除成员位置：\n";
				cin >> site;
				line.Delete(site, InfoValue);
				
				cout << "成员" << InfoValue.Age << " " << InfoValue.Name <<  "删除成功! ^_^ \n";
			    break;
			}
			case 4:
			{		
				line.Traverse();
				cout << "信息遍历成功! ^_^ \n";
				break;
			}
			case 5:
			{	
				line.Clear();
				cout << "信息清空成功! ^_^ \n";
				break;
			}

			default:
				cout << "Sorry, 没有该选项!\n";
		}
		
		cout << "请输入 y 或 Y 进行继续:\n";
		cin >> ch;
		system("cls");
		
    }

	return 0;
}