#ifndef __ADJ_LIST_NETWORK_EDGE_H__
#define __ADJ_LIST_NETWORK_EDGE_H__

// �ڽӱ�����������
template <class WeightType>
class AdjListNetworkEdge
{
public:
// ���ݳ�Ա:
	int adjVex;								// �ڽӵ�
	WeightType weight;						// Ȩֵ

// ���캯��:
	AdjListNetworkEdge();						// �޲����Ĺ��캯��
	AdjListNetworkEdge(int v, WeightType w);	// �����ڽӵ�Ϊv��ȨΪw���ڽӱ�
};

// �ڽӱ������������ʵ�ֲ���
template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge()
// �������������һ�����ڽӱ�߽��ߡ����޲ι��캯��
{
	adjVex = -1;
}

template <class WeightType>
AdjListNetworkEdge<WeightType>::AdjListNetworkEdge(int v, WeightType w)
// ��������������ڽӵ�Ϊv��ȨΪw���ڽӱ�
{
	adjVex = v;								// �ڽӵ�
	weight = w;								// Ȩ
}

#endif