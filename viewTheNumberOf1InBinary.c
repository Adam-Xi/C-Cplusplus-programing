#include<stdio.h>
#include<Windows.h>
#pragma warning (disable:4996)
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
//��32Ϊϵͳ�£����ж�32��
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
//ÿһ��ѭ���ͻ��жϳ���һ��1
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
	printf("������һ�������Լ������������1�ĸ�����");
	scanf("%d", &number);
	
	count=count_one_bits(number);
	printf("%d", count);
	
	system("pause");
	return 0;
}
