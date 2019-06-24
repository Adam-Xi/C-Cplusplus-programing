/********************************************************************************************
字符串左旋

题目描述：
实现一个函数，可以左旋字符串中的k个字符。 
ABCD左旋一个字符得到BCDA 
ABCD左旋两个字符得到CDAB 

**********************************************************************************************/
void reverse(char *left, char *right)
{//逆置函数
	while (left < right){
		char temp = *left;
		*left = *right;
		*right = temp;
	}
}
void left_move(char *str, int k)
{
	int len = strlen(str);
	assert(str != NULL && k <= len);
	if (str == NULL || k>len){
		return;
	}
	//三步逆置
	reverse(str, str + k - 1);
	reverse(str + k, str + len - 1);
	reverse(str, str + len - 1);
}


/***********************************************************
判断字符串是否左旋

题目描述：
判断一个字符串是否为另外一个字符串旋转之后的字符串。 
例如：给定s1 =AABCD和s2 = BCDAA，返回1 
给定s1=abcd和s2=ACBD，返回0. 

AABCD左旋一个字符得到ABCDA 
AABCD左旋两个字符得到BCDAA 

AABCD右旋一个字符得到DAABC

**************************************************************/


void reverse(char *left, char *right)
{//逆置函数
	while (left < right){
		char temp = *left;
		*left = *right;
		*right = temp;
	}
}
void left_move(char *str, int k)
{
	int len = strlen(str);
	assert(str != NULL && k <= len);
	if (str == NULL || k>len){
		return;
	}
	//三步逆置
	reverse(str, str + k - 1);
	reverse(str + k, str + len - 1);
	reverse(str, str + len - 1);
}

int Is_left_move1(char *arr, const char *p)
{
	assert(arr != NULL&&p != NULL&&strlen(arr) == strlen(p));
	int len = strlen(arr);
	int i = 0;
	for (; i < len; i++){
		left_move(arr, 1);
		if (!strcmp(arr, p)){
			return 1;
		}
	}
	return 0;
}
//"abcd"------>"abcdabcd"    拼接
int Is_left_move2(char *arr, const char *p)
{
	assert(arr != NULL&&p != NULL&&strlen(arr) == strlen(p));
	int len = strlen(arr);
	strncat(arr, arr, len);  //需要注意字符串定义的长度，否则数组越界，程序崩溃
	if (strstr(arr, p) != NULL){  //strstr()函数返回char * 类型
		return 1;
	}
	return 0;
}

void find_two_dif_num(int *arr, int len, int *px, int *py)
{
	int res = 0;
	int i;
	for (i = 0; i < len; i++){
		res ^= *(arr + i);
	}
	int pos = 1;
	for (; pos <= 32; pos++){
		if ((res >> pos) & 1){
			break;
		}
	}

	for (i = 0; i < len; i++){
		if ((*(arr + i) >> pos) & 1){
			*px ^= *(arr + i);
		}
		else{
			*py ^= *(arr + i);
		}
	}
}
