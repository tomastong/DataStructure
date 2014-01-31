// �ļ�·����: tcs_genealogy\tcs_genealogy.h
#ifndef __TCS_GENEALOGY__H__
#define __TCS_GENEALOGY__H__

#include "string.h"							// ����
#include "parent_forest.h"					// ɭ����

// Ԫ�ؽṹ
struct ElemType
{
	String student;							// ѧ������
	String adivisor;						// ѧ�����ĵ�ʦ����
	String place;							// ���販ʿѧλ�Ĵ�ѧ������д
	String dataOfPHD;						// ���販ʿѧλ�����
};

// �������
enum OutputType {OUTPUT_TO_SCREEN, OUTPUT_TO_FILE};

// ���ۼ������ѧ��������
class TCSGenealogy
{
private:
// ��԰����������ݳ�Ա:
	ParentForest<ElemType> *pForest;		// �����ۼ������ѧ��������ɵ�ɭ��
	ifstream inFile;						// ������ 
	
// ��������:
	void Readln();							// ����һ��  
	void BuildForest();						// �������ۼ������ѧ��������ɵ�ɭ��
	void OutputHelp(ostream &outStream, int r, int level);	
		// ������ۼ������ѧ�����׸���������levelΪ���������������Ĳ����Ϊ1

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	TCSGenealogy();							// �޲����Ĺ��캯��
	virtual ~TCSGenealogy();				// ��������
	void Output(OutputType tp);				// ������ۼ������ѧ������, tpΪ�������
};

// ���ش�����/��������
ostream &operator <<(ostream &outStream, const String &outStr);
	// ���������<<
istream &operator >>(istream &inStream, String &inStr);
	// ���������>>

// ���ۼ������ѧ�������༰��غ�����ʵ�ֲ���
void TCSGenealogy::Readln()
// �������������һ��
{	
	char ch;								// �ַ�
	while ((ch = inFile.peek()) != EOF		// ��Ϊ�ļ�������
		&& (ch = inFile.get()) != '\n');	// ��Ϊ���з�
}

void TCSGenealogy::BuildForest()
// ������������������ۼ������ѧ��������ɵ�ɭ��
{
	int n = 0;								// ɭ�ְ����Ľ�����
	char ch;								// ��ʱ�ַ�

	while ((ch = inFile.peek()) != EOF)
	{	// ͳ���ļ��а��������Ϣ������
		if (ch >= 'a' && ch <= 'z'			// ��Сд��ĸ
			|| ch >= 'A' && ch <= 'Z'		// ��Сд��ĸ
			|| ch == '?') n++;				// ���ʺ�'?'��ʼ����Ϊ�����Ϣ
		Readln();							// ����һ��
	}

	ElemType *elems = new ElemType[2 * n];	// ���Ԫ��
	int *parents = new int[2 * n];			// ���˫��
	int count = 0;							// ��ǰ�����

	inFile.clear();							// ���EOFf��־
	inFile.seekg(0);						// ����������λ����ʼ��
	while ((ch = inFile.peek()) != EOF)
	{	// ����ɭ�ֽ����Ϣ
		if (ch >= 'a' && ch <= 'z'			// ��Сд��ĸ
			|| ch >= 'A' && ch <= 'Z'		// ��Сд��ĸ
			|| ch == '?')					// ���ʺ�'?'��ʼ����Ϊ�����Ϣ
		{
			ElemType e;						// ����Ԫ��
			inFile >> e.student;			// ����ѧ������
			inFile >> e.adivisor;			// ����ѧ�����ĵ�ʦ����
			inFile >> e.place;				// �������販ʿѧλ�Ĵ�ѧ������д
			inFile >> e.dataOfPHD;			// �������販ʿѧλ�����
			elems[count++] = e;				// ��Ԫ�ش�������elems��
		}
		else
		{	// �ǽ����Ϣ��
			Readln();						// ����һ��
		}
	}

	for (int pos = 0; pos < n; pos++)
	{	// ��pos��Ԫ��elems[pos]
		if (elems[pos].adivisor == "---" || elems[pos].adivisor == "?")
		{	// elems[pos]��˫��
			parents[pos] = -1;							
		}
		else
		{
			int par;						// ˫��
			for (par = 0; par < n; par++)
			{	// ����Ԫ��elems[pos]��˫��
				if (elems[pos].adivisor == elems[par].student)
				{	// �ҵ�elems[pos]��˫��
					parents[pos] = par;		// Ԫ��elems[pos]��˫��Ϊpar
					break;
				}
			}

			if (par >= n)
			{	// ��ʾ��ʦelems[pos].adivisorû�а�����elems��
				// ����ʦelems[pos].adivisor����elems
				elems[n].student = elems[pos].adivisor;							// ��ʦ��
				elems[n].adivisor = elems[n].place = elems[n].dataOfPHD = "---";
					// ��˫�׵ĵ�ʦ����������Ϊ"---"
				parents[pos] = n;
				n++;						// �ڵ�ʦelems[pos].adivisor������elems��,�������Լ�1
			}
		}

	}

	pForest = new ParentForest<ElemType>(elems, parents, n, n);	// ����ɭ�� 
	
	delete []elems;							// �ͷ�elems�洢�ռ�
	delete []parents;						// �ͷ�parents�洢�ռ�
}

TCSGenealogy::TCSGenealogy(): inFile("database.txt")
// ����������������ۼ������ѧ������
{
	BuildForest();							// ���������ۼ������ѧ��������ɵ�ɭ��
}

TCSGenealogy::~TCSGenealogy()
// ����������ͷŴ洢�ռ估�ر�������
{
	delete pForest;							// �ͷ�ɭ��
	inFile.close();							// �ر�������
}

void TCSGenealogy::OutputHelp(ostream &outStream, int r, int level)
// ���������������ۼ������ѧ�����׸���������levelΪ���������������Ĳ����Ϊ1
{
	if (r >= 0 && r < pForest->NodeCount())
	{	// ���ڽ��r,����ʾr����Ϣ
		outStream<<endl;					// �������	
		for(int i = 0; i< level - 1; i++)
			outStream << "   ";				// ���λ��
		ElemType e;
		pForest->GetElem(r, e);				// ȡ�����r��Ԫ��ֵ

		outStream << e.student;				// ���ѧ������
		outStream << "(";					// ������"("
		if (e.place != "---") outStream << e.place << " ";
			// ������販ʿѧλ�Ĵ�ѧ������д
		if (e.dataOfPHD != "---") outStream << e.dataOfPHD;
			// ������販ʿѧλ�����
		outStream << ")";					// ������")"

		for (int child = pForest->FirstChild(r); child != -1; child = pForest->RightSibling(child))
		{	// ������ʾ��������
			OutputHelp(outStream, child, level + 1);
		}
	}
}

void TCSGenealogy::Output(OutputType tp)
// ���������������ۼ������ѧ������, tpΪ�������
{
	bool isFirstTree = true;				// �Ƿ��ǵ�1����
	ofstream *pOutFile = NULL;				// ����� 

	if (tp == OUTPUT_TO_FILE) 
	{	// ���������
		pOutFile = new ofstream("viewtree.txt");
	}

	for (int cur = 0; cur < pForest->NodeCount(); cur++)
	{	// ����ɭ���и������ĸ����
		if (pForest->Parent(cur) == -1)				
		{	// �����
			if (isFirstTree) isFirstTree = false;
			else if (tp == OUTPUT_TO_SCREEN) system("PAUSE");

			if (tp == OUTPUT_TO_SCREEN) 
			{	// ����Ļ��������ۼ������ѧ������
				OutputHelp(cout, cur, 1);
				cout << endl;				// ����
			}
			else 
			{	// ���������������ۼ������ѧ������
				OutputHelp(*pOutFile, cur, 1);
				*pOutFile << endl;			// ����
			}
		}
	}

	if (tp == OUTPUT_TO_FILE) 
	{	// ������ļ�
		pOutFile->close();					// �ر��ļ�
		delete pOutFile;					// �ͷŴ洢�ռ�
	}
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
		&& ch != '\t')						// chҲ��Ϊ�Ʊ��	
	{	// ��������ַ�׷�ӵ����Ա���
		temp.Insert(++size, ch);
	}
	String answer(temp);					// ���촮
	inStr = answer;							// ��inStr���ش�
	return inStream;						// ��������������
}

#endif
