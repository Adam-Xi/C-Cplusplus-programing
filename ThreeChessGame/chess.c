#include "chess.h"

void Game()
{
	char result = '\0';//char ������Ҳ��һ������
	char board[ROW][COL];

	InitBoard(board, ROW, COL);
	srand((unsigned int)time(NULL));//srand��һ����������ӣ�һ�����¼�Ϊ���ӣ�time.h��

	while (1){

		printf("It's turn to you to select point:\n");
		PlayerMove(board, ROW, COL);
		ShowBoard(board, ROW, COL);
		result = Judge(board, ROW, COL);
		if (result != 'N'){
			break;
		}
		printf("\n");

		printf("It's turn to computer to select point:\n");
		ComputerMove(board, ROW, COL);
		ShowBoard(board, ROW, COL);
		result = Judge(board, ROW, COL);
		if (result != 'N'){
			break;
		}
		printf("=====================================================\n");
		printf("\n");
	}
	switch (result){
	case 'X'://Player win
		printf("You win��\n");
		break;
	case 'O'://Computer win
		printf("You lost��\n");
		break; 
	case 'E'://It ends in a draw ƽ��
		printf("It ends in a draw��\n");
		break;
	default:
		printf("bug?\n");
		break;
	}

}
//	memset(board, ' ', sizeof(board));  ��ʼ������board��������
void InitBoard(char board[][COL], int row, int col)
{
	int i = 0;
	for (; i < row; i++){
		int j = 0;
		for (; j < col; j++){
			board[i][j] = ' ';//ȫ����Ϊ�ո�
		}
	}
}

void ShowBoard(char board[][COL], int row, int col)
{
	for (row = 0; row < ROW; row++){
		for (col = 0; col < COL; col++){
			printf("|  %c  \t", board[row][col]);
		}
		printf("\n-----------------------\n");
	}
}

void PlayerMove(char board[][COL], int row, int col)
{
	while (1){
		int x = 0;
		int y = 0;
		printf("Please input Pos<x,y>: \n");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= 3 && y >= 1 && y <= 3){ //Player���������Ҫ����������
			if (board[x - 1][y - 1] == ' '){ //�жϸ�λ���Ƿ��Ѿ���ռ��
				board[x - 1][y - 1] = PLAYER_COLOR;
				break;
			}
			else{
				printf("Enter error, Try again: \n");
			}
		}
	}
}

void ComputerMove(char board[][COL], int row, int col)
{
	while (1){
		int x = GetRandom(1,3); //������ɵ������ӵĺ�������
		int y = GetRandom(1,3);
		if (board[x - 1][y - 1] == ' '){ //�ж����������λ���Ƿ��Ѿ���ռ��
			board[x - 1][y - 1] = COMPUTER_COLOR;
			printf("The point selected  by computer is Pos<%d,%d>.\n", x, y);
			break;
		}
	}
}

int GetRandom(int start, int end){
	//[start,end]
	return rand() % (end - start) + start;//���ܹ�ʽ����һ����������ɵ������
}

char Judge(char board[][COL], int row, int col)
{
	int i, j;
	for (i = 0; i < ROW; i++){//���������飬�򷵻�'X'��'O',��ʾʤ������ִ����

		for (i = 0; i < row; i++){ //��
			if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1]!=' ')
				return board[i][0];
		}

		for (i = 0; i < col; i++){//��
			if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != ' ')
				return board[0][i];
		}

		if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' '){ //�Խ���
			return board[0][0];
		}
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' '){ //�Խ���
			return board[0][0];
		}
	}
	if (IsFull(board, ROW, COL)){ //��ִ�е��˲��裬����û�л�ʤ���������ж������Ƿ�����
		return 'E'; //���ˣ�ƽ��
	}
	else{
		return 'N'; //δ����NEXT������
	}
}

int IsFull(char board[ROW][COL], int row, int col){ //0--������1--δ��
	int i, j;
	for (i = 0; i < ROW; i++){
		for (j = 0; j < COL; j++){
			if (board[ROW][COL] == ' '){
				return 1;
			}
		}
	}
	return 0;
}
