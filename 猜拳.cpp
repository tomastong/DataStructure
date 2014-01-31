/*********************************Program Description*****************************
purpose: 用C++写一个石头剪刀布的游戏，人机对战，结果输出一共多少局，赢了多少局
author: Dong-Hong-Yan
created: 2013-5-11
version: codeblocks 10.05 编译通过
**********************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cTime>

using namespace std;

int main()
{
    cout << "              ***********************************\n";
    cout << "              *            猜拳游戏             *\n";
    cout << "              *   石头（S） 剪刀（J） 布（B）   *\n";
    cout << "              *  石头赢剪刀，剪刀赢布，布赢石头 *\n";
    cout << "              *      输入字符 'N' 退出游戏      *\n";
    cout << "              ***********************************";

    char arr[]= {'S','J','B'};
    srand((unsigned)time(NULL));

    char A = arr[rand()%3];
    char B;
    int cnt=0, win=0,flag=0;

    while (1 && B!='N' && B!='n')
    {

        cnt++;

        cout << "\n您要出拳：";
        cin >> B;

        switch (B)
        {
        case 'S':
        case 's':
            if (A == 'B'||A == 'b')
            {
                win++;
                cout << "电脑出拳是：" << A << "，您出的是：" << B
                     << "，太遗憾，您输了！";
            }
            else if (A == 'S'||A == 's')
            {
                flag++;
                cout << "电脑出拳是：" << A << "，您出的是：" << B
                     << "，很遗憾，平局！";
            }
            else
            {
                cout << "电脑出拳是：" << A << "，您出的是：" << B
                     << "，恭喜您，您赢了！";
            }
            break;
        case 'J':
        case 'j':
            if (A == 'S'||A == 's')
            {
                win++;
                cout << "电脑出拳是：" << A << "，您出的是：" << B
                     << "，太遗憾，您输了！";
            }
            else if (A == 'J'||A == 'j')
            {
                flag++;
                cout << "电脑出拳是：" << A << "，您出的是：" << B
                     << "，很遗憾，平局！";
            }
            else
            {
                cout << "电脑出拳是：" << A << "，您出的是：" << B
                     << "，恭喜您，您赢了！";
            }
            break;
        case 'B':
        case 'b':
            if (A == 'J'||A == 'j')
            {
                win++;
                cout << "电脑出拳是：" << A << "，您出的是：" << B
                     << "，太遗憾，您输了！";
            }
            else if (A == 'B'||A == 'b')
            {
                flag++;
                cout << "电脑出拳是：" << A << "，您出的是：" << B
                     << "，很遗憾，平局！";
            }
            else
            {
                cout << "电脑出拳是：" << A << "，您出的是：" << B
                     << "，恭喜您，您赢了！";
            }
            break;
        default:
            if (B!='N' && B!='n')
            {
                cout << "对不起，输入有误，请重新输入...\n";
                cnt--;
            }
        }

        A = arr[rand()%3];
    }

    cout << "              *************Game Over*************\n";
    cout << "              您好，一共玩了"<< --cnt <<"局\n";
    cout << "              您赢了"<<win<<"局，平了"<<flag<<"局,输了"<<cnt-flag-win<<"局\n";
    return 0;
}
