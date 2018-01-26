#include<cstdio>
#include<cstdlib>
struct matrix {
	int rows;
	int columns;
	double *elements;
};

matrix input(FILE *f);
matrix multimat(matrix mat1, matrix mat2);
void output(FILE *f, matrix mat);

int main() {
	FILE *f1 = fopen("mat1.txt", "r");
	FILE *f2 = fopen("mat2.txt", "r");
	FILE *f = fopen("multimatrix.txt", "w");
	if ((f1 == NULL) || (f2 == NULL)) {
		fprintf(f, "The file with matrix is not found\n");
		fclose(f1);
		fclose(f2);
		return 0;
	}
	else {
		matrix mat1 = input(f1);
		matrix mat2 = input(f2);
		if (mat1.columns == mat2.rows) {
			matrix mat = multimat(mat1, mat2);
			output(f, mat);
			free(mat1.elements);
			free(mat2.elements);
			free(mat.elements);
			return 0;
		}
		else {
			fprintf(f, "Incorrect option\n");
			free(mat1.elements);
			free(mat2.elements);
			return 0;
		}
	}
}

matrix input(FILE *f) {
	matrix mat;
	fscanf(f, "%d", &mat.rows);
	fscanf(f, "%d", &mat.columns);
	mat.elements = (double*)malloc(mat.rows*mat.columns*sizeof(double));
	for (int i = 0; i < mat.rows*mat.columns; i++) {
		fscanf(f, "%lf", &mat.elements[i]);
	}
	fclose(f);
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

void output(FILE *f, matrix mat) {
	fprintf(f, "Multimatrix:\n");
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.columns; j++) {
			fprintf(f, "%lf  ", mat.elements[j + i*mat.columns]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}