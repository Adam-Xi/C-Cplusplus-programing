//方法一：


    //分离奇偶序列函数
    void getSequence(int o[], int e[], int value)
    {
    	int c = 0;  //控制循环变量
    	int m = 0, n = 0;  //分别控制等待存的数组的下标
    	while (c < 32){
    		if (c % 2 == 0){  //也可以为 c&1 ，判断c的奇偶
    			o[m] = value & 1;
    			m++;
    		}
    		else{
    			e[n] = value & 1;
    			n++;
    		}
    		value >>= 1;
    		c++;
    	}
    }



//方法2
void getSequence(int num)//全部从左边开始，不改变输入的数的原值，只是在其基础上向右移动一定的位数
{
	int i = 0;
	//偶数
	printf("偶数位序列为：");
	for (i = 31; i >= 1; i -= 2){
		printf("%d ", (num >> i) & 1);
	}
	printf("\n");
	//奇数
	printf("奇数位序列为：");
	for (i = 30; i >= 0; i -= 2){
		printf("%d ", (num >> i) & 1);
	}
	printf("\n");
}
    //将数分解为二进制序列函数
    void FullSequence(int f[],int value)
    {
    	int c = 0;
    	while (c < 32){
    		if (value & 1){
    			f[c] = value & 1;
    		}
    		else{
    			f[c] = value & 1;
    		}
    		value >>= 1;
    		c++;
    	}
    }
    void PrintArr(int a[],int Max)
    {
    	int i = Max-1;
    	for (; i >=0; i--){
    		printf("%d ", a[i]);
    	}
    	printf("\n");
    }
int main()
{
	int odd[16] = { 0 };
	int even[16] = { 0 };
	int full[32] = { 0 };
	int number = 0;
	printf("请输入一个数用以分离它的二进制奇偶序列：");
	scanf("%d", &number);
	//将输入的数以二进制形式输出
	FullSequence(full, number);
	PrintArr(full, 32);
	//分离奇偶序列
	getSequence(odd,even,number);
	//输出
	printf("偶数位序列为 ：");
	PrintArr(odd,16);
	printf("奇数位序列为 ：");
	PrintArr(even,16);
	system("pause");
	return 0;
} 

***********************************************************************************
***********************************************************************************

int Compare_By_Bit(int m, int n)
{
	int count = 0;
	//若m，n有一个不为零，不然存在不相同的位，故仍需进行比较，直到两者都为零为止
	while (m || n){
		if ((m & 1) != (n & 1)){  //两者分别求最低位的值，进行比较
			count++;
		}
		m >>= 1;  //移位，右移一位，比较下一位
		n >>= 1;
	}
	return count;
}

//将数分解为二进制序列
void FullSequence(int f[], int value)
{
	int c = 0;
	while (c < 32){
		if (value & 1){
			f[c] = value & 1;
		}
		else{
			f[c] = value & 1;
		}
		value >>= 1;
		c++;
	}
}

//输出
void PrintArr(int a[], int Max)
{
	int i = Max - 1;
	for (; i >= 0; i--){
		printf("%d ", a[i]);
	}
	printf("\n");
}
#include<stdio.h>
#include<Windows.h>
#pragma warning (disable:4996)

int main()
{
	int m, n;
	int res = 0;
	int fulla[32] = { 0 };
	int fullb[32] = { 0 };

	printf("输入两个数以进行位比较：");
	scanf("%d %d", &m, &n);

	FullSequence(fulla, m);
	PrintArr(fulla,32);
	
	FullSequence(fullb, n);
	PrintArr(fullb, 32);

	res=Compare_By_Bit(m, n);
	printf("不相同的位数有 %d 个 \n", res);

	system("pause");
	return 0;
}
