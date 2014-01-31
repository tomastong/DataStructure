// �ļ�·����: queen\queen.h
#ifndef __QUEEN_H__
#define __QUEEN_H__

// �ʺ������㷨

void BackTrack(int c, int n, bool row[], bool diag[], bool backDiag[], int x[]);	// �������n�ʺ�����
void OutSolution(int n, int x[]);// ���һ��� 

void Queen(int n)
// �������: ���n�ʺ�����
{
	bool *row = new bool[n + 1];				// ���Ƿ��лʺ�
	bool *diag = new bool[2 * n];				// ���Խ����Ƿ��лʺ�
	bool *backDiag = new bool[2 * n];			// ���Խ����Ƿ��лʺ�
	int *x = new int[n + 1];					// n�ʺ�����Ľ�
	int i;										// ��ʱ����

	// ����ֵ
	for (i = 1; i <= n; i++) row[i] = false;
	for (i = 1; i < 2 * n; i++) diag[i] = false;
	for (i = 1; i < 2 * n; i++) backDiag[i] = false;

	BackTrack(1, n, row, diag, backDiag, x);					// �ݹ����n�ʺ�����

	delete []row; delete []diag; delete []backDiag;	delete []x;	// �ͷŴ洢�ռ�
}

void BackTrack(int c, int n, bool row[], bool diag[], bool backDiag[], int x[])
// �������: ǰi-1���ʺ��ѷ��ú�Ϊ��i���ʺ�ѡ����ʵ�λ�ã�row[]���ڱ�ʾĳ��
//	�Ƿ�����лʺ�backDiag[]��ʾĳ�����Խ����Ƿ�����лʺ�diag[]��ʾĳ����
//	�Խ����Ƿ�����лʺ�,x[]��ʾ�ʺ������õ���
{
	int r;
	if (c > n)
	{	// c>n��ʾ��1~n���ʺ��ѷ��ú�
		OutSolution(n, x);	// �ѵõ���,�����
	}
	else
	{
		for (r = 1; r <= n; r++)	
		{	// ��c���ʺ������õ���
			if(!row[r] && !diag[n - c + r] && !backDiag[r + c - 1])
			{	// λ��(r,c)���ڵ��У��Խ���û�����лʺ�,
				// ����λ��(r, c)���õ�c���ʺ�
				row[r] = diag[n - c + r] = backDiag[r + c - 1] = true;	// ��ʾλ��(r, c)���лʺ�
				x[c] = r;					// ��ʾ��c���ʺ������õ���
				BackTrack(c + 1, n, row, diag, backDiag, x);	// ��̽��c + 1���ʺ������õ�λ��
				row[r] = diag[n - c + r] = backDiag[r + c - 1] = false; // �ͷ�λ��(r,c)�����л���
			}
		}
	}
}

void OutSolution(int n, int x[])
//�������: ����ʺ�����Ľ�
{
	int static num = 0;		// num��ʾ��ǰ����ý�ĸ���
	
	cout << "��" << ++num << "����:";
	for(int c = 1; c <= n; c++)
	{	// �����
		cout << "(" << x[c] << "," << c << ") ";
	}
	cout << endl;
}

#endif