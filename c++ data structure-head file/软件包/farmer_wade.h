// �ļ�·����: farmer_wade\farmer_wade.h
#ifndef __FARMER_WADE_H__
#define __FARMER_WADE_H__

#include "sq_list.h"								// ˳���

// ���Ӷ���ö������
enum Wader
{
	cabbage,	// �ײ�
	goat,		// ��
	wolf,		// ��
	farmer		// ũ��
};

// ���ӷ���ö������
enum WadeDirection
{
	southToNorth,	// ���ϰ�������
	northToSouth	// �ɱ������ϰ�
};


// �Զ��崮�� 
class MyString
{
private:
// ��������ݳ�Ա
	char strVal[5];									// ��ֵ

public:                           
//  ��������
	MyString(int value = 0);						// ���캯��
	MyString(char strValue[]);						// ���캯��
	virtual ~MyString(){};							// ��������
	operator int() const;							// ������ת������
	char &operator [](int pos);						// �����±������
};

// �Զ��崮���ʵ�ֲ���
MyString::MyString(int value)
// ������������캯��,������ת��Ϊ�����ƴ� 
{
	int mask = 1;									// ������
	strVal[4] = '\0';								// ��������
	for (int pos = 3; pos >= 0; pos--)
	{	// ����ȡ�������Ƶĸ�λ
		strVal[pos] = value & mask ? '1' : '0';		// ȡ��1λ��������
		mask = mask << 1;							// ����1λ
	}
}

MyString::MyString(char strValue[])
// ������������캯��, ��C��񴮹���C++���
{
	strcpy(strVal, strValue);
}

MyString::operator int() const
// ���������������ת������, �������ƴ�����ת��Ϊ����
{
	int val = 0;									// ����ֵ
	for (int pos = 0; pos < 4; pos++) 
	{	// �������ƴ�����ת��Ϊ����
		val = val * 2 + strVal[pos] - '0';
	}
	return val;										// ��������ֵ
}

char &MyString::operator [](int pos)
// ��������������±������
{
	return strVal[pos];					
}

// ũ�������
class FarmerWade
{
private:
// ũ�����������ݳ�Ա
	int path[16];							// ��ʾ·��,��ĳ״̬stateδ���ֹ�,��-1��ʾ,���Ϊǰ��״̬

// ��������
	bool WithFarmer(Wader wader, MyString &state) const;	// ������wader�Ƿ���farmer�ںӵ�ͬһ��
	bool IsSafe(MyString &state) const;		// �ж�״̬�Ƿ�ȫ
	void DisplayRoute();					// ��ʾ���ӷ���
	void Init();							// ��ʼ��·��
	void DFS(MyString curState = "0000");	// ��������������ӵķ���

public:
//  ��������
	FarmerWade(){};							// �޲����Ĺ��캯��
	virtual ~FarmerWade(){};				// ��������
	void Run();								// ����ũ�����

};

// ũ��������ʵ�ֲ���
bool FarmerWade::WithFarmer(Wader wader, MyString &state) const
// ���������������wader�Ƿ���ũ��farmer�ںӵ�ͬһ��
{
	return (state[wader] == state[farmer]);
}

bool FarmerWade::IsSafe(MyString &state) const
// ����������ж�״̬�Ƿ�ȫ
{
	if (state[goat] == state[cabbage] && state[farmer] != state[cabbage] ||			// ��԰ײ�
		state[wolf] == state[goat] && state[farmer] != state[goat]) return false;	// �ǳ���
	else return true;
}

void FarmerWade::DisplayRoute()
// �����������ʾ���ӷ���
{
	if (path[15] == -1)
	{	// path[15]��ǰ��,��ʾ���ܳɹ�����Ŀ��״̬
		cout << "ũ����������޽�" << endl;
		return;
	}

	SqList<MyString> statePath;				// �ô��洢״̬·��
	int state;								// ��ʱ���� 
	for (state = 15; state >= 0; state = path[state])
	{	// �������,��ɴӳ�ʼ״̬��Ŀ��״̬��ת��
		statePath.Insert(1, state);			// ��״Ҫ�õ�MyString�Ĺ��캯��,�Զ�������ת��ΪMyString�Ĵ�
	}

	WadeDirection direction = southToNorth;	// ���ӷ���
	MyString current, next;					// ��ǰ״̬,��һ״̬
	for (int step = 1; step < statePath.Length(); step++)
	{	// ������ʾ���ӵ�ÿһ��
		statePath.GetElem(step, current);	// ȡ����ǰ״̬
		statePath.GetElem(step + 1, next);	// ȡ����һ״̬
		Wader wader; 
		for (int w = 0; w <= 3; w++)
		{	// ��ȡ״̬�����仯�ĵ�1��������
			if (current[w] != next[w])
			{	// ״̬�����仯
				wader = (Wader)w;		
				break;
			}
		}

		cout << "����" << step << ": ";
		switch (wader)
		{
		case cabbage:
			cout << "ũ��Ѱײ˴�" << ((direction == southToNorth) ? "������" : "���ϰ�") << endl;
			break;
		case goat:
			cout << "ũ������" << ((direction == southToNorth) ? "������" : "���ϰ�") << endl;
			break;
		case wolf:
			cout << "ũ����Ǵ�" << ((direction == southToNorth) ? "������" : "���ϰ�") << endl;
			break;
		case farmer:
			cout << "ũ�����" << ((direction == southToNorth) ? "������" : "���ϰ�") << endl;
			break;
		}
		direction = ((direction == southToNorth) ? northToSouth : southToNorth);	// �ı䷽��
	}

	cout << "ף����! �����������ɹ�!" << endl;
}

void FarmerWade::Init()
// �����������ʼ��·��
{
	for (int pos = 0; pos < 16; pos++) path[pos] = -1;
}

void FarmerWade::DFS(MyString curState)
// �����������������������ӵķ���
{
	if (path[15] == -1)
	{	// ��δ��������״̬
		for (int companion = 0; companion <= 3; companion++)
		{	// ������
			if (WithFarmer((Wader)companion, curState))
			{	// ��ũ����ӵ�ֻ����ũ����ͬһ�Ӱ�
				MyString nextState = curState;	// ��һ״̬
				nextState[farmer] = ((nextState[farmer] == '0') ? '1' : '0');// ũ��ض�����
				if (companion != (int)farmer)
				{	// ����ũ�򵥶�����
					nextState[companion] = ((nextState[companion] == '0') ? '1' : '0');
				}
				if (IsSafe(nextState) && path[nextState] == -1 && nextState != 0)
				{	// ����������ת�������Զ�����MyString -> int
					path[nextState] = curState;	// ��ǰ״̬����һ״̬����ϵ
					DFS(nextState);				// ����һ״̬������������
				}
			}
		}
	}
}

void FarmerWade::Run()
// �������������ũ�����
{
	Init();			// ��ʼ��·��
	DFS();			// ��������������ӵķ���
	DisplayRoute();	// ��ʾ���ӷ���
}

#endif
