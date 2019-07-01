#include <stdio.h>
#include <windows.h>
#pragma warning (disable:4996)
 
int _add(int x, int y)
{
	return x + y;
}
 
int _sub(int x, int y)
{
	return x - y;
}
 
int _mul(int x, int y)
{
	return x * y;
}
 
int _div(int x, int y)
{
	if (!y)
	{
		printf("div  zero!\n");
		return -1;
	}
	return x / y;
}
 
int _mod(int x, int y)
{
	if (!y)
	{
		printf("mod  zero!\n");
		return -1;
	}
	return x % y;
}
int _quit(int x, int y)
{
	printf("Exit.......Done\n");
	int i = 5;
	while (i)
	{
		printf("quit   seconds.......%d\r", i--);
		Sleep(1000);
	}
	exit(1);
}
 
void Showmemu()
{
	printf("########################################\n");
	printf("## 1、ADD        2、SUB       3、MUL  ##\n");
	printf("## 4、DIV        5、MOD       0、EXIT ##\n");
	printf("########################################\n");
	printf("Please Select :");
}
int main()
{
	int x, y;
	int input = 1;
	int result = 0;
	const char *pos = " +-*/%";
	int(*p[6])(int x, int y) = { _quit, _add, _sub, _mul, _div, _mod }; //函数指针数组
	for (;;)
	{	
		Showmemu();
		scanf("%d", &input);
		if (input == 0)
		{
			p[0](-1, -1);//调用倒计时退出程序
		}
		else if (input <= 5 && input >= 1)
		{
			printf("Enter <x,y> :");
			scanf("%d %d", &x, &y);
			result = (*p[input])(x, y);//通过函数指针数组调用函数
			if (result == -1)//除0操作
			{
				printf("Select error !  Please try again!\n");
				continue;//跳过下方内容，直接进行下次循环
			}
			system("cls");//清屏操作
			printf("%d %c %d = %d\n", x, pos[input], y, result);
		}
		else
		{
			system("cls");
			printf("Select error ! Please try again! \n");		
		}
	}
	system("pause");
	return 0;
}