#ifndef __POLY_ITEM_H__
#define __POLY_ITEM_H__

// ����ʽ����
struct PolyItem
{
// ���ݳ�Ա:
	double coef;				// ϵ��
	int    expn;				// ָ��	

// ���캯��:
    PolyItem() ;				// �����ݵĹ��캯��
    PolyItem(double cf, int en);// ��֪ϵ�����ָ�������ṹ
};



// ����ʽ�����ʵ�ֲ���

PolyItem::PolyItem()
// �������������ָ����Ϊ-1�Ľ��
{
   expn = -1;
}


PolyItem::PolyItem(double cf, int en)
// �������������һ��ϵ����Ϊcf��ָ����Ϊen�Ľ��
{
   coef = cf;
   expn = en;
}

#endif
