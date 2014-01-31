// �ļ�·����:line_LineEditor\line_LineEditor.h
#ifndef __LINE_LineEditor_H__
#define __LINE_LineEditor_H__

#include "dbl_lk_list.h"				// ˫������
#include "string.h"						// �ַ���

// �ı��༭��
class LineEditor
{
private:
// �ı��༭������ݳ�Ա:
	DblLinkList<String> textBuffer;		// �ı�����
	int curLineNo;						// ��ǰ�к�
	DblLinkList<String> textUndoBuffer;	// ���ڻָ����ı�����
	int curUndoLineNo;					// ���ڻָ��ĵ�ǰ�к�
	ifstream inFile;					// �����ļ�
	ofstream outFile;					// ����ļ�

// ��������:
	StatusCode NextLine();				// ת����һ��
	StatusCode PreviousLine();			// ת��ǰһ��
	StatusCode GotoLine();				// ת��ָ����
	StatusCode InsertLine();			// ����һ��	
	void ChangeLine();					// �滻��ǰ�л������е�ָ���ı���
	void ReadFile();					// �����ı��ļ�
	void WriteFile();					// д�ı��ļ�
	void FindString();					// ���Ҵ�

public:
//  ��������:
	LineEditor(char infName[], char outfName[]);	// ���캯��
	void Run();							// �����ı��༭��
};

// �ı��༭���ʵ�ֲ���
LineEditor::LineEditor(char infName[], char outfName[]):inFile(infName), outFile(outfName)
// �������: �������ļ���infName������ļ���outfName����༭���������캯��
{
	if (inFile == NULL) throw Error("�������ļ�ʧ��!");	// �׳��쳣
	if (outFile == NULL) throw Error("������ļ�ʧ��!");	// �׳��쳣
	ReadFile();												// �����ı���
}

void LineEditor::Run()
// �������: �����ı��༭��
{
	char userCommand;							// �û�����

	do
	{
		String tempString;						// ��ʱ��
		String curLine;							// ��ǰ��

		if (curLineNo != 0)
		{	// ���ڵ�ǰ��
			textBuffer.GetElem(curLineNo, curLine);	// ȡ����ǰ��
			cout << curLineNo << " : "			// ��ʾ�к�
				<< curLine.CStr() << endl << "?";	// ��ʾ��ǰ�м��ʺ�?
		}
		else
		{	// �����ڵ�ǰ��
			cout << "�ļ������" << endl << "?";
		}

		userCommand = GetChar();				// ���Կո�ȡ�ò��������ַ�
		userCommand = tolower(userCommand);		// ת��ΪС����ĸ
		while (cin.get() != '\n');				// �����û�����������ַ�

		if (userCommand != 'u' && userCommand != 'h' && 
			userCommand != '?' && userCommand != 'v')
		{	// �洢������Ϣ
			textUndoBuffer = textBuffer;		// ���ڳ����Ļ���
			curUndoLineNo = curLineNo;			// ���ڳ������к�
		}
		// ���в�������
		switch (userCommand) 
		{
		case 'b':	// ת����1��b(egin)
			if (textBuffer.Empty())
			{	// �ı������
				cout << " ����: �ı������ " << endl;
			}
			else
			{	// �ı�����ǿ�, ת����1��
				curLineNo = 1;
			}
			break;
		case 'c':	// �滻��ǰ�л�������c(hange)
			if (textBuffer.Empty())
			{
				cout << " ����: �ı������" << endl;
			}
			else
			{	// �滻����
				ChangeLine();
			}
			break;
		case 'd':	// ɾ����ǰ��d(elelete)
			if (textBuffer.Delete(curLineNo, tempString) != SUCCESS)
			{	// ɾ����ǰ��ʧ��
				cout << " ����: ɾ��ʧ�� " << endl;
			}
			break;
		case 'e':	// ת�����һ��e(nd)
			if (textBuffer.Empty())
			{
				cout << " ����: �ı������ " << endl;
			}
			else
			{	// ת������һ��
				curLineNo = textBuffer.Length();
			}
			break;
		case 'f':	// �ӵ�ǰ�л��1�п�ʼ����ָ���ı�f(ind)
			if (textBuffer.Empty())
			{
				cout << " ����: �ı������ " << endl;
			}
			else
			{	// �ӵ�ǰ�п�ʼ����ָ���ı�
				FindString();
			}
			break;
		case 'g':	// ת��ָ����g(o)
			if (GotoLine() != SUCCESS)
			{	// ת��ָ����ʧ��
				cout << " ����: û����������" << endl;
			}
			break;
		case '?':	// ��ð���?
		case 'h':	// ��ð���h(elp)
			cout << "��Ч����: b(egin) c(hange) d(el) e(nd)" << endl
				<< "f(ind) g(o) h(elp) i(nsert) n(ext) p(rior)" << endl
				<< "q(uit) r(ead) u(ndo) v(iew) w(rite) " << endl;
			break;
		case 'i':	// ����ָ����i(nsert)
			if (InsertLine() != SUCCESS)
				cout << " ����: �����г��� " << endl;
			break;
		case 'n':	// ת����һ��n(ext)
			if (NextLine() != SUCCESS)
			{	// ����һ��
				cout << " ����: ��ǰ���������һ��" << endl;
			}
			break;
		case 'p':	// ת��ǰһ��p(rior)
			if (PreviousLine() != SUCCESS)
			{	// ��ǰһ��
				cout << " ����: ��ǰ�����ǵ�һ��" << endl;
			}
			break;
		case 'q':	// �˳�p(uit)
			break;
		case 'r':	// �����ı���r(ead)
			ReadFile();
			break;
		case 'u':	// �����ϴβ���u(ndo)
			Swap(textUndoBuffer, textBuffer);	// ����textUndoBuffer��textBuffer
			Swap(curUndoLineNo, curLineNo);		// ����curUndoLineNo��curLineNo
			break;
		case 'v':	// ��ʾ�ı�v(iew)
			textBuffer.Traverse(Write);
			break;
		case 'w':	// д�ı����浽����ļ���w(rite)
			if (textBuffer.Empty())
			{	// �ı������
				cout << " ����: �ı������" << endl;
			}
			else
			{	// д�ı����浽����ļ���
				WriteFile();
			}
			break;
		default :
			cout << "����h��?��ð�����������Ч�����ַ�: \n";
		}
	}
	while (userCommand != 'q');
}

StatusCode LineEditor::NextLine()
// �������: ת����һ��
{
	if( curLineNo >= textBuffer.Length())
	{	// ��ǰ�к��������һ��
		return FAIL;
	}
	else
	{	// ��ǰ�кŲ������һ��
		curLineNo++;
		return SUCCESS;
	}
}

StatusCode LineEditor::PreviousLine()
// �������: ת��ǰһ��
{
	if(curLineNo <= 1)
	{	// ��ǰ�к����ǵ�һ��
		return FAIL;
	}
	else
	{	// ��ǰ�кŲ��ǵ�һ��
		curLineNo--;
		return SUCCESS;
	}
}

StatusCode LineEditor::GotoLine()
// �������: ת��ָ����
{
	int lineNumber;
	cout << " ����ָ�����к�: ";
	cin  >> lineNumber;
	if(lineNumber < 1 || lineNumber > textBuffer.Length())
	{	// �кŷ�Χ��
		return RANGE_ERROR;
	}
	else
	{	// �кŷ�Χ��ȷ
		curLineNo = lineNumber;
		return SUCCESS;
	}
}

StatusCode LineEditor::InsertLine()
// �������: ����ָ����
{
	int lineNumber;	
	cout << " ����ָ���к�? ";
	cin  >> lineNumber;
	while (cin.get() != '\n');			// ���������ַ�
	cout << " ���������ı���: ";
	String toInsert = Read(cin);		// ������
	if (textBuffer.Insert(lineNumber, toInsert) == SUCCESS)
	{	// ����ɹ�
		curLineNo = lineNumber;
		return SUCCESS;
	}
	else
	{	// ����ʧ��
		return RANGE_ERROR;
	}
}

void LineEditor::ChangeLine()
// �������: �û�����ָ���ı������ڵ�ǰ�л�������������������ı����滻ָ���ı���
//	�滻�ɹ�����SUCCESS�����򷵻�FAIL
{
	char answer;						// �û��ش��ַ�
	bool initialResponse = true;		// ��ʼ�ش�

	do
	{	// ѭ��ֱ���û�����ǡ���Ļش�Ϊֹ
		if (initialResponse)
		{	// ��ʼ�ش�
			cout << "�滻��ǰ��c(urrent)���滻������a(ll):";
		}
		else
		{	// �ǳ�ʼ�ش�
			cout << "��c��a�ش�:";
		}
		
		answer = GetChar();				// �������������ո��Ʊ����ȡһ�ַ�
		while (cin.get() != '\n');		// �����û�����������ַ�
		answer = tolower(answer);		// ת��ΪС����ĸ
		initialResponse = false;
	} while (answer != 'c' && answer != 'a');

	cout << " ����Ҫ���滻��ָ���ı���: ";
	String strOld = Read(cin);			// �ɴ�
	cout << " �������ı���:";
	String strNew = Read(cin);			// �´�

	for (int row = 1; row <= textBuffer.Length(); row++)
	{
		if (answer == 'c' && row != curLineNo)
		{	// ֻ�滻��ǰ��,row��Ϊ��ǰ��
			continue;							// ������һ��ѭ��
		}

		String strRow;							// ��	
		textBuffer.GetElem(row, strRow);		// ȡ����
		int index = Index(strRow, strOld);		// �ڵ�ǰ���в��Ҿ��ı�	
		if (index != -1) 
		{	// ģʽƥ��ɹ�
			String newLine;						// ����
			Copy(newLine, strRow, index);		// ����ָ���ı�ǰ�Ĵ�
			Concat(newLine, strNew);			// �������ı���
			const char *oldLine = strRow.CStr();// ����
			Concat(newLine, (String)(oldLine + index + strlen(strOld.CStr())));
				// ����ָ���ı�����Ĵ�,oldLine + index + strlen(oldText.CStr())���ڼ���һ��
				// ��ʱָ�룬ָ������ڱ��滻�ַ�������ַ�, Ȼ��C���ת����String����
				// �����ӵ�newline�ĺ��档
			textBuffer.SetElem(row, newLine);		// ���õ�ǰ���´�
		}
	}
}

void LineEditor::ReadFile()
// �������: �����ı���
{
	bool proceed = true;
	if (!textBuffer.Empty()) 
	{	// �ı�����ǿ�
		cout << "�ı�����ǿ�; �����ļ�ʱ��������." << endl;
		cout << " �ش�yes��ִ�д˲���? " << endl;
		if (proceed = UserSaysYes()) 
		{	// �ش�yes
			textBuffer.Clear();	// ��ջ���
		}
	}

	int lineNumber = 1;			// ��ʼ�к�	
	char terminalChar;			// ����ֹ�ַ�
	while (proceed) 
	{
		String inString = Read(inFile, terminalChar);	// ����һ���ı�
		if (terminalChar == EOF) 
		{	// ���ļ�����������, �����ѽ���
			proceed = false;
			if (strlen(inString.CStr()) > 0) 
			{	// ����ǿ���
				textBuffer.Insert(lineNumber , inString);		
			}
		}
		else
		{	// ����δ����
			textBuffer.Insert(lineNumber++, inString);
		}
	}

	textUndoBuffer = textBuffer;	// ���ڳ����Ļ���
	if (textBuffer.Empty())
	{	// ��ǰ�ı�����Ϊ��
		curLineNo = 0;				// ��ʾ����Ϊ��
		curUndoLineNo = 0;			// ���ڳ������к�
	}
	else
	{	// ��ǰ�ı�����ǿ�
		curLineNo = 1;				// ��ʾ����ǿ�
		curUndoLineNo = 1;			// ���ڳ������к�
	}
}

void LineEditor::WriteFile()
// �������: д�ı����浽����ļ���
{
	String curLine;			// ��ǰ��
    int lineNumber;			// �к�
	for(lineNumber=1; lineNumber <= textBuffer.Length(); lineNumber++)
	{	// д�ı�������е�����ļ���
		textBuffer.GetElem(lineNumber, curLine);	// ȡ����ǰ��
		outFile << curLine.CStr() << endl;	// �����ǰ��
	}
}

void LineEditor::FindString()
// �������: �ӵ�ǰ�л��1�п�ʼ����ָ���ı�
{
	char answer;						// �û��ش��ַ�
	bool initialResponse = true;		// ��ʼ�ش�

	do
	{	// ѭ��ֱ���û�����ǡ���Ļش�Ϊֹ
		if (initialResponse)
		{	// ��ʼ�ش�
			cout << "�ӵ�1�п�ʼf(irst)��ӵ��п�ʼc(urrent):";
		}
		else
		{	// �ǳ�ʼ�ش�
			cout << "��f��c�ش�:";
		}
		
		answer = GetChar();				// �������������ո��Ʊ����ȡһ�ַ�
		while (cin.get() != '\n');		// �����û�����������ַ�
		answer = tolower(answer);		// ת��ΪС����ĸ
		initialResponse = false;
	} while (answer != 'f' && answer != 'c');
	if (answer == 'f') curLineNo = 1;	// �ӵ�1�п�ʼ
	
	int index;
	cout << "���뱻���ҵ��ı���:";
	String searchString = Read(cin);		// ��������ı���
	String curLine;							// ��ǰ��	
	textBuffer.GetElem(curLineNo, curLine);	// ȡ����ǰ��
	while ((index = Index(curLine, searchString)) == -1)
	{	// ����ָ���ı���
		if (curLineNo < textBuffer.Length()) 
		{	// ������һ��
			curLineNo++;					// ��һ��
			textBuffer.GetElem(curLineNo, curLine);// ȡ����һ��
		}
		else
		{	// �Ѳ�����������
			break;
		}
	}
	
	if (index == -1) 
	{	// ����ʧ��
		cout << "���Ҵ�ʧ��.";
	}
	else 
	{	// ���ҳɹ�
		cout << curLine.CStr() << endl;		// ��ʾ��
		for (int i = 0; i < index; i++)
		{	// �ڲ��Ҵ�ǰ��λ�����пո�
			cout << " ";
		}
		for (int j = 0; j < (int)strlen(searchString.CStr()); j++)
		{	// �ڲ��Ҵ�ǰ��λ������^
			cout << "^";
		}
   }
   cout << endl;
}

#endif