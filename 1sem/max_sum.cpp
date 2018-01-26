#include <cstdio>
#define N 5

int main() {
	int a[N];
	int i;
	for (i = 0; i < N; i++) {
		scanf("%d", &a[i]);
	}
	int sum = *a;                                        //����� ���� ��-��� �� �����, ��� ��� ����� ������ 0
	int maxsum = *a;                                     //������������ �� ���� sum
	int begin = 0;										 //������ ��-��, ����� ������� ����� sum ����������
	int beg = 0;                                         //������ ���������� ��-�� � maxsum
	int end = 0;										 //������ ��������� ��-�� � maxsum
	int minus = 0;                                       //������� ��������������� ��-��� � �������
	for (i = 0; i < N; i++) {
		(a[i] <= 0) ? minus += 1 : minus = minus;        //�������, ������� ��������������� ��-��� � ����� �������
	}
	if (minus == N) {                                    //���� � �� ������ ��������������� ��-��, 
		int max = a[0];
		beg = end = 0;
		for (i = 1; i < N; i++) {
			if (a[i] > max) {
				max = a[i];                              //�� ����� - ��� ���������� ��-�
				beg = end = i;
			}
		}
	}
	else {
		for (i = 1; i < N; i++) {                        //���� � ������� ���� ������������� ��-��, �� ������� ���������� �����
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