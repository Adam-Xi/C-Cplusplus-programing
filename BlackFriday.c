
#include<stdio.h>
#include<windows.h>
#pragma warning (disable:4996)

int Judge_IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
		return 1; //是闰年
	}
	return 0; //是平年
}

int Judge_Month(int year, int month)
{
	if (2 == month){
		if (Judge_IsLeapYear(year) == 1){//闰年2月
			return 29;
		}
		else{//平年2月
			return 28;
		}
	}
	if (month == 4 || month == 6 || month == 9 || month == 11){
		return 30;//小月
	}
	else{
		return 31;//大月
	}

}

void WeekCount(int week[], int total_days, int cur_month)
{
	int cur_13 = total_days - (cur_month - 13);
	switch (cur_13 % 7){
		case 0:week[1]++; break;
		case 1:week[2]++; break;
		case 2:week[3]++; break;
		case 3:week[4]++; break;
		case 4:week[5]++; break;
		case 5:week[6]++; break;
		case 6:week[0]++; break;
		default:break;
	}
}

int main()
{
	int total_days = 0;
	int week[7] = { 0 }; //week[0]:星期六 week[1]:星期日 week[2]:星期一 ......
	int year = 1900;
	int month = 1;

	int n = 0;
	printf("请输入要查询截止的年份：");
	scanf("%d", &n);

	for (; year < 1900 + n; year++){
		for (month = 1; month <= 12; month++){
//			printf("%d:%d----", year, month);
			int cur_month = Judge_Month(year, month);
//			printf("%d\t\t\t", cur_month);
			total_days += cur_month;

			WeekCount(week, total_days, cur_month);
//			printf("%d\n", total_days);
			/*
			printf("\n");
			for (int i = 0; i < 7; i++){
				printf("%d ", week[i]);
			}
			printf("\n");
			*/

		}
	}


	//输出
	printf("\n\n\n");
	for (int i = 0; i < 7; i++){
		printf("%d ", week[i]);
	}

	system("pause");
	return 0;
}
