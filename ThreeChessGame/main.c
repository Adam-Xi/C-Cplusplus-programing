#include "chess.h"

void ShowMenu()
{
	system("cls");
	printf("======Welcome play the game=====\n");
	printf("================================\n");
	printf("========  1¡¢Play  =============\n");
	printf("========  2¡¢Exit  =============\n");
	printf("================================\n");
	printf("================================\n");

	printf("Please Select: \n");

}

int main()
{
	int select = 0;
	int quit = 0;
	while (!quit){
		ShowMenu();
		scanf("%d", &select);
		Sleep(500);
		system("cls");
		switch (select){
		case 1:
			Game();
			break;
		case 2:
			printf("Bye-bye!\n");
			quit = 1;
			break;
		default:
			printf("select error, try again!\n");
			break;
		}
	}
	system("pause");
	return 0;
}