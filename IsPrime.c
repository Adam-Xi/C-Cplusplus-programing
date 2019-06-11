#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<math.h>

#define N 100000

//���淽��---�Գ���
int IsPrime(int num)
{
	int i;
	if (num <= 1){
		return 0;
	}
	if (num == 2){
		return 1;
	}
	for (i = 2; i < num; i++){
		if (num%i == 0){
			return 0;
		}
	}
	return 1;
}
//�Գ����ļ�
int IsPrime2(int num)
{
	int i;
	if (num % 2 == 0){
		return 0;
	}
	for (i = 3; i < sqrt(num); i += 2){
		if (num%i == 0){
			return 0;
		}
	}
	return 1;
}
int main()
{
	int i, top = N;
	int start = clock();
	for (i = 2; i <= top; i++){
		if (IsPrime(i)){
			printf("%d ", i);
		}
	}
	int end = clock();
	printf("\n����ʱ�䣺%d\n", end - start);
	system("pause");
	return 0;
}
/*
//ɸѡ��
int flag[100000];

void IsPrime()
{
	int i, j;
	for (i = 2; i <= N; i++){   //InitArray
		flag[i] = 1;
	}
	for (i = 2; i <= N; i++){
		if (flag[i]){
			printf("%d ", i);
		}
		for (j = 2 * i; j <= N; j += i){
			flag[j] = 0;
		}
	}
}
int main()
{
	int start = clock();
	IsPrime();
	int end = clock();
	printf("\n��������ʱ�䣺%d", end - start);
	system("pause");
	return 0;
}
*/