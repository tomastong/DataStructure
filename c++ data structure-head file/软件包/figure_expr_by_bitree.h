// �ļ�·����:figure_expr_by_bitree\figure_expr_by_bitree.h
#ifndef __FIGURE_EXPR_BY_BI_TREE_H__
#define __FIGURE_EXPR_BY_BI_TREE_H__

#include "lk_stack.h"								// ��ջ
#include "bin_tree_node.h"							// �����������
#include "binary_tree.h"							// ��������

// ���ʽ�Ķ�������ʾ��
class FigureExprByBiTree
{
private:
// ��������:
	static bool IsOperator(char ch);				// �ж�ch�Ƿ�Ϊ�����
	static int LeftPri(char op);					// �������������ȼ�
	static int RightPri(char op);					// �ұ�����������ȼ�

public:
// �ӿڷ�������:
	FigureExprByBiTree(){};							// �޲����Ĺ��캯��
	virtual ~FigureExprByBiTree(){};				// ��������
	static void Run();								// ���Ӽ����������׺���ʽ�ö�������ʾ
};

// ���ʽ�Ķ�������ʾ���ʵ�ֲ���
bool FigureExprByBiTree::IsOperator(char ch)
// �������: ���ch�������, �򷵻�true, ���򷵻�false
{	
	if (ch == '=' || ch == '(' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == ')') return true;
	else return false; 
}

int FigureExprByBiTree::LeftPri(char op)
// �������: �������������ȼ�	
{
	int result;										// ���ȼ�
	if (op == '=') result = 0;
	else if (op == '(') result = 1;
	else if (op == '*' || op == '/') result = 5;
	else if (op == '+' || op == '-') result = 3;
	else if (op == ')') result = 6;
	return result;									// �������ȼ�
}

int FigureExprByBiTree::RightPri(char op)
// �������: �ұ�����������ȼ�	
{
	int result;										// ���ȼ�
	if (op == '=') result = 0;
	else if (op == '(') result = 6;
	else if (op == '*' || op == '/') result = 4;
	else if (op == '+' || op == '-') result = 2;
	else if (op == ')') result = 1;
	return result;									// �������ȼ�
}

void FigureExprByBiTree::Run()
// �������: ���Ӽ������������׺���ʽת��Ϊ��׺���ʽ���ö�������ʾ,����ʾ������
{
	LinkStack<BinTreeNode<char> *> biTr;			// ������ջ
	LinkStack<char> optr;							// ������ջ
	char ch, optrTop, theta;						// ������ַ�ch, ������ջoptrջ��������,������theta
	BinTreeNode<char> *r;							// ָ��������ṹָ��
	optr.Push('=');									// Ϊ��̷����������optr��ջ��ѹ��'='
	optr.Top(optrTop);								// ȡ��������ջoptr��ջ��
	ch = GetChar();									// ��������cin���������뻻�з�ȡ��һ���ַ�
	while (optrTop != '=' || ch != '=')
	{	//��optrTop����'='��ch����'='������ʱ�����ʽ����δ����
		if (!IsOperator(ch))
		{	// chΪ������
			r = new BinTreeNode<char>(ch);			// ����ֻ��һ�����Ķ�����
			biTr.Push(r);							// r��optrջ
			ch = GetChar();							// ��������cin���������뻻�з�ȡ��һ���ַ�
		}
		else
		{	// chΪ������
			if (LeftPri(optrTop) < RightPri(ch))
			{	// ch���ȼ�����
				optr.Push(ch);						// ch��optrջ
				ch = GetChar();						// ��������cin���������뻻�з�ȡ��һ���ַ�
			}
			else if (LeftPri(optrTop) > RightPri(ch))
			{	// optrTop���ȼ�����
				BinTreeNode<char> *leftr, *rightr;	// ������ 
				if(biTr.Pop(rightr) == UNDER_FLOW) throw Error("���ʽ�д�!");	// �׳��쳣
				if(biTr.Pop(leftr) == UNDER_FLOW) throw Error("���ʽ�д�!");	// �׳��쳣
				optr.Pop(theta);					// ��optrջ�˳�theta
				r = new BinTreeNode<char>(theta, leftr, rightr);				// �����¶�����
				biTr.Push(r);						// r��biTrջ
			}
			else if (LeftPri(optrTop) == RightPri(ch) && ch == ')')
			{	// ��ʾoptrTop����'('�����')'
				optr.Pop(ch);						// ��optrջ�˳�ջ����'('
				ch = GetChar();						// ��������cin���������뻻�з�ȡ��һ���ַ�
			}
		}
		optr.Top(optrTop);							// ȡ��������ջoptr��ջ��
	}
	biTr.Pop(r);									// rΪ���ɵĶ������ĸ�
	BinaryTree<char> bt(r);							// ���ɶ�����
	DisplayBTWithTreeShape(bt);						// ��ʾ������
}

#endif


