#include<stdio.h>
#include<Windows.h>
#pragma warning (disable:4996)

int Recursion_Factorial(int n) 
{
	if (1 == n){
		return 1;
	}
	else{
		return n * Recursion_Factorial(n - 1);
	}
}

int Factorial(int n) //�ǵݹ���׳�
{
	int res = 1;
	while (n){
		res *= n;
		n--;
	}
	return res;
}

int main()
{
	int num;
	int res1 = 0;//int��������12��治��
	int res2 = 0;
/*	
    	long res = 0;--------long������ͬ��12��ʹ治���ˣ����ִ���
	long int res = 0;--------long int15�Ժ�ͻ����
	long long int res = 0;---------ͬ����15�Ժ�治��
*/
	printf("Enter a number to calculate:");
	scanf("%d", &num);
	res1 = Recursion_Factorial(num);
	printf("Recursion_Factorial=%d\n", res1);

	res2 = Factorial(num);
	printf("Factrial=%d\n", res2);

	system("pause");
	return 0;
}

//�����׳�
/*
#include <stdio.h>
#include<Windows.h>
#pragma warning (disable:4996)

#define N 10000

int main()
{
	int a[N] = { 1 };
	int k = 0, length = 1;
	int num;
	int i, j;
	printf("Enter a number to calculate its factorial:\n");
	scanf("%d", &num);
	for (i = 1 ; i <= num; i++)
	{
		for (j = 0; j<length; j++)
		{
			a[j] = a[j] * i + k;
			k = a[j] / 10000;
			a[j] = a[j] % 10000;
		}
		if (k)
		{
			a[j] = k;
			length++;
			k = 0;
		}
	}
	printf("%d", a[length - 1]);
	for (i = length - 2; i >= 0; i--)
		printf("%d", a[i]);
	printf("\n");
	system("pause");
	return 0;
}


*/

