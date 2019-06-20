//直接插入排序

#include<stdio.h>
#include<windows.h>
 
void Insert_Sort(int *a,int num)
{
	int i, j;
	int temp;
	for (i = 1; i < num; i++) {
		temp = a[i];  //将待插入的值存入temp中
		for (j = i; j >= 0; j--) {
			if (a[j - 1] > temp) {
				a[j] = a[j - 1];  //后移
			}
			else {
				a[j] = temp;  //插入
				break;
			}
		}
	}
}
 
void Print(int *a,int num)
{
	int i;
	for (i = 0; i < num; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
}
int main()
{
	int arr[] = { 48, 62, 35, 77, 55, 14, 35, 98 };
	int len = sizeof(arr) / sizeof(arr[0]);
	Insert_Sort(arr, len);
	Print(arr, len);
	system("pause");
	return 0;
 
}



//折半插入排序
#include<stdio.h>
#include<windows.h>
 
void Print(int *a,int num)
{
	int i;
	for (i = 0; i < num; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
}
 
void Bin_Sort(int *a, int num)
{
	int i, j;
	int low, high, mid;
	int temp;
	for (i = 1; i < num; i++){
		temp = a[i]; //待插入的元素
		low = 0;   
		high = i - 1;
		while (low <= high){
			mid = (low + high) / 2;  //折半
			if (temp < a[mid]){
				high = mid - 1;
			}
			else{
				low = mid + 1;
			}
		}
		for (j = i - 1; j >= low; j--){
			a[j + 1] = a[j];
			a[j] = temp;
		}
	}
}
 
int main()
{
	int arr[] = { 48, 62, 35, 77, 55, 14, 35, 98 };
	int len = sizeof(arr) / sizeof(arr[0]);
	Bin_Sort(arr, len);
	Print(arr, len);
 
 
	system("pause");
	return 0;
}


