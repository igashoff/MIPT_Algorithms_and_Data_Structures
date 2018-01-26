#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>

typedef double(*fptr)(double);

double foo1(double x);
double foo2(double x);
double foo3(double x);
double solve(double a, double b, double eps, fptr y);
int signum(double x);

int main() {
	int choice;
	double result;
	double a = 0;
	double b = 3;
	double eps = 0.0001;
	fptr y;
	printf("x^2-1: 1\n");
	printf("x-2: 2\n");
	printf(": 3\n");
	scanf("%d", &choice);
	printf("\n");
	switch (choice) {
		case 1: {
			y = foo1;
			result = solve(a, b, eps, y);
			break;
		}
		case 2: {
			y = foo2;
			result = solve(a, b, eps, y);
			break;
		}
		case 3: {
			y = foo3;
			result = solve(a, b, eps, y);
			break;
		}
		default: {
			printf("Incorrect number\n");
			return 0;
		}
	}

	printf("Result is: %lf\n", result);
	getchar();
	getchar();
	return 0;
}

double foo1(double x) {
	double y = x*x - 1;
	return y;
}

double foo2(double x) {
	double y = x - 2;
	return y;
}

double foo3(double x) {
	double y = x;
	return y;
}

int signum(double x) {
	if (x < 0) {
		return -1;
	}
	else {
		return 1;
		}
}

double solve(double a, double b, double eps, fptr y) {
	int found = 0;
	double result = a - 1;
	double check = result;
	int n = 0;
	while ((n <= 100 ) && (found == 0)) {
		double m = (b + a) / 2;
		if (signum(y(a)) == signum(y(m))) {
			a = m;
			if ((y(a) < eps) && (y(a) > -eps)) {
				result = a;
				found = 1;
			}
		}
		else {
			b = m;
			if ((y(b) < eps) && (y(b) > -eps)) {
				result = b;
				found = 1;
			}

		}
		printf("%f, %f\n", a, b);
		n++;
	}

	if (result == check) {
		printf("NONE\n");
		return -100;
	}
	else {
		return result;
	}
}