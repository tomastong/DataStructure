#ifndef __SHORTEST_PATH_DIJ_H__
#define __SHORTEST_PATH_DIJ_H__

#include "adj_matrix_dir_network.h"			// �ڽӾ���������

template <class ElemType, class WeightType>
void ShortestPathDIJ(const AdjMatrixDirNetwork<ElemType, WeightType> &net, int v0, 
	int *path, WeightType *dist)
// �������: ��Dijkstra�㷨��������net�Ӷ���v0�����ඥ��v�����·��path��·������dist[v],
//	path[v]�洢���·�������˶����ǰһ����Ķ����
{
	for (int v = 0; v < net.GetVexNum(); v++)
	{	// ��ʼ��path��dist�������־
		dist[v] = (v0 != v && net.GetWeight(v0, v) == 0 ) ? net.GetInfinity() : net.GetWeight(v0, v);
		if (v0 != v && dist[v] < net.GetInfinity()) path[v] = v0;
		else path[v] = -1;		// ·����������ʼ��
		net.SetTag(v, UNVISITED);	// �ö����־
	}
	net.SetTag(v0, VISITED);		// U={v0}

	for (int u = 1; u < net.GetVexNum(); u++)
	{	// ��v0�������net.GetVexNum() - 1������
		WeightType minVal = net.GetInfinity(); int v1 = v0;
		for (int w = 0; w < net.GetVexNum(); w++)
		{	// disk[v1] = min{dist[w] | w ��V - U
			if (net.GetTag(w) == UNVISITED && dist[w] < minVal)
			{	// net.GetTag(w) == UNVISITED��ʾw��V - U
				v1 = w;
				minVal = dist[w];
			}
		}
		net.SetTag(v1, VISITED);		// ��v1����U

		for (int v2 = net.FirstAdjVex(v1); v2 != -1; v2 = net.NextAdjVex(v1, v2))
		{	// ���µ�ǰ���·��������
			if (net.GetTag(v2) == UNVISITED && minVal + net.GetWeight(v1, v2) < dist[v2])
			{	// ��v2��V - U��minVal + net.GetWeight(v1, v2) < dist[v2],���޸�dist[v2]
				// ��path[v2]
				dist[v2] = minVal + net.GetWeight(v1, v2);
				path[v2] = v1;
			}
		}
	}
}

#endif

