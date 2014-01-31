#ifndef __STOPPING_PLACE_H__
#define __STOPPING_PLACE_H__

#include "lk_list.h"							// ����
#include "lk_stack.h"							// ��ջ

// �ļ�·����:stopping_place\stopping_place.h
struct VehicleType
{	// ��������
	unsigned int num;							// �������
	unsigned int time;							// ����/�뿪ʱ��
};
ostream &operator <<(ostream &outStream, const VehicleType &vehicle);
	// ������������<<	

// ͣ������
class StoppingPlace
{
private:
// ͣ����������ݳ�Ա:
	LinkStack<VehicleType> *pStopPath;			// ͣ������ͣ����
	LinkList<VehicleType> *pShortcutPath;		// ���
	int maxNumOfStopVehicle;					// ͣ������ͣ����ͣ�ų����������
	int rate;									// ͣ��λʱ����շ�ֵ

// ��������
	bool ExistVehicleInStopPath(const VehicleType &vehicle) const;
		// ͣ������ͣ�������Ƿ���ڳ���vehicle
	int LocateInpShortcutPath(const VehicleType &vehicle) const;		
		// �ڱ���в��ҳ���vehicle��λ��

public:
//  �������������ر���ϵͳĬ�Ϸ�������:
	StoppingPlace(int n, int r);				// ���캯��
	virtual ~StoppingPlace();					// ��������
	void DisplayStatus() const;					// ��ʾͣ���������г���״̬
	void Arrive(const VehicleType &vehicle);	// ���������������
	void Leave(const VehicleType &vehicle);		// �������뿪������
};

// ͣ�����༰��غ�����ʵ�ֲ���
ostream &operator <<(ostream &outStream, const VehicleType &vehicle) 
// �������: ������������<<
{
	cout << "(" << vehicle.num << "," << vehicle.time << ")  "; 
		// �����������뵽��ʱ��
	return outStream;
}

bool StoppingPlace::ExistVehicleInStopPath(const VehicleType &vehicle) const
// �������: ͣ������ͣ�������Ƿ���ڳ���vehicle
{
	VehicleType ve;								// ��ʱԪ��
	LinkStack<VehicleType> tmpS;				// ��ʱջ
	bool found = false;							// ��ʾ�Ƿ��ҵ�����
	
	while (!pStopPath->Empty() && !found)
	{	// ���ͣ������ͣ�����ĳ���
		pStopPath->Pop(ve);						// ������ջ
		tmpS.Push(ve);							// ��������ʱջ
		if (vehicle.num == ve.num)
		{	// ���ҵ�����
			found = true;
		}
	}
	while (!tmpS.Empty())
	{	// ����ʱջ�еĳ����ͻ�ͣ����pStopPath
		tmpS.Pop(ve);							// ������ջ
		pStopPath->Push(ve);					// ������ջ
	}

	return found;
}

int StoppingPlace::LocateInpShortcutPath(const VehicleType &vehicle) const
// �������: �ڱ���в��ҳ���vehicle��λ��, ���ҳɹ�,��������,���򷵻�0
{
	VehicleType ve;								// ��ʱԪ��
	
	for (int pos = 1; pos <= pShortcutPath->GetElem(pos, ve); pos++)
	{	// �����ڱ���еĳ���
		if (vehicle.num == ve.num)
		{	// ���ҵ�����
			return pos;							// ���س���λ��
		}
	}

	return 0;									// ����ʧ��
}

StoppingPlace::StoppingPlace(int n, int r)
// �������: ͣ����ͣ�ų����������Ϊn, ͣ��λʱ����շ�ֵΪr��ͣ��������
{
	pStopPath = new LinkStack<VehicleType>;		// ����ͣ������ͣ����
	pShortcutPath = new LinkList<VehicleType>;	// ���ɱ��
	maxNumOfStopVehicle = n;					// ͣ������ͣ����ͣ�ų����������
	rate = r;									// ͣ��λʱ����շ�ֵ
}

StoppingPlace::~StoppingPlace()
// �������: �ͷŴ洢�ռ�
{
	delete pStopPath;							// �ͷ�ͣ������ͣ����
	delete pShortcutPath;						// �ͷű��
}


void StoppingPlace::DisplayStatus() const
// �������: ��ʾͣ���������г���״̬
{
	cout << "ͣ�����еĳ���:";
	pStopPath->Traverse(Write);
	cout << endl;

	cout << "����еĳ���:";
	pShortcutPath->Traverse(Write);
	cout << endl << endl;
}

void StoppingPlace::Arrive(const VehicleType &vehicle)
// �������: ���������������
{
	if (pStopPath->Length() < maxNumOfStopVehicle)
	{	// ͣ����δ��
		pStopPath->Push(vehicle);				// ��������ͣ������ͣ����
	}
	else
	{	// ͣ��������
		pShortcutPath->Insert(pShortcutPath->Length() + 1, vehicle);	
			// ����������
	}
}

void StoppingPlace::Leave(const VehicleType &vehicle)
// �������: �������뿪������
{
	LinkStack<VehicleType> tmpS;				// ��ʱջ
	VehicleType ve;								// ��ʱԪ��

	if (ExistVehicleInStopPath(vehicle))
	{	// ������ͣ������
		for (pStopPath->Pop(ve); vehicle.num != ve.num; pStopPath->Pop(ve))
		{	// ��ͣ�����в��ҳ���
			tmpS.Push(ve);						// ������ջ
		}
		cout << "��ͣ�����д��ڱ��Ϊ" << vehicle.num << "�ĳ���" << endl;
		cout << "�˳����뿪, Ӧ��ͣ����" << (vehicle.time - ve.time) * rate << "Ԫ." << endl;
		while (!tmpS.Empty())
		{	// ����ʱջ�еĳ����ͻ�ͣ����pStopPath
			tmpS.Pop(ve);						// ������ջ
			pStopPath->Push(ve);				// ������ջ
		}
		if (!pShortcutPath->Empty())
		{	// ������г��� 
			pShortcutPath->Delete(1, ve);		// ȡ������еĵ�1���� 
			pStopPath->Push(ve);				// ���˳��ŵ�ͣ������
		}
	}
	else if (LocateInpShortcutPath(vehicle) != 0)
	{	// �����ڱ���� 
		int pos = LocateInpShortcutPath(vehicle);// �����ڱ���е�λ��
		cout << "�ڱ���д��ڱ��Ϊ" << vehicle.num << "�ĳ���" << endl;
		cout << "�˳����뿪, ����ͣ����." << endl;
		pShortcutPath->Delete(pos, ve);			// �ڱ���п��߳��� 
	}
	else
	{	// ��ͣ�����������޳���vehicle
		cout << "��ͣ���������в����ڱ��Ϊ" << vehicle.num << "�ĳ���" << endl;
	}
}

#endif