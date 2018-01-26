#include <cstdio>
#define N 5

int main() {
	int a[N];
	int i;
	for (i = 0; i < N; i++) {
		scanf("%d", &a[i]);
	}
	int sum = *a;                                        //сумма всех эл-тов до места, где она стала меньше 0
	int maxsum = *a;                                     //максимальная из всех sum
	int begin = 0;										 //индекс эл-та, перед которым сумма sum обнулилась
	int beg = 0;                                         //индекс начального эл-та в maxsum
	int end = 0;										 //индекс конечного эл-та в maxsum
	int minus = 0;                                       //счетчик неположительных эл-тов в массиве
	for (i = 0; i < N; i++) {
		(a[i] <= 0) ? minus += 1 : minus = minus;        //считаем, сколько неположительных эл-тов в нашем массиве
	}
	if (minus == N) {                                    //если в нём только неположительные эл-ты, 
		int max = a[0];
		beg = end = 0;
		for (i = 1; i < N; i++) {
			if (a[i] > max) {
				max = a[i];                              //то ответ - это наибольший эл-т
				beg = end = i;
			}
		}
	}
	else {
		for (i = 1; i < N; i++) {                        //если в масииве есть положительные эл-ты, то находим наибольшую сумму
			if ((sum + a[i]) >= 0) {
				sum = sum + a[i];
				if (sum > maxsum) {
					maxsum = sum;
					beg = begin;
					end = i;
				}
			}
			else {
				begin = i + 1;
				sum = 0;
			}
		}
	}
	printf("Begin:%d\nEnd:%d\n", beg, end);
	getchar();
	getchar();
	return 0;
}