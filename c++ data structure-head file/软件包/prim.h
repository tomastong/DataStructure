#ifndef __PRIM_H__
#define __PRIM_H__

template <class ElemType, class WeightType>
int MinVertex(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int *adjVex)	
// �������������w��ʹ�ñ�<w, adjVex[w]>Ϊ����V-U��U�ľ�����СȨֵ�ı�
{
	int w = -1;				// ��ʼ����С����
	int v;					// ��ʱ����
	for (v = 0; v < net.GetVexNum(); v++)	
	{	// ���ҵ�һ������������V - U�ж���v
		if (net.GetTag(v) == UNVISITED				// ��ʾvΪV - U�еĶ���
			&& net.GetWeight(v, adjVex[v]) > 0)		// ���ڴ�v��U�ı�(v, adjVex[v])
		{	 
			w = v;
			break;
		}
	}
    for (v++; v < net.GetVexNum(); v++)	// ��������V-U��U�ľ�����СȨֵ�ı�<w, adjVex[w]>
		if (net.GetTag(v) == UNVISITED && net.GetWeight(v, adjVex[v]) >0 &&
			net.GetWeight(v, adjVex[v]) < net.GetWeight(w, adjVex[w]))
			w = v;
	return w;
}

template <class ElemType, class WeightType>
void MiniSpanTreePrim(const AdjMatrixUndirNetwork<ElemType, WeightType> &net, int u0)
// ��ʼ������������net,u0Ϊg��һ������
// �����������Prim�㷨��u0����������g����С����������
{
	if (u0 < 0 || u0 >= net.GetVexNum())	throw Error("u0���Ϸ�1!");// �׳��쳣

	int *adjVex;						// ���v��V-U,net.GetWeight(v, adjVex[v])>0
										// ��ʾ(v, adjVex[v])��v��U������СȨֵ�ߵ��ڽӵ�
	int u, v, w;						// ��ʾ�������ʱ���� 
	adjVex = new int[net.GetVexNum()];	// ����洢�ռ�
	for (v = 0; v < net.GetVexNum(); v++)
	{	// ��ʼ����������adjVex�����Զ�������־����ʱU = {v0}
		if (v != u0)
		{	// ����v��V-U
			adjVex[v] = u0;
			net.SetTag(v, UNVISITED);
		}
		else
		{	// ����v��U
			net.SetTag(v, VISITED);
			adjVex[v] = u0;
		}
	}
	for (u = 1; u < net.GetVexNum(); u++)
	{	// ѡ��������������net.GetVexNum() - 1������
		w = MinVertex(net, adjVex);	
			// ѡ��ʹ�ñ�<w, adjVex[w]>Ϊ����V-U��U�ľ�����СȨֵ�ı�
		if (w == -1)
		{	// ��ʾU��V-U���ޱ�����
			return;
		}
		cout << "edge:(" << adjVex[w] << "," <<  w << ") weight:" 
			<<net.GetWeight(w, adjVex[w])<< endl ; // ����߼�Ȩֵ
		net.SetTag(w, VISITED);		// ��w����U
		for (int v = net.FirstAdjVex(w); v >= 0 ; v = net.NextAdjVex(w, v))
		{	// �¶��㲢��U������ѡ����С��
			if (net.GetTag(v) == UNVISITED &&		// v ��V - U
				(net.GetWeight(v, w) < net.GetWeight(v, adjVex[v]) || // ��<v,w>��Ȩֵ��С
				net.GetWeight(v, adjVex[v]) == 0) ) // �����ڱ�<v, adjVex[v]>
			{	// <v, w>Ϊ�µ���С��
				adjVex[v] = w;
			}
		}
	}
	delete []adjVex;			// �ͷŴ洢�ռ�
}

#endif

