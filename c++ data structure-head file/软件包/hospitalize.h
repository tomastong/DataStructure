#ifndef __HOSPITALIZE_H__
#define __HOSPITALIZE_H__

#include "lk_queue.h"					// ������

// ��ҽ��
class Hospitalize
{
private:
//  ��ҽ������ݳ�Ա:
	LinkQueue <unsigned int> queue;					// ���˶���

// ��������
	void StandInALine();							// �Ŷ�
	void Cure();									// ����
	void Display();									// �鿴�Ŷ�

public:
//  �������������ر���ϵͳĬ�Ϸ�������:
	Hospitalize(){};								// �޲����Ĺ��캯��
	~Hospitalize(){};								// ��������
	void Work();									// ҽ������
};

// ��ҽ���ʵ�ֲ���
void Hospitalize::StandInALine()
// �������: �����ŶӲ��˵Ĳ����ţ����뵽�����ŶӶ�����
{
	unsigned int num;								// ������
	
	cout << "�����벡����:"; 
	cin >> num;										// �����ŶӲ���
	queue.InQueue(num);								// �������ż��뵽�����ŶӶ�����
}

void Hospitalize::Cure()
// �������: �����ŶӶ�������ǰ��Ĳ��˾��������Ӷ�����ɾ��
{
	if (queue.Empty())
	{	// �޲���
		cout << "����û�в������Ŷ���!" << endl;
	}
	else
	{
		unsigned int num;							// ������
		queue.OutQueue(num);						// �����ŶӶ�������ǰ��Ĳ��˾��������Ӷ�����ɾ��
		cout << num << "�Ų������ھ�ҽ." << endl;
	}
}

void Hospitalize::Display()
// �������: �Ӷ��׵���β�г����е��ŶӲ��˵Ĳ�����
{
	queue.Traverse(Write);							// �Ӷ��׵���β�г����е��ŶӲ��˵Ĳ�����
	cout << endl;
}

void Hospitalize::Work()
// �������: ҽ������
{
	int select = 0;

	while (select != 4)
	{
		cout << "1. �Ŷ�--���벡�˵Ĳ����ţ����뵽���˶�����" << endl;
		cout << "2. ����--�����ŶӶ�������ǰ��Ĳ��˾��������Ӷ�����ɾ��" << endl;
		cout << "3. �鿴�Ŷ�--�Ӷ��׵���β�г����е��ŶӲ��˵Ĳ�����" << endl;
		cout << "4. �°�--�˳�����" << endl;
		cout << "��ѡ��:";
		cin >> select;								// ѡ����
		switch(select)
		{
		case 1:
			StandInALine();		// �Ŷ�--���벡�˵Ĳ����ţ����뵽���˶�����
			break;
		case 2:
			Cure();				// ����--�����ŶӶ�������ǰ��Ĳ��˾��������Ӷ�����ɾ��
			break;
		case 3:
			Display();			// �鿴�Ŷ�--�Ӷ��׵���β�г����е��ŶӲ��˵Ĳ�����
			break;
		}
	}
}

#endif