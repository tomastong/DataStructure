#ifndef __TOPSORT_H__
#define __TOPSORT_H__

#include "lk_queue.h"
#include "adj_matrix_dir_graph.h"			// �ڽӾ�������ͼ

template <class ElemType>
void StatIndegree(const AdjMatrixDirGraph<ElemType> &g, int *indegree)
// ���������ͳ��ͼg����������
{
	for (int v = 0; v < g.GetVexNum(); v++)
	{	// ��ʼ�����Ϊ0
		indegree[v] = 0;
	}

	for (int v1 = 0; v1 < g.GetVexNum(); v1++)
	{	// ����ͼ�Ķ���
		for (int v2 = g.FirstAdjVex(v1); v2 != -1; v2 = g.NextAdjVex(v1, v2))
		{	// v2Ϊv1��һ���ڽӵ�
			indegree[v2]++;
		}
	}
}

template <class ElemType>
StatusCode TopSort(const AdjMatrixDirGraph<ElemType> &g)
// ��ʼ��������������ͼg
// �����������g�޻�·,�����g�Ķ����һ����������,������SUCCESS,���򷵻�FAIL
{
	int *indegree = new int[g.GetVexNum()];	// �����������		
	LinkQueue<int> q;					// ����
	int count = 0;
	StatIndegree(g, indegree);				// ͳ�ƶ�������

	for (int v = 0; v < g.GetVexNum(); v++)
	{	// ��������
		if (indegree[v] == 0)
		{	// �������Ϊ0�Ķ������
			q.InQueue(v);
		}
	}

	while (!q.Empty())
	{	// ���зǿ�
		int v1;
		q.OutQueue(v1);		// ȡ��һ�����Ϊ0�Ķ���
		cout << v1 << "  ";
		count++;			// �����������м���
		for (int v2 = g.FirstAdjVex(v1); v2 != -1; v2 = g.NextAdjVex(v1, v2))
		{	// v2Ϊv1��һ���ڽӵ�,��v1��ÿ���ڽӵ���ȼ�1
			if (--indegree[v2] == 0)
			{	// v2���Ϊ0,��v2���
				q.InQueue(v2);
			};
		}
	}
	delete []indegree;						// �ͷ�indegree��ռ�õĴ洢�ռ�

	if (count < g.GetVexNum()) return FAIL;	// ͼg�л�·
	else return SUCCESS;					// ��������ɹ�
}

#endif

