// �ļ�·����: game_of_21_point\card.h 
#ifndef __CARD_H__
#define __CARD_H__

typedef enum 
{	// �˿�����ֵ:ACE(A),TWO(2)~TEN(10),JACK(J), QUEEN(Q), KING(K)
	ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
} RankType;

typedef enum 
{	// �˿��ƻ�ɫ:CLUBS(÷��), DIAMONDS(����), HEARTS(����)��SPADES(����)
	CLUBS, DIAMONDS, HEARTS, SPADES
} SuitType;

struct Card
{	// �˿��ƽṹ��
	RankType rank;									// �˿�����ֵ
	SuitType suit;									// �˿��ƻ�ɫ
};

ostream& operator<<(ostream& outStream, const Card &card) 
// �������������<<�����
{
	// �����ɫ
	if (card.suit == CLUBS) outStream << " ÷��";		// CLUBS��ʾ÷��
	else if (card.suit == DIAMONDS) outStream << " ����";// DIAMONDS��ʾ����
	else if (card.suit == HEARTS) outStream << " ����";	// HEARTS��ʾ����
	else if (card.suit == SPADES) outStream << " ����";	// SPADES��ʾ����

	// �����ֵ
	if (card.rank == ACE) outStream << "A";				// ACE��ʾA
	else if  (card.rank == JACK) outStream << "J";		// JACK��ʾJ
	else if  (card.rank == QUEEN) outStream << "Q";		// QUEEN��ʾQ
	else if  (card.rank == KING) outStream << "K";		// KING��ʾK
	else cout << (int)card.rank;						// (int)card.rankΪ��ֵ

	return outStream;
}

#endif
