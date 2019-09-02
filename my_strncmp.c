#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<assert.h>

char *my_strcmp(const char *str1, const char *str2)
{
	int ret = 0;
	assert(str1 != NULL);
	assert(str2 != NULL);

	while (!(ret = *(unsigned char *)str1 - *(unsigned char *)str2) && *str2){
		++str1;
		++str2;
	}
	if (ret < 0){
		ret = -1;
	}
	else if (ret > 0){
		ret = 1;
	}
	else{
		ret = 0;
	}

	return ret;
}
char *my_strncmp(const char *str1, const char *str2, int num)
{
	int ret = 0;
	assert(str1 != NULL);
	assert(str2 != NULL);

	while (num--){
		if (*str1 == *str2){
			str1++;
			str2++;
		}
		else{
			ret = *str1 - *str2;
			break;
		}
	}

	if (ret < 0){
		ret = -1;
	}
	else if (ret > 0){
		ret = 1;
	}
	else{
		ret = 0;
	}

	return ret;
}

int main()
{
	char *str1 = "hello world!";
	char *str2 = "hallo world?";

	int ret = my_strncmp(str1, str2, 11);

	if (ret == 0){
		printf("equal!");
	}
	else if (ret == -1){
		printf("str1 < str2!");
	}
	else if (ret == 1){
		printf("str1 > str2!");
	}

	system("pause");
	return 0;
}
