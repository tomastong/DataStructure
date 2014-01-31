/**
******************************************************************************
*  File Name  : main.cpp                                                     *
*  Description: ����������BinTree������Դ�ļ�                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : ���ݽṹ���㷨��C++��������Դ��                             *
******************************************************************************
**/
/*
�ն˶����ַ���������Ӧ��Ƶ�ȣ���������������
��ʾ���ַ��Ĺ���������
�����ѽ��ɵĹ����������б��룻
����һ�������Ʊ��룬�������ù���������������
*/

#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <algorithm>

#include "HuffmanTree.h"

#ifdef DEBUG
#undef DEBUG
//#define DEBUG
#endif

using namespace std;

/// �ⲿ�����������ļ�Other.cpp��
void Read(char &);
void Write(char &);
bool IsNull(char &);
void Welcome( );        // ��ӭ����
void Menu( );       // �˵���ʾ����
void Delay( );      // ��ʱ����
void Lording( );    // ���뺯��
void Stop( );       // ��ֹ����



// �ڲ�����(main.cpp)

int DisStr(char *str, char chars[], int weight[]);  // ��������ַ���ת��ΪΪ��Ȩֵ���ַ���Ϣ
void CreateTree(HuffmanTree<char, int> &tree); // �½��ַ��͹���������
void ShowTree(HuffmanTree<char, int> &tree);       // ��ӡ�ַ�������Ϣ
void EnHuffman(HuffmanTree<char, int> &tree);       // ������������
void DeHuffman(HuffmanTree<char, int> &tree);   // ����������

/// ������
int main( )
{
    system("title ��������");     // ����ϵͳ�������DOS��������

    // ����״̬�µ������Ϣ
#ifdef DEBUG           // ����궨����DEBUG, ִ��һ�����
    cout <<"\t\tHello World*****************************************" <<endl;
    cout <<"\t\t**              Now Start Debug                   **" <<endl;
    cout <<"\t\t*****************************************Hello World" <<endl;
#else
    cout <<"\t\t****************************************************" <<endl;
    cout <<"\t\t**             Test HufffmanTree Of               **" <<endl;
    cout <<"\t\t****************************************************" <<endl;
#endif

    Welcome( );         // ��ӭ����

    // �����ʼ������
    int choice;
    //HuffmanTreeNode<int> node;
    HuffmanTree<char, int> tree;
    Lording( );         // ���뺯��

    while( 1 )
    {

        Menu( );        // ϵͳ�˵�

        cin >>choice;         //��������ѡ��
        system("cls");
        switch(choice)
        {
            /// 1 -=> �½�һ�������Ա�
        case 1:
            // ϵͳ��Ϣ��ʾ
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**����ǰ��ѡ��1 -=> �½��ַ��͹���������**" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // ������Բ���
            CreateTree(tree);

            // ϵͳ��Ϣ��ʾ
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              ���ݲ������            **" <<endl;
            cout <<"\t\t**             �����������˵�           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            //getchar( );
            system("pause");
            break;



            /// ��ӡ�ַ�������Ϣ
        case 2:
            // ϵͳ��ʾ��Ϣ
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**  ����ǰ��ѡ��2 -=> ��ӡ�ַ�������Ϣ  **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;

            // ������Բ���
            ShowTree(tree);

            // ϵͳ��ʾ��Ϣ
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              ���ݲ������            **" <<endl;
            cout <<"\t\t**             �����������˵�           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 3 -=> ��չ�����
        case 3:
            // ϵͳ��ʾ��Ϣ
            system("cls");
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**     ����ǰ��ѡ��3-=>������������     **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl <<endl;


            // ������Բ���
            EnHuffman(tree);


            // ϵͳ��ʾ��Ϣ
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              ���ݲ������            **" <<endl;
            cout <<"\t\t**             �����������˵�           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;
            /// 4 -=> ����������
        case 4:
            // ϵͳ��ʾ��Ϣ
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**      ����ǰ��ѡ��4 -=> ����������      **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // ������Բ���
            DeHuffman(tree);     // ��������������

            // ϵͳ��ʾ��Ϣ
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              ���ݲ������              **" <<endl;
            cout <<"\t\t**             �����������˵�             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 5-=>������ʾ��������
        case 5:
            // ϵͳ��ʾ��Ϣ
            system("cls");
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**    ����ǰ��ѡ��5-=>������ʾ��������    **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl <<endl;

            // ������Բ���
            tree.DisplayWithShape( );

            // ϵͳ��ʾ��Ϣ
            cout <<"\t\t********************************************" <<endl;
            cout <<"\t\t**              ���ݲ������              **" <<endl;
            cout <<"\t\t**             �����������˵�             **" <<endl;
            cout <<"\t\t********************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;
            system("pause");
            break;

            /// 0 -=> �˳�����
        case 0:
            // ϵͳ��ʾ��Ϣ
            cout <<"\t\t******************************************" <<endl;
            cout <<"\t\t**              ���ݲ������            **" <<endl;
            cout <<"\t\t**             �����������˵�           **" <<endl;
            cout <<"\t\t******************************************" <<endl <<endl;
            cout <<"Please ent any key to continue........................" <<endl;          // ϵͳ��ʾ��Ϣ

            Stop( );

            Lording( );         // ���뺯��
        }
    }

    return 0;
}


// ��������ַ���ת��ΪΪ��Ȩֵ���ַ���Ϣ
int DisStr(char *str, char chars[], int weight[])
{
    int i, j, count;
    sort(str, str + strlen(str));     // ���ַ�������������

    i = 0;
    j = 0;
    count = 1;
    while(str[i] != '\0')
    {
        if(str[i] == str[i+1])
        {
            count++;            // ����������1
        }
        else
        {
            chars[j] = str[i];        // ����ǰ�ַ������ַ���Ϣ����
            weight[j] = count;        // ����ǰ�ַ���Ȩֵ�����ַ���Ϣ����
            j++;
            count = 1;
        }
        i++;
    }

//    #ifdef DEBUG
//    for(int i = 0; i < j; i++)
//    {
//        cout <<weight[i]<<chars[i];
//    }
//    #endif

    return j;
}


void CreateTree(HuffmanTree<char, int> &tree) // ��������������
{
    char str[81];
    char chars[100];
    int weight[100];
    int size;

    cout <<"��������Ҫ������ַ���" <<endl;
    cin >>str;
    size = DisStr(str, chars, weight);      // ����������ַ���

    tree.CreateHuffmanTree(chars, weight, size);        // �������������
}

void ShowTree(HuffmanTree<char, int> &tree)       // ��ʾ���ַ��Ĺ���������
{
    for(int i = 1; i <= tree.Size( ); i++)
    {
        cout <<tree.Char(i) <<" : "  <<tree.EnCode(tree.Char(i)) <<endl;
    }
}

void EnHuffman(HuffmanTree<char, int> &tree)     // ��������������
{
    cout <<"��ǡ�������ı�������Ϊ:" <<endl;
    ShowTree(tree);     // ������ʾ������Ϣ

    string huffman;
    string strCode;
    while( 1 )
    {

        cout <<endl <<endl <<"��������Ҫ����ı��봮[����\"#\"ֹͣ����]" <<endl <<"huffman =";
        cin >>strCode;

        if(strCode == "#")      // ����#ֹͣ����
        {
            break;
        }

        huffman = "";
        for(unsigned int pos = 0; pos < strCode.size(); pos++)
        {
            huffman += tree.EnCode(strCode[pos]);
        }

        cout <<"��ǰ���������Ĺ�����������ϢΪ��" <<endl;
        cout <<huffman <<endl;
    }
}

void DeHuffman(HuffmanTree<char, int> &tree)     // ��������������
{
    cout <<"��ǡ�������ı�������Ϊ:" <<endl;
    ShowTree(tree);     // ������ʾ������Ϣ

    string huffman;
    while( 1 )
    {
        cout <<endl <<endl <<"��������Ҫ����ı��봮[����\"#\"ֹͣ����]" <<endl <<"huffman =";
        cin >>huffman;

        if(huffman == "#")      // ����#ֹͣ����
        {
            break;
        }

        cout <<"��ǰ����Ĺ���������Ϊ:" <<endl;
        cout <<tree.DeCode(huffman);
    }
}





