#ifndef __KRUSKAL_H__
#define __KRUSKAL_H__
#include "adj_list_undir_network.h"		// �ڽӱ�������

// Kruskalɭ����
class KruskalForest
{
private:
	int *treeNo;		// �������ڵ������
	int vexNum;			// ������
public:
	KruskalForest(int num = DEFAULT_SIZE);	// ���캯��
	~KruskalForest(){ delete []treeNo; };	// ��������
	bool IsSameTree(int v1, int v2);		// �ж�v1��v2�Ƿ���ͬһ������
	void Union(int v1, int v2);				// ��v2�����������ж���ϲ���v1��������
};

// Kruskalɭ����ʵ��
KruskalForest::KruskalForest(int num)
// ������������춥����Ϊnum��Kruskalɭ��
{
	vexNum = num;					// ������
	treeNo = new int[vexNum];		// ����洢�ռ�
	for (int v = 0; v < vexNum; v++)
	{	// ��ʼʱ,ÿ����ֻ��һ������,���ĸ����붥�������ͬ
		treeNo[v] = v;
	}
}

bool KruskalForest::IsSameTree(int v1, int v2)
// ������������v1��v2��ͬһ������,�򷵻�true,���򷵻�false
{
	return treeNo[v1] == treeNo[v2]; 
}

void KruskalForest::Union(int v1, int v2)
// �����������v2�����������ж���ϲ���v1��������
{
	int v1TNo = treeNo[v1], v2TNo = treeNo[v2]; 
	for (int v = 0; v < vexNum; v++)
	{	// ����v2�������Ķ���
		if (treeNo[v] == v2TNo)
		{	// // ��v2�������ϵĶ�����������Ÿ�Ϊv1�������ı��
			treeNo[v] = v1TNo; 
		}
	}
}

// Kruskal����
template <class WeightType>
class KruskalEdge
{
public:
	int vertex1, vertex2;			// �ߵĶ���
	WeightType weight;				// �ߵ�Ȩֵ
	KruskalEdge(int v1 = -1, int v2 = -1, int w = 0);	// ���캯��
};

template <class WeightType>
KruskalEdge<WeightType>::KruskalEdge(int v1, int v2, int w)
// �������: �ɶ���v1��v2��Ȩw����ߡ������캯��
{	// ���캯��
	vertex1 = v1;					// ����vertex1
	vertex2 = v2;					// ����vertex2
	weight = w;						// Ȩweight
}

template <class WeightType>
void Sort(KruskalEdge<WeightType> *a, int n)
// �����������Ȩֵ�Ա߽�����������
{
	for (int i = n - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (a[j].weight > a[j + 1].weight)
			{	// ��������,�򽻻�a[j]��a[j + 1] 
				KruskalEdge<WeightType> tmpEdge;	// ��ʱ��
				tmpEdge = a[j]; 
				a[j] = a[j + 1];
				a[j + 1] = tmpEdge;
			}
}

template <class ElemType, class WeightType>
void MiniSpanTreeKruskal(const AdjListUndirNetwork<ElemType, WeightType> &net)
// ��ʼ������������net
// �����������Kruskal�㷨������net����С����������
{
	int count;						// ������
	KruskalForest kForest(net.GetVexNum());	// ����Kruskalɭ��
	KruskalEdge<WeightType> *kEdge;
	kEdge = new KruskalEdge<WeightType>[net.GetEdgeNum()];	// ���������,ֻ�洢v > u�ı�(v,u)

	count = 0;						// ��ʾ��ǰ�Ѵ���kEdge�ı���
	for (int v = 0; v < net.GetVexNum(); v++)
	{
		for (int u = net.FirstAdjVex(v); u >= 0; u = net.NextAdjVex(v, u))
		{	// ����(v, u)����kEdge��
			if (v > u)
			{	// ֻ�洢v > u�ı�(v,u)
				KruskalEdge<WeightType> tmpKEdge(v, u, net.GetWeight(v, u));
				kEdge[count++] = tmpKEdge;
			}
		}
	}

	Sort(kEdge, count);				// �Ա߰�Ȩֵ��������

	for (int i = 0; i < count; i++)
	{	// ��kEdgePtr�еı߽�������
		int v1 = kEdge[i].vertex1, v2 = kEdge[i].vertex2;
		if (!kForest.IsSameTree(v1, v2))
		{	// �ߵ����˲���ͬһ������,��Ϊ��С�����������ϵı�
			cout << "edge:(" << v1 << "," << v2 << ") weight:" 
				<<net.GetWeight(v1, v2)<< endl ; // ����߼�Ȩֵ
			kForest.Union(v1, v2);		// ��v2�����������ж���ϲ���v1��������
		}
	}
	delete []kEdge;					// �ͷŴ洢�ռ�
}

#endif

