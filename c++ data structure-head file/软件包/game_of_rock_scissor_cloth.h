// �ļ�·����: game_of_rock_scissor_cloth\game_of_rock_scissor_cloth.h 
#ifndef __GAME_OF_ROCK_SCISSOR_CLOTH_H__
#define __GAME_OF_ROCK_SCISSOR_CLOTH_H__

typedef enum 
{	// ѡ�ֿɹ���ѡ��: ROCK(ʯͷ),SCISSOR(����),CLOTH(��),DISPLAY(��ʾ),HELP(����)
	// ��QUIT(�˳�)
	ROCK, SCISSOR, CLOTH, DISPLAY, HELP, QUIT
} SelectType;

typedef enum 
{	// ʤ�������WIN(ʤ),LOSE(��)��TIE(ƽ)
	WIN, LOSE, TIE
} ResultType;		

// ʯͷ������������Ϸ��GameOfRockScissorCloth����
class GameOfRockScissorCloth
{
private:
// ʯͷ������������Ϸ������ݳ�Ա:
	int winCount;								// ����ѡ�ֻ�ʤ����
	int loseCount;								// ����ѡ��ʧ�ܴ���
	int tieCount;								// ����ѡ��ƽ�ִ���

// ��������
	ResultType Compare(SelectType playerChoice, SelectType computerChoice); // �ȽϾ���ʤ��
	void DisplayFinalStatus();					// ��ʾ��Ϸ���״̬
	void DisplayGameStatus();					// ��ʾ��Ϸ״̬
	void DisplayHelp();							// ��ʾ������Ϣ
	void Report(ResultType result);				// ��������������ͳ�ƻ�ʤ��ʧ�ܺ�ƽ�ִ���
	SelectType SelectByMachine();				// ����ѡ����ѡ��
	SelectType SelectByPlayer();				// ����ѡ����ѡ��

public:
// ʯͷ������������Ϸ�෽������:
	GameOfRockScissorCloth();					// �޲����Ĺ��캯��
	virtual ~GameOfRockScissorCloth(){};		// ��������
	void Game();								// ������Ϸ
};

// ʯͷ������������Ϸ��GameOfRockScissorCloth��ʵ�ֲ���
GameOfRockScissorCloth::GameOfRockScissorCloth()
// �����������ʼ�����ݳ�Ա
{
	winCount = 0;								// ����ѡ�ֻ�ʤ����
	loseCount = 0;								// ����ѡ��ʧ�ܴ���
	tieCount = 0;								// ����ѡ��ƽ�ִ���
}

ResultType GameOfRockScissorCloth::Compare(SelectType playerChoice, SelectType computerChoice)
// ����������ȽϾ�������ѡ�ֵĻ�ʤ����ʧ��ƽ��
{
	ResultType result;

	if (playerChoice == computerChoice)
	{	// ѡ����ͬ��ʾƽ��
		return TIE;
	}

	switch (playerChoice)
	{
	case ROCK:		// ����ѡ��ѡ��ʯͷ
		result = (computerChoice == SCISSOR) ? WIN : LOSE;	// ���ݵ���ѡ�ֵ�ѡ��õ��ȽϽ��
		break;
	case SCISSOR:	// ����ѡ��ѡ�����
		result = (computerChoice == CLOTH) ? WIN : LOSE;	// ���ݵ���ѡ�ֵ�ѡ��õ��ȽϽ��
		break;
	case CLOTH:		// ����ѡ��ѡ��
		result = (computerChoice == ROCK) ? WIN : LOSE;		// ���ݵ���ѡ�ֵ�ѡ��õ��ȽϽ��
		break;
	}

	return result;
}

void GameOfRockScissorCloth::DisplayFinalStatus()
// �����������ʾ��Ϸ���״̬
{
	if (winCount > loseCount)
	{	// ����ѡ�ֻ�ʤ��������
		cout << "ף���㣬��ȡ������ʤ����!" << endl << endl;
	}
	else if (winCount < loseCount)
	{	// ����ѡ��ʧ�ܴ�������
		cout << "��Ҫʧȥ���İ���ֻҪŬ��������ʤ��һ��������!" << endl << endl;
	}
	else
	{	// ����ѡ�ֻ�ʤ������ʧ�ܴ�����ͬ
		cout << "����������Ȼ����ƽ�֣���Ҳûʧ�ܰ�!" << endl << endl;
	}
}

void GameOfRockScissorCloth::DisplayGameStatus()
// �����������ʾ��Ϸ״̬
{
	cout << "��Ϸ״̬:" << endl;
	cout << "��ʤ����:" << winCount << endl;
	cout << "ʧ�ܴ���:" << loseCount << endl;
	cout << "ƽ�ִ���:" << tieCount << endl;
}

void GameOfRockScissorCloth::DisplayHelp()
// �����������ʾ������Ϣ
{
	cout << "������ѡ�ֿɹ�������ַ�:" << endl;
	cout << "  r	��ʾѡ��ʯͷ(rock)" << endl;
	cout << "  s	��ʾѡ�����(scissor)" << endl;
	cout << "  c	��ʾѡ��(cloth)" << endl;
	cout << "  d	��ʾѡ����ʾ(display)��Ϸ��ǰ״̬" << endl;
	cout << "  h	��ʾѡ���ð���(help)" << endl;
	cout << "  q	��ʾѡ���˳�(quit)" << endl << endl;
	cout << "��Ϸ����:" << endl;
	cout << "  ʯͷ�һ�����" << endl;
	cout << "  �������鲼" << endl;
	cout << "  ������ʯͷ" << endl;
}


void GameOfRockScissorCloth::Report(ResultType result)
// �����������������������ͳ�ƻ�ʤ��ʧ�ܺ�ƽ�ִ���
{
	switch (result)
	{
	case WIN:	// ����ѡ�ֻ�ʤ
		winCount = winCount + 1;		// ��ʤ������1
		cout << "                            ���ʤ�˰�!" << endl;
		break;
	case LOSE:	// ����ѡ��ʧ��
		loseCount = loseCount + 1;		// ʧ�ܴ�����1
		cout << "                            �Բ�����ʧ���˰�!" << endl;
		break;
	case TIE:	// ƽ��
		tieCount = tieCount + 1;		// ƽ�ִ�����1
		cout << "                            ������ƽ�ְ�!" << endl;
		break;
	}
}

SelectType GameOfRockScissorCloth::SelectByMachine()
// �������������ѡ����ѡ��
{
	return (SelectType) (GetRand(3));
}

SelectType GameOfRockScissorCloth::SelectByPlayer()
// �������������ѡ����ѡ��
{
	char select;
	SelectType playerChoice;

	printf("��ѡ��(r,s,c,d,h,q)");
	do
	{	// ����ѡ����ѡ��
		cin >> select;
		select = tolower(select);	// ��д��ĸת��ΪСд��ĸ
	} while (select != 'r' && select != 's' && select != 'c' 
		&& select != 'd' &&  select != 'h' &&  select != 'q');
	
	switch (select)
	{
	case 'r':	// ѡ��ʯͷ
		playerChoice = ROCK;
		break;
	case 's':	// ѡ�����
		playerChoice = SCISSOR;
		break;
	case 'c':	// ѡ��
		playerChoice = CLOTH;
		break;
	case 'd':	// ѡ����ʾ��Ϸ״̬
		playerChoice = DISPLAY;
		break;
	case 'h':	// ѡ�����
		playerChoice = HELP;
		break;
	case 'q':	// ѡ���˳�
		playerChoice = QUIT;
		break;
	}

	return playerChoice;
}

void GameOfRockScissorCloth::Game()
// ���������������Ϸ
{
	ResultType result;						// ����ѡ�ֵ�ʤ��ƽ���
	SelectType playerChoice, machineChoice;	// ѡ������ѡ��

	SetRandSeed();							// �������������
	DisplayHelp();							// ��ʾ������Ϣ

	while ((playerChoice = SelectByPlayer()) != QUIT)
	{
		switch (playerChoice)
		{
		case ROCK:
		case SCISSOR:
		case CLOTH:							// ѡ��ѡ����ʯͷ�������Ͳ�
			machineChoice = SelectByMachine();
			result = Compare(playerChoice, machineChoice);// �ȽϾ�������ѡ��ʤ��ƽ���
			Report(result);					// ��������������ͳ�ƻ�ʤ��ʧ�ܺ�ƽ�ִ���
			break;
		case DISPLAY:						// ѡ��ѡ����ʾ��Ϸ��ǰ״̬
			DisplayGameStatus();			// ��ʾ��Ϸ״̬
			break;
		case HELP:							// ѡ��ѡ���ð���
			DisplayHelp();					// ��ʾ������Ϣ
			break;
		}
	}
	
	DisplayGameStatus();					// ��ʾ��Ϸ״̬
	DisplayFinalStatus();					// ��ʾ��Ϸ���״̬
}

#endif



