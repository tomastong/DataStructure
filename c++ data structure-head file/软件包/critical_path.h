#ifndef __TOPSORT_H__
#define __TOPSORT_H__

#include "lk_queue.h"						// ����
#include "lk_stack.h"						// ջ
#include "adj_matrix_dir_network.h"			// �ڽӾ���������

template <class ElemType, class WeightType>
void StatIndegree(const AdjMatrixDirNetwork<ElemType, WeightType> &net, int *indegree)
// ���������ͳ����net����������
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// ��ʼ�����Ϊ0
		indegree[v] = 0;
	}

	for (int v1 = 0; v1 < net.GetVexNum(); v1++)
	{	// �������Ķ���
		for (int v2 = net.FirstAdjVex(v1); v2 != -1; v2 = net.NextAdjVex(v1, v2))
		{	// v2Ϊv1��һ���ڽӵ�
			indegree[v2]++;
		}
	}
}

template <class ElemType, class WeightType>
StatusCode CriticalPath(const AdjMatrixDirNetwork<ElemType, WeightType> &net)
// ��ʼ����������������net
// �����������net�޻�·,�����net�Ĺؼ��,������SUCCESS,���򷵻�FAIL
{
	int *indegree = new int[net.GetVexNum()];	// �����������
	int *ve = new int[net.GetVexNum()];			// �¼����緢��ʱ������
	LinkQueue<WeightType> q;					// ���ڴ洢���Ϊ0�Ķ���
	LinkStack<WeightType> s;					// ����ʵ�����������е�ջ
	int ee, el, u, v, count = 0;

	for (v = 0; v < net.GetVexNum(); v++) 
	{	// ��ʼ���¼����緢��ʱ��
		ve[v] = 0;
	}

	StatIndegree(net, indegree);				// ͳ�ƶ�������

	for (v = 0; v < net.GetVexNum(); v++)
	{	// ��������
		if (indegree[v] == 0)
		{	// �������Ϊ0�Ķ������
			q.InQueue(v);
		}
	}

	while (!q.Empty())
	{	// ���зǿ�
		q.OutQueue(u);			// ȡ��һ�����Ϊ0�Ķ���
		s.Push(u);				// ����u��ջ,�Ա����������������
		count++;				// �Զ�����м���
		for (v = net.FirstAdjVex(u); v != -1; v = net.NextAdjVex(u, v))
		{	// v2Ϊv1��һ���ڽӵ�,��v1��ÿ���ڽӵ���ȼ�1
			if (--indegree[v] == 0)
			{	// v���Ϊ0,��v���
				q.InQueue(v);
			};
			if (ve[u] + net.GetWeight(u, v) > ve[v])
			{	// �޸�ve[v]
				ve[v] = ve[u] + net.GetWeight(u, v);
			}
		}
	}
	delete []indegree;			// �ͷ�indegree��ռ�õĴ洢�ռ�

	if (count < net.GetVexNum()) 
	{
		delete []ve;			// �ͷ�ve��ռ�õĴ洢�ռ�
		return FAIL;			// ��g�л�·
	}

	int *vl = new int[net.GetVexNum()];		// �¼���ٷ���ʱ������
	s.Top(u);								// ȡ��ջ��,ջ��Ϊ���
	for (v = 0; v < net.GetVexNum(); v++) 
	{	// ��ʼ���¼���ٷ���ʱ��
		vl[v] = ve[u];
	}

	while (!s.Empty())
	{	// s�ǿ�
		s.Pop(u);
		for (v = net.FirstAdjVex(u); v != -1; v = net.NextAdjVex(u, v))
		{	// vΪu��һ���ڽӵ�
			if (vl[v] - net.GetWeight(u, v) < vl[u])
			{	// �޸�vl[u]
				vl[u] = vl[v] - net.GetWeight(u, v);
			}
		}
	}

	for (u = 0; u < net.GetVexNum(); u++)
	{	// ��ee, el�͹ؼ�·��
		for (v = net.FirstAdjVex(u); v != -1; v = net.NextAdjVex(u, v))
		{	// vΪu��һ���ڽӵ�
			ee = ve[u]; el = vl[v] - net.GetWeight(u, v);
			if (ee == el)
			{	// <u, v>Ϊ�ؼ��
				cout << "<" << u << "," << v << "> ";
			}
		}
	}
	
	delete []ve;				// �ͷ�ve��ռ�õĴ洢�ռ�
	delete []vl;				// �ͷ�vl��ռ�õĴ洢�ռ�
	return SUCCESS;				// �����ɹ�
}

#endif

