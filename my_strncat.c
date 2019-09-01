#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<assert.h>


char *my_strcat(char *des, const char *src)
{
	char *ret = des;
	assert(des != NULL);
	assert(src != NULL);

	while (*des){
		des++;
	}
	while (*des++ = *src++);

	return ret;
}
char *my_strncat(char *des, const char *src, int num)
{
	char *ret = des;
	assert(des != NULL);
	assert(src != NULL);
	
	while (*des != '\0'){
		des++;
	}
	while (num--){
		*des = *src;
		if (*src == '\0'){
			break;
		}
		des++;
		src++;
	}
	return ret;
}


int main()
{
	char destination[20] = "hello !";
	char *source = " world!";
	my_strncat(destination, source, 10);
	printf("%s", destination);

	system("pause");
	return 0;
}
