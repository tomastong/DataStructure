// �ļ�·����: encrypt\encrypt.h 
#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

#include "string.h"								// ����
#include "lk_list.h"							// ��������

// ������
class Encrypt
{
private:
//  ����������ݳ�Ա:
	String letters;								// ��Сд��ĸ��
	String map;									// ��ĸӳ���

public:
// �����෽������:
	Encrypt();									// �޲����Ĺ��캯��
	virtual ~Encrypt(){};						// ��������
	String Encode(const String &str);			// �����ı������м��ܺ���ı���
	String Decode(const String &str);			// �����Ѽ��ܵ��ı������н��ܺ���ı���
};

// �������ʵ�ֲ���
Encrypt::Encrypt()
// �����������ʼ�����ݳ�Ա
{
	letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";	// ��ĸ��
	map = "NgzQTCobmUHelkPdAwxfYIvrsJGnZqtcOBMuhELKpaDWXFyiVRjS";		// ��ĸӳ���
}

String Encrypt::Encode(const String &str)
// ��������������ı������м��ܺ���ı���
{
	LinkList<char> lk_tem;						// ��ʱ��������,���ڴ洢���ܺ���ı���

	for (int i = 0; i < str.Length(); i++)
	{	// �����ı���str��ÿ���ַ�
		int pos;								// λ��			
		for (pos = 0; pos < 52; pos++)
		{	// �����ַ�str[i]���ַ����е�λ��
			if (str[i] == letters[pos])
			{	// ���ҳɹ�
				lk_tem.Insert(lk_tem.Length() + 1, map[pos]);	// �����ܺ����ĸ����lk_tem;
				break;							// �˳��ڲ�forѭ��
			}
		}
		if (pos == 52)
		{	// ����ʧ��
			lk_tem.Insert(lk_tem.Length() + 1, str[i]);	// δ��ӳ����ַ������Ըı����lk_tem;
		}
	}
	String result(lk_tem);						// ���ɼ����ı���
	return result;								// ���ؼ����ı���
}

String Encrypt::Decode(const String &str)
// ������������ؼ����ı������н��ܺ���ı���
{
	LinkList<char> lk_tem;						// ��ʱ��������,���ڴ洢���ܺ���ı���

	for (int i = 0; i < str.Length(); i++)
	{	// �����ı���str��ÿ���ַ�
		int pos;								// λ��			
		for (pos = 0; pos < 52; pos++)
		{	// �����ַ�str[i]����ĸӳ����е�λ��
			if (str[i] == map[pos])
			{	// ���ҳɹ�
				lk_tem.Insert(lk_tem.Length() + 1, letters[pos]);	// �����ܺ����ĸ��������lk_tem;
				break;							// �˳��ڲ�forѭ��
			}
		}
		if (pos == 52)
		{	// ����ʧ��
			lk_tem.Insert(lk_tem.Length() + 1, str[i]);	// δ��ӳ����ַ������Ըı����lk_tem;
		}
	}

	String result(lk_tem);						// ���ɽ����ı���
	return result;								// ���ؽ����ı���
}

#endif