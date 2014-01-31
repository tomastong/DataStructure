#ifndef __MPOLYNOMIAL_NODE_H__
#define __MPOLYNOMIAL_NODE_H__

#ifndef __MPOLYNOMIAL_NODE_TYPE__
#define __MPOLYNOMIAL_NODE_TYPE__
enum MPolynomialNodeType {HEAD, ATOM, LIST};
#endif

#include "use_space_list.h"					// �����ʹ�ÿռ����

// mԪ����ʽ�����
template<class CoefType>
struct MPolynomialNode
{
// ���ݳ�Ա:
	MPolynomialNodeType tag;				// ��־��,HEAD(0):ͷ���, ATOM(1):ԭ�ӽ��, LIST(2):����
	MPolynomialNode<CoefType> *nextLink;	// ָ��ͬһ���е���һ�����ָ����
	union
	{
		char var;							// tag=HEAD,���mԪ����ʽ��������
		struct								// tag=ATOM��ԭ�ӽ��
		{
			CoefType coef;					// ���ϵ����
			int exp;						// ���ָ����
		} atom;								// ԭ�ӽṹ
		struct								// tag=LISK, ��ṹ
		{
			MPolynomialNode<CoefType> *subLink;	// ���ָ���ӱ��ָ����
			int exp;						// ���ָ����
		} list;								// ����ṹ 
	}; 

// ���캯��:
	MPolynomialNode(MPolynomialNodeType tg = HEAD, 
		MPolynomialNode<CoefType> *next = NULL);// �ɱ�־tg��ָ��next����mԪ����ʽ���
};

// mԪ����ʽ������ʵ�ֲ���
template<class CoefType>
MPolynomialNode<CoefType>::MPolynomialNode(MPolynomialNodeType tg, MPolynomialNode<CoefType> *next)
// ����������ɱ�־tg��ָ��next����mԪ����ʽ���
{
	tag = tg;								// ��־
	nextLink = next;						// ���
	gUseSpaceList.Push(this);				// ��ָ��ǰ����ָ����뵽�����ʹ�ÿռ����
}

#endif
