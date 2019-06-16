#include "mine.h"

void Menu()  //菜单函数， 显示导向
{
	printf("========================================\n");
	printf("=====Welcome To Mine_sweeping Games=====\n");
	printf("========================================\n");
	printf("=====1、PLAY     ======     2、EXIT=====\n");
	printf("========================================\n");
	printf("Please Select...\n");
}

int main()
{
	int select = 0;
	int quit = 0;
	while (!quit){
		Menu();
		scanf("%d", &select);
		system("cls");
		switch (select){
		case 1:  //玩游戏
			Game();
			break;
		case 2:
			printf("Bye-bye...\n");  //退出
			quit = 1;
			break;
		default:
			printf("Your select is no-exit, Please select again!\n");  //输入的选择错误
			break;
		}

	}
	system("pause");
	return 0;
}
