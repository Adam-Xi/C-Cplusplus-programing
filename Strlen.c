#include<stdio.h>
#include<Windows.h>

int Recursion_Strlen(const char *string)//递归：（自外向内递归，自内向外计算），以遇到 '\0' 为递归结束点，返回确定值，自内向外，不断返回新值，直到最外层，恰好累加至字符串长度
{
	if (*string == '\0'){
		return 0;
	}
	else{
		return (Recursion_Strlen(string+1)) + 1;
	}
}
/*
int Recursion_Strlen(const char *string) //递归精简版
{
	return ('\0' != *string) ? (Recursion_Strlen(string++) + 1) : 0;
}
*/
int Strlen(const char *string)//非递归
{
	int count = 0;
	while (*string != '\0'){
		count++;
		string += 1;
	}
	return count;
}

int Pointer_Strlen(char *string)//指针加减法：根据字符串首地址向后移动的次数作为字节数，直到遇到 '\0' 为止
{
	char *p = string;
	while (*p != '\0'){
		p++;
	}
	return p - string;
}

int main()
{
    //递归
	const char *p = "abcdefg";
	int Recursion_count = 0;
	Recursion_count = Recursion_Strlen(p);
	printf("Recursion_count=%d\n", Recursion_count);
    //非递归，一般算法
	int count = 0;
	count = Strlen(p);
	printf("count=%d\n", count);
    //非递归，指针加减法
	int pointer_count = 0;
	pointer_count = Pointer_Strlen(p);
	printf("Pointer_Strlen=%d\n", pointer_count);

	system("pause");
	return 0;
}
