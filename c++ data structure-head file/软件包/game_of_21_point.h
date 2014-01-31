// �ļ�·����: game_of_21_point\game_of_21_point.h 
#ifndef __GAME_OF_21_POINT_H__
#define __GAME_OF_21_POINT_H__

#include "card.h"			// �˿���

#define LEN_OF_MAX_NAME 21	// �����������

// 21����Ϸ��GameOf21Point����
class GameOf21Point
{
private:
// 21����Ϸ������ݳ�Ա:
	Card deck[52];		// һ���˿���
	int dealPos;		// ����λ��
	Card hands[8][21];	// hand[0]�洢ׯ�����е��˿���, hand[1~7]�洢��λ������е��˿���
	int numOfCard[8];	// ׯ��(numOfCard[0])�����(numOfCard[1~7])���е��˿�����
	char name[8][LEN_OF_MAX_NAME];	// ׯ�����������
	int numOfPlayer;	// �������

// ��������
	void Shuffle();		// ϴ��, ���˿��ƻ���һ���Ա����һ��������������
	int GetTotalScore(Card hand[21], int n);// ����һ���˿��Ƶ��ܷ�ֵ
	void ShowStatus(int num, bool hideFirstCardAndTotalScore = false);	
		// ��ʾׯ��(��Ӧnum=0)�����(��Ӧnum>0)�ĵ�ǰ״̬
	Card DealOneCard();	// ��һ���˿���

public:
// 21����Ϸ�෽������:
	GameOf21Point();			// �޲����Ĺ��캯��
	virtual ~GameOf21Point(){};	// ��������
	void Game();				// ������Ϸ
};

// 21����Ϸ��GameOf21Point��ʵ�ֲ���
GameOf21Point::GameOf21Point()
// �����������ʼ���˿���,����λ��,ׯ�����������е��˿�����
{
	int curPos = 0;				// ��ǰ�˿���λ��		
	for (int suitPos = 0; suitPos < 4; suitPos++)
	{	// ��ɫ
		for (int rankPos = 1; rankPos <= 13; rankPos++)
		{	// ��ֵ
			deck[curPos].suit = (SuitType)suitPos;	// ��ɫ
			deck[curPos].rank = (RankType)rankPos;	// ��ֵ
			curPos++;								// ��һ��λ��
		}
	}
	cout << "�����˼�����Ϸ?(1~7):"; 
	cin >> numOfPlayer;			// ������� 
	dealPos = 0;				// ����λ��
	int i;						// ��ʱ����
	for (i = 0; i <= numOfPlayer; i++) numOfCard[i] = 0;	
		//  ׯ��(numOfCard[0])�����(numOfCard[1~7])���е��˿�����
	strcpy(name[0], "ׯ��");	// ׯ��
	for (i = 1; i <= numOfPlayer; i++)
	{	// �������
		cout << "�����" << i << "λ��ҵ�����:";
		cin >> name[i];
	}
	cout << "��Ϸ��ʼ" << endl;
}

void GameOf21Point::Shuffle()
// ���������ϴ��, ���˿��ƻ���һ���Ա����һ��������������
{
	for (int curPos = 51; curPos > 0; curPos--)
	{	// ���������λ��ΪcurPos���˿���
		int pos = GetRand(curPos + 1);	// ����0~curPos֮��������
		Swap(deck[pos], deck[curPos]);	// ����deck[pos]��deck[curPos]
	}
}

int GameOf21Point::GetTotalScore(Card hand[21], int n)
// �������������һ���˿��Ƶ��ܷ�ֵ
{
	int pos;							// ��ʱ����
	int totalScore = 0;					// �ܷ�ֵ
	for (pos = 0; pos < n; pos++)
	{	// ѭ��������ֵ(A�ķ�ֵΪ11)
		if (hand[pos].rank == ACE) totalScore += 11;	// A�ķ�ֵΪ11
		else if (hand[pos].rank > TEN) totalScore += 10;// J,Q,K�ķ�ֵΪ10
		else totalScore += (int)hand[pos].rank;			// TWO~TEN�ķ�ֵΪ2~10
	}
	
	for (pos = 0; totalScore > 21 && pos < n; pos++)
	{	// ��ֵ����21ʱ, ��A�ķ�ֵ��Ϊ1
		if (hand[pos].rank == ACE) totalScore -= 10;	// A�ķ�ֵ��11�ָ�Ϊ1��
	}

	return totalScore;					// �����ܷ�
}

void GameOf21Point::ShowStatus(int num, bool hideFirstCardAndTotalScore)
// �����������num=0ʱ,��ʾׯ�ҵ�ǰ״̬,��num>0ʱ,��ʾ��num����ҵĵ�ǰ״̬,
//	��hideFirstCardAndTotalScoreΪ��ʱ,�����������˿������ܷ�, ������ʾ
//	�����˿������ܷ�
{
	cout << name[num] << ":";			// ��ʾׯ�һ�������� 
	if (hideFirstCardAndTotalScore) cout << " <����>";	// ���������˿���
	else cout << hands[num][0];							// ��ʾ�����˿���
	for (int i = 1; i < numOfCard[num]; i++)
		cout << hands[num][i];			// ��ʾׯ�һ�������е��˿���
	if (!hideFirstCardAndTotalScore)
		cout << " �ܷ�ֵ" << GetTotalScore(hands[num], numOfCard[num]); // ��ʾׯ�һ�����ܷ�
	cout << endl;
	if (GetTotalScore(hands[num], numOfCard[num]) > 21)
		cout << name[num] << "����!" << endl;
}

Card GameOf21Point::DealOneCard()
// �����������һ���˿���
{
	return deck[dealPos++];	
}

void GameOf21Point::Game()
// ���������������Ϸ
{
//	SetRandSeed();										// �������������
	Shuffle();		// ϴ��, ���˿��ƻ���һ���Ա����һ��������������
	int i, j;		// ��ʱ����

	for (i = 0; i < 2; i++) 
		hands[0][numOfCard[0]++] = DealOneCard();		// Ϊׯ�ҷ������˿���
	ShowStatus(0, true);								// ��ʾׯ��״̬,���������˿������ܷ�
	
	for (i = 1; i <= numOfPlayer; i++)
	{	// �����ҷ��˿���,��ʾ��������е��˿���
		for (j = 0; j < 2; j++) 
			hands[i][numOfCard[i]++] = DealOneCard();	// Ϊ���i�������˿���
		ShowStatus(i);									// ��ʾ���i
	}
	cout << endl;

	for (i = 1; i <= numOfPlayer; i++)
	{	// ��������ҷ��������
		cout << name[i] << ", ������Ҫһ������";
		if (UserSaysYes())
		{	// �����Ҫһ����
			hands[i][numOfCard[i]++] = DealOneCard();	// Ϊ���i��1���˿���
			ShowStatus(i);								// ��ʾ���i
		}
	}	

	ShowStatus(0);										// ��ʾׯ��
	while (GetTotalScore(hands[0], numOfCard[0]) <= 16)
	{	// ׯ���ܷ�С�ڵ���16, ����������
		hands[0][numOfCard[0]++] = DealOneCard();		// Ϊׯ�ҷ�1���˿���
		ShowStatus(0);									// ��ʾׯ��
	}
	cout << endl;

	if (GetTotalScore(hands[0], numOfCard[0]) > 21)
	{	// ׯ������, û��������������Ӯ
		for (i = 1; i <= numOfPlayer; i++)
		{	// ���β鿴ÿλ���
			if (GetTotalScore(hands[i], numOfCard[i]) <= 21)	
			{	// ���û������
				cout << name[i] << ", ��ϲ��, ��Ӯ��!" << endl; 
			}
		}
	}
	else
	{	// ׯ��û������
		for (i = 1; i <= numOfPlayer; i++)
		{	// ���β鿴ÿλ���
			if (GetTotalScore(hands[i], numOfCard[i]) <= 21 &&	// δ����
				GetTotalScore(hands[i], numOfCard[i]) > GetTotalScore(hands[0], numOfCard[0]) 
					// �ֱܷ�ׯ�Ҵ�
				)	
			{	// ���δ����, ���ֱܷ�ׯ�Ҵ�, ���Ӯ
				cout << name[i] << ", ��ϲ��, ��Ӯ��!" << endl;
			}
			else if (GetTotalScore(hands[i], numOfCard[i]) == GetTotalScore(hands[0], numOfCard[0]))
			{	// ����ܷ���ׯ�����, ƽ��
				cout << name[i] << ", ��, ���ƽ����!" << endl;
			}
			else
			{	// ����������ֱܷ�ׯ��С, �����
				cout << name[i] << ", �Բ���, ������!" << endl;
			}
		}
	}
}

#endif


