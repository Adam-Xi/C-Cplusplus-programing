//����һ��


    //������ż���к���
    void getSequence(int o[], int e[], int value)
    {
    	int c = 0;  //����ѭ������
    	int m = 0, n = 0;  //�ֱ���Ƶȴ����������±�
    	while (c < 32){
    		if (c % 2 == 0){  //Ҳ����Ϊ c&1 ���ж�c����ż
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



//����2
void getSequence(int num)//ȫ������߿�ʼ�����ı����������ԭֵ��ֻ����������������ƶ�һ����λ��
{
	int i = 0;
	//ż��
	printf("ż��λ����Ϊ��");
	for (i = 31; i >= 1; i -= 2){
		printf("%d ", (num >> i) & 1);
	}
	printf("\n");
	//����
	printf("����λ����Ϊ��");
	for (i = 30; i >= 0; i -= 2){
		printf("%d ", (num >> i) & 1);
	}
	printf("\n");
}
    //�����ֽ�Ϊ���������к���
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
	printf("������һ�������Է������Ķ�������ż���У�");
	scanf("%d", &number);
	//����������Զ�������ʽ���
	FullSequence(full, number);
	PrintArr(full, 32);
	//������ż����
	getSequence(odd,even,number);
	//���
	printf("ż��λ����Ϊ ��");
	PrintArr(odd,16);
	printf("����λ����Ϊ ��");
	PrintArr(even,16);
	system("pause");
	return 0;
} 

***********************************************************************************
***********************************************************************************

int Compare_By_Bit(int m, int n)
{
	int count = 0;
	//��m��n��һ����Ϊ�㣬��Ȼ���ڲ���ͬ��λ����������бȽϣ�ֱ�����߶�Ϊ��Ϊֹ
	while (m || n){
		if ((m & 1) != (n & 1)){  //���߷ֱ������λ��ֵ�����бȽ�
			count++;
		}
		m >>= 1;  //��λ������һλ���Ƚ���һλ
		n >>= 1;
	}
	return count;
}

//�����ֽ�Ϊ����������
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

//���
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

	printf("�����������Խ���λ�Ƚϣ�");
	scanf("%d %d", &m, &n);

	FullSequence(fulla, m);
	PrintArr(fulla,32);
	
	FullSequence(fullb, n);
	PrintArr(fullb, 32);

	res=Compare_By_Bit(m, n);
	printf("����ͬ��λ���� %d �� \n", res);

	system("pause");
	return 0;
}
