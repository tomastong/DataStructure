// �ļ�·����: dictionary_anagram_search_system\dictionary_anagram_search_system.h
#ifndef __DICTIONARY_ANAGRAM_SEARCH_SYSTEM_H__
#define __DICTIONARY_ANAGRAM_SEARCH_SYSTEM_H__

#include "string.h"								// ��
#include "quick_sort.h"							// ��������
#include "bin_serach.h"							// �۰����

// �ʵ��λ�ʼ���ϵͳ��
class DictionaryAnagramSearchSystem
{
private:
// �ʵ��λ�ʼ���ϵͳ������ݳ�Ա
	String *dict;								// �ʵ�
	int size;									// ������

// ��������
	void AllArrageCreateAnagram(String word, String &anagram, int curLen = 0);
		// ��word���ַ���ȫ���в�����λ��

public:
//  ��������
	DictionaryAnagramSearchSystem();			// �޲����Ĺ��캯��
	virtual ~DictionaryAnagramSearchSystem();	// ��������
	void Run();									// ���дʵ��λ�ʼ���ϵͳ

};

// ��غ���
istream &operator >>(istream &inStream, String &inStr);			// �������������>>
ostream &operator <<(ostream &outStream, const String &outStr);	// ������������<<
void readln(istream &inStream);	// ��������inStream����һ��

// �ʵ��λ�ʼ���ϵͳ�༰��غ�����ʵ�ֲ���
void DictionaryAnagramSearchSystem::AllArrageCreateAnagram(String word, String &anagram, int curLen)
// �����������word���ַ���ȫ���в�����λ��
{
	if (curLen == anagram.Length())
	{	// ����һ�����ܵı�λ��
		if (anagram != word && BinSerach(dict, size, anagram) >= 0)
		{	// wordΪ�ʵ��еĵ���
			cout << anagram << " ";				// �����λ��
		}
	}
	else
	{	// �Խ�ռ����ǰ�������anagram[curLen..anagram.Length()-1]�ж�����У��ݹ�
		// ����������j
		for (int pos = curLen; pos < anagram.Length(); pos++)
		{	// ����ȡ��anagram[curLen..anagram.Length()-1]�е��ַ�
			Swap(anagram[curLen], anagram[pos]);// ����anagram[curLen]��anagram[pos]
			AllArrageCreateAnagram(word, anagram, curLen + 1);	// �ݹ����������
			Swap(anagram[curLen], anagram[pos]);// ����anagram[curLen]��anagram[pos]
		}
	}
}

DictionaryAnagramSearchSystem::DictionaryAnagramSearchSystem()
// ������������ʵ��ļ�
{
	ifstream dictFile("diction.txt");			// �ʵ��ļ�
	if (dictFile == NULL) throw Error("���ļ�ʧ��!");	// �׳��쳣
	size = 0;									// ͳ�Ƶ�����
	char ch;									// ��ʱ����
	
	cout << "����ͳ�ƴʵ�����ĵ�����..." << endl;
	while ((ch = dictFile.peek()) != EOF && ch != '\n')
	{	// ��ǰ�еĵ�һ���ַ������ļ��������뻻�з�, ͳ�Ƶ�����
		readln(dictFile);						// ����һ��
		size++;									// һ����һ��
	}
	cout << "�ʵ������" << size << "������" << endl;

	cout << "���ڶ�ȡ�ʵ�..." << endl;
	dict = new String[size];					// ����洢�ռ�
	dictFile.clear();							// ���EOF��־
	dictFile.seekg(0);							// ��λ���ļ�ͷ
	for (int pos = 0; pos < size; pos++)
	{	// ���뵥��
		dictFile >> dict[pos];
	}

	cout << "���ڽ�������..." << endl;
	QuickSort(dict, size);						// �Ե��ʽ�������

	dictFile.close();							// �ر��ļ�
}

DictionaryAnagramSearchSystem::~DictionaryAnagramSearchSystem()
// ����������ͷŶ��ʵ���Ϣ
{
	delete []dict;
}				

void DictionaryAnagramSearchSystem::Run()
// ������������дʵ��λ�ʼ���ϵͳ
{
	do 
	{
		String word;
		cout << "���뵥��:";
		cin >> word;
		cout << word << "�ı�λ����:";
		AllArrageCreateAnagram(word, word);		// ��word���ַ���ȫ���в�����λ��
		cout << endl;
		cout << "�Ƿ����";
	} while (UserSaysYes());
}

istream &operator >>(istream &inStream, String &inStr)
// ������������������>>
{
	LinkList<char> temp;						// ��ʱ���Ա�
	int length = 0;								// ��ʼ���Ա���
	char ch= GetChar(inStream);					// ��������inStream�������ո��Ʊ����ȡһ�ַ�
	inStream.putback(ch);						// ��c����������
	while ((ch = inStream.peek()) != EOF &&		// peek()����������ȡһ���ַ�
												// ������ָ�벻��
		(ch = inStream.get()) != '\n')			// get()����������ȡһ���ַ�ch,ch��Ϊ���з�
	{	// ��������ַ�׷�ӵ����Ա���
		temp.Insert(++length, ch);
	}
	String answer(temp);						// ���촮
	inStr = answer;								// ��inStr���ش�
	return inStream;							// ��������������
}

ostream &operator <<(ostream &outStream, const String &outStr)
// ������������������<<
{
	cout << outStr.CStr();						// �����ֵ
	return outStream;							// �������������
}

void readln(istream &inStream)
// �����������������inStream����һ��
{
	char ch;									// ��ʱ����
	while ((ch = inStream.peek()) != EOF &&		// peek()����������ȡһ���ַ�
												// ������ָ�벻��
		(ch = inStream.get()) != '\n');			// get()����������ȡһ���ַ�ch,ch��Ϊ���з����ļ�������
}

#endif

