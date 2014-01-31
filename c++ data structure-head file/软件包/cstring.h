// �ļ�·����:cstring\cstring.h
#ifndef __CString_H__
#define __CString_H__

#include "lk_list.h"							// ��������

// ����
class CString 
{
protected:
//  ��ʵ�ֵ����ݳ�Ա:
	mutable char *strVal;						// ��ֵ
	int length;									// ����	

public:                           
//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	CString();									// ���캯�� 
	virtual ~CString();							// ��������
	CString(const CString &copy);				// ���ƹ��캯��
	CString(const char *copy);					// ��C���ת���Ĺ��캯��
	CString(LinkList<char> &copy);				// �����Ա�ת���Ĺ��캯��
	int Length() const;							// �󴮳���			 
	bool Empty() const;							// �жϴ��Ƿ�Ϊ��
	CString &operator =(const CString &copy);	// ��ֵ�������
	const char *CStr() const;					// ����ת����C���
	char &CString::operator [](int pos) const;	// �����±������
};

// ����ز���
CString operator +(const CString &strFirst, const CString &strSecond);
	// ���ؼӷ������+
ostream &operator <<(ostream &outStream, const CString &outStr);
	// ���������<<
istream &operator >>(istream &inStream, CString &inStr);
	// ���������>>
CString Read(istream &input);					// �����������봮
CString Read(istream &input, char &terminalChar);
	// �����������봮������terminalChar���ش������ַ�
void Write(CString &s);							// �����
void Concat(CString &addTo, const CString &addOn);
	// ����addOn���ӵ�addTo���ĺ���
void Copy(CString &copy, const CString &original);
	// ����original���Ƶ���copy
void Copy(CString &copy, const CString &original, int n);
	// ����original����n���ַ�����copy 
int Index(const CString &target, const CString &pattern, int pos = 0);
	// ����ģʽ��pattern��һ����Ŀ�괮target�дӵ�pos���ַ���ʼ���ֵ�λ��
CString SubString(const CString &s, int pos, int len);	
	// ��s�ĵ�pos���ַ���ʼ�ĳ���Ϊlen���Ӵ�
bool operator ==(const CString &first, const CString &second);
	// ���ع�ϵ�����==
bool operator <(const CString &first, const CString &second);
	// ���ع�ϵ�����<
bool operator >(const CString &first, const CString &second);
	// ���ع�ϵ�����>
bool operator <=(const CString &first, const CString &second);
	// ���ع�ϵ�����<=
bool operator >=(const CString &first, const CString &second);
	// ���ع�ϵ�����>=
bool operator !=(const CString &first, const CString &second);
	// ���ع�ϵ�����!=

// ���༰��ز�����ʵ�ֲ���
CString::CString()
//  �����������ʼ���� 
{
	length = 0;									// ������Ϊ0
	strVal = NULL;								// �մ�
}

CString::~CString()
// ������������ٴ����ͷŴ���ռ�ÿռ�
{
	delete []strVal;							// �ͷŴ�strVal
}

CString::CString(const CString &copy)
// ����������ɴ�copy�����´��������ƹ��캯��
{
	length = strlen(copy.CStr());				// ����
	strVal = new char[length + 1];				// ����洢�ռ�
	strcpy(strVal, copy.CStr());				// ���ƴ�ֵ
}

CString::CString(const char *copy)
// �����������C���ת�������´�����ת�����캯��
{
	length = strlen(copy);						// ����
	strVal = new char[length + 1];				// ����洢�ռ� 
	strcpy(strVal, copy);						// ���ƴ�ֵ
}

CString::CString(LinkList<char> &copy)
// ��������������Ա�ת�������´�����ת�����캯��
{
	length = copy.Length();						// ����
	strVal = new char[length + 1];				// ����洢�ռ� 
	for (int i = 0; i < length; i++) 
	{	// ���ƴ�ֵ
		copy.GetElem(i + 1, strVal[i]);
	}
	strVal[length] = '\0';						// ��ֵ��'\0'����	
}

int CString::Length() const
// ������������ش�����			 
{
	return length;
}

bool CString::Empty() const
// ��������������Ϊ�գ�����true�����򷵻�false
{
	return length == 0;
}

CString &CString::operator =(const CString &copy)
// �����������ֵ�������
{
	if (&copy != this)
	{
		delete []strVal;						// �ͷ�ԭ���洢�ռ�
		length = strlen(copy.CStr());			// ����
		strVal = new char[length + 1];			// ����洢�ռ� 
		strcpy(strVal, copy.CStr());			// ���ƴ�ֵ
	}
	return *this;
}

const char *CString::CStr() const
// �������������ת����C���
{
	return (const char *)strVal;				// ��ֵ����ת��
}

char &CString::operator [](int pos) const
// ��������������±������
{
	return strVal[pos];
}

void Concat(CString &addTo, const CString &addOn)
// �������������addOn���ӵ�addTo���ĺ���
{
	const char *cFirst = addTo.CStr();			// ָ���һ����
	const char *cSecond = addOn.CStr();			// ָ��ڶ�����
	char *copy = new char[strlen(cFirst) + strlen(cSecond) + 1];// ����洢�ռ�
	strcpy(copy, cFirst);						// ���Ƶ�һ����
	strcat(copy, cSecond);						// ���ӵڶ�����
	addTo = copy;								// ����ֵ
	delete []copy;								// �ͷ�copy
}

CString operator +(const CString &strFirst, const CString &strSecond)
// ������������ؼӷ������+
{
	const char *cFirst = strFirst.CStr();		// ָ���һ����
	const char *cSecond = strSecond.CStr();		// ָ��ڶ�����
	char *copy = new char[strlen(cFirst) + strlen(cSecond) + 1];// ����洢�ռ�
	strcpy(copy, cFirst);						// ���Ƶ�һ����
	strcat(copy, cSecond);						// ���ӵڶ�����
	CString answer(copy);						// ���촮
	delete []copy;								// �ͷ�copy
	return answer;								// ���ش�
}

ostream &operator <<(ostream &outStream, const CString &outStr)
// ������������������<<
{
	cout << outStr.CStr();						// �����ֵ
	return outStream;							// �������������
}

istream &operator >>(istream &inStream, CString &inStr)
// ������������������>>
{
	LinkList<char> temp;						// ��ʱ���Ա�
	int size = 0;								// ��ʼ���Ա���
	char ch= GetChar(inStream);					// ��������inStream�������ո��Ʊ����ȡһ�ַ�
	inStream.putback(ch);						// ��ch����������
	while ((ch = inStream.peek()) != EOF &&		// peek()����������ȡһ���ַ�
												// ������ָ�벻��
		(ch = inStream.get()) != '\n'			// get()����������ȡһ���ַ�ch
												// ������ָ��ָ����һ�ַ�,ch��Ϊ���з�
		&& ch != '\t' && ch != ' ')				// chҲ��Ϊ�Ʊ����ո�	
	{	// ��������ַ�׷�ӵ����Ա���
		temp.Insert(++size, ch);
	}
	CString answer(temp);						// ���촮
	inStr = answer;								// ��inStr���ش�
	return inStream;							// ��������������
}

CString Read(istream &input)
// ��������������������봮
{
	LinkList<char> temp;						// ��ʱ���Ա�
	int size = 0;								// ��ʼ���Ա���
	char c;										// ��ʱ�ַ�
	while ((c = input.peek()) != EOF &&			// peek()����������ȡһ���ַ�
												// ������ָ�벻��
		(c = input.get()) != '\n')				// get()����������ȡһ���ַ�
												// ������ָ��ָ����һ�ַ�
	{	// ��������ַ�׷�����Ա���
		temp.Insert(++size, c);
	}
	CString answer(temp);						// ���촮
	return answer;								// ���ش�
}

CString Read(istream &input,char &terminalChar)
// ��������������������봮������terminalChar���ش������ַ�
{
	LinkList<char> temp;						// ��ʱ���Ա�
	int size = 0;								// ��ʼ���Ա���
	char c;										// ��ʱ�ַ�
	while ((c = input.peek()) != EOF &&			// peek()����������ȡһ���ַ�
												// ������ָ�벻��
		(c = input.get()) != '\n')				// get()����������ȡһ���ַ�
												// ������ָ��ָ����һ�ַ�
	{	// ��������ַ�׷�����Ա���
		temp.Insert(++size, c);
	}
	terminalChar=c;	// ��terminalChar���ش������ַ�
	CString answer(temp);						// ���촮
	return answer;								// ���ش�
}

void Write(CString &s)
// ��������������
{
	cout << s.CStr() << endl;					// �����ֵ
}

void Copy(CString &copy, const CString &original)
// �������������original���Ƶ���copy
{
	const char *cOriginal = original.CStr();	// ��ʼ��
	char *cCopy = new char[strlen(cOriginal) + 1];// ����洢�ռ�
	strcpy(cCopy, cOriginal);					// ���ƴ�
	copy = cCopy;								// ����ֵ
	delete []cCopy;								// �ͷŴ�cCopy
}

void Copy(CString &copy, const CString &original, int n)
// �������������original����n���ַ�����copy 
{
	const char *cOriginal = original.CStr();// ��ʼ��
	int len = (int)strlen(cOriginal) < n ? (int)strlen(cOriginal) : n;//Ŀ�괮��
	char *cCopy = new char[len + 1];			// ����洢�ռ�
	strncpy(cCopy, cOriginal, n);				// ���ƴ�
	cCopy[len] = '\0';							// ��ֵ��'\0'����
	copy = cCopy;								// ����ֵ
	delete []cCopy;								// �ͷŴ�cCopy
}

int Index(const CString &target, const CString &pattern, int pos)
// ������������ƥ��ɹ�������ģʽ��pattern��һ����Ŀ�괮target�дӵ�pos
//	���ַ���ʼ���ֵ�λ��, ���򷵻�-1
{
	const char *cTarget = target.CStr();		// Ŀ�괮
	const char *cPattern = pattern.CStr();		// ģʽ��
	const char *ptr=strstr(cTarget + pos, cPattern);	// ģʽƥ��
	if (ptr == NULL)
	{	// ƥ��ʧ��	
		return -1; 
	}
	else
	{	// ƥ��ɹ�	
		return ptr - cTarget;
	}
}

CString SubString(const CString &s, int pos, int len)
// ��ʼ��������s���ڣ�0 <= pos < s.Length()��0 <= len <= s.Length() - pos
// ������������ش�s�ĵ�pos���ַ���ʼ�ĳ���Ϊlen���Ӵ�
{
	if  (0 <= pos && pos < s.Length() && 0 <= len)
	{	// ���ش�s�ĵ�pos���ַ���ʼ�ĳ���Ϊlen���Ӵ�
		len = (len < s.Length() - pos) ? len : (s.Length() - pos);// �Ӵ���
		char *sub = new char[len + 1];			// ����洢�ռ�
		const char *str = s.CStr();				// ����C���
		strncpy(sub, str + pos, len);			// ���ƴ�
		sub[len] = '\0';						// ��ֵ��'\0'����
		CString tem(sub);						// ���ɴ�����
		return tem;
	}
	else
	{	// ���ؿմ�
		CString tem("");						// ���ɿմ�����
		return tem;
	}
}

bool operator ==(const CString &first, const CString &second)
// ������������ع�ϵ�����==
{
	return strcmp(first.CStr(), second.CStr()) == 0;
}

bool operator <(const CString &first, const CString &second)
// ������������ع�ϵ�����<
{
	return strcmp(first.CStr(), second.CStr()) < 0;
}

bool operator >(const CString &first, const CString &second)
// ������������ع�ϵ�����>
{
	return strcmp(first.CStr(), second.CStr()) > 0;
}

bool operator <=(const CString &first, const CString &second)
// ������������ع�ϵ�����<=
{
	return strcmp(first.CStr(), second.CStr()) <= 0;
}

bool operator >=(const CString &first, const CString &second)
// ������������ع�ϵ�����>=
{
	return strcmp(first.CStr(), second.CStr()) >= 0;
}

bool operator !=(const CString &first, const CString &second)
// ������������ع�ϵ�����!=
{
	return strcmp(first.CStr(), second.CStr()) != 0;
}

#endif