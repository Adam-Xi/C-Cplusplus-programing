#include<stdio.h>

void YoungMatrix(int arr[][5], int *px, int *py, int key)
{
	int x = 0;
	int y = *py - 1;
	while (x < *px&&y >= 0){
		if (arr[x][y] == key){
			*px = x;
			*py = y;
			return;
		}
		else if (arr[x][y] < key){
			x++;
		}
		else{
			y--;
		}
	}
	*px = -1; //函数若没有在前面跳出，则此处将x，y都置为-1，表示没有查询到
	*py = -1;
}

int main()
{
	int x = 5;
	int y = 5;
	int arr[5][5] = { { 1, 2, 3, 4, 5 }, 
					{ 2, 5, 6, 7, 9 },
					{ 4, 6, 9, 10, 14 }, 
					{ 6, 7, 10, 11, 15 }, 
					{ 8, 10, 12, 15, 16 } };

	YoungMatrix(arr, &x, &y, 8);

	if (x >= 0 && y >= 0 && x < 5 && y < 5){
		printf("Find it!\nThe location is <%d,%d>\n", x, y);
	}
	else{
		printf("No found!\n");
	}

	return 0;

}
