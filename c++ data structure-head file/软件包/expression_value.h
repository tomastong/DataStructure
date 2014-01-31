#ifndef __EXPRESSION_VALUE_H__
#define __EXPRESSION_VALUE_H__

#include "lk_stack.h"								// ��ջ

// ���ʽ��ֵ��
template<class ElemType>
class ExpressionValue
{
private:
// ��������:
	static bool IsOperator(char ch);				// �ж�ch�Ƿ�Ϊ�����
	static int LeftPri(char op);					// �������������ȼ�
	static int RightPri(char op);					// �ұ�����������ȼ�
	static void Get2Operands(LinkStack<ElemType> &opnd, ElemType &a1, ElemType &a2);			
		// ��opndջ��ȡ������������
	static void DoOperator(LinkStack<ElemType> &opnd, const ElemType &a1, 
		char op, const ElemType &a2);				// �γ�����ָ�� (a1)op(a2)�������opndջ
	static void PostfixExpression(ofstream &outFile);		
		// ���Ӽ������������׺���ʽת��Ϊ��׺���ʽ���ٴ���������ļ�outFile��
	static void PostfixExpressionValue(ifstream &inFile);
		// �������ļ�inFile�������׺���ʽ, �����׺���ʽ��ֵ

public:
// �ӿڷ�������:
	ExpressionValue(){};							// �޲����Ĺ��캯��
	virtual ~ExpressionValue(){};					// ��������
	static void Run();								// ��Ӽ����������׺���ʽֵ֮
};

// ���ʽ��ֵ���ʵ�ֲ���
template<class ElemType>
bool ExpressionValue<ElemType>::IsOperator(char ch)
// �������: ���ch�������, �򷵻�true, ���򷵻�false
{	
	if (ch == '=' || ch == '(' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == ')') return true;
	else return false; 
}

template<class ElemType>
int ExpressionValue<ElemType>::LeftPri(char op)
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

template<class ElemType>
int ExpressionValue<ElemType>::RightPri(char op)
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

template<class ElemType>
void ExpressionValue<ElemType>::Get2Operands(LinkStack<ElemType> &opnd, 
	ElemType &a1, ElemType &a2)
// �������: ��opndջ��ȡ������������
{
	if(opnd.Pop(a2) == UNDER_FLOW) throw Error("���ʽ�д�!");	// �׳��쳣
	if(opnd.Pop(a1) == UNDER_FLOW) throw Error("���ʽ�д�!");	// �׳��쳣
}

template<class ElemType>
void ExpressionValue<ElemType>::DoOperator(LinkStack<ElemType> &opnd, 
	const ElemType &a1, char op, const ElemType &a2)
// �������: �γ�����ָ�� (a1) op (a2)�������opndջ
{
	switch(op)
	{
	case '+':
		opnd.Push(a1 + a2);							// �ӷ�+����
		break;
	case '-':
		opnd.Push(a1 - a2);							// ����-����
		break;
	case '*':
		opnd.Push(a1 * a2);							// �˷�*����
		break;
	case '/':
		if (a2==0)  throw Error("����Ϊ0!");		// �׳��쳣
		opnd.Push(a1 / a2);							// ����/����
		break;
	}
}

template<class ElemType>
void ExpressionValue<ElemType>::PostfixExpression(ofstream &outFile)
// �������: ���Ӽ������������׺���ʽת��Ϊ��׺���ʽ���ٴ��������
//	�ļ�outFile��
{
	LinkStack<char> optr;							// ������ջoptr
	char ch, optrTop, op;							// ������ַ�ch, ������ջoptrջ��������,������op
	ElemType operand;								// ������
	optr.Push('=');									// Ϊ��̷����������optr��ջ��ѹ��'='
	optr.Top(optrTop);								// ȡ��������ջoptr��ջ��
	ch = GetChar();									// ��������cin�������ո����Ʊ��ȡ��һ���ַ�
	while (optrTop != '=' || ch != '=')
	{	//��optrTop����'='��ch����'='������ʱ�����ʽ����δ����
		if (isdigit(ch) || ch=='.')
		{	// chΪ���ֻ���ʱ�Ĵ��� 
			cin.putback(ch);						// ��ch�Ż�������
			cin >> operand;							// ��������operand
			outFile << operand << " ";				// ��operand������ļ�outFile��
			ch = GetChar();							// ��������cin�������ո����Ʊ��ȡ��һ���ַ�
		}
		else if (!IsOperator(ch))
		{	// chΪ�Ƿ��ַ�
			throw Error("�Ƿ��ַ�!");				// �׳��쳣
		}
		else
		{
			if (LeftPri(optrTop) < RightPri(ch))
			{	
				optr.Push(ch);						// ch��optrջ
				ch = GetChar();						// ��������cin�������ո����Ʊ��ȡ��һ���ַ�
			}
			else if (LeftPri(optrTop) > RightPri(ch))
			{	
				optr.Pop(op);						// ��optrջ�˳�op
				outFile << op << " ";				// �������op�����outFile��
			}
			else if (LeftPri(optrTop) == RightPri(ch) && ch == ')')
			{	// ��ʾoptrTop����'('��ch����')'
				optr.Pop(ch);						// ��optrջ�˳�ջ����'('
				ch = GetChar();						// ��������cin�������ո����Ʊ��ȡ��һ���ַ�
			}
		}
		optr.Top(optrTop);							// ȡ��������ջoptr��ջ��
	}
	outFile << '=';									// �������ļ�outFile��'='�������Ա���ʵ��
}

template<class ElemType>
void ExpressionValue<ElemType>::PostfixExpressionValue(ifstream &inFile)
// �������: �������ļ�inFile�������׺���ʽ, �����׺���ʽ��ֵ
{
	LinkStack<ElemType> opnd;						// ������ջopnd
	char ch;										// ��ǰ�ַ�
	double operand;									// ������
	
	while (inFile >> ch, ch != '=')
	{	// ֻҪ���������ļ�inFileȡ�õ��ַ���Ϊ'='��ѭѭ��
		if (IsOperator(ch))
		{	// chΪ�������������������
			ElemType a1, a2;						// ������
			Get2Operands(opnd, a1, a2);				// ��opndջ��ȡ������������
			DoOperator(opnd, a1, ch, a2);			// �γ�����ָ�� (a1) op (a2)�������opndջ
		}
		else
		{	// ch���ǲ�����
			inFile.putback(ch);						// ��ch�Ż��������ļ�inFile
			inFile >> operand;						// ���������ļ�inFile���������
			opnd.Push(operand);						// ��operand��ջopnd
		}
	}
	opnd.Top(operand);								// ȡ��opnd��ջ��Ԫ����Ϊ���ʽ������
	cout << operand << endl;						// ��ʾ������
}

template<class ElemType>
void ExpressionValue<ElemType>::Run()
// �������: ��Ӽ����������׺���ʽֵ֮
{
		ofstream outFile("temp.dat");				//����������ļ�
		PostfixExpression(outFile);	
			// ���Ӽ������������׺���ʽת��Ϊ��׺���ʽ�����������������ļ���
			//����'='������
		outFile.close();							//�ر�������ļ�

		ifstream inFile("temp.dat");				//�����������ļ�
		PostfixExpressionValue(inFile);		
			// ������������ļ�������ĺ�׺���ʽ����'='�������ģ������������Ļ
			// ����ʾ����
		inFile.close();								//�ر��������ļ�

		remove("temp.dat");							//ɾ����ʱ�ļ�temp.dat
}

#endif


