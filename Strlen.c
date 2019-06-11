#include<stdio.h>
#include<Windows.h>

int Recursion_Strlen(const char *string)//�ݹ飺���������ڵݹ飬����������㣩�������� '\0' Ϊ�ݹ�����㣬����ȷ��ֵ���������⣬���Ϸ�����ֵ��ֱ������㣬ǡ���ۼ����ַ�������
{
	if (*string == '\0'){
		return 0;
	}
	else{
		return (Recursion_Strlen(string+1)) + 1;
	}
}
/*
int Recursion_Strlen(const char *string) //�ݹ龫���
{
	return ('\0' != *string) ? (Recursion_Strlen(string++) + 1) : 0;
}
*/
int Strlen(const char *string)//�ǵݹ�
{
	int count = 0;
	while (*string != '\0'){
		count++;
		string += 1;
	}
	return count;
}

int Pointer_Strlen(char *string)//ָ��Ӽ����������ַ����׵�ַ����ƶ��Ĵ�����Ϊ�ֽ�����ֱ������ '\0' Ϊֹ
{
	char *p = string;
	while (*p != '\0'){
		p++;
	}
	return p - string;
}

int main()
{
    //�ݹ�
	const char *p = "abcdefg";
	int Recursion_count = 0;
	Recursion_count = Recursion_Strlen(p);
	printf("Recursion_count=%d\n", Recursion_count);
    //�ǵݹ飬һ���㷨
	int count = 0;
	count = Strlen(p);
	printf("count=%d\n", count);
    //�ǵݹ飬ָ��Ӽ���
	int pointer_count = 0;
	pointer_count = Pointer_Strlen(p);
	printf("Pointer_Strlen=%d\n", pointer_count);

	system("pause");
	return 0;
}
