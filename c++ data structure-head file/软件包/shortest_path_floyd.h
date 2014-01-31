#ifndef __SHORTEST_PATH_FLOYD_H__
#define __SHORTEST_PATH_FLOYD_H__

#include "adj_list_dir_network.h"			// �ڽӱ�������

template <class ElemType, class WeightType>
void ShortestPathFloyd(const AdjListDirNetwork<ElemType, WeightType> &net, int **path, 
	WeightType **dist)
// �������: ��Floyd�㷨��������net�и��Զ���u��v֮������·��path[u][v]��·������
//	dist[u][v],path[u][v]�洢��u��v�����·�������˶����ǰһ����Ķ����,dist[u][v]
//	�洢��u��v�����·���ĳ���
{
	for (int u = 0; u < net.GetVexNum(); u++)
		for (int v = 0; v < net.GetVexNum(); v++)
		{	// ��ʼ��path��dist
			dist[u][v] = (u != v) ? net.GetWeight(u, v) : 0;
			if (u != v && dist[u][v] < net.GetInfinity()) path[u][v] = u;	// ���ڱ�<u,v>
			else path[u][v] = -1;											// �����ڱ�<u,v>
		}

	for (int k = 0; k < net.GetVexNum(); k++)
		for (int i = 0; i < net.GetVexNum(); i++)
			for (int j = 0; j < net.GetVexNum(); j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{	// ��i��k�ٵ�j��·�����ȸ���
					dist[i][j] = dist[i][k] + dist[k][j]; 
					path[i][j] = path[k][j];
				}
}

#endif

