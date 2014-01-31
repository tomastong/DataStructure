#ifndef __DFS_H__
#define __DFS_H__

#include "adj_matrix_dir_graph.h"	// �ڽӾ�������ͼ

template <class ElemType>
void DFSTraverse(const AdjMatrixDirGraph<ElemType> &g, void (*Visit)(const ElemType &))
// ��ʼ����������ͼg
// �����������ͼg����������ȱ���
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
	{	// ��ÿ�����������ʱ�־
		g.SetTag(v, UNVISITED);
	}

	for (v = 0; v < g.GetVexNum(); v++)
	{	// ����δ���ʵĶ��㰴DFS���������������
		if (g.GetTag(v) == UNVISITED)
		{	// ��v��ʼ���������������   
			#ifdef _MSC_VER
				DFS<ElemType>(g, v , Visit);	// VC��<ElemType>ȷ������ģ�����
			#else
				DFS(g, v , Visit);
			#endif
		}
	}
}

template <class ElemType>
void DFS(const AdjMatrixDirGraph<ElemType> &g, int v, void (*Visit)(const ElemType &))
// ��ʼ����������ͼg
// ����������Ӷ���v�������������������ͼg
{	
	g.SetTag(v, VISITED);			// �����ʱ�־
	ElemType e;						// ��ʱ����
	g.GetElem(v, e);				// ����v������Ԫ��
	Visit(e);						// ���ʶ���v������Ԫ��
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
	{	// ��v����δ���ʹ����ڽӶ���w�ݹ����DFS
		if (g.GetTag(w) == UNVISITED)
		{	// ��w��ʼ���������������
			#ifdef _MSC_VER
				DFS<ElemType>(g, w , Visit);	// VC��<ElemType>ȷ������ģ�����
			#else
				DFS(g, w , Visit);
			#endif
		}
	}
}

#endif
