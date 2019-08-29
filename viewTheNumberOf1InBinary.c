#include<stdio.h>

/*
int count_one_bits(unsigned int value)
{
	int count = 0;
	while (value){
		if (value % 2 == 1){
			count++;
		}
		value /= 2;
	}
	return count;
}
*/
/*
//在32为系统下，需判断32次
int count_one_bits(int value)
{
	int count = 0;
	int c = 0;
	while (c < 32){
		if (value & 1){
			count++;
		}
		value >>= 1;
		c++;
	}
	return count;
}
*/
//每一次循环就会判断出来一个1
int count_one_bits(unsigned int value)
{
	int count = 0;
	while (value){
		count++;
		value &= (value - 1);
	}
	return count;
}
int main()
{
	int number = 0;
	int count = 0;
	printf("请输入一个数用以计算其二进制中1的个数：");
	scanf("%d", &number);
	
	count=count_one_bits(number);
	printf("%d", count);
	
	return 0;
}
