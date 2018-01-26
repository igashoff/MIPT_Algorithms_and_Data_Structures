#include<cstdio>
#include<cstdlib>
struct matrix {
	int rows;
	int columns;
	double* elements;
};

matrix input();
matrix multimat(matrix mat1, matrix mat2);
void output(matrix mat);

int main() {
	matrix mat1 = input();
	matrix mat2 = input();
	if (mat1.columns == mat2.rows) {
		matrix mat = multimat(mat1, mat2);
		output(mat);
		free(mat1.elements);
		free(mat2.elements);
		free(mat.elements);
		getchar();
		getchar();
		return 0;
	}
	else {
		printf("incorrect option\n");
		free(mat1.elements);
		free(mat2.elements);
		getchar();
		getchar();
		return 0;
	}
}

matrix input() {
	matrix mat;
	printf("\nRows: ");
	scanf("%d", &mat.rows);
	printf("\nColumns: ");
	scanf("%d", &mat.columns);
	mat.elements = (double*)malloc(mat.rows*mat.columns*sizeof(double));
	printf("\nMatrix:\n");
	for (int i = 0; i < mat.rows*mat.columns; i++) {
			scanf("%lf", &mat.elements[i]);
		}
		
	printf("\n");
	return mat;
	}

matrix multimat(matrix mat1, matrix mat2) {
	matrix mat;
	mat.rows = mat1.rows;
	mat.columns = mat2.columns;
	mat.elements = (double*)malloc(mat.rows*mat.columns*sizeof(double));

	for (int i = 0; i < mat.rows*mat.columns; i++) {
		mat.elements[i] = 0;
	}

	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.columns; j++) {
			double sum = 0;
			int k = 0;
			while (k < mat1.columns) {
				sum += mat1.elements[k + i*mat1.columns] * mat2.elements[j + k*mat2.columns];
				k++;
			}
			mat.elements[j + i*mat.columns] = sum;
		}
	}
	return mat;
}

void output(matrix mat) {
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.columns; j++) {
			printf("%lf  ", mat.elements[j + i*mat.columns]);
		}	
		printf("\n");
	}
}