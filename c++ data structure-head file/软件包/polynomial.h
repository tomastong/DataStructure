#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include "lk_list.h"			// ������
#include "poly_item.h"			// ����ʽ����


// ����ʽ��
class Polynomial
{
protected:
// ����ʽʵ�ֵ����ݳ�Ա:
	LinkList<PolyItem> polyList;// ����ʽ��ɵ����Ա�

public:
	//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	Polynomial(){};				// �޲ι��캯��
	~Polynomial(){};			// ��������
	int Length() const;			// �����ʽ������			 
	bool IsZero() const;		// �ж϶���ʽ�Ƿ�Ϊ0
	void SetZero();				// ������ʽ��Ϊ0
	void Display();				// ��ʾ����ʽ
	void InsItem( const PolyItem &item);		// ����һ��
	Polynomial operator +(const Polynomial &p) const; // �ӷ����������
	Polynomial operator -(const Polynomial &p) const; // �������������
	Polynomial operator *(const Polynomial &p) const; // �˷����������
	Polynomial(const Polynomial &copy);			// ���ƹ��캯��
	Polynomial(const LinkList<PolyItem> &copyLinkList);				
		// �ɶ���ʽ��ɵ����Ա������ʽ
	Polynomial &operator =(const Polynomial &copy);	// ��ֵ�������
	Polynomial &operator =(const LinkList<PolyItem> &copyLinkList);	// ��ֵ�������
};


// ����ʽ���ʵ�ֲ���

int Polynomial::Length() const
// ������������ض���ʽ������
{
	return polyList.Length();
}

bool Polynomial::IsZero() const
// ��������������ʽΪ0���򷵻�true�����򷵻�false
{
	return polyList.Empty();
}

void Polynomial::SetZero()
// ���������������ʽ��Ϊ0
{
	polyList.Clear(); 
}

void Polynomial::Display()
// �����������ʾ����ʽ
{
	int pos = 1;
	PolyItem it;
	StatusCode status = polyList.GetElem(pos, it);
	while ( status == ENTRY_FOUND)
	// ������ʾ����ʽ��ÿһ��
	{
		cout << "  (" << it.coef << "," << it.expn << ")"; //��ʾ����ʽ��һ��
		status = polyList.GetElem(++pos, it);	// ȡ����һ��
	}
}

void Polynomial::InsItem( const PolyItem &item)
// ��������������ʽ����һ��
{
	int pos = 1;
	PolyItem it;
	StatusCode status = polyList.GetElem(pos, it);
	while ( status == ENTRY_FOUND && it.expn < item.expn)
	// ���Ҳ���λ��
	{
		status = polyList.GetElem(++pos, it);	// ȡ����һ��
	}

	polyList.Insert(pos, item);					// �����ʽ����һ��
}

Polynomial Polynomial::operator +(const Polynomial &p) const
// ������������ص�ǰ����ʽ��p֮�͡����ӷ����������
{
	LinkList<PolyItem> la = polyList;			// ��ǰ����ʽ��Ӧ�����Ա�
	LinkList<PolyItem> lb = p.polyList;			// ����ʽp��Ӧ�����Ա�
	LinkList<PolyItem> lc;						// �Ͷ���ʽ��Ӧ�����Ա�
	int aPos = 1, bPos = 1;
	PolyItem aItem, bItem;
	StatusCode aStatus, bStatus;
	
	aStatus = la.GetElem(aPos, aItem);			// ȡ��la�ĵ�1��
	bStatus = lb.GetElem(bPos, bItem);			// ȡ��lb�ĵ�1��

	while (aStatus == ENTRY_FOUND && bStatus == ENTRY_FOUND )
	{
		if (aItem.expn < bItem.expn)
		// la�е���aItemָ����С
		{
			lc.Insert(lc.Length() + 1, aItem);	// ��aItem׷�ӵ�lc�ĺ���
			aStatus = la.GetElem(++aPos, aItem);// ȡ��la�ĵ���һ��
		}
		else if (aItem.expn > bItem.expn)
		// lb�е���bItemָ����С
		{
			lc.Insert(lc.Length() + 1, bItem);	// ��bItem׷�ӵ�lc�ĺ���
			bStatus = lb.GetElem(++bPos, bItem);// ȡ��lb�ĵ���һ��
		}
		else
		// la�е���aItem��lb�е���bItemָ�����
		{
			PolyItem sumItem(aItem.coef + bItem.coef, aItem.expn);
			if (sumItem.coef != 0)
				lc.Insert(lc.Length() + 1, sumItem);	// ��bItem׷�ӵ�lc�ĺ���
			aStatus = la.GetElem(++aPos, aItem);// ȡ��la�ĵ���һ��
			bStatus = lb.GetElem(++bPos, bItem);// ȡ��lb�ĵ���һ��
		}
	}

	while (aStatus == ENTRY_FOUND)
	// ��la��ʣ����׷�ӵ�lc�ĺ���
	{
		lc.Insert(lc.Length() + 1, aItem);	// ��aItem׷�ӵ�lc�ĺ���
		aStatus = la.GetElem(++aPos, aItem);// ȡ��la�ĵ���һ��
	}

	while (bStatus == ENTRY_FOUND)
	// ��lb��ʣ����׷�ӵ�lc�ĺ���
	{
		lc.Insert(lc.Length() + 1, bItem);	// ��bItem׷�ӵ�lc�ĺ���
		bStatus = lb.GetElem(++bPos, bItem);// ȡ��lb�ĵ���һ��
	}

	Polynomial fs;							// �Ͷ���ʽ
	fs.polyList = lc;

	return fs;
}

Polynomial Polynomial::operator -(const Polynomial &p) const
// ������������ص�ǰ����ʽ��p֮����������������
{
	LinkList<PolyItem> la = polyList;			// ��ǰ����ʽ��Ӧ�����Ա�
	LinkList<PolyItem> lb = p.polyList;			// ����ʽp��Ӧ�����Ա�
	int bPos = 1;
	PolyItem bItem;
	StatusCode bStatus;
	
	// ��lb�ĸ����ϵ��ȡ�෴��
	bStatus = lb.GetElem(bPos, bItem);			// ȡ��lb�ĵ�1��
	while (bStatus == ENTRY_FOUND )
	{
		bItem.coef = -bItem.coef;				// ��ϵͳȡ��
		lb.SetElem(bPos, bItem);				// ������

		bStatus = lb.GetElem(++bPos, bItem);	// ȡ��lb����һ��
	}

	Polynomial fa(la), fb(lb), fc = fa + fb;

	return fc;
}

Polynomial Polynomial::operator *(const Polynomial &p) const
// ������������ص�ǰ����ʽ��p֮�������˷����������
{
	LinkList<PolyItem> la = polyList;			// ��ǰ����ʽ��Ӧ�����Ա�
	LinkList<PolyItem> lb = p.polyList;			// ����ʽp��Ӧ�����Ա�
	LinkList<PolyItem> lc;					
	Polynomial fMultiply;						// �˻�����ʽ
	int aPos = 1 , bPos;
	PolyItem aItem, bItem, cItem;
	StatusCode aStatus, bStatus;
	
	// ��la�ĸ���ȥ��lb
	aStatus = la.GetElem(aPos, aItem);			// ȡ��la�ĵ�1��
	while (aStatus == ENTRY_FOUND)
	{
		
		bPos = 1;
		bStatus = lb.GetElem(bPos, bItem);		// ȡ��lb�ĵ�1��
		while (bStatus == ENTRY_FOUND)
		{
			// ��la��lb��ÿһ�����
			cItem.coef = aItem.coef * bItem.coef;// ϵ�����
			cItem.expn = aItem.expn + bItem.expn;// ָ�����

			lc.Clear();							// ���lc
			lc.Insert(lc.Length() + 1, cItem);	// lcΪ�˻�
			// ���˻��ӵ�fMultiply
			Polynomial fc(lc);
			fMultiply = fMultiply + fc;
			
			bStatus = lb.GetElem(++bPos, bItem);// ȡ��lb����һ��
		}
		
		aStatus = la.GetElem(++aPos, aItem);	// ȡ��la����һ��
	}

	return fMultiply;
}

Polynomial::Polynomial(const Polynomial &copy)
// ����������ɶ���ʽcopy�����¶���ʽ�������ƹ��캯��
{
	polyList = copy.polyList;
}

Polynomial::Polynomial(const LinkList<PolyItem> &copyLinkList)	
// ����������ɶ���ʽ��ɵ����Ա������ʽ����ת�����캯��
{
	polyList = copyLinkList;
}

Polynomial &Polynomial::operator =(const Polynomial &copy)	
// ���������������ʽcopy��ֵ����ǰ����ʽ������ֵ�������
{
	if ( &copy != this)
	{
		polyList = copy.polyList;
	}
	return *this;
}

Polynomial &Polynomial::operator =(const LinkList<PolyItem> &copyLinkList)
// ���������������ʽ��ɵ����Ա�copyLinkList��ֵ����ǰ����ʽ
//	������ֵ�������
{
	polyList = copyLinkList;
	return *this;
}

#endif