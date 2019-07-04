#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<assert.h>

int my_strlen(const char *str)  //计数器方法
{
	int count = 0;
	while (*str){
		count++;
		str++;
	}
	return count;
}
int my_strlen2(const char *str)  //不创建临时变量计数器
{
	if (*str == '\0'){
		return 0;
	}
	else{
		return my_strlen(str++) + 1;
	}
}
int my_strlen3(char *str)  //指针减指针的方式
{
	char *p = str;
	while (*p != '\0'){
		p++;
	}
	return p - str;
}

char *my_strcpy(char *des, const char *src)
{
	char *ret = des;
	assert(des != NULL);
	assert(src != NULL);
	
	while (*des++ = *src++);

	return ret;
}
char *my_strncpy(char *des, const char *src, int num)
{
	char *ret = des;
	assert(des != NULL);
	assert(src != NULL);
	int len = my_strlen(src);
	int i = 0;
	if (len >= num){
		while (i < num){
			*des = *src;
			des++;
			src++;
			i++;
		}
	}
	else{
		while (i < len){
			*des = *src;
			des++;
			src++;
			i++;
		}
		while (i < num){
			*des = 0;
			des++;
			i++;
		}
	}
	return ret;
}


int main()
{

	char destination[20] = { 0 };
	char *source = "hello world!";
	my_strncpy(destination, source, 7);  //拷贝7个字符
	printf("%s\n", destination);

	system("pause");
	return 0;
}