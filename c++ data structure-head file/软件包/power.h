#ifndef __FACTORIAL_H__
#define __FACTORIAL_H__

// �׳��㷨

// �ļ�·����:power\power.h 
CLargeInt Power(const CLargeInt &base,	const CLargeInt &exp)
// �������: �����Ǹ��������Ĵ�Ǹ��������η�
{
	CLargeInt tmpLargInt(1);
	for (int i = 0; i < exp; i = i + 1)
	{	// �������Ǹ��������Ĵ�Ǹ��������η�
		tmpLargInt = tmpLargInt * base;
	}

	return tmpLargInt;
}

#endif
