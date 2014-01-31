/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : HuffmanTree.h                                                *
*  Description: ��������HuffmanTree��ģ��ͷ�ļ�                             *                                       *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : ���ݽṹ���㷨��C++��������Դ��                             *
******************************************************************************
**/

#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED

#include <algorithm>
#include <string>
#include <iomanip>


#include "HuffmanTreeNode.h"

/// ����������ģ����������
template <class CharType, class WeightType>
class HuffmanTree
{
    /*===========================��PUBLIC�������ӿڡ�============================*/
public :      // �����ӿ�
    // ����������HuffmanTree������Ա����
    HuffmanTree( );                     // Ĭ�Ϲ��캯��ģ��

    HuffmanTree(CharType *chars, WeightType *weight, int size); //  ���ַ�chars[], Ȩֵweight[]���ַ�����size�����������

    HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);     // ���ƹ��캯��

    ~HuffmanTree( );            // ��������ģ��

    HuffmanTree<CharType, WeightType> &operator=(const HuffmanTree<CharType, WeightType> &copy);

    // ������Ա����ʵ��
    void CreateHuffmanTree(CharType *chars, WeightType *weight, int size);   // ���ַ�chars[], Ȩֵweight[]���ַ�����size�����������

    std::string EnCode(CharType chType);               // ���뺯��

  //  std::string EnCode(std::String charCode);             // ���뺯��

    std::string DeCode(std::string strCode);                  // ���뺯��

    int Size( );                         // ��ȡ��ǰ���������Ľ����Ŀ

    CharType Char(int pos);             // ��ȡ��ǰ����������ĵ�pos���ַ�����

    void DisplayWithShape( );
/*===========================��PUBLIC�������ӿڡ�============================*/
///////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////
    /*=========================��PROTECTED��������Ա��===========================*/
protected :
    // ����������HuffmanTree���ݳ�Ա
    HuffmanTreeNode<WeightType> *m_nodes;   // �洢�����Ϣ, m_nodes[0]��ʹ��
    CharType *m_leafChars;                  // Ҷ����ַ���Ϣ, m_LeafChars[0]��ʹ��
    std::string *m_leafCharCodes;                 // char **m_leafCharCodesҶ����ַ��ı�����Ϣ, m_leafCharCodes[0]��ʹ��
    int m_curPos;                           // ����ʱ�Ӹ���㵽Ҷ���·���ĵ�ǰ���
    int m_size;                              // Ҷ������Ŀ

    // ����������HuffmanTree��������
    void Select(int cur, int &minOne, int &minTwo); // ��m_nodes[0~curPos-1]��ѡ��˫��Ϊ0[Ҳ���ǻ�û�м�����������еı���], Ȩֵ

    void DisplayWithShape(int root, int level);                // ������ʾ��������
};


/// ����������ģ��ʵ�ֲ���
/**��������������Ϣ[ʵ��]************************************************************************************************************
    void Select(int cur, int &minOne, int &minTwo); // ��m_nodes[0~curPos-1]��ѡ��˫��Ϊ0[Ҳ���ǻ�û�м�����������еı���], Ȩֵ
    void DisplayWithShape(int root);                // ������ʾ��������
************************************************************************************************************��������������Ϣ[ʵ��]**/
// �������ƣ�void Select(int cur, int &minOne, int &minTwo)
// ����������ݹ鸴��ÿ��������Ϣ
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::Select(int cur, int &minOne, int &minTwo) // ��m_nodes[0~curPos-1]��ѡ��˫��Ϊ0[Ҳ���ǻ�û�м�����������еı���], Ȩֵ
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    minOne = minTwo = 0;
    //len = 2*cur;
    for (int pos = 1; pos <= cur; pos++)        // ѭ�����еĽ��
    {
        if (m_nodes[pos].m_parent != 0)
        {
            continue;	// ˫����0�Ľ���Ѿ����뵽�����������˲���Ҫ�����
        }

        if(minOne == 0)     // minOneΪ��ֵ��,��pos��ֵ��minOne[��С]
        {
            minOne = pos;
        }

        if(m_nodes[pos].m_weight < m_nodes[minOne].m_weight)  // m_nodes[pos]Ȩֵ��m_nodes[minOne]��С,��pos��ΪminOne
        {
            // ���ҵ�ǰδ������������е�Ȩֵ��С��
            minOne = pos;
        }
    }

    for (int pos = 1; pos <= cur; pos++)        // ѭ�����еĽ��
    {
        if(m_nodes[pos].m_parent != 0)
        {
            continue;	// ˫����0�Ľ���Ѿ����뵽�����������˲���Ҫ�����
        }

        if(minTwo == 0 && m_nodes[minOne].m_weight != m_nodes[pos].m_weight)       // minTwoΪ��ֵ��,��pos��ֵ��minTwo[��С]
        {
            minTwo = pos;
        }
        else if((m_nodes[pos].m_weight < m_nodes[minTwo].m_weight) && pos != minOne)// m_nodes[pos]Ȩֵ��m_nodes[minOne]��С,��pos��ΪminOne
        {
            // ���ҵ�ǰδ������������е�Ȩֵ��С��
            minTwo = pos;
        }
        //std::cout <<"minOne = " <<minOne <<", minTwo = " <<minTwo <<std::endl;
    }
}

template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::DisplayWithShape(int root, int level)  // ������ʾ��������
{
    if(m_nodes[root].m_leftChild == 0 && m_nodes[root].m_rightChild == 0)
    {
        std::cout <<std::endl;
        for(int i = 0; i < level-1; i++)
        {
            std::cout <<"   ";
        }
        if(root > m_size)
        {
            std::cout <<std::setw(2)<<m_nodes[root].m_weight <<"#";
        }
        else
        {
            std::cout <<std::setw(2)<<m_nodes[root].m_weight <<m_leafChars[root];
        }
        //return ;
    }
    else //(m_nodes[m_curPos].m_rightChild == 0))
    {
        // ��ʾ������
        DisplayWithShape(this->m_nodes[root].m_rightChild, level+1);

        std::cout <<std::endl;
        for(int i =0; i  < level-1; i++)
        {
            std::cout <<"   ";
        }
        if(root > m_size)
        {
            std::cout <<std::setw(2)<<m_nodes[root].m_weight <<"#";
        }
        else
        {
            std::cout <<std::setw(2)<<m_nodes[root].m_weight <<m_leafChars[root];
        }
        // ��ʾ������
        DisplayWithShape(this->m_nodes[root].m_leftChild, level+1);

    }

}

/**����������HuffmanTree������Ա����[ʵ��]********************************************************************************
    HuffmanTree( );                     // Ĭ�Ϲ��캯��ģ��
    HuffmanTree(CharType *chars, WeightType *weight, int size); //  ���ַ�chars[], Ȩֵweight[]���ַ�����size�����������
    HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);     // ���ƹ��캯��
    ~HuffmanTree( );            // ��������ģ��
    HuffmanTree<CharType, WeightType> &operator=(const HuffmanTree<CharType, WeightType> &copy);
    void CreatHuffmanTree(CharType *chars, WeightType *weight, int size);   // ���ַ�chars[], Ȩֵweight[]���ַ�����size�����������
    int getSize( );                         // ��ȡ��ǰ���������Ľ����Ŀ
    charType Char(int pos);             // ��ȡ��ǰ����������ĵ�pos���ַ�����
********************************************************************************[ʵ��]����������HuffmanTree������Ա����**/
// �������ƣ�HuffmanTree( );                     // Ĭ�Ϲ��캯��ģ��
// �������������һ���յĶ���
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree( )                     // Ĭ�Ϲ��캯��ģ��
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    this->m_nodes = NULL;   // �洢�����Ϣ, m_nodes[0]��ʹ��
    this->m_leafChars = NULL;                  // Ҷ����ַ���Ϣ, m_LeafChars[0]��ʹ��
    this->m_leafCharCodes = NULL;                 // char **m_leafCharCodesҶ����ַ��ı�����Ϣ, m_leafCharCodes[0]��ʹ��
}


// �������ƣ�HuffmanTree(CharType *chars, WeightType *weight, int size);
// ������������ַ�chars[], Ȩֵweight[]���ַ�����size�����������
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType *chars, WeightType *weight, int size) //  ���ַ�chars[], Ȩֵweight[]���ַ�����size�����������
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    this->CreateHuffmanTree(chars, weight, size);       // ���ַ�����chars, Ȩֵ����weight, ���ַ���Ŀsize�����������;
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(const HuffmanTree<CharType, WeightType> &copy)     // ���ƹ��캯��
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    this->m_size = copy.m_size;
    this->m_curPos = copy.m_curPos;
    this->m_size = copy.m_size;						// Ҷ������
    int len = 2 * m_size - 1;				// ������

    // ���ٱ�Ҫ�ռ�
    m_nodes = new HuffmanTreeNode<WeightType>[len + 1];	        // ���ٹ������������Ϣ����
    m_leafChars = new CharType[m_size + 1];				            // �����ַ���Ϣ����
    m_leafCharCodes = new std::string[m_size + 1];				            //���ٹ������ַ���������

    int curPos;
    for(curPos = 1; curPos < len; curPos++)
    {
        this->m_nodes = copy.m_nodesp[curPos];   // �洢�����Ϣ, m_nodes[0]��ʹ��
    }

    for(curPos = 1; curPos <= m_size; curPos++)
    {

        this->m_leafChars = copy.m_leafChars[curPos];                  // Ҷ����ַ���Ϣ, m_LeafChars[0]��ʹ��
        this->m_leafCharCodes = copy.m_leafCharCode[curPos];                 // char **m_leafCharCodesҶ����ַ��ı�����Ϣ, m_leafCharCodes[0]��ʹ��
    }
}

// �������ƣ�~HuffmanTree( )
template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree( )            // ��������ģ��
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    delete[] this->m_nodes;   // �洢�����Ϣ, m_nodes[0]��ʹ��
    delete[] this->m_leafChars;                  // Ҷ����ַ���Ϣ, m_LeafChars[0]��ʹ��
    delete[] this->m_leafCharCodes;                 // char **m_leafCharCodesҶ����ַ��ı�����Ϣ, m_leafCharCodes[0]��ʹ��

}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>& HuffmanTree<CharType, WeightType>::operator=(const HuffmanTree<CharType, WeightType> &copy)
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    this->m_size = copy.m_size;
    this->m_curPos = copy.m_curPos;
    this->m_size = copy.m_size;						// Ҷ������
    int len = 2 * m_size - 1;				// ������

    // ���ٱ�Ҫ�ռ�
    m_nodes = new HuffmanTreeNode<WeightType>[len + 1];	        // ���ٹ������������Ϣ����
    m_leafChars = new CharType[m_size + 1];				            // �����ַ���Ϣ����
    m_leafCharCodes = new std::string[m_size + 1];				            //���ٹ������ַ���������

    int curPos;
    for(curPos = 1; curPos < len; curPos++)
    {
        this->m_nodes = copy.m_nodesp[curPos];   // �洢�����Ϣ, m_nodes[0]��ʹ��
    }

    for(curPos = 1; curPos <= m_size; curPos++)
    {

        this->m_leafChars = copy.m_leafChars[curPos];                  // Ҷ����ַ���Ϣ, m_LeafChars[0]��ʹ��
        this->m_leafCharCodes = copy.m_leafCharCode[curPos];                 // char **m_leafCharCodesҶ����ַ��ı�����Ϣ, m_leafCharCodes[0]��ʹ��
    }

    return (*this);
}



// �������ƣ�void CreatHuffmanTree(CharType *chars, WeightType *weight, int size)
// ����������ݹ鸴��ÿ��������Ϣ
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::CreateHuffmanTree(CharType *chars, WeightType *weight, int size)   // ���ַ�chars[], Ȩֵweight[]���ַ�����size�����������
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    this->m_size = size;						// Ҷ������
    int len = 2 * m_size - 1;				// ������

    m_nodes = new HuffmanTreeNode<WeightType>[len + 1];	        // ���ٹ������������Ϣ����
    m_leafChars = new CharType[m_size + 1];				            // �����ַ���Ϣ����
    m_leafCharCodes = new std::string[m_size + 1];				            //���ٹ������ַ���������

    int pos, minOne, minTwo;										// ��ʱ����
    for(pos = 1; pos <= m_size; pos++)
    {
        // �洢Ҷ�����Ϣ
        m_nodes[pos].m_weight = weight[pos - 1];				// Ȩֵ
        m_leafChars[pos] = chars[pos - 1];				// �ַ�
    }

    for(pos = size + 1; pos <= len; pos++)
    {
        // ������������
        Select(pos - 1, minOne, minTwo);	// m_nodes[1 ~ pos - 1]��ѡ��˫��Ϊ0,Ȩֵ��С���������minOne,minTwo

        // �ϲ���minOne,minTwoΪ������
        m_nodes[minOne].m_parent = m_nodes[minTwo].m_parent = pos;	// minOne,minTwo˫��Ϊpos
        m_nodes[pos].m_leftChild = minOne;					// minOneΪpos������
        m_nodes[pos].m_rightChild = minTwo;					// minTwoΪpos���Һ���
        m_nodes[pos].m_weight = m_nodes[minOne].m_weight + m_nodes[minTwo].m_weight;//pos��ȨΪminOne,minTwo��Ȩֵ֮��
    }

    for(pos = 1; pos <= m_size; pos++)
    {
        int j = 81;
        std::string charCode;			// �ݴ�Ҷ����ַ�������Ϣ
        charCode[j--] = '\0';

        for(unsigned int child = pos, parent = m_nodes[child].m_parent;
            parent != 0;
            child = parent, parent = m_nodes[child].m_parent)
        {
            // ��Ҷ��㵽��������������
            if (m_nodes[parent].m_leftChild == child)
            {
                charCode[j--]  = '0';
            }
            else
            {
                charCode[j--] = '1';	// �ҷ�֧����Ϊ'1'
            }
        }
        this->m_leafCharCodes[pos] = &charCode[j+1];		// charCode�д洢�ַ�����
    }

//        int len;
//        std::string charCode = "";			// �ݴ�Ҷ����ַ�������Ϣ
//
//        for(unsigned int child = pos, parent = m_nodes[child].m_parent;
//            parent != 0;
//            child = parent, parent = m_nodes[child].m_parent)
//        {
//            // ��Ҷ��㵽��������������
//            if (m_nodes[parent].m_leftChild == child)
//            {
//                len = charCode.size( );
//                while(len > 0)          // ���ַ����κ���
//                {
//                    charCode[len] = charCode[len-1];
//                    len--;
//                }
//                charCode[len]  = '0';
//            }
//            else
//            {
//                len = charCode.size( );
//                while(len > 0)          // ���ַ����κ���
//                {
//                    charCode[len] = charCode[len-1];
//                    len--;
//                }
//                charCode[len]  = '1';
//            }
//        }
//        this->m_leafCharCodes[pos] = &charCode[0];		// charCode�д洢�ַ�����
//    }
    this->m_curPos = len;
}


// �������ƣ�string Encode(CharType chType);               // ���뺯��
// ��������������ַ�chType�Ĺ���������
template <class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::EnCode(CharType chType)       // ���뺯��
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    for(int pos = 1; pos <= this->m_size; pos++)        // ѭ����ű��������
    {
        if(m_leafChars[pos] == chType)
        {
            #ifdef DEBUG
            std::cout <<m_leafCharCodes[pos] <<std::endl;
            #endif
            return this->m_leafCharCodes[pos];
        }
    }
    throw  std::out_of_range("�Ƿ��ַ�, �޷�����");
}

//// �������ƣ�std::string EnCode(std::String strCode)             // ���뺯��
//// �����������strCode�ַ������б���
//template <class CharType, class WeightType>
//std::string EnCode(std::String charCode)             // ���뺯��
//{
//#ifdef DEBUG    // ��׮������Ϣ
//    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
//#endif
//    // ����ʵ�ֲ���
//
//}


// �������ƣ�string DeCode(string strCode)                  //���뺯��
// ��������������ַ�chType�Ĺ���������
template <class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::DeCode(std::string strCode)                 // ���뺯��
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    int charPos = 0;
    //std::string charStr;                 // ��ű�������
    char charStr[81];

    #ifdef DEBUG
    std::cout <<strCode <<std::endl;
    #endif

    for(unsigned int pos = 0; pos < strCode.size(); pos++)         // ����strCode��ÿ������λ
    {
        #ifdef DEBUG
        std::cout <<strCode[pos];
        #endif
        if(strCode[pos] == '0')     // �����ǰ�ַ���0
        {
            this->m_curPos = m_nodes[m_curPos].m_leftChild;       // Ѱ�����֧
            #ifdef DEBUG
            std::cout <<"Ѱ�����֧" <<std::endl;
            #endif
        }
        else if(strCode[pos] == '1')
        {
            this->m_curPos = m_nodes[m_curPos].m_rightChild;      // Ѱ���ҷ�֧
            #ifdef DEBUG
            std::cout <<"Ѱ���ҷ�֧" <<std::endl;
            #endif
        }
        else
        {
            //throw std::invalid_argument("�������Ϸ�\n");
            std::cout <<"��ǰ������Ϣ����, ����������" <<std::endl;
            return "";
        }
        if(/*m_nodes[m_curPos].m_leftChild == 0 && */m_nodes[m_curPos].m_rightChild == 0)
        {
            charStr[charPos++] =  this->m_leafChars[m_curPos];      // �����ַ���Ϣ
            this->m_curPos = 2*this->m_size-1;                      // �õ�ǰλ��ָ��ص�������λ��, �Ա������һ�εĲ���
        }
    }
   // system("pause");
    charStr[charPos] = '\0';

    //system("pause");
    return &charStr[0];
}

// �������ƣ�int Size( )
// ��������������ַ�chType�Ĺ���������
template <class CharType, class WeightType>
int HuffmanTree<CharType, WeightType>::Size( )                       // ��ȡ��ǰ���������Ľ����Ŀ
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    return m_size;
}

// �������ƣ�Char(int pos)
// ������������ض�Ӧ��pos���ַ���Ϣ
template <class CharType, class WeightType>
CharType HuffmanTree<CharType, WeightType>::Char(int pos)            // ��ȡ��ǰ����������ĵ�pos���ַ�����
{
#ifdef DEBUG    // ��׮������Ϣ
    std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    //assert(pos >= 1 && pos <= m_size);
    if(pos <= 0 || pos > m_size)
    {
        throw std::out_of_range("�������Ϸ�\n");
    }

    return this->m_leafChars[pos];
}


template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::DisplayWithShape( )  // ������ʾ��������
{
    this->DisplayWithShape(this->m_curPos, 1);

    this->m_curPos = 2*this->m_size-1;
//    std::cout <<std::endl;
//    for(int i = 1; i <= m_size; i++)
//    {
//        std::cout <<m_nodes[i].m_weight;// <<endl;
//    }
//    std::cout <<std::endl;
//
//    for(int i = 1; i <= m_size; i++)
//    {
//        std::cout <<m_leafChars[i];
//    }
//    std::cout <<std::endl;


}



#endif // HuffmanTree_H_INCLUDED
