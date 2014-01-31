// �ļ�·����: telephone_book\telephone_book.h
#ifndef __TELEPHONE_BOOK_H__
#define __TELEPHONE_BOOK_H__

// �绰�ṹ
struct TelephoneType
{	
	char teleNo[18];					// �绰����
	char name[16];						// �û���
	char addr[18];						// ��ַ
	bool isEmpty;						// �Ƿ�Ϊ��
};

// �绰���벾��(m��ʾͰ����, b��ʾ��Ͱ��)
template <int m, int b>
class TelephoneBook
{
private:
// ���ݳ�Ա
	fstream hashFile;					// �绰���벾�ļ�

	// Ͱ�ṹ
	struct BucketType
	{
		TelephoneType records[m];		// �洢�绰��¼
		long next;						// ��ʾ��̵ĵ�ַ
	};

// ��������
	long Hash(const char teleNo[18]);	// ɢ�к���
	int LocateHelp(const BucketType &bucket, char teleNo[18]);					// ��λ��������
	void Locate(BucketType &bucket, long &offset, int &pos, char teleNo[18]);	// ��λ����
	int LocateEmptyRecordHelp(const BucketType &bucket);						// ��λ�ռ�¼��������
	void LocateEmptyRecord(BucketType &bucket, long &offset, int &pos, char teleNo[18]);
		// ��λ�ռ�¼
	void Input();						// �����¼
	void Delete();						// ɾ����¼
	void Serach();						// ��ѯ��¼

public:
// ���캯��, ���������뷽��
	TelephoneBook();					// �޲����Ĺ��캯��
	virtual ~TelephoneBook();			// ��������
	void Run();							// ����绰���벾
};

// �绰���벾���ʵ��
template <int m, int b>
long TelephoneBook<m, b>::Hash(const char teleNo[18])
// �������: ����ɢ�к���ֵ
{
	long h = 0;							// ɢ�к���ֵ
	for (int pos = 0; pos < (int)strlen(teleNo); pos++)
	{	// ���δ���������ַ�
		h = (h * 10 + teleNo[pos] - '0') % b;
	}
	return h;							// ����ɢ�к���ֵ
}

template <int m, int b>
int TelephoneBook<m, b>::LocateHelp(const BucketType &bucket, char teleNo[18])
// �������: ���ص绰����teleNo��Ͱbucket�е�λ��
{
	
	for (int pos = 0; pos < m; pos++)
	{	// ���αȽ�Ͱ�и��绰��¼
		if (!bucket.records[pos].isEmpty &&
			strcmp(bucket.records[pos].teleNo, teleNo) == 0) return pos; // ��λ�ɹ�
	}
	return -1;							// ��λʧ��
}

template <int m, int b>
void TelephoneBook<m, b>::Locate(BucketType &bucket, long &offset, 
	int &pos, char teleNo[18])
// �������: ��λ�绰����teleNo���ڵ�Ͱbucket, ��Ͱ�е�λ��pos, Ͱ���ļ�
//	�е�λ��λ��offset
{
	long h = Hash(teleNo);								// ɢ�к���ֵ
	offset = sizeof(BucketType) * h;					// Ͱ���ļ��е�λ��
	hashFile.clear();									// �����־	
	hashFile.seekg(offset, ios::beg);					// �ļ���λ
	hashFile.read((char *)&bucket, sizeof(BucketType));	// ��ȡ��Ͱ
	pos = LocateHelp(bucket, teleNo);					// ��λ�绰��¼��Ͱ�е�λ��
	if (pos == -1) offset = bucket.next;				// ���Ͱ��λ��
	while (pos == -1 && offset != -1)
	{	// ���������Ͱ�в���
		hashFile.clear();								// �����־	
		hashFile.seekg(offset, ios::beg);				// �ļ���λ
		hashFile.read((char *)&bucket, sizeof(BucketType));	// ������Ͱ
		pos = LocateHelp(bucket, teleNo);				// ��λ�绰��¼��Ͱ�е�λ��
		if (pos == -1) offset = bucket.next;			// ������Ͱ��λ��
	}
}

template <int m, int b>
int TelephoneBook<m, b>::LocateEmptyRecordHelp(const BucketType &bucket)
// �������: ���ؿռ�¼λλ��
{
	for (int pos = 0; pos < m; pos++)
	{	// ���αȽ�Ͱ�и��绰��¼
		if (bucket.records[pos].isEmpty) return pos;	// ��λ�ɹ�
	}
	return -1;											// ��λʧ��
}

template <int m, int b>
void TelephoneBook<m, b>::LocateEmptyRecord(BucketType &bucket, long &offset, 
	int &pos, char teleNo[18])
// �������: ��λ�绰����teleNo���ڵľ��пռ�¼��Ͱbucket, Ͱ�еĿռ�¼λ��pos, Ͱ
//	���ļ��е�λ��λ��offset
{
	long h = Hash(teleNo);								// ɢ�к���ֵ
	offset = sizeof(BucketType) * h;					// Ͱ���ļ��е�λ��
	hashFile.clear();									// �����־	
	hashFile.seekg(offset, ios::beg);					// �ļ���λ
	hashFile.read((char *)&bucket, sizeof(BucketType));	// ������Ͱ
	pos = LocateEmptyRecordHelp(bucket);				// ��λͰ�пռ�¼��λ��
	if (pos == -1) offset = bucket.next;				// ���Ͱ��λ��
	while (pos == -1 && offset != -1)
	{	// ���������Ͱ�в���
		hashFile.clear();								// �����־	
		hashFile.seekg(offset, ios::beg);				// �ļ���λ
		hashFile.read((char *)&bucket, sizeof(BucketType));	// ������Ͱ
		pos = LocateEmptyRecordHelp(bucket);			// ��λͰ�пռ�¼��λ��
		if (pos == -1) offset = bucket.next;			// ������Ͱ��λ��
	}
}

template <int m, int b>
void TelephoneBook<m, b>::Input()
// �������: �����¼
{
	TelephoneType telph;								// �绰�����¼
	telph.isEmpty = false;								// ���

	cout << "����绰����:";
	cin >> telph.teleNo;
	cout << "�����û���:";
	cin >> telph.name;
	cout << "�����ַ:";
	cin >> telph.addr;
	BucketType bucket;									// Ͱ
	long offset;										// Ͱ���ļ��е���Ӧλ��
	int pos;											// �绰��¼��Ͱ�е�λ��
	Locate(bucket, offset, pos, telph.teleNo);			// ��λ�绰��¼��λ��
	if (pos != -1) 
	{	// ��λ�ɹ�
		cout << "�绰����ɢ���ļ���!" << endl;
	}
	else
	{	// ��λʧ��
		LocateEmptyRecord(bucket, offset, pos, telph.teleNo);// ��λ�ռ�¼λ��
		if (pos != -1)
		{	// �ҵ��ռ�¼
			bucket.records[pos] = telph;				// ���绰��¼��ֵ��bucket.records[pos]
			hashFile.clear();							// �����־	
			hashFile.seekg(offset, ios::beg);			// ��λ�ļ�
			hashFile.write((char *)&bucket, sizeof(BucketType));// дͰ
		}
		else
		{
			hashFile.clear();							// �����־	
			hashFile.seekg(0, ios::end);				// ��λ���ļ�β
			bucket.next = hashFile.tellg();				// ������Ͱλ��
			hashFile.clear();							// �����־	
			hashFile.seekg(offset, ios::beg);			// ��λ�ļ�
			hashFile.write((char *)&bucket, sizeof(BucketType));// дͰ
			offset = bucket.next;						// �����Ͱ���ļ��е�λ��
			for (pos = 1; pos < m; pos++)
			{	// ���ÿռ�¼
				bucket.records[pos].isEmpty = true;
			}
			pos = 0;									// �绰��¼��λ��
			bucket.records[pos] = telph;				// ���绰��¼��ֵ��bucket.records[pos]
			hashFile.clear();							// �����־	
			hashFile.seekg(offset, ios::beg);			// ��λ�ļ�
			hashFile.write((char *)&bucket, sizeof(BucketType));// дͰ
		}
	}
}

template <int m, int b>
void TelephoneBook<m, b>::Delete()
// �������: ɾ����¼
{
	char teleNo[18];					// �绰����
	cout << "����绰����:";
	cin >> teleNo;
	BucketType bucket;					// Ͱ
	long offset;						// Ͱ���ļ��е���Ӧλ��
	int pos;							// �绰��¼��Ͱ�е�λ��
	Locate(bucket, offset, pos, teleNo);// ��λ�绰��¼��λ��
	if (pos == -1)
	{	// ��λʧ��
		cout << "ɾ����¼ʧ��!" << endl;
	}
	else
	{
		hashFile.clear();									// �����־	
		hashFile.seekg(offset, ios::beg);					// ��λ�ļ�
		hashFile.read((char *)&bucket, sizeof(BucketType));	// ��Ͱ
		bucket.records[pos].isEmpty = true;					// �ռ�¼
		hashFile.clear();									// �����־	
		hashFile.seekg(offset, ios::beg);					// ��λ�ļ�
		hashFile.write((char *)&bucket, sizeof(BucketType));// дͰ
		cout << "�绰����:" << bucket.records[pos].teleNo << endl;
		cout << "�û���:" << bucket.records[pos].name << endl;
		cout << "��ַ:" << bucket.records[pos].addr << endl;
		cout << "ɾ���ɹ�!" << endl;
	}
}

template <int m, int b>
void TelephoneBook<m, b>::Serach()
// �������: ���Ҽ�¼
{
	char teleNo[18];					// �绰����
	cout << "����绰����:";
	cin >> teleNo;
	BucketType bucket;					// Ͱ
	long offset;						// Ͱ���ļ��е���Ӧλ��
	int pos;							// �绰��¼��Ͱ�е�λ��
	Locate(bucket, offset, pos, teleNo);// ��λ�绰��¼��= -1)
	if (pos == -1)
	{	// ��λʧ��
		cout << "����ʧ��!" << endl;
	}
	else
	{
		hashFile.clear();									// �����־	
		hashFile.seekg(offset, ios::beg);					// ��λ�ļ�
		hashFile.read((char *)&bucket, sizeof(BucketType));	// ��Ͱ
		cout << "�绰����:" << bucket.records[pos].teleNo << endl;
		cout << "�û���:" << bucket.records[pos].name << endl;
		cout << "��ַ:" << bucket.records[pos].addr << endl;
	}
}

template <int m, int b>
TelephoneBook<m, b>::TelephoneBook()
// �������: ��ʼ���绰���벾
{
	ifstream iFile("telph.dat");					// ���������ļ�
	if (iFile.fail())
	{	// ���ļ�ʧ��,��ʾ�������ļ�
		ofstream oFile("telph.dat");				// ��������ļ�
		if (oFile.fail()) throw("���ļ�ʧ��!");	// �׳��쳣 
		oFile.close();								// �ر��ļ�
	}
	else
	{	// �����ļ�
		iFile.close();								// �ر��ļ�
	}

	hashFile.open("telph.dat", ios::in|ios::out|ios::binary);	// �Զ�д��ʽ���ļ�
	if (hashFile.fail()) throw("���ļ�ʧ��!");	// �׳��쳣 

	hashFile.seekg(0, ios::end);					// ��λ���ļ�β
	int bucketNum = hashFile.tellg() / sizeof(BucketType);	// Ͱ��
	
	if (bucketNum < b)
	{	// Ͱ�����ڻ�Ͱ��,˵���ļ����������ѱ��ƻ�, Ӧ��ʼ����Ͱ
		BucketType bucket;
		int pos;									// ��ʱ����
		for (pos = 0; pos < m; pos++)
		{	// ��ʼ����Ͱ
			bucket.records[pos].isEmpty = true;		// �ռ�¼
			bucket.next = -1;						// �����
		}
		hashFile.clear();							// �����־	
		hashFile.seekg(0, ios::beg);				// ��λ���ļ�ͷ
		for (pos = 0; pos < b; pos++)
		{	// д��Ͱ���ļ���
			hashFile.write((char *)&bucket, sizeof(BucketType));// д���Ͱ
		}
	}
}

template <int m, int b>
TelephoneBook<m, b>::~TelephoneBook()
// �������: �ر��ļ�
{
	hashFile.close();											// �ر��ļ�
}

template <int m, int b>
void TelephoneBook<m, b>::Run()
// �������: ����绰���벾
{
	int select;									// ��ʱ����
	do
	{
		cout << "1.�����¼ 2.ɾ����¼ 3.���Ҽ�¼ 4.�˳�" << endl;
		cout << "����ѡ��:";
		cin >> select;							// ����ѡ��
		while (GetChar() != '\n');				// ������ǰ�е������ַ�
		switch (select)
		{
		case 1:
			Input();							// �����¼
			break;
		case 2:
			Delete();							// ɾ����¼
			break;
		case 3:
			Serach();							// ���Ҽ�¼
			break;
		}
	} while (select != 4);
}

#endif


