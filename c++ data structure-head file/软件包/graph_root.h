// �ļ�·����: graph_root\graph_root.h
#ifndef __GRPH_ROOT_H__
#define __GRPH_ROOT_H__

#include "adj_matrix_dir_graph.h"				// ����ͼ���ڽӾ�����

template <class ElemType>
void GraphRoot(const AdjMatrixDirGraph<ElemType> &g)
// �������: �ж�����ͼg�Ƿ��и������У�����ʾ���и�����ֵ
{
	bool exitRoot = false;						// �Ƿ������

	for (int v = 0; v < g.GetVexNum(); v++)
	{	// �����ж�ÿ�������Ƿ�Ϊ��
		for(int u = 0; u < g.GetVexNum(); u++)
		{	// ���÷��ʱ�־
			g.SetTag(u, UNVISITED);
		}
		int count = 0;							// �ѷ��ʶ�����
		DFS(g, v, count);						// ��DFS�㷨��v����������
		if (count == g.GetVexNum())
		{	//count == g.GetVexNum()��ʾvΪ������
			if (!exitRoot)
			{	// ��ʾ�洢������
				exitRoot = true;				// ��ʾ���ڸ�����
				cout << "���ڸ�����:";
			}
			cout << v << "  ";					// ��ʾ������
		}
	}
	cout << endl;								// ����
	
	if (!exitRoot)
	{	// ��ʾ�����ڸ�����
		cout << "���ڸ�����." << endl;
	}
}

template <class ElemType>
void DFS(const AdjMatrixDirGraph<ElemType> &g, int v, int &count)
// �������: �ӵ�v����������ݹ�������������ͼG
{
	g.SetTag(v, VISITED);						// �����ʱ�־
	count++;									// ���ѷ��ʶ�����м���
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
	{	// ��v����δ���ʹ����ڽӶ���w�ݹ����DFS
		if (g.GetTag(w) == UNVISITED)
		{	// ��w��ʼ���������������
			#ifdef _MSC_VER
				DFS<ElemType>(g, w , count);	// VC��<ElemType>ȷ������ģ�����
			#else
				DFS(g, w , count);
			#endif
		}
	}
}

#endif

