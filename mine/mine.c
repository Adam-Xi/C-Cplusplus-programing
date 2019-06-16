#include "mine.h"

int GetRandIndex(int start, int end)  //获取随机值作为雷的横纵坐标【1,10】
{
	return rand() % (end - start + 1) + start;  //万能公式，任意闭区间内的随机值
}

void SetMine(char mine[][COL], int row, int col)
{
	srand((unsigned long)time(NULL));  //种子，供rand函数生成随机值
	int count = 0;
	while (count<MINE_NUM){  //生成MINE_NUM个随机坐标
		int x = GetRandIndex(1, 10);
		int y = GetRandIndex(1, 10);
		if (mine[x][y] == '0'){  //当埋雷空间为空时，符合埋雷条件，将其置'1'
			mine[x][y] = '1';
			count++;
		}
	}
}

char GetMines(char mine[][COL],int row,int col)
{  //获取以该坐标为中心的九宫格内的外围八个格子中埋雷的总数
	return mine[row - 1][col - 1] + mine[row - 1][col] + mine[row - 1][col + 1] + \
		mine[row][col - 1] + mine[row][col + 1] + \
		mine[row + 1][col - 1] + mine[row + 1][col] + mine[row + 1][col + 1] \
		- 8 * '0' + '0';
}  //mine中存储的为'0' / '1'，都是以字符形式存储，最后返回的结果为字符'0' - '8'中的之一

void ShowBoard(char board[][COL],int row,int col)  //展示“游戏界面”
{
	printf("=============================================\n");
	printf(" \\ ");
	int i;
	for (i = 1; i <= 10; i++){
		printf("|%-3d", i);
	}
	printf(" ||\n");
	printf("----");
	for (i = 1; i <= 10; i++){
		printf("----");
	}
	printf("||\n");
	for (i = 1; i <= 10; i++){
		printf("%-3d", i);
		int j;
		for (j = 1; j <= 10; j++){
			printf("|%-3c", board[i][j]);
		}
		printf(" ||\n----");
		int k;
		for (k = 1; k <= 10; k++){
			printf("----");
		}
		printf("||\n");
	}
	printf("=============================================\n");

}

void OpenMine(char mine[ROW][COL], char board[ROW][COL], int x, int y)  //展开选中坐标周围的空间附近埋雷情况
{  //有雷则不显示，没有雷将显示以该点为中心所在九宫格外围八个点的埋雷总数
	if (mine[x - 1][y - 1] == '0')
	{
		board[x - 1][y - 1] = GetMines(mine, x - 1, y - 1);  //左上
	}
	if (mine[x - 1][y] == '0')
	{
		board[x - 1][y] = GetMines(mine, x - 1, y);  //正上
	}
	if (mine[x - 1][y + 1] == '0')
	{
		board[x - 1][y + 1] = GetMines(mine, x - 1, y + 1);  //右上
	}
	if (mine[x][y - 1] == '0')
	{
		board[x][y - 1] = GetMines(mine, x, y - 1);  //正左
	}
	if (mine[x][y + 1] == '0')
	{
		board[x][y + 1] = GetMines(mine, x, y + 1);  //正右
	}
	if (mine[x + 1][y - 1] == '0')
	{
		board[x + 1][y - 1] = GetMines(mine, x + 1, y - 1);  //左下
	}
	if (mine[x + 1][y] == '0')
	{
		board[x + 1][y] = GetMines(mine, x + 1, y);  //正下
	}
	if (mine[x + 1][y + 1] == '0')
	{
		board[x + 1][y + 1] = GetMines(mine, x + 1, y + 1);  //右下
	}
}


void Game()
{
	int count = TOTAL;  
	char mine[ROW][COL];  //负责存储埋雷坐标，进行判断或修改
	char board[ROW][COL];  //为玩家展示埋雷状况，与玩家进行互动

	//初始化两个数组
	memset(mine, '0', sizeof(mine));  //mine中初始值为'0'
	memset(board, '*', sizeof(board));  //board中初始值为'*'

	SetMine(mine, ROW, COL);  //埋雷
	int x = 0;
	int y = 0;
	while (1){
		Sleep(500);
		ShowBoard(board,ROW,COL);  //先展示“游戏界面”，帮助用户输入坐标
		Sleep(500);
		printf("Please inter a pos<x,y> to clear mine:\n");
		scanf("%d %d", &x, &y);  
		if (x >= 1 && x <= ROW - 2 && y >= 1 && y <= COL - 2){  //输入的点在扫雷空间之内，未越界
			if (mine[x][y] == '1' && count == TOTAL)  //第一次就踩到雷后补救
			{
				mine[x][y] = '0';  //补救，置为没有雷
				char num = GetMines(mine, ROW, COL);  //计算周围埋雷总数
				board[x][y] = num ;  //修改为周围埋雷数
				OpenMine(mine, board, x, y);  //展开周围未埋雷的坐标的埋雷情况
				int ret = 1;
				while (ret)  //在其余有空的地方设置一个雷
				{
					int x = GetRandIndex(1, 10);
					int y = GetRandIndex(1, 10);
					if (mine[x][y] == '0')  //找不是雷的地方布雷
					{
						mine[x][y] = '1';
						ret--;
						break;
					}
				}break;
			}

			if (mine[x][y] == '0'){ //玩家输入的点没有埋雷
				if (board[x][y] != '*'){  //该点之前未被显示出来
					printf("Your input has been exits, Please try again...\n");
					continue;
				}
				else{ 
					char num = GetMines(mine, x, y);
					board[x][y] = num;
					OpenMine(mine, board, x, y);
					count--;
					if (count <= 20){  //排出了所有的雷--->获胜
						printf("===========================You win !===========================\n");
						break;
					}
				}
			}
			else{  //踩到了雷---->输了
				printf("===========================Sorry, You Lost! ===========================\n");
				Sleep(500);
				printf("The Mine is:\n");
				ShowBoard(mine, ROW, COL);
				Sleep(5000);
				printf("\n\n");
				break;
			}
		}
		else{
			printf("Your input is out of limited. Please input again...\n");
		}
	}
	Sleep(1000);
	system("cls");
}