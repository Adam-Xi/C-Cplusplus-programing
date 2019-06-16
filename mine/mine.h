#ifndef _MINE_H_
#define _MINE_H_

#include<stdio.h>
#include<windows.h>
#include<time.h>

#define ROW 12  //行 10+2
#define COL 12  //列 10+2
#define MINE_NUM 20  //买下雷的数目
#define TOTAL 10*10  //10*10有效的空间

#pragma  warning (disable:4996)

void Game();  

int GetRandIndex(int start, int end);

void SetMine(char mine[][COL], int row, int col);

char GetMines(char mine[][COL], int row, int col);

void ShowBoard(char board[][COL], int row, int col);

void OpenMine(char mine[ROW][COL], char board[ROW][COL], int x, int y);


#endif