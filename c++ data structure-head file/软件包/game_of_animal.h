// �ļ�·����: game_of_animal\game_of_animal.h
#ifndef __GAME_OF_ANIMAL_H__
#define __GAME_OF_ANIMAL_H__

#include "string.h"								// ����
#include "binary_tree.h"						// ��������
#include "lk_stack.h"							// ��ջ

// ������Ϸ��
class GameOfAnimal
{
private:
// ������Ϸ������ݳ�Ա:
	BinaryTree<String> *pDTree;					// ������

//	��������:
	void WriteHelp(BinTreeNode<String> *root, ofstream &outFile);	// д��������Ϣ
	bool IsQuestion(String strSentence);		// �Ƿ�Ϊ���ʾ�

public:
// ���к���:
	GameOfAnimal();								// ���캯��
	virtual ~GameOfAnimal();					// ��������
	void Run();									// ���ж�����Ϸ
};

// ���ش�����/��������
ostream &operator <<(ostream &outStream, const String &outStr);
	// ���������<<
istream &operator >>(istream &inStream, String &inStr);
	// ���������>>

// ������Ϸ�༰��غ�����ʵ�ֲ���
void GameOfAnimal::WriteHelp(BinTreeNode<String> *root, ofstream &outFile)
// �������: ����������Ϣд���ļ�outFile
{
	if (root != NULL)
	{
		WriteHelp(root->leftChild, outFile);	// д������
		WriteHelp(root->rightChild, outFile);	// д������
		outFile << root->data << endl;			// д����Ϣ
	}
}

bool GameOfAnimal::IsQuestion(String strSentence)
// �������: �Ƿ�Ϊ���ʾ�
{
	return strSentence[strSentence.Length() - 1] == '?';// ���ʺŽ���Ϊ���ʾ�
}


GameOfAnimal::GameOfAnimal()
// �������: ��֪ʶ���ļ�����������
{
	ifstream inFile("animal.dat");				// �����ļ���
	if (inFile == NULL) throw Error("���ܴ�֪ʶ���ļ�!");	// �׳��쳣
	String strElem;								// ������Ԫ��
	LinkStack<BinTreeNode<String> *> s;			// ջ
	BinTreeNode<String> *r, *r1, *r2;			// ָ�����������ָ�� 

	inFile >> strElem;							// ���������Ԫ��
	while (!strElem.Empty())
	{	// ���ھ�����Ԫ��, ѭ��
		if (IsQuestion(strElem))
		{	// ���ʾ�, Ϊ��������֧���
			s.Pop(r2);	s.Pop(r1);				// ��ջ�е������Һ��� 
			r = new BinTreeNode<String>(strElem, r1, r2);// �����½��
			s.Push(r);							// ���½����ջ
		}
		else
		{	// �����ʾ�, ��ʾ������, Ϊ������Ҷ�ӽ��
			r = new BinTreeNode<String>(strElem);		// �����½��
			s.Push(r);							// ���½����ջ
		}
		inFile >> strElem;						// ���������Ԫ��
	}
	s.Top(r);									// ȡ��ջ��Ԫ��
	pDTree = new BinaryTree<String>(r);			// ���ɾ�����
	inFile.close();								// �ر��ļ�
}

GameOfAnimal::~GameOfAnimal()
// �������: ��������Ϣ���ͷŴ洢�ռ�
{
	ofstream outFile("animal.dat");				// ����ļ���
	if (outFile == NULL) throw Error("���ܴ�֪ʶ���ļ�!");	// �׳��쳣
	WriteHelp(pDTree->GetRoot(), outFile);		//  ����������Ϣд���ļ�outFile
	outFile.close();							// �ر��ļ�
	delete pDTree;								// �ͷŴ洢�ռ�
}

void GameOfAnimal::Run()
// �������: ���ж�����Ϸ
{
	cout << "��ӭ����������Ϸ!" << endl;
	do
	{
		cout << "���һ������, �ҽ���������..." << endl;
		BinTreeNode<String> *p = pDTree->GetRoot();	// ����㿪ʼ���д���
		String strElem = p->data;					// ������Ԫ��
		while (IsQuestion(strElem))
		{	// ���ʾ�, Ϊ��������֧���
			cout << strElem;						// ��ʾ���ʾ� 
			cout << "��ش�";
			if (UserSaysYes()) p = p->leftChild;	// �϶��ش�Ϊ����
			else p = p->rightChild;					// �񶨻ش�Ϊ�Һ���
			strElem = p->data;						// ������Ԫ��
		}

		cout << "����Ķ�����" << strElem << "��? ��ش�";
		if (UserSaysYes())
		{ 	// �϶��ش�
			cout << "��! һ̨��������������..." << endl;
		}
		else
		{ 	// �񶨻ش�
			cout << "�������˵�..." << endl;
			cout << "�����ʲô������?" << endl;
			String strNewAnimal, strOldAnimal = strElem;// ��������
			cin >> strNewAnimal;				// ���붯������
			cout << "������һ�����ʾ�, �϶��ش�Ϊ" << strNewAnimal 
				<< ", �񶨻ش�Ϊ" << strOldAnimal << endl; 
			cin >> strElem;						// �������ʾ�
			p->data = strElem;					// ��Ϊ���ʾ�
			p->leftChild = new BinTreeNode<String>(strNewAnimal);	// ����
			p->rightChild = new BinTreeNode<String>(strOldAnimal);	// �Һ���
		}
		
		cout << "������һ����? ��ش�";
	}while (UserSaysYes());
}

ostream &operator <<(ostream &outStream, const String &outStr)
// ������������������<<
{
	outStream << outStr.CStr();				// �����ֵ
	return outStream;						// �������������
}

istream &operator >>(istream &inStream, String &inStr)
// ������������������>>
{
	LinkList<char> temp;					// ��ʱ���Ա�
	int size = 0;							// ��ʼ���Ա���
	char ch= GetChar(inStream);				// ��������inStream�������ո��Ʊ����ȡһ�ַ�
	inStream.putback(ch);					// ��ch����������
	while ((ch = inStream.peek()) != EOF &&	// peek()����������ȡһ���ַ�
											// ������ָ�벻��
		(ch = inStream.get()) != '\n'		// get()����������ȡһ���ַ�ch
											// ������ָ��ָ����һ�ַ�,ch��Ϊ���з�
		&& ch != '\t' && ch != ' ')			// chҲ��Ϊ�Ʊ����ո�	
	{	// ��������ַ�׷�ӵ����Ա���
		temp.Insert(++size, ch);
	}
	String answer(temp);					// ���촮
	inStr = answer;							// ��inStr���ش�
	return inStream;						// ��������������
}

#endif
