#ifndef __HUFFMAN_TREE_NODE_H__
#define __HUFFMAN_TREE_NODE_H__

// �������������
template <class WeightType>
struct HuffmanTreeNode
{
// ���ݳ�Ա:
	WeightType weight;							// Ȩ������
	unsigned int parent, leftChild, rightChild;	// ˫��,���Һ�����

// ���캯��:
	HuffmanTreeNode();							// �޲����Ĺ��캯��
	HuffmanTreeNode(WeightType w, int p = 0, int lChild = 0, int rChild = 0);
		// ��֪Ȩ,˫�׼����Һ��ӹ���ṹ
};

// ��������������ʵ�ֲ���
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode()
// �������������ս��
{
	parent = leftChild = rightChild = 0;
}

template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType w, int p, int lChild, int rChild)									// �Һ���
// �������������һ��ȨΪw,˫��Ϊp,����ΪlChild,�Һ���ΪrChild�Ľ��
{
	weight = w;								// Ȩ
	parent = p;								// ˫��
	leftChild = lChild;						// ����
	rightChild = rChild;					// �Һ���
}

#endif
