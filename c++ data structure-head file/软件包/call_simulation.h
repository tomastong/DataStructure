// �ļ�·����: call_simulation\call_simulation.h 
#ifndef __CALL_SIMULATION_H__
#define __CALL_SIMULATION_H__

#include "lk_queue.h"							// ��������

// �ͻ�����
struct CustomerType
{
	int arrivalTime;							// �ͻ�����ʱ��
	int duration;								// �ͻ����ܷ��������ʱ��
	int curServiceTime;							// ��ǰ���ܷ����ʱ��
};

// �绰�ͻ�����ģ����
class CallSimulation
{
private:
//  �绰�ͻ�����ģ��������ݳ�Ա:
	LinkQueue<CustomerType> *callsWaitingQueue;	// �ͷ��绰�ȴ�����
	CustomerType *customerServed;				// �ͷ���Ա���ڷ���Ŀͻ�
	int curTime;								// ��ǰʱ��
	int totalWaitingTime;						// �ܵȴ�ʱ��
	int numOfCalls;								// ����ĵ绰��
	int numOfCustomerServiceStaffs;				// �ͷ���Ա������
	int limitTime;								// ʱ������(���ٽ��ܸ���绰)
	double arrivalRate;							// �ͻ�������
	int averageServiceTime;						// ƽ������ʱ��

// ��������
	void Service();								// ����ǰ�绰(�й��е绰)
	void CheckForNewCall();						// ����Ƿ����µ绰,�����,�򽫵绰��ӵ��绰����
	void Display();								// ��ʾģ����
	int GetNumOfWaitingCall();					// �õ��绰�����еȴ��ĵ绰��
	int MinLengthCallsWaitingQueue();			// ��̿ͷ��绰�ȴ�����
	int MaxLengthCallsWaitingQueue();			// ��ͷ��绰�ȴ�����

public:
// �绰�ͻ�����ģ���෽������:
	CallSimulation();							// �޲����Ĺ��캯��
	virtual ~CallSimulation();					// ��������
	void Run();									// ģ��绰�ͻ�����
};

// �绰�ͻ�����ģ�����ʵ�ֲ���
CallSimulation::CallSimulation()
// �����������ʼ�����ݳ�Ա
{
	// ��ʼ�����ݳ�Ա
	curTime = 0;								// ��ǰʱ���ֵΪ0
	totalWaitingTime = 0;						// �ܵȴ�ʱ���ֵΪ0
	numOfCalls = 0;								// ����ĵ绰����ֵΪ0

	// ���ģ�����
	cout << "����ͷ���Ա������:";
	cin >> numOfCustomerServiceStaffs;			// ����ͷ���Ա������ 
	cout << "����ʱ������:";
	cin >> limitTime;							// ���ٽ����µ绰��ʱ��
	int callsPerHour;							// ÿСʱ�绰��
	cout << "����ÿСʱ�绰��:";
	cin >> callsPerHour;						// ����ÿСʱ�绰��
	arrivalRate = callsPerHour / 60.0;			// ת��Ϊÿ���ӵ绰��
	cout << "����ƽ������ʱ��:";
	cin >> averageServiceTime;					// ����ƽ������ʱ��

	// ���䶯̬�洢�ռ�
	callsWaitingQueue = new LinkQueue<CustomerType>[numOfCustomerServiceStaffs];
		// Ϊ�ͷ��绰�ȴ������������洢�ռ�
	customerServed = new CustomerType[numOfCustomerServiceStaffs];	
		// Ϊ�ͷ���Ա���ڷ���Ŀͻ�����洢�ռ�

	// ��ʼ���ͷ���Ա���ڷ���Ŀͻ�
	for (int i = 0; i < numOfCustomerServiceStaffs; i++)
	{	// ��ʼ��ÿ���ͷ���Ա���ڷ���Ŀͻ�
		customerServed[i].curServiceTime = customerServed[i].duration = 0;	
			// ��ʾ��û�˽��ܷ���
	}

	// �������������
	SetRandSeed();								// �Ե�ǰʱ��ֵΪ���������
}

CallSimulation::~CallSimulation()
// ����������ͷŴ洢�ռ�
{
	delete []callsWaitingQueue;					// �ͷŷֿͷ��绰�ȴ�����������ռ�õĴ洢�ռ�
	delete []customerServed;					// �ͷſͷ���Ա���ڷ���Ŀͻ���ռ�õĴ洢�ռ�
}

void CallSimulation::Run()
// ���������ģ��绰�ͻ�����
{
	while (curTime < limitTime)
	{	// δ����ʱ������, �ɼ���µ绰
		CheckForNewCall();						// ����Ƿ����µ绰,�����,�򽫵绰��ӵ��绰����
		Service();								// ���з���
		curTime++;								// ����ʱ��
	}

	while (callsWaitingQueue[MaxLengthCallsWaitingQueue()].Length() > 0)
	{	// �ڷ��绰�ȴ������л��пͻ��ڵȴ�����
		Service();								// ���з���
		curTime++;								// ����ʱ��
	}

	Display();									// ��ʾģ����
}

void CallSimulation::Service()
// �������������ǰ�绰(�й��е绰)
{
	for (int i = 0; i < numOfCustomerServiceStaffs; i++)
	{	// ����ÿ���ͷ�������Ա�ṩ�ķ���
		if (customerServed[i].curServiceTime < customerServed[i].duration)
		{	// δ����ͻ����ܷ��������ʱ��, ����Ϊ�ͻ��ṩ����
			customerServed[i].curServiceTime++;	// ���ӿͻ����ܷ���ʱ��	
		}
		else
		{	// �ѵ���ͻ����ܷ��������ʱ��, Ϊ��һ�ͻ��ṩ����
			if (!callsWaitingQueue[i].Empty())
			{	// �пͻ��ڵȴ�
				callsWaitingQueue[i].OutQueue(customerServed[i]);	// �ӵȴ�������ȡ���¿ͻ����з���
				totalWaitingTime += curTime - customerServed[i].arrivalTime;	// �����ܵȴ�ʱ��
			}
		}
	}
}

void CallSimulation::CheckForNewCall()
// �������������Ƿ����µ绰,�����,�򽫵绰��ӵ��绰����
{
	int calls = GetPoissionRand(arrivalRate);	// ��ǰʱ�����绰������
	
	for (int i = 1; i <= calls; i++)
	{	// ��i���绰
		CustomerType customer;					// �ͻ�
		customer.arrivalTime = curTime;			// �ͻ�����ʱ��
		customer.duration = GetPoissionRand(averageServiceTime);	// �ͻ����ܷ��������ʱ��
		customer.curServiceTime = 0;			// ��ǰ���ܷ����ʱ��
		int pos = MinLengthCallsWaitingQueue();	// ��̿ͷ��绰�ȴ����е�λ��
		callsWaitingQueue[pos].InQueue(customer);	// �ͻ���ȴ�����
		numOfCalls++;							// ����ĵ绰��
	}
}

void CallSimulation::Display()
// �����������ʾģ����
{
	cout << "������ܵ绰��:" << numOfCalls << endl;
	cout << "ƽ���ȴ�ʱ��:" << (double)totalWaitingTime / numOfCalls << endl << endl;
}

int CallSimulation::GetNumOfWaitingCall()
// ����������õ��绰�����еȴ��ĵ绰��
{
	int n = 0;									// �绰����ʼ��Ϊ0
	
	for (int i = 0; i < numOfCustomerServiceStaffs; i++)
	{	// ��i����̿ͷ��绰����
		n += callsWaitingQueue[i].Length();		// �ۼӵ�i���绰�����еĵȴ�����
	}

	return n;									// ���ص绰�����еȴ��ĵ绰��
}

int CallSimulation::MinLengthCallsWaitingQueue()
// ����������õ���̿ͷ��绰�ȴ�����
{
	int pos = 0;								// ��ǰ��̿ͷ��绰�ȴ�����

	for (int i = 1; i < numOfCustomerServiceStaffs; i++)
	{	// ��i���ͷ��绰����
		if (callsWaitingQueue[i].Length() < callsWaitingQueue[pos].Length())
		{	// ��i���ͷ��绰���и���
			pos = i;							// ��i���ͷ��绰����Ϊ�µ���̿ͷ��绰�ȴ�����
		}
	}

	return pos;									// ������̿ͷ��绰�ȴ�����
}

int CallSimulation::MaxLengthCallsWaitingQueue()
// ����������õ���ͷ��绰�ȴ�����
{
	int pos = 0;								// ��ǰ��̿ͷ��绰�ȴ�����

	for (int i = 1; i < numOfCustomerServiceStaffs; i++)
	{	// ��i���ͷ��绰����
		if (callsWaitingQueue[i].Length() > callsWaitingQueue[pos].Length())
		{	// ��i���ͷ��绰���и���
			pos = i;							// ��i���ͷ��绰����Ϊ�µ���̿ͷ��绰�ȴ�����
		}
	}

	return pos;									// ������̿ͷ��绰�ȴ�����
}

#endif