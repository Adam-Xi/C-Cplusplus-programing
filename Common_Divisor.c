#include<stdio.h>
#include<Windows.h>

int CommonDivisor(int x, int y)
{
	int min = x > y ? y : x;
	while (min > 1){
		if (x%min == 0 && y%min == 0){
			break;
		}
		min--;
	}
	return min;
}
int CommonDivisor2(int x, int y)
{
	while (1){
		if (x > y){
			x = x - y;
		}
		else if (y > x){
			y = y - x;
		}
		else{
			break;
		}
	}
	return x;
}
//Õ·×ªÏà³ý·¨
int CommonDivisor3(int x, int y)
{
	while ((x*y) != 0){
		if (x > y){
			x %= y;
		}
		else if (y > x){
			y %= x;
		}
		else{
			break;
		}
	}
	return x;
}


int main()
{
	int max = CommonDivisor(25, 125);
	printf("%d\n", max);
	system("pause");
	return 0;
}
