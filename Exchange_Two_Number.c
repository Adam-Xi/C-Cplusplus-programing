#include<stdio.h>
#include<Windows.h>

int main()
{
	int A = 101, B = 202;
	printf("before interchange:A=%d,B=%d\n", A, B);
	//加减法交换
	A = A + B;
	B = A - B;
	A = A - B;

	/*
	//乘除法交换
	A = A*B;
	B = A / B;
	A = A / B;
	*/

	/*
	//异或法交换
	A ^= B; //A = A ^ B ;
	B ^= A; //B = B ^ A ;==> B = B ^ ( A ^ B ) = ( B ^ B ) ^ A = 0 ^ A = A ;
	A ^= B; //A = A ^ B ;==> A = ( A ^ B ) ^ A = ( A ^ A ) ^ B = 0 ^ B = B ;
	*/

	printf("after interchange:A=%d,B=%d\n", A, B);
	system("pause");
	return 0;
}
