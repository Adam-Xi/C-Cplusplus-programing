#include "mine.h"

int GetRandIndex(int start, int end)  //��ȡ���ֵ��Ϊ�׵ĺ������꡾1,10��
{
	return rand() % (end - start + 1) + start;  //���ܹ�ʽ������������ڵ����ֵ
}

void SetMine(char mine[][COL], int row, int col)
{
	srand((unsigned long)time(NULL));  //���ӣ���rand�����������ֵ
	int count = 0;
	while (count<MINE_NUM){  //����MINE_NUM���������
		int x = GetRandIndex(1, 10);
		int y = GetRandIndex(1, 10);
		if (mine[x][y] == '0'){  //�����׿ռ�Ϊ��ʱ����������������������'1'
			mine[x][y] = '1';
			count++;
		}
	}
}

char GetMines(char mine[][COL],int row,int col)
{  //��ȡ�Ը�����Ϊ���ĵľŹ����ڵ���Χ�˸����������׵�����
	return mine[row - 1][col - 1] + mine[row - 1][col] + mine[row - 1][col + 1] + \
		mine[row][col - 1] + mine[row][col + 1] + \
		mine[row + 1][col - 1] + mine[row + 1][col] + mine[row + 1][col + 1] \
		- 8 * '0' + '0';
}  //mine�д洢��Ϊ'0' / '1'���������ַ���ʽ�洢����󷵻صĽ��Ϊ�ַ�'0' - '8'�е�֮һ

void ShowBoard(char board[][COL],int row,int col)  //չʾ����Ϸ���桱
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

void OpenMine(char mine[ROW][COL], char board[ROW][COL], int x, int y)  //չ��ѡ��������Χ�Ŀռ丽���������
{  //��������ʾ��û���׽���ʾ�Ըõ�Ϊ�������ھŹ�����Χ�˸������������
	if (mine[x - 1][y - 1] == '0')
	{
		board[x - 1][y - 1] = GetMines(mine, x - 1, y - 1);  //����
	}
	if (mine[x - 1][y] == '0')
	{
		board[x - 1][y] = GetMines(mine, x - 1, y);  //����
	}
	if (mine[x - 1][y + 1] == '0')
	{
		board[x - 1][y + 1] = GetMines(mine, x - 1, y + 1);  //����
	}
	if (mine[x][y - 1] == '0')
	{
		board[x][y - 1] = GetMines(mine, x, y - 1);  //����
	}
	if (mine[x][y + 1] == '0')
	{
		board[x][y + 1] = GetMines(mine, x, y + 1);  //����
	}
	if (mine[x + 1][y - 1] == '0')
	{
		board[x + 1][y - 1] = GetMines(mine, x + 1, y - 1);  //����
	}
	if (mine[x + 1][y] == '0')
	{
		board[x + 1][y] = GetMines(mine, x + 1, y);  //����
	}
	if (mine[x + 1][y + 1] == '0')
	{
		board[x + 1][y + 1] = GetMines(mine, x + 1, y + 1);  //����
	}
}


void Game()
{
	int count = TOTAL;  
	char mine[ROW][COL];  //����洢�������꣬�����жϻ��޸�
	char board[ROW][COL];  //Ϊ���չʾ����״��������ҽ��л���

	//��ʼ����������
	memset(mine, '0', sizeof(mine));  //mine�г�ʼֵΪ'0'
	memset(board, '*', sizeof(board));  //board�г�ʼֵΪ'*'

	SetMine(mine, ROW, COL);  //����
	int x = 0;
	int y = 0;
	while (1){
		Sleep(500);
		ShowBoard(board,ROW,COL);  //��չʾ����Ϸ���桱�������û���������
		Sleep(500);
		printf("Please inter a pos<x,y> to clear mine:\n");
		scanf("%d %d", &x, &y);  
		if (x >= 1 && x <= ROW - 2 && y >= 1 && y <= COL - 2){  //����ĵ���ɨ�׿ռ�֮�ڣ�δԽ��
			if (mine[x][y] == '1' && count == TOTAL)  //��һ�ξͲȵ��׺󲹾�
			{
				mine[x][y] = '0';  //���ȣ���Ϊû����
				char num = GetMines(mine, ROW, COL);  //������Χ��������
				board[x][y] = num ;  //�޸�Ϊ��Χ������
				OpenMine(mine, board, x, y);  //չ����Χδ���׵�������������
				int ret = 1;
				while (ret)  //�������пյĵط�����һ����
				{
					int x = GetRandIndex(1, 10);
					int y = GetRandIndex(1, 10);
					if (mine[x][y] == '0')  //�Ҳ����׵ĵط�����
					{
						mine[x][y] = '1';
						ret--;
						break;
					}
				}break;
			}

			if (mine[x][y] == '0'){ //�������ĵ�û������
				if (board[x][y] != '*'){  //�õ�֮ǰδ����ʾ����
					printf("Your input has been exits, Please try again...\n");
					continue;
				}
				else{ 
					char num = GetMines(mine, x, y);
					board[x][y] = num;
					OpenMine(mine, board, x, y);
					count--;
					if (count <= 20){  //�ų������е���--->��ʤ
						printf("===========================You win !===========================\n");
						break;
					}
				}
			}
			else{  //�ȵ�����---->����
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