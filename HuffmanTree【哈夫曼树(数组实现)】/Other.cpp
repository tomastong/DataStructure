/**
******************************************************************************
*  File Name  : Other.cpp                                                    *
*  Description: ����������ʵ���ⲿ�����ļ�                                  *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : ���ݽṹ���㷨��C++��������Դ��                             *
******************************************************************************
**/


#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;


// �������ƣ�template <class ElemType> void Write(const ElemType &e)
// �������: ��������Ԫ��
//template <class ElemType>
//void Read(ElemType &elem)
//{
//    cin >>elem;    //����Ԫ�ص���Ϣ
//}


void Read(char &elem)
{
    cin >>elem;    //����Ԫ�ص���Ϣ
}

void Write(char &elem)
{
    cout <<elem;     //���Ԫ�ص���Ϣ
}
// �������ƣ�template <class ElemType> void Write(const ElemType &e)
// �������: ��ʾ����Ԫ��
//template <class ElemType>
//void Write(ElemType &elem)
//{
//    cout <<elem;     //���Ԫ�ص���Ϣ
//}

bool IsNull(char &temp)  // CreateTree�����ĸ�������
{
    return (temp == '#');
}

void Welcome( )
{
    const char *inFor[11];
    inFor[0] = "                ****************************************************              ";
    inFor[1] = "                *          Welcome To The Hufffman World!          *              ";
    inFor[2] = "                *       You Will Fall In Love In This World!       *              ";
    inFor[3] = "                *       We All Hope That Which Is Said To Us       *              ";
    inFor[4] = "                *        List's Strory Is Only The Begining        *              ";
    inFor[5] = "                ****************************************************              ";

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; inFor[i][j] != '\0'; j++)
        {
            cout <<inFor[i][j];
        }
        cout <<endl;
    }

    cout <<"Please enter any key to continue" <<endl;
    getchar( );
    system("cls");
}



void Menu( )
{
    system("cls");
    const char *menu[8] = {
        "\t\t********************************************",
        "\t\t**      1 -=> �½��ַ��͹���������        **",
        "\t\t**         2 -=> ��ʾ�ַ�������Ϣ         **",
        "\t\t**           3-=>������������             **",
        "\t\t**           4 -=> ����������             **",
        "\t\t**         5-=>������ʾ��������           **",
        "\t\t**          0 -=> �˳�����                **",
        "\t\t********************************************",
        };

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; menu[i][j] != '\0'; j++)
        {
            cout <<menu[i][j];
        }
        cout <<endl;
    }
    cout <<"����������ѡ��" <<endl;
}


// ��ʱ����
void Delay( )
{
    for(int i = 0; i < 1000000; i++);
}

// ���뺯��
void Lording( )
{
    system("cls");

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10000000; j++);
        cout <<"��";
    }
    cout <<endl;

    system("cls");
}

void Version( )
{
    cout <<"\t\t**************************************************" <<endl;
    cout <<"\t\t**  Wacky Window (c) 2012 Wacky SoftWare. Inc.  **"<<endl;
    cout <<"\t\t**     Complied on " <<__DATE__ <<" at " <<__TIME__ <<"      **"<<endl;
    cout <<"\t\t**************************************************" <<endl;
    system("pause");
}


void Stop( )        // ֹͣ����
{
    char answer;

    do
    {	// ѭ��ֱ���û�����ǡ���Ļش�Ϊֹ
        cout << "(y, n)?";
        cout << "��y��n�ش�:";
        while ((answer = getchar( )) == '\n');	// �����ո�,�Ʊ�������з���ȡһ�ַ�

    }while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');

    //#if (VERSION)     // ���������Ϣ���
    Version( );         // ��ʾ����ı�����Ϣ
  //  #endif

    if(answer == 'y' || answer == 'Y')
    {
        cout <<"�û�ѡ���˳�";
        exit(0);
    }
    else
    {
        cout <<"�û�ȡ��" <<endl;
    }
}
