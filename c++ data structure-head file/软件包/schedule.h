// �ļ�·����:my_huffman_tree\my_huffman_tree.h
#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include "adj_list_dir_graph.h"		// ����ͼ��
#include "lk_queue.h"				// ��������
#include "string.h"					// ����

// �γ̽ṹ
struct CourseType 
{
	char courseNo[5];				// �γ̱��
	char courseName[100];			// �γ���
    int period;						// ѧʱ��
    int term;						// ����ѧ��
};	

// �γ̱���
template<int termsNum>				// termsNum��ʾҪ�ſε�ѧ����
class Schedule
{
private:
// �γ̱�������ݳ�Ա:
	AdjListDirGraph<CourseType> *pGraph;	// �ɿγ���Ϣ��������ͼ 
	int *indegree;							// �������
	ifstream *pInFile;						// ������ 
    ofstream *pOutFile;						// �����
	LinkQueue<int> q[termsNum + 1];			// ���Ϊ0�Ľ��Ļ������
	char courseTable[termsNum + 1][11][6][100];
		// �α�,�±�ֱ��ʾ��ѧ�ڡ��ڴΡ����ڡ��γ���
    int coursesNumOfPerTerm[termsNum + 1];	// ÿѧ�ڵĿγ���

// ��������:
	int LocateVex(char courseNo[]);			// ���ر��ΪcourseNo�Ŀγ���ͼ��λ��
	void Readln();							// ����һ��  
	void Range(int num, int term, char courseName[]);			// �ſ�
	bool RangeOne(int &weekDay, int term, char courseName[]);	// ��һ���1�ڿ�
	bool RangeTwo(int &weekDay, int term, char courseName[]);	// ��һ���2�ڿ�
	bool RangeThree(int &weekDay, int term, char courseName[]);	// ��һ���3�ڿ�
	int FindOne(int weekDay, int term);		// ����һ��1�ڿտ�
	int FindTwo(int weekDay, int term);		// ����һ������2�ڿտ�
	int FindThree(int weekDay, int term);	// ����һ������3�ڿտ�
	void Write(char s[], int l);			// ���ָ�����ȵ��ַ��� 
	char *DecimalToChineseChar(int n, char *s);		// �����ı�ʾʮ������

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	Schedule(ifstream *pIFile, ofstream *pOFile);	// ���캯��
	virtual ~Schedule();			// ��������
	void Read();					// ���������������й���Ϣ���Խ���һ������ͼ
	void TopologicalOrder();		// ����������ʽ�����ſ�
	void Write();					// ����α���Ϣ 
};

// �γ̱����ʵ�ֲ���
template<int termsNum> 
int Schedule<termsNum>::LocateVex(char courseNo[])
// ������������ر��ΪcourseNo�Ŀγ���ͼ��λ��
{
	for (int v = 0; v < pGraph->GetVexNum(); v++)
	{	// ���β��ҿγ�
		CourseType course;			// ��ʱ����
		pGraph->GetElem(v, course);	// ���ض���(�γ�)��Ϣ
		if (strcmp(course.courseNo, courseNo) == 0)
		{	// ���ҳɹ�
			return v;						// �Ǹ���ʾ���ҳɹ�
		}
	}
	
	return -1;								// -1��ʾ����ʧ��
}

template<int termsNum> 
void Schedule<termsNum>::Readln()
// �������������һ��
{	
	char ch;								// �ַ�
	while ((ch = (*pInFile).peek()) != EOF	// ��Ϊ�ļ�������
		&& (ch = (*pInFile).get()) != '\n');// ��Ϊ���з�
}

template<int termsNum> 
Schedule<termsNum>::Schedule(ifstream *pIFile, ofstream *pOFile)
// �������: ��ʼ�������ļ�������ļ�,�ſο�ʼ�����ڼ�, ��տα�
{
	pInFile = pIFile;						// �����ļ�
	pOutFile = pOFile;						// ����ļ�
	pGraph = NULL;							// ��ʼ��pGraphΪ��
	indegree = NULL;							// ��ʼ��indegreeΪ��

	for (int i = 1; i <= termsNum; i++)
	{	// ѧ����
		for (int j = 1; j <= 10; j++)
		{	// �ڴ�
			for (int k = 1; k <= 5; k++)
			{	// ����   
				strcpy(courseTable[i][j][k], "");	// ��տα�
			}
		}
	}
}

template<int termsNum> 
Schedule<termsNum>::~Schedule()
// �������: �ͷŴ洢�ռ�
{
	if (pGraph != NULL) delete pGraph;		// �ͷ�pGraph
	if (indegree != NULL) delete []indegree;// �ͷ�indegree
}

template<int termsNum> 
void Schedule<termsNum>::Range(int num, int term, char courseName[])
// �������: �ſ�, numΪҪ�ſεĽ���, termΪѧ��, courseNameΪ�γ���
{
	static int weekDay=1;					// Ҫ�ſε�����
	int i;									// ��ʱ����
	if (num == 1)
	{	// ��1�ڿν����ſ�
		if (!RangeOne(weekDay, term, courseName))
		{	// �ſ�ʧ��
			throw Error("�ſ�ʧ��!");		// �׳��쳣
		}
	}
	else if (num % 3 == 0)
	{	// �ſν���Ϊ3��λ��
		for ( i =0; i < num / 3; i++)
		{
			if (!RangeThree(weekDay, term, courseName))
			{	// �ſ�ʧ��
				throw Error("�ſ�ʧ��!");	// �׳��쳣
			}
		}
	}
	else if (num % 3 == 1)
	{	// �ſν�����3����1
		for (i = 0; i < num / 3 - 1; i++)
		{
			if (!RangeThree(weekDay, term, courseName))
			{	// �ſ�ʧ��
				throw Error("�ſ�ʧ��!");	// �׳��쳣
			}
		}
		for (i = 0; i < 2; i++)
		{
			if (!RangeTwo(weekDay, term, courseName))
			{	// �ſ�ʧ��
				throw Error("�ſ�ʧ��!");	// �׳��쳣
			}
		}
	}
	else
	{	// �ſν�����3����2
		for (i = 0; i < num / 3; i++)
		{
			if (!RangeThree(weekDay, term, courseName))
			{	// �ſ�ʧ��
				throw Error("�ſ�ʧ��!");	// �׳��쳣;
			}
		}
		if (!RangeTwo(weekDay, term, courseName))
		{	// �ſ�ʧ��
			throw Error("�ſ�ʧ��!");		// �׳��쳣
		}
	}
}

template<int termsNum> 
bool Schedule<termsNum>::RangeOne(int &weekDay, int term, char courseName[])
// �����������һ���1�ڿ�
{	
	for(int k = 1; k <= 5; k++)
	{	// ��һ�����ڵ�5�������ս����ſ�
		int i = FindOne(weekDay,term);			// ����һ��1�ڿտ�
		if (i == -1)
		{	// ����ʧ��
			weekDay = (weekDay +2 > 5) ? (weekDay + 2 - 5) : (weekDay + 2);	
				// ��һ��Ҫ�ſε�����
		}
		else
		{	// ���ҳɹ�
			strcpy(courseTable[term][i][weekDay], courseName);	
				// ��ʾ���γ�courseName���ڵ�i�ڿ�
			return true;						// �ſγɹ�
		}
	}
	return false;								// �ſ�ʧ��
}


template<int termsNum> 
bool Schedule<termsNum>::RangeTwo(int &weekDay, int term, char courseName[])
// �����������һ���2�ڿ�
{
	for (int k = 1; k <= 5; k++)
	{	// ��һ�����ڵ�5�������ս����ſ�
		int i = FindTwo(weekDay, term);			// ��������2�ڿοտ�
		if (i != -1)
		{	// ���ҳɹ�
			weekDay = (weekDay +2 > 5) ? (weekDay + 2 - 5) : (weekDay + 2);	
				// ��һ��Ҫ�ſε�����
			strcpy(courseTable[term][i][weekDay], courseName);
				// ��ʾ���γ�courseName���ڵ�i�ڿ�
			strcpy(courseTable[term][i + 1][weekDay], courseName);
				// ��ʾ���γ�courseName���ڵ�i+1�ڿ�
			return true;						// �ſγɹ�
		}
	}
	
	// ��2�������ϵĿηֽ�Ϊ���������ϵ�1�ڿ�
	if (!RangeOne(weekDay, term, courseName)) return false;
	if (!RangeOne(weekDay, term, courseName)) return false;
	return true;								// �ſγɹ�
}

template<int termsNum> 
bool Schedule<termsNum>::RangeThree(int &weekDay, int term, char courseName[])
// �����������һ���3�ڿ�
{
	for (int k = 0; k <= 5; k++)
	{	// ��һ�����ڵ�5�������ս����ſ�
		int i = FindThree(weekDay, term);	// ��������2�ڿοտ�
		if (i != -1)
		{	// ���ҳɹ�
			weekDay = (weekDay +2 > 5) ? (weekDay + 2 - 5) : (weekDay + 2);	
				// ��һ��Ҫ�ſε�����
			strcpy(courseTable[term][i][weekDay], courseName);
				// ��ʾ���γ�courseName���ڵ�i�ڿ�
			strcpy(courseTable[term][i + 1][weekDay], courseName);
				// ��ʾ���γ�courseName���ڵ�i+1�ڿ�
			strcpy(courseTable[term][i + 2][weekDay], courseName);
				// ��ʾ���γ�courseName���ڵ�i+2�ڿ�
			return true;					// �ſγɹ�
		}
	}
	// ��3�������ϵĿηֽ�Ϊ2�������ϵĿ��뵥���ϵ�1�ڿ�
	if (!RangeTwo(weekDay,term,courseName)) return false;
	if (!RangeOne(weekDay,term,courseName)) return false;
	return true;							// �ſγɹ�
}

template<int termsNum> 
int Schedule<termsNum>::FindOne(int weekDay, int term)
// �������������һ��1�ڿտ�,�����пյĽڴΣ�����-1��ʾ��������
{
	for(int i = 1; i <= 8; i++)
	{	// ��ʾ��termѧ��,����weekDay�ĵ�i�ڿ�
		if (strlen(courseTable[term][i][weekDay]) == 0)
		{	// ��ʾ��termѧ��,����weekDay�ĵ�i�ڿ�δ��
			return i;						// ����i
		}
	}
	return -1;								// ��ʾ��������	
}

template<int termsNum> 
int Schedule<termsNum>::FindTwo(int weekDay,int term)
// �������������һ������2�ڿտ�,��������2�ڿ��пյĵ�1�ڿεĽڴΣ�����-1��ʾʧ��
{
	if (strlen(courseTable[term][1][weekDay]) ==0 && strlen(courseTable[term][2][weekDay]) ==0 )
	{	// ����1����Ƿ��п�
		return 1;							// ��1����Ƿ��п�
	}
	if (strlen(courseTable[term][3][weekDay]) == 0 && strlen(courseTable[term][4][weekDay]) == 0)
	{	// ����2����Ƿ��п�	
		return 3;							// ��2����Ƿ��п�
	}
	if (strlen(courseTable[term][6][weekDay]) == 0 && strlen(courseTable[term][7][weekDay]) == 0)
	{	// ����3����Ƿ��п�
		return 6;							// ���3����Ƿ��п�
	}
	if (strlen(courseTable[term][8][weekDay]) == 0 && strlen(courseTable[term][9][weekDay]) == 0)
	{	// ����4����Ƿ��п�
		return 8;							// ��4����Ƿ��п�
	}
	return -1;								// ��ʾʧ��
}


template<int termsNum> 
int Schedule<termsNum>::FindThree(int weekDay,int term)
// �������������һ������3�ڿտ�,��������3�ڿ��пյĵ�1�ڿεĽڴΣ�����-1��ʾʧ��
{
	if (strlen(courseTable[term][3][weekDay]) == 0 && strlen(courseTable[term][4][weekDay]) == 0 && strlen(courseTable[term][5][weekDay]) == 0)
	{	// ����2����Ƿ��п�
		return 3;							// ��2����Ƿ��п�
	}
	if (strlen(courseTable[term][8][weekDay]) == 0 && strlen(courseTable[term][9][weekDay]) == 0 && strlen(courseTable[term][10][weekDay]) == 0)
	{	// ����3����Ƿ��п�
		return 8;							// ��3����Ƿ��п�
	}
	return -1;								// ��ʾʧ��
}


template<int termsNum> 
void Schedule<termsNum>::Write(char s[], int l)
// ������������ָ�����ȵ��ַ���(����s����С�ڵ���l)
{
	(*pOutFile) << s;						// ���s
	for(unsigned int i = 0; i < l - strlen(s); i++) (*pOutFile) << " ";
		// ����ո�, ʹ��������Ϊl
}

template<int termsNum> 
char *Schedule<termsNum>::DecimalToChineseChar(int n, char *s)
// ��������������ı�ʾʮ������ 
{	
	char digital[11][3] = {"��", "һ", "��", "��", "��", "��", "��", "��", 
		"��", "��", "ʮ"};					// ���ı�ʾ��ʮ��������

	strcpy(s, "");							// ��s��Ϊ�մ�= '\0'
	if (n < 0)
	{	// nΪ��
		strcat(s, "��");					// �Դ�s��"��"��ʼ
		n = -n;								// ȥ��n�ĸ���
	}
	n = n % 100;							// ����n�����һ����λ��
	if (n / 10 > 1)
	{	// ʮλ������1
		strcat(s, digital[n / 10]);			// ��ʮλ�������ı�ʾ����s�ĺ���
		strcat(s, digital[10]);				// ��s�����"ʮ"
		if (n %10 >0)
		{	// ��λ����0
			strcat(s, digital[n % 10]);		// ����λ�������ı�ʾ����s�ĺ���
		}
	}
	else if (n /10 == 1)
	{	// ʮλ��Ϊ1
		strcat(s, digital[10]);				// ��s�����"ʮ"
		if (n %10 >0)
		{	// ��λ����0
			strcat(s, digital[n % 10]);		// ����λ�������ı�ʾ����s�ĺ���
		}
	}
	else
	{	// ʮλ��Ϊ0
		strcpy(s, digital[n % 10]);			// ����λ�������ı�ʾ����s�ĺ���
	}

	return s;
}

template<int termsNum> 
void Schedule<termsNum>::Read()
// ������������������������й���Ϣ���Խ���һ������ͼ
{ 
	char ch;									// �ַ�
	int i, n, v, u;								// ��ʱ����
	int courseTotalNum = 0;						// �γ�����
	CourseType course;							// �γ���Ϣ
	char prioCourseNo[5];						// �Ⱦ��γ̺�

	//����Ϊ���������������ѧ�������Ŀγ���
	(*pInFile).seekg(0);						// ��λ���ļ���ʼ��
	ch = GetChar(*pInFile);						// ���ַ�
	while (ch < '0' || ch > '9')
	{	// �������ֿ�ʼ����
		if (ch != '\n') Readln();				// ����
		ch = GetChar(*pInFile);					// �����ַ�
	}
	(*pInFile).putback(ch);						// ��ch����������
	for (i = 1; i <= termsNum; i++)
	{	// ����ÿѧ��������Ŀγ���
		(*pInFile) >> n;						// �γ���
		coursesNumOfPerTerm[i] = n;				// ��iѧ��������Ŀγ���
		courseTotalNum += n;				 	// �ۼ����ܿγ���
	}

	CourseType *vex = new CourseType[courseTotalNum];		// ͼ�Ķ�����Ϣ
	indegree = new int[courseTotalNum];						// ͼ�Ķ������
	for (i = 0; i < courseTotalNum; i++) indegree[i] = 0;	// ��ʼ���������
	
	// ����Ϊ����������������γ���Ϣ(����ͼ�Ķ�����Ϣ)
	(*pInFile).seekg(0);						// ��λ���ļ���ʼ��
	ch = GetChar(*pInFile);						// ���ַ�
	int count = 0;								// ������
	while (ch != EOF)
	{	// �ļ�������
		while (ch != EOF && ch != 'c')
		{	// ������'c'��ʼ����
			if(ch != '\n') Readln();			// ��������'c'��ʼ����
			ch = GetChar(*pInFile);				// ���ַ�
		}
		if (ch != EOF)
		{	// ������'c'��ʼ����
			(*pInFile).putback(ch);				// ��ch���ͻ�������
			(*pInFile) >> course.courseNo;		// ����γ̺�
			(*pInFile) >> course.courseName;	// ��������
			(*pInFile) >> course.period;		// ����ѧʱ��
			(*pInFile) >> course.term;			// ����ѧ��

			vex[count++] = course;					// ���γ���Ϣ����vex
			Readln();							// ����
		}
		ch = GetChar(*pInFile);					// �����ַ�
	}
	if (count != courseTotalNum) throw Error("�γ��������õĿγ���������!");	// �׳��쳣
	pGraph = new AdjListDirGraph<CourseType>(vex, courseTotalNum);	// ����ͼpGraph

	// ����Ϊ����������������γ����޿γ���Ϣ(����ͼ�ı���Ϣ)
	(*pInFile).seekg(0);
	ch = GetChar(*pInFile);
	while (ch != EOF)
	{	// �ļ�������
		while (ch != EOF && ch != 'c')
		{	//������'c'��ʼ����
			if (ch != '\n') Readln();			// ����
			ch = GetChar(*pInFile);				// �����ַ�
		}
		if (ch != EOF)
		{	// ������'c'��ʼ����
			(*pInFile).putback(ch);				// ��ch���ͻ�������
			(*pInFile) >> course.courseNo;		// ����γ̺�
			(*pInFile) >> course.courseName;	// ��������
			(*pInFile) >> course.period;		// ����ѧʱ��
			(*pInFile) >> course.term;			// ����ѧ��	
			v = LocateVex(course.courseNo);		// ���Ҷ����λ��
			if (v == -1) throw Error("�Ƿ�����!");	// �׳��쳣
  
			ch = GetChar(*pInFile);				// �����ַ�
			while (ch == 'c')
			{	// ���޿κ�
				(*pInFile).putback(ch);			// ��ch���ͻ�������
				(*pInFile) >> prioCourseNo;		// ����γ̺�
				u = LocateVex(prioCourseNo);	// ���Ҷ����λ��
				if (u == -1)  throw Error("�Ƿ����޿κ�!");	// �׳��쳣
				pGraph->InsertEdge(u, v);		// �����<u,v>
				indegree[v]++;					// ����v��ȼ�1  
				ch = GetChar(*pInFile);
			}
		}
		if (ch != '\n') Readln();				// ������ǰ��
		ch = GetChar(*pInFile);					// �����ַ�
	}
}

template<int termsNum> 
void Schedule<termsNum>::TopologicalOrder()
// �������������������ʽ�����ſ�
{
	CourseType courseV, courseW;				// ������Ӧ�γ���Ϣ
	int i, size0, sizeTerm, term, v, w;			// ��ʱ����		
	for (v = 0; v < pGraph->GetVexNum(); v++)
	{	// �������Ϊ0����Ķ���q[0..termsNum]	
		if (indegree[v] == 0)   
		{	// ���Ϊ0�߽�����Ӧѧ�ڵĶ���
			pGraph->GetElem(v, courseV);		// ȡ������v��������Ϣ
			q[courseV.term].InQueue(v);
		}
	}

	//���ɿα�
	for (term = 1; term <= termsNum; term++)
	{	// ��termѧ��
		size0 = q[0].Length();					// ���ر�Ҫ������ѧ�ڿ��εĿγ�
		sizeTerm = q[term].Length();			// Ҫ���ڵ�termѧ�ڿ��εĿγ�
		

		if (size0 + sizeTerm < coursesNumOfPerTerm[term] || sizeTerm > coursesNumOfPerTerm[term])
		{	// ��ʾ�ſ�ʱ���ֳ�ͻ
		cout << "term:" << term << endl;
		cout << "size0:" << size0 << endl;
		cout << "sizeTerm:" << sizeTerm << endl;
		cout << "coursesNumOfPerTerm[term]:" << coursesNumOfPerTerm[term] << endl << endl;

		throw Error("�ſ�ʱ���ֳ�ͻ!");			// �׳��쳣
		}
		for (i = 1; i <= sizeTerm; i++)
		{	// ��Ҫ���termѧ�ڿ��Ŀγ�
			q[term].OutQueue(v);				// ����
			pGraph->GetElem(v, courseV);		// ȡ������v��������Ϣ
			Range(courseV.period, term, courseV.courseName);	// �ſ�
			for (w = pGraph->FirstAdjVex(v); w != -1; w = pGraph->NextAdjVex(v, w))
			{	// wΪv���ڽӵ�
				indegree[w]--;					// w������Լ�1
				pGraph->GetElem(w, courseW);	// ȡ������w��������Ϣ
				if (indegree[w] == 0 && (courseW.term == 0 || courseW.term > term))
				{	// ����w���Ϊ0 
					q[courseW.term].InQueue(w);	// w����Ӧ����
				}
				else if (indegree[w] == 0 && (courseW.term > 0 && courseW.term <= term))
				{	// ��ʾ�ſ�ʱ���ֳ�ͻ
					throw Error("�ſ�ʱ���ֳ�ͻ!");		// �׳��쳣
				}
			}
		}
		for (i = 1; i <= coursesNumOfPerTerm[term] - sizeTerm; i++)
		{	// �����ر�Ҫ������ѧ�ڿ��εĿγ�
			q[0].OutQueue(v);					// ����
			pGraph->GetElem(v, courseV);		// ȡ������v��������Ϣ
			Range(courseV.period,term,courseV.courseName);
			for (w = pGraph->FirstAdjVex(v); w != -1; w = pGraph->NextAdjVex(v, w))
			{	// wΪv���ڽӵ�
				indegree[w]--;					// w������Լ�1
				pGraph->GetElem(w, courseW);	// ȡ������w��������Ϣ
				if (indegree[w] == 0 && (courseW.term == 0 || courseW.term > term))
				{	// ����w���Ϊ0 
					q[courseW.term].InQueue(w);	// w����Ӧ����
				}
				else if (indegree[w] == 0 && (courseW.term > 0 && courseW.term <= term))
				{	// ��ʾ�ſ�ʱ���ֳ�ͻ
					throw Error("�ſ�ʱ���ֳ�ͻ!");		// �׳��쳣
				}
			}
		}
	}
}

template<int termsNum> 
void Schedule<termsNum>::Write()
// �������������α���Ϣ
{
	int term, i, weekDay;					// ��ʱ����
	char s[20], strTem[20];					// ��ʱ����
	for (term = 1; term <= termsNum; term++)
	{	// �����termѧ�ڿγ̱�
		(*pOutFile) << "��" << DecimalToChineseChar(term, strTem) << "ѧ�ڿα�" << endl;	// �����ͷ
		(*pOutFile) << endl;				// ����
		
		//��ʾ����
		Write("�ڴ�", 8);
		for (i = 1; i <= 5; i++)
		{	// ����1~����5
			DecimalToChineseChar(i, strTem);				// �����ֱ�Ϊ����
			Write(strcat(strcpy(s, "����"), strTem), 16);	// �������i
		}
		(*pOutFile) << endl << endl;		// ����
		
		// ��ʾ�γ̱�����
		for (i = 1; i <= 10; i++)
		{	// �Եڵ�1�ڵ���10�ڿ�
			DecimalToChineseChar(i, strTem);				// �����ֱ�Ϊ����
			Write(strcat(strcat(strcpy(s, "��"), strTem), "��"), 8);	// �����i��
			for (weekDay = 1; weekDay <= 5; weekDay++)
			{	// ��ʾ�γ�
				Write(courseTable[term][i][weekDay], 16);	// ��termѧ��,����weekDay,��i�ڿογ���
			}
			(*pOutFile)<<endl;				// ����

			if (i==2 || i == 7)
			{	// ��1������3��ں�Ŀμ���Ϣ
				(*pOutFile) << endl << "�μ���Ϣ" << endl << endl;
			}
			if (i == 5)
			{	// ��2��ں�������Ϣ
				(*pOutFile) << endl << endl << "�����Ϣ" << endl << endl << endl;
			}
			if (i == 10)
			{	// ��4��ں������ϰ
				(*pOutFile) << endl << "����ϰ" << endl << endl;
			}
		}

		(*pOutFile) << endl << endl << endl;
			// ���α�֮���Խ϶�������
	}
}

#endif