/********************************************************************************************
�ַ�������

��Ŀ������
ʵ��һ�����������������ַ����е�k���ַ��� 
ABCD����һ���ַ��õ�BCDA 
ABCD���������ַ��õ�CDAB 

**********************************************************************************************/
void reverse(char *left, char *right)
{//���ú���
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
	//��������
	reverse(str, str + k - 1);
	reverse(str + k, str + len - 1);
	reverse(str, str + len - 1);
}


/***********************************************************
�ж��ַ����Ƿ�����

��Ŀ������
�ж�һ���ַ����Ƿ�Ϊ����һ���ַ�����ת֮����ַ����� 
���磺����s1 =AABCD��s2 = BCDAA������1 
����s1=abcd��s2=ACBD������0. 

AABCD����һ���ַ��õ�ABCDA 
AABCD���������ַ��õ�BCDAA 

AABCD����һ���ַ��õ�DAABC

**************************************************************/


void reverse(char *left, char *right)
{//���ú���
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
	//��������
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
//"abcd"------>"abcdabcd"    ƴ��
int Is_left_move2(char *arr, const char *p)
{
	assert(arr != NULL&&p != NULL&&strlen(arr) == strlen(p));
	int len = strlen(arr);
	strncat(arr, arr, len);  //��Ҫע���ַ�������ĳ��ȣ���������Խ�磬�������
	if (strstr(arr, p) != NULL){  //strstr()��������char * ����
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
