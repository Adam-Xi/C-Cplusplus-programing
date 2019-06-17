#include "chess.h"

void Game()
{
	char result = '\0';//char 本质上也是一个整数
	char board[ROW][COL];

	InitBoard(board, ROW, COL);
	srand((unsigned int)time(NULL));//srand种一个随机数种子，一般以事件为种子（time.h）

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
		printf("You win！\n");
		break;
	case 'O'://Computer win
		printf("You lost！\n");
		break; 
	case 'E'://It ends in a draw 平局
		printf("It ends in a draw！\n");
		break;
	default:
		printf("bug?\n");
		break;
	}

}
//	memset(board, ' ', sizeof(board));  初始化数组board【】【】
void InitBoard(char board[][COL], int row, int col)
{
	int i = 0;
	for (; i < row; i++){
		int j = 0;
		for (; j < col; j++){
			board[i][j] = ' ';//全部置为空格
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
		if (x >= 1 && x <= 3 && y >= 1 && y <= 3){ //Player输入的坐标要求在棋盘内
			if (board[x - 1][y - 1] == ' '){ //判断该位置是否已经被占了
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
		int x = GetRandom(1,3); //随机生成电脑落子的横纵坐标
		int y = GetRandom(1,3);
		if (board[x - 1][y - 1] == ' '){ //判断随机产生的位置是否已经被占了
			board[x - 1][y - 1] = COMPUTER_COLOR;
			printf("The point selected  by computer is Pos<%d,%d>.\n", x, y);
			break;
		}
	}
}

int GetRandom(int start, int end){
	//[start,end]
	return rand() % (end - start) + start;//万能公式，求一随机区间生成的随机数
}

char Judge(char board[][COL], int row, int col)
{
	int i, j;
	for (i = 0; i < ROW; i++){//若三字连珠，则返回'X'或'O',表示胜利方所执的棋

		for (i = 0; i < row; i++){ //行
			if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1]!=' ')
				return board[i][0];
		}

		for (i = 0; i < col; i++){//列
			if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != ' ')
				return board[0][i];
		}

		if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' '){ //对角线
			return board[0][0];
		}
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' '){ //对角线
			return board[0][0];
		}
	}
	if (IsFull(board, ROW, COL)){ //若执行到此步骤，表明没有获胜方，下面判断棋盘是否满了
		return 'E'; //满了，平局
	}
	else{
		return 'N'; //未满，NEXT，继续
	}
}

int IsFull(char board[ROW][COL], int row, int col){ //0--了满；1--未满
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
