// �ļ�·����: student_infor_manage\student_infor_manage.h
#ifndef __STUDENT_INFOR_MANAGE_H__
#define __STUDENT_INFOR_MANAGE_H__

#include "bin_serach.h"		// ���ֲ����㷨

// ѧ����Ϣ��¼�ṹ
struct StuInforType
{
	char num[7];			// ѧ��
	char name[9];			// ����
	char sex[3];			// �Ա�
	int age;				// ����
	char dep[19];			// ϵ
	bool isDeleted;			// �Ƿ�ɾ��
};

// ������ṹ
struct IndexItemType
{
	char num[7];			// ѧ��
	long offset;			// ѧ�����������¼���������ļ��е���Ӧλ��
};

// ���������������Ҫ�Ĺ�ϵ�����
bool operator <=(const char num[7], const IndexItemType &item);
	// ���ع�ϵ�����<=
bool operator <(const char num[7], const IndexItemType &item);
	// ���ع�ϵ�����<
bool operator ==(const char num[7], const IndexItemType &item);
	// ���ع�ϵ�����==
bool operator <(const IndexItemType &first, const IndexItemType &second);
	// ���ع�ϵ�����<

static const long INCREMENT_OF_INDEX_TABLE = 100;// ����������

// ѧ����Ϣ������
class StudentInforManage
{
private:
// ѧ����Ϣ����������ݳ�Ա:
	FILE *pFStuData;							// ѧ�������ļ�
	IndexItemType *pIndexTable;					// ������
	long size;									// ������ǰ��������
	long maxSize;								// �����������������

//	��������:
	void Display(const StuInforType &stuInfor);	// ��ʾ��¼
	void DisplayALL();							// ��ʾ���м�¼
	void Serach();								// ���Ҽ�¼
	void Input();								// �����¼
	void Delete();								// ɾ����¼
	void Update();								// ���¼�¼

public:
// ���к���:
	StudentInforManage();						// �޲����Ĺ��캯��
	virtual ~StudentInforManage();				// ��������
	void Run();									// ѧ����Ϣ����
};

// ѧ����Ϣ�����༰��غ�����ʵ�ֲ���
bool operator <=(const char num[7], const IndexItemType &item)
// �������: ���ع�ϵ�����<=
{
	return strcmp(num, item.num) <= 0;
}

bool operator <(const char num[7], const IndexItemType &item)
// �������: ���ع�ϵ�����<
{
	return strcmp(num, item.num) < 0;
}

bool operator ==(const char num[7], const IndexItemType &item)
// �������: ���ع�ϵ�����==
{
	return strcmp(num, item.num) == 0;
}

bool operator <(const IndexItemType &first, const IndexItemType &second)
// �������: ���ع�ϵ�����<
{
	return strcmp(first.num, second.num) < 0;
}

StudentInforManage::StudentInforManage()
// �������: ������������ʼ�������Ϣ
{
	if ((pFStuData = fopen("student.dat", "rb+")) == NULL)
	{	// �������ļ�student.dat
		if ((pFStuData = fopen("student.dat", "wb+")) == NULL)
			throw Error("�������ļ�ʧ��!");		// �׳��쳣
	}
	
	FILE *pFStuIndex;								// �����ļ�
	if ((pFStuIndex = fopen("student.idx", "rb+")) == NULL)
	{	// �������ļ�student.idx
		size = 0;									// ��������
		maxSize = INCREMENT_OF_INDEX_TABLE;			// �����������������
		pIndexTable = new IndexItemType[maxSize];		// ����洢�ռ�
	}
	else
	{
		fseek(pFStuIndex, 0, SEEK_END);				// ʹ�ļ�ָ��ָ���ļ�β
		size = ftell(pFStuIndex) / sizeof(IndexItemType);// ��������
		maxSize = size + INCREMENT_OF_INDEX_TABLE;	// �����������������
		pIndexTable = new IndexItemType[maxSize];		// ����洢�ռ�
		fseek(pFStuIndex, 0, SEEK_SET);				// ʹ�ļ�ָ��ָ���ļ�ͷ
		for (int pos = 0; pos < size; pos++)
		{	// ����������
			fread(&pIndexTable[pos], sizeof(IndexItemType), 1, pFStuIndex);	// ��������
		}
		fclose(pFStuIndex);							// �ر��ļ�
	}
}

StudentInforManage::~StudentInforManage()
// �������: �ر��ļ����ͷŴ洢�ռ�
{
	fclose(pFStuData);							// �ر��ļ�
	FILE *pFStuIndex;							// �����ļ�
	if ((pFStuIndex = fopen("student.idx", "wb")) == NULL)
		throw Error("�������ļ�ʧ��!");		// �׳��쳣
	for (int pos = 0; pos < size; pos++)
	{	// д������
		fwrite(&pIndexTable[pos], sizeof(IndexItemType), 1, pFStuIndex);
	}
	fclose(pFStuIndex);							// �ر��ļ�
	delete []pIndexTable;						// �ͷŴ洢�ռ�
}

void StudentInforManage::Display(const StuInforType &stuInfor)
// �������: ��ʾ��¼
{
	cout << "ѧ��:" << stuInfor.num << endl;
	cout << "����:" << stuInfor.name << endl;
	cout << "�Ա�:" << stuInfor.sex << endl;
	cout << "����:" << stuInfor.age << endl;
	cout << "ϵ:" << stuInfor.dep << endl;
}

void StudentInforManage::DisplayALL()
// �������: ��ʾ���м�¼
{
	cout << setw(8) << "ѧ��" << setw(10) << "����" << setw(6) << "�Ա�" 
		<< setw(6) << "����" << setw(16) << "ϵ" << endl;
	for (int pos = 0; pos < size; pos++)
	{	// ��ʾ���м�¼
		StuInforType stuInfor;					// ѧ����Ϣ
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// ��λ���ļ���¼
		fread(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// ����¼
		cout << setw(8) << stuInfor.num << setw(10) << stuInfor.name << setw(6) << stuInfor.sex 
			<< setw(6) << stuInfor.age << setw(16) << stuInfor.dep << endl;
	}
}

void StudentInforManage::Serach()
// �������: ���Ҽ�¼
{
	char num[7];
	cout << "����ѧ��:";
	cin >> num;
	while (GetChar() != '\n');					// ������ǰ�е������ַ�
	int pos = BinSerach(pIndexTable, size, num);// ���ֲ���
	if (pos == -1)
	{	// ����ʧ��
		cout << "���޴�ѧ��!" << endl;
	}
	else
	{	// ���ҳɹ�
		StuInforType stuInfor;					// ѧ����Ϣ
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// ��λ���ļ���¼
		fread(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// ����¼
		Display(stuInfor);						// ��ʾ��¼
	}
}

void StudentInforManage::Input()
// �������: �����¼
{
	StuInforType stuInfor;						// ѧ����Ϣ
	stuInfor.isDeleted = false;					// ɾ�����
	cout << "ѧ��:"; cin >> stuInfor.num;
	cout << "����:"; cin >> stuInfor.name;
	cout << "�Ա�:"; cin >> stuInfor.sex;
	cout << "����:"; cin >> stuInfor.age;
	cout << "ϵ:"; cin >>stuInfor.dep;
	while (GetChar() != '\n');					// ������ǰ�е������ַ�
	if (BinSerach(pIndexTable, size, stuInfor.num) >= 0)
	{	// ���ҳɹ�
		cout << "ѧ���ظ�, ����ʧ��!" << endl;
		return;
	}

	fseek(pFStuData, 0, SEEK_END);				// ��λ���ļ���ǰλ��Ϊ�ļ�β
	long offset = ftell(pFStuData);				// ѧ�����������¼���������ļ��е���Ӧλ��
	fwrite(&stuInfor, sizeof(StuInforType), 1, pFStuData);		// д��¼

	if (size >= maxSize)
	{	// �������Ѵﵽ�������
		maxSize += INCREMENT_OF_INDEX_TABLE;	// �����������
		IndexItemType *pTmp;					// ��ʱ������
		pTmp = new IndexItemType[maxSize];		// ���·���洢�ռ�
		for (int pos = 0; pos < size; pos++)
			pTmp[pos] = pIndexTable[pos];		// ����������
		delete []pIndexTable;					// �ͷ�pIndexTable
		pIndexTable = pTmp;						// pIndexTableָ���´洢�ռ�
	}

	int j;
	for (j = size - 1; j >= 0 && stuInfor.num < pIndexTable[j]; j--)
	{	// ����stuInfor.num������������
		pIndexTable[j + 1] = pIndexTable[j];
	}
	strcpy(pIndexTable[j + 1].num, stuInfor.num);	// ѧ��
	pIndexTable[j + 1].offset = offset;			// ѧ�����������¼���������ļ��е���Ӧλ��
	size++;										// ����������Լ�1
}

void StudentInforManage::Delete()
// �������: ɾ����¼
{
	char num[7];
	cout << "����ѧ��:";
	cin >> num;
	while (GetChar() != '\n');					// ������ǰ�е������ַ�
	int pos = BinSerach(pIndexTable, size, num);// ���ֲ���
	if (pos == -1)
	{	// ����ʧ��
		cout << "���޴�ѧ��!" << endl;
	}
	else
	{	// ���ҳɹ�
		StuInforType stuInfor;					// ѧ����Ϣ
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// ��λ���ļ���¼
		fread(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// ����¼
		stuInfor.isDeleted = true;				// ɾ�����
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// ��λ���ļ���¼
		fwrite(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// д��¼
		
		for (int i = pos + 1; i < size; i++)
		{	// ����������ɾ��������
			pIndexTable[i - 1] = pIndexTable[i];
		}
		size--;									// ����������Լ�1
		Display(stuInfor);						// ��ʾ��¼
		cout << "ɾ���ɹ�!" << endl;
	}
}

void StudentInforManage::Update()
// �������: ���¼�¼
{
	char num[7];
	cout << "����ѧ��:";
	cin >> num;
	while (GetChar() != '\n');					// ������ǰ�е������ַ�
	int pos = BinSerach(pIndexTable, size, num);// ���ֲ���
	if (pos == -1)
	{	// ����ʧ��
		cout << "���޴�ѧ��!" << endl;
	}
	else
	{	// ���ҳɹ�
		StuInforType stuInfor;					// ѧ����Ϣ
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// ��λ���ļ���¼
		fread(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// ����¼
		Display(stuInfor);						// ��ʾ��¼

		cout << "ѧ��:"; cin >>stuInfor.num;
		cout << "����:"; cin >> stuInfor.name;
		cout << "�Ա�:"; cin >> stuInfor.sex;
		cout << "����:"; cin >> stuInfor.age;
		cout << "ϵ:"; cin >>stuInfor.dep;
		while (GetChar() != '\n');				// ������ǰ�е������ַ�
		fseek(pFStuData, pIndexTable[pos].offset, SEEK_SET);	// ��λ���ļ���¼
		long offset = pIndexTable[pos].offset;	// �ݴ�offset
		if (strcmp(stuInfor.num, pIndexTable[pos].num) == 0)
		{	// �ؼ���û��, ��������
			fwrite(&stuInfor, sizeof(StuInforType), 1, pFStuData);	// д��¼
		}
		else
		{	// �޸�������
			if (BinSerach(pIndexTable, size, stuInfor.num) >= 0)
			{	// ���º�,ѧ���ظ�
				cout << "ѧ���ظ�, ����ʧ��!" << endl;
			}
			else
			{
				for (int i = pos + 1; i < size; i++)
				{	// ����������ɾ��������
					pIndexTable[i - 1] = pIndexTable[i];
				}
				strcpy(pIndexTable[size - 1].num, stuInfor.num);	// ѧ��
				pIndexTable[size - 1].offset = offset;	
					// ѧ�����������¼���������ļ��е���Ӧλ��
				for (int j = size - 1; j > 0 && pIndexTable[j] < pIndexTable[j - 1]; j--)
				{	// ��pIndexTable[size-1]��ļ�¼��������pIndexTable[size-1]�ĺ���
					Swap(pIndexTable[j], pIndexTable[j - 1]);
				}
			}
		}
	}
}

void StudentInforManage::Run()
// �������: ѧ����Ϣ����
{
	int select;									// ��ʱ����
	do
	{
		cout << "1.�����¼ 2.ɾ����¼ 3.���¼�¼ 4.���Ҽ�¼ 5.��ʾ���м�¼ 6.�˳�" 
			<< endl;
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
			Update();							// ���¼�¼
			break;
		case 4:
			Serach();							// ���Ҽ�¼
			break;
		case 5:
			DisplayALL();						// ��ʾ���м�¼
			break;
		}
	} while (select != 6);
}

#endif
