// �ļ�·����: calculator\calculator.h 
#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include "lk_stack.h"										// ��ջ��

// ��������
template<class ElemType>
class Calculator
{
private:
//  �����������ݳ�Ա:
	LinkStack<ElemType> opnd;								// ������ջ
	LinkStack<char> optr;									// ������ջ

// ��������
	int OperPrior(char op);									// ���������ȼ�
	void Get2Operands(ElemType &left, ElemType &right);		// ��ջopnd���˳�����������
	ElemType Operate(ElemType left, char op, ElemType right);// ִ������left op right
	bool IsOperator(char ch);								// �ж�ch�Ƿ�Ϊ������ 

public:
// �������෽������:
	Calculator(){};											// �޲����Ĺ��캯��
	virtual ~Calculator(){};								// ��������
	void Run();												// ������ʽ
};

// ���������ʵ�ֲ���
template<class ElemType>
int Calculator<ElemType>::OperPrior(char op)
// ������������������ȼ�
{
	int prior;										// ���ȼ�
	if (op == '=') prior = 1;						// =���ȼ�Ϊ1
	else if (op == '(' || op == ')') prior = 2;		// (���ȼ�Ϊ2
	else if (op == '+' || op == '-') prior = 3;		// +-���ȼ�Ϊ3
	else if (op == '*' || op == '/'|| op == '%') prior = 4;
		// */%���ȼ�Ϊ4
	else if (op == '^')  prior = 5;					// ^���ȼ�Ϊ5
	return prior;									// �������ȼ�
}

template<class ElemType>
void Calculator<ElemType>::Get2Operands(ElemType &left, ElemType &right)
// �����������ջopnd���˳�����������
{
	if (opnd.Pop(right) == UNDER_FLOW) throw Error("���ʽ�д�!");	// �׳��쳣
	if (opnd.Pop(left) == UNDER_FLOW) throw Error("���ʽ�д�!");	// �׳��쳣
};

template<class ElemType>
ElemType Calculator<ElemType>::Operate(ElemType left, char op, ElemType right)
// ���������ִ������left op right
{
	ElemType result;
	if (op == '+') result = left + right;			// �ӷ�����
	else if (op == '-') result = left - right;		// ��������
	else if (op == '*') result = left * right;		// �˷�����
	else if (op == '/' && right == 0) throw Error("����Ϊ��!");	
		// �׳��쳣
	else if (op == '/' && right != 0) result = left / right;	// ��������
	else if (op == '%' && (long)right == 0) throw Error("����Ϊ��!");	
		// �׳��쳣
	else if (op == '%' && (long)right != 0) result = (long)left % (long)right;
		// ��������
	else if (op == '^') result = pow(left, right);	// �˷�����
	return result;									// ����result
}

template<class ElemType>
bool Calculator<ElemType>::IsOperator(char ch)
// ����������ж�ch�Ƿ�Ϊ������ 
{
	if (ch == '=' || ch == '(' || ch == '^' || ch == '*' ||
		ch == '/' || ch =='%' || ch == '+' || ch== '-' || ch == ')') return true;
	else return false;
};

template<class ElemType>
void Calculator<ElemType>::Run()
// ���������������ʽ
{
	optr.Clear();	opnd.Clear();		// ���optrջ��opndջ
	optr.Push('=');						// ��optrջ�м���һ��'='
	char ch;							// ��ʱ�ַ�
	char priorChar;						// ��ǰ�����ǰһ���ַ����粻Ϊ��������������ֵΪ'0'
	char optrTop;						// ��optrջ��ջ���ַ�
	double operand;						// ������
	char op;							// ������

	priorChar = '=';					// ǰһ�ַ�
	ch = GetChar();						// ����һ���ַ�
	if (optr.Top(optrTop) == UNDER_FLOW) throw Error("���ʽ�д�!");		// �׳��쳣
		// ȡ��optrջ��ջ��
	while (optrTop != '=' || ch != '=')
	{	// ��ǰ���ʽ��δ�������, ��������
		if (isdigit(ch) || ch == '.')
		{	// chΪһ���������ĵ�1���ַ�
			cin.putback(ch);			// ���ַ�ch�Ż�������
			cin >> operand;				// ���������
			opnd.Push(operand);			// ��������opndջ 
			priorChar = '0';			// ǰһ�ַ����ǲ�����, �涨ǰһ�ַ�Ϊ'0'
			ch = GetChar();				// ������һ���ַ�
		}
		else if(!IsOperator(ch))
		{	// �Ȳ��ǲ�����,Ҳ�����ڲ�����
			throw Error("���ʽ�д�!");// �׳��쳣
		}
		else
		{	// chΪ������
			if ((priorChar == '=' || priorChar == '(') && (ch == '+' || ch == '-'))
			{
				opnd.Push(0);			// chΪ��Ŀ�����+-, ����ǰ����ϲ�����0
				priorChar = '0';		// ǰһ�ַ����ǲ�����, �涨ǰһ�ַ�Ϊ'0'
			}
			if (optrTop == ')' && ch == '(' || optrTop == '(' && ch == '=' || optrTop == '=' && ch == ')')
				 throw Error("���ʽ�д�!");	
			else if	(optrTop == '(' && ch == ')')
			{	// ȥ����
				if (optr.Pop(optrTop) == UNDER_FLOW) throw Error("���ʽ�д�!");	
					// �׳��쳣
			    ch = GetChar();			// �������ַ�
			    priorChar = ')';		// �µ�ǰһ�ַ�Ϊ)
			}
			else if (ch == '(' || OperPrior(optrTop) < OperPrior(ch))
			{	// optrTopΪ(,��optrTop��ch�����ȼ���
				optr.Push(ch);			// ch��optrջ
			    priorChar = ch;			// �µ�ǰһ�ַ�Ϊch
				ch = GetChar();			// �������ַ�
			}
			else
			{	// optrTop�Ĵ��ڻ����ch�����ȼ�
				if (optr.Pop(op) == UNDER_FLOW) throw Error("���ʽ�д�!");	
					// �׳��쳣
				ElemType left, right;	// ������
				Get2Operands(left, right);				// ��opndջ��ȡ������
				opnd.Push(Operate(left, op, right));	// ��������opndջ
			}
		}
		if (optr.Top(optrTop) == UNDER_FLOW) throw Error("���ʽ�д�!");// �׳��쳣
			// ȡ��optrջ��ջ��
	}
	if (opnd.Top(operand) == UNDER_FLOW) throw Error("���ʽ�д�!");	// �׳��쳣
	cout << operand << endl;			// ��ʾ���ʽ��ֵ
};

#endif