/**
******************************************************************************
*  CopyRight  : 2012-2013, HerBinUnversity, GatieMe                          *
*  File Name  : HuffmanTreeNode.h                                                    *
*  Description: �������������HuffmanTreeNodeģ��ͷ�ļ�                               *
*  Author     : Gatie_Me                                                     *
*  Version    : Copyright 2012 JULY_CITY                                     *
*  Data_Time  : 2012-11-6_10:21:43                                           *
*  Content    : ���ݽṹ���㷨��C++��������Դ��                             *
******************************************************************************
**/



#ifndef HUFFMANTREENODE_H_INCLUDED
#define HUFFMANTREENODE_H_INCLUDED

#include <stdexcept>        // ��׼�쳣���������
#include <exception>
//using namespace std;

#include "HuffmanTreeNode.h"    // �����������


//#define DEBUG           // ��׮������Ϣ[�궨��]
#define SHOW        // ���������а�æ��ʾ�ս�����Ϣ

/// �������������HuffmanTreeNode��������
template <class WeightType>
class HuffmanTreeNode
{
/*===========================��PUBLIC�������ӿڡ�============================*/
  public :      // �����ӿ�
    // �������������HuffmanTreeNode������Ա����
    HuffmanTreeNode( ); // Ĭ�Ϲ��캯��ģ��

	HuffmanTreeNode(WeightType weight, int parent = 0, int leftChild = 0, int rightChild = 0);	// �������Ĺ��캯��

    HuffmanTreeNode(const HuffmanTreeNode<WeightType> &copy);     // ���ƹ��캯��

    ~HuffmanTreeNode( );            // ����������ģ��

    // �������������HuffmanTreeNode������Ա����
    HuffmanTreeNode<WeightType> &operator=(const HuffmanTreeNode<WeightType> &copy);

    // �������������HuffmanTreeNode���ݳ�Ա
    WeightType m_weight;            // ������Ϣ��Ȩֵ[����ѹ�������б�����ֵ�Ƶ��]
    unsigned int m_parent, m_leftChild, m_rightChild;       // �洢��ǰ������Ϣ˫��, ���Һ���λ�õ�������
};



/**�������������HuffmanTreeNode������Ա����[ʵ��]*****************************************************
    HuffmanTreeNode( ); // Ĭ�Ϲ��캯��ģ��
	HuffmanTreeNode(WeightType weight, int parent, int leftChild, int rightChild);	// �������Ĺ��캯��
    HuffmanTreeNode(const HuffmanTreeNode<WeightType> &copy);     // ���ƹ��캯��
    ~HuffmanTreeNode( );            // ����������ģ��
    // �������������HuffmanTreeNode������Ա����
    HuffmanTreeNode<WeightType> &operator=(const HuffmanTreeNode<WeightType> &copy);
*****************************************************[ʵ��]�������������HuffmanTreeNode������Ա����**/
// �������ƣ�HuffmanTreeNode( );
// �������������һ����������������, �������Ҫ�ռ�
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode( )     // // Ĭ�Ϲ��캯��ģ��
{
#ifdef DEBUG    // ��׮������Ϣ
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    this->m_parent = 0;     // ��ʼ�����еĽ��ָʾ��Ϊ0
    this->m_leftChild = 0;
    this->m_rightChild = 0;
}

// �������ƣ�HuffmanTreeNode(WeightType weight, int parent = 0, int leftChild = 0, int rightChild = 0);
// �������������һ��������������
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType weight, int parent/* = 0*/, int leftChild/* = 0*/, int rightChild/* = 0*/)	// �������Ĺ��캯��
{
#ifdef DEBUG    // ��׮������Ϣ
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    this->m_weight = weight;        // Ȩֵ��Ϣ
    this->m_parent = parent;        // ˫�׽��
    this->m_leftChild = leftChild;  // ����
    this->m_rightChild = rightChild;// �Һ���
}

// �������ƣ�HuffmanTreeNode(const HuffmanTreeNode<WeightType> &copy);
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(const HuffmanTreeNode<WeightType> &copy)  // ���ƹ��캯��    // ���ƹ��캯��
{
#ifdef DEBUG    // ��׮������Ϣ
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    this->m_weight = copy.weight;        // Ȩֵ��Ϣ
    this->m_parent = copy.parent;        // ˫�׽��
    this->m_leftChild = copy.leftChild;  // ����
    this->m_rightChild = copy.rightChild;// �Һ���
}


// �������ƣ�~HuffmanTreeNode( );
template <class WeightType>
HuffmanTreeNode<WeightType>::~HuffmanTreeNode( )            // ��������ģ��
{
#ifdef DEBUG    // ��׮������Ϣ
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
}

/**�������������HuffmanTreeNode������Ա����[ʵ��]*****************************************************
    HuffmanTreeNode<WeightType> &operator=(const HuffmanTreeNode<WeightType> &copy);
*****************************************************[ʵ��]�������������HuffmanTreeNode������Ա����**/
// �������ƣ�HuffmanTreeNode<WeightType> &operator=(const HuffmanTreeNode<WeightType> &copy);
template <class WeightType>
HuffmanTreeNode<WeightType>& HuffmanTreeNode<WeightType>::operator=(const HuffmanTreeNode<WeightType> &copy)
{
#ifdef DEBUG    // ��׮������Ϣ
std::cout <<"FUN:"<<__func__  <<", LINE:" <<__LINE__ <<std::endl;   // ���������Ϣ
#endif
    // ����ʵ�ֲ���
    this->m_weight = copy.weight;        // Ȩֵ��Ϣ
    this->m_parent = copy.parent;        // ˫�׽��
    this->m_leftChild = copy.leftChild;  // ����
    this->m_rightChild = copy.rightChild;// �Һ���
}



#endif // HuffmanTreeNode_H_INCLUDED
