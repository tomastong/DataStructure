// �ļ�·����: park_dragoman\park_dragoman.h
#ifndef __PARK_DRAGOMAN_H__
#define __PARK_DRAGOMAN_H__

#include "adj_list_undir_network.h"			// ���������ڽӱ���
#include "lk_stack.h"						// ��ջ
#include "string.h"							// ����

// ��԰������
class ParkDragoman
{
private:
// ��԰����������ݳ�Ա:
	AdjListUndirNetwork<String, double> *pNet;	// �ɹ�԰��Ϣ���������� 
	ifstream *pInFile;						// ������ 
	int maxNumOfShowPath;					// �����ʾ·������
	double **dist;							// ���Զ���u��v֮������·������dist[u][v]
	int **path;								// ���Զ���u��v֮������·��path[u][v]
	
// ��������:
	int LocateVex(const String &e);			// ���ض���Ԫ�������е�λ��
	void Readln();							// ����һ��  
	void ShowTourismPath(int tourismPath[]);// ���������·
	void CreateTourismPath(int to, int v, int tourismPath[], int pathVertexNum); 
		// tourismPathΪ����·��, ����Ϊto, vΪ��ǰ��ǰ����, pathVertexNumΪ·����ǰ������
	void ShortestPathFloyd();				// ��Floyd�㷨��������net�и��Զ�������·��

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	ParkDragoman(ifstream *pIFile);			// ���캯��
	virtual ~ParkDragoman();				// ��������
	void Run();								// ��԰����
};

// ���ش�����/��������
ostream &operator <<(ostream &outStream, const String &outStr);
	// ���������<<
istream &operator >>(istream &inStream, String &inStr);
	// ���������>>

// ��԰�����༰��غ�����ʵ�ֲ���
int ParkDragoman::LocateVex(const String &e)
// ������������ض��������е�λ��
{
	for (int v = 0; v < pNet->GetVexNum(); v++)
	{	// ���β��ҿγ�
		String strTmp;						// ��ʱ����
		pNet->GetElem(v, strTmp);			// ���ض�����Ϣ
		if (strTmp == e)
		{	// ���ҳɹ�
			return v;						// �Ǹ���ʾ���ҳɹ�
		}
	}
	
	return -1;								// -1��ʾ����ʧ��
}

void ParkDragoman::Readln()
// �������������һ��
{	
	char ch;								// �ַ�
	while ((ch = (*pInFile).peek()) != EOF	// ��Ϊ�ļ�������
		&& (ch = (*pInFile).get()) != '\n');// ��Ϊ���з�
}
 
void ParkDragoman::ShowTourismPath(int tourismPath[])
// ������������������·
{
	int pos;								// ��ʱ����

	cout << "��·:";
	cout << "��� ";						// ���			
	String e;								// ·���϶���Ԫ��ֵ
	for (pos = 1; pos < pNet->GetVexNum() - 1; pos++)
	{	// ���·���ϵ��м䶥��Ԫ��ֵ
		pNet->GetElem(tourismPath[pos], e);	// ȡ������Ԫ��ֵ
		cout << e << " ";					// ���·���ϵ��м��
	}
	cout << "����" << endl;					// ����
	
	double pathLength = 0;					// ��·����
	for (pos = 1; pos < pNet->GetVexNum(); pos++)
	{	// ��ÿ���ߵĳ������
		pathLength = pathLength + pNet->GetWeight(tourismPath[pos - 1], tourismPath[pos]);
	}
	cout << "����:" << pathLength << endl << endl;
}

void ParkDragoman::CreateTourismPath(int to, int v, int tourismPath[], int pathVertexNum) 
// ��ʼ����: tourismPathΪ����·��, ����Ϊto, vΪ��ǰ��ǰ����, pathVertexNumΪ·����ǰ������
// �������: ���ɲ��������·��
{
	static int n = 0;						// �������������·����
	
	for (int w = pNet->FirstAdjVex(v); w >= 0; w = pNet->NextAdjVex(v, w))
	{	// ��v�������ڽӵ����ѭ��
		if (n == maxNumOfShowPath)
		{	// ����������ʾ·����
			break;							// �˳�ѭ��
		}
		else if (pNet->GetTag(w) == UNVISITED && pathVertexNum == pNet->GetVexNum() - 1 && 
			w == to && n < maxNumOfShowPath)
		{	// �õ�һ��������·
			++n;							// �������������·�����Լ�1
			tourismPath[pathVertexNum++] = w;	// ��w���뵽������·��
			ShowTourismPath(tourismPath);	// ���������·
		}
		else if	(pNet->GetTag(w) == UNVISITED)
		{	// wδ�����ʹ�
			tourismPath[pathVertexNum++] = w;	// ��w���뵽������·��
			pNet->SetTag(w, VISITED);		// �÷��ʱ�־ΪVISITED
			CreateTourismPath(to, w, tourismPath, pathVertexNum);	
				// ��w��Ϊ�µĵ�ǰ��㽨��������·
			pathVertexNum--;				// �ָ�·���������������
			pNet->SetTag(w, UNVISITED);		// ���÷��ʱ�־ΪUNVISITED,�Ա����
		}
	}
}

void ParkDragoman::ShortestPathFloyd()
// �������: ��Floyd�㷨��������net�и��Զ���u��v֮������·��path[u][v]��·������
//	dist[u][v],path[u][v]�洢��u��v�����·�������˶����ǰһ����Ķ����,dist[u][v]
//	�洢��u��v�����·���ĳ���
{
	for (int u = 0; u < pNet->GetVexNum(); u++)
		for (int v = 0; v < pNet->GetVexNum(); v++)
		{	// ��ʼ��path��dist
			dist[u][v] = (u != v && pNet->GetWeight(u, v) == 0 ) ? pNet->GetInfinity() : pNet->GetWeight(u, v);
			if (u != v && dist[u][v] < pNet->GetInfinity()) path[u][v] = u;	// ���ڱ�(u,v)
			else path[u][v] = -1;											// �����ڱ�(u,v)
		}

	for (int k = 0; k < pNet->GetVexNum(); k++)
		for (int i = 0; i < pNet->GetVexNum(); i++)
			for (int j = 0; j < pNet->GetVexNum(); j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{	// ��i��k�ٵ�j��·�����ȸ���
					dist[i][j] = dist[i][k] + dist[k][j]; 
					path[i][j] = path[k][j];
				}
}

ParkDragoman::ParkDragoman(ifstream *pIFile)
// �������: �������ļ�������ʾ��԰��Ϣ����
{
	pInFile = pIFile;						// �����ļ�
	char ch;								// ��ʱ����

	// �������������뾰����, ������"n="����
	(*pInFile).seekg(0);					// ��λ���ļ���ʼ��
	ch = GetChar(*pInFile);					// ���ַ�
	while (ch != 'n')
	{	// ������'n'��ʼ����
		if (ch != '\n') Readln();			// ����
		ch = GetChar(*pInFile);				// �����ַ�
	}
	GetChar(*pInFile);						// ����"="
	int n;									// ������
	*pInFile >> n;							// ���뾰����

	String *es = new String[n + 2];			// ������Ԫ��, �����������/���
	// �������������뾰������, ��������"v="����, ���辰���������ո񣬲�ͬ������֮
	// ���ÿո�ָ�
	(*pInFile).seekg(0);					// ��λ���ļ���ʼ��
	ch = GetChar(*pInFile);					// ���ַ�
	while (ch != 'v')
	{	// ������'v��ʼ����
		if (ch != '\n') Readln();			// ����
		ch = GetChar(*pInFile);				// �����ַ�
	}
	ch=GetChar(*pInFile);					// ����"="
	int i;									// ��ʱ����
	for (i = 0; i < n; i++)
	{	// ���뾰������
		*pInFile >> es[i];					// ��������*pInFile�����뾰������
	}
	es[n] = "���";							// ���
	es[n + 1] = "����";						// ����

	// �������������������ʾ·������, �����ʾ·��������"s="���� 
	(*pInFile).seekg(0);					// ��λ���ļ���ʼ��
	ch = GetChar(*pInFile);					// ���ַ�
	while (ch != 's')
	{	// ������'s'��ʼ����
		if (ch != '\n') Readln();			// ����
		ch = GetChar(*pInFile);				// �����ַ�
	}
	GetChar(*pInFile);						// ����"="
	*pInFile >> maxNumOfShowPath;			// ���������ʾ·������

	pNet = new AdjListUndirNetwork<String, double>(es, n + 2);
		// ������

	// �����������������Ϣ
	(*pInFile).seekg(0);					// ��λ���ļ���ʼ��
	ch = GetChar(*pInFile);					// ���ַ�
	while (true)
	{	// �ļ�δ����
		while (ch != '(' && ch != EOF)
		{	// ������'('��ʼ���л��������ѽ���
			if (ch != '\n') Readln();		// ����
			ch = GetChar(*pInFile);			// �����ַ�
		}
		if (ch == EOF) break;				// �������ѽ���
		String e1, e2;				 		// �߶���Ԫ��
		int v1, v2;							// �߶���
		double w;							// Ȩֵ
		(*pInFile) >> e1 >> e2 >> w;		// ���붥��Ԫ�ؼ�Ȩֵ
		if ((v1 = LocateVex(e1)) == -1) throw Error("�߶���Ԫ�ش�!");// �׳��쳣
		if ((v2 = LocateVex(e2)) == -1) throw Error("�߶���Ԫ�ش�!");// �׳��쳣
		pNet->InsertEdge(v1, v2, w);		// �����
		ch = GetChar(*pInFile);				// �����ַ�
	}

	dist = new double *[pNet->GetVexNum()], path = new int *[pNet->GetVexNum()];
		// ����洢�ռ�
	for (i = 0; i < pNet->GetVexNum(); i++)
	{	// �Զ�ά�����ÿһ�з���洢�ռ�
		dist[i] = new double[pNet->GetVexNum()]; path[i] = new int[pNet->GetVexNum()]; 
	}
	ShortestPathFloyd();					// ��Floyd�㷨��������net�и��Զ���u��v֮������·��
}

void ParkDragoman::Run()
// �������: ��԰����
{
	LinkStack<int> s;						// �洢·�ϵĶ���
	String e1, e2, e;						// ����Ԫ��
	int v1, v2, v;							// �����
	int *tourismPath = new int[pNet->GetVexNum()];	 // ������·
	int pathVertexNum;						// ·����ǰ������
	int from = LocateVex("���");			// ��ڶ����
	int to = LocateVex("����");				// ���ڶ����
	char select;							// ��ʱ����

	do 
	{
		cout << "1.���·��" << endl;
		cout << "2.������·" << endl;
		cout << "3.�˳�" << endl;
		cin >> select;						// ����ѡ��
		while (cin.get() != '\n');			// �������к�����ַ�(Ҳ���ǻ���)

		switch (select)
		{
		case '1':
			cout << "���:";
			cin >> e1;						// ��� 
			cout << "�յ�:";
			cin >> e2;						// �յ� 
			if ((v1 = LocateVex(e1)) == -1)  throw Error("����Ԫ�ش�!");// �׳��쳣
			if ((v2 = LocateVex(e2)) == -1)  throw Error("����Ԫ�ش�!");// �׳��쳣
			cout << "���·������Ϊ:" << dist[v1][v2] << endl;	// ���·������
			cout << "���·��:";
			s.Clear();						// ���s
			v = v2;							// ·���ϵ�ǰ����
			while (v != v1)
			{	// ���յ���ݵ����
				s.Push(v);					// vΪ·���ϵĶ���
				v = path[v1][v];			// ȡ��·���ϵ�ǰһ������
			}

			s.Push(v1);						// v��·������ʼ��
			while (!s.Empty())
			{	// ���·�ϵĶ���
				s.Pop(v);					// ·���϶����ջ
				pNet->GetElem(v, e);		// ȡ������Ԫ��
				cout << e << " ";			// �������Ԫ��
			}
			cout << endl << endl;			// ����
			break;
		case '2':
			pathVertexNum = 0;				// ·����ǰ������
			tourismPath[pathVertexNum++] = from;//·�����
			v = from;						// fromΪ·���ϵ�ǰ����
			cout << "������·������:" << endl;
			CreateTourismPath(to, v, tourismPath, pathVertexNum);	// ���ɲ����������·
			break;
		}
	} while (select != '3');
	delete []tourismPath;					// �ͷŴ洢�ռ�
}

ParkDragoman::~ParkDragoman()
// �������: �ͷŴ洢�ռ� 
{

	if (pNet != NULL) delete pNet;			// �ͷ�pNet
	for (int i = 0; i < pNet->GetVexNum(); i++)
	{	// �ͷŶ�ά����ĵ�j��
		if (dist != NULL && dist[i] != NULL) delete []dist[i]; 
		if (path != NULL && path[i] != NULL) delete []path[i]; 
	}
	if (dist != NULL) delete []dist;		// �ͷ�dist
	if (path != NULL) delete []path;		// �ͷ�path
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
		&& ch != '\t' && ch != ' ')			// chҲ��Ϊ�Ʊ����ո�	
	{	// ��������ַ�׷�ӵ����Ա���
		temp.Insert(++size, ch);
	}
	String answer(temp);					// ���촮
	inStr = answer;							// ��inStr���ش�
	return inStream;						// ��������������
}

#endif
