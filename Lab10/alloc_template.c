#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

void print_mat(int rows, int cols, int* t);
void read_mat(int rows, int cols, int* t);
int is_digit(char x);

// 1
////////////////////////////////////////////////////////////

int get(int cols, int row, int col, const int *A) {
	return A[(row * cols) + col];
}

void set(int cols, int row, int col, int *A, int value) {
	A[(row * cols) + col] = value;
}

void prod_mat(int rowsA, int colsA, int colsB, int *A, int *B, int *AB) {
	int value;
	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < colsB; j++) {
			value = 0;

			for (int k = 0; k < colsA; k++) {
				value += get(colsA, i, k, A) * get(colsB, k, j, B);
			}

			set(colsB, i, j, AB, value);
		}
	}
}

void read_mat(int rows, int cols, int *t) {
	int value;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &value);
			set(cols, i, j, t, value);
		}
	}
}

void print_mat(int rows, int cols, int *t) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", get(cols, i, j, t));
		}
		printf("\n");
	}
}

// 2
/////////////////////////////////////////////////////////////

int read_ints_from_line(char* c_buf, int *int_buf) {
	int index = -1, inside_number = 0, minus = 0;

	for (int i = 0; i < (int)strlen(c_buf); i++)
	{
		if (!inside_number && is_digit(c_buf[i]))
		{
			inside_number = 1;
			index++;

			if (c_buf[i] == '-')
			{
				int_buf[index] = 0;
				minus = 1;
			}
			else
				int_buf[index] = (int)(c_buf[i] - '0');
		}
		else if (inside_number && is_digit(c_buf[i]))
		{
			int_buf[index] *= 10;
			int_buf[index] += (int)(c_buf[i] - '0');
		}
		else if (inside_number && !is_digit(c_buf[i]))
		{
			if (minus)
			{
				int_buf[index] *= -1;
				minus = 0;
			}
			inside_number = 0;
		}
	}

	return index + inside_number + 1;
}

int is_digit(char x)
{
	return ('0' <= x && x <= '9') || x == '-';
}

int read_int_lines_cont(int *ptr_array[]) {
	char buff[BUF_SIZE];
	int result = 0, totalNumbers = 0;

	for (int i = 1; i < TAB_SIZE; i++) {
		ptr_array[i] = NULL;
	}

	while (!feof(stdin)) {
		strcpy(buff, "");
		fgets(buff, BUF_SIZE, stdin);

		ptr_array[++result] = &ptr_array[0][totalNumbers];
		totalNumbers += read_ints_from_line(buff, ptr_array[0] + totalNumbers);
	}

	return result;
}

void write_int_line_cont(int *ptr_array[], int n) {
	int *start = ptr_array[n + 1];

	while (start < ptr_array[n + 2]) {
		printf("%d ", *start++);
	}

	printf("\n");
}

// 3
///////////////////////////////////////////////////////////

int read_char_lines(char *array[]) {
	char buffor[BUF_SIZE];
	int result = 0;

	while (!feof(stdin))
	{
		strcpy(buffor, "");
		fgets(buffor, BUF_SIZE, stdin);
		array[result] = malloc(sizeof(char) * (strlen(buffor) + 1));
		strcpy(array[result], buffor);

		if (array[result][strlen(buffor) - 1] == '\n')
			array[result][strlen(buffor) - 1] = '\0';

		result++;
	}

	return result;
}

void write_char_line(char *array[], int n) {
	for (int i = 0; i < strlen(array[n]); i++)
		printf("%c", array[n][i]);
	printf("\n");
}

void delete_lines(char *array[]) {
	for (int i = 0; array[i] != NULL; i++)
		free(array[i]);
}

// 4
////////////////////////////////////////////////

typedef struct {
	int *values;
	int len;
	double average;
} line_type;

int count_nums_in_string(char* array)
{
	int result = 0, inside_number = 0;

	for (int i = 0; i < strlen(array); i++)
	{
		if (!inside_number && is_digit(array[i]))
		{
			inside_number = 1;
			result++;
		}
		else if (inside_number && !is_digit(array[i]))
			inside_number = 0;
	}

	return result;
}

int read_int_lines(line_type lines_array[]) {
	char buffor[BUF_SIZE];
	int result = 0;

	while (!feof(stdin))
	{
		strcpy(buffor, "");
		fgets(buffor, BUF_SIZE, stdin);
		
		lines_array[result].len = count_nums_in_string(buffor);
		lines_array[result].values = malloc(sizeof(int) * lines_array[result].len);

		read_ints_from_line(buffor, lines_array[result].values);
		result++;
	}

	return result - 1;
}

void write_int_line(line_type lines_array[], int n) {
	for (int i = 0; i < lines_array[n].len; i++)
		printf("%d ", lines_array[n].values[i]);

	printf("\n%.2f\n", lines_array[n].average);
}

void delete_int_lines(line_type array[], int line_count) {
	for (int i = 0; i < line_count; i++)
		free(array[i].values);
}

int cmp (const void *a, const void *b) {
	line_type *x = (line_type*)a, *y = (line_type*)b;

	return x->average > y->average ? 1 :
		x->average == y->average ? 0 : -1;
}

void sort_by_average(line_type lines_array[], int line_count) {
	long int sum;
	for (int i = 0; i < line_count; i++)
	{
		sum = 0;
		for (int j = 0; j < lines_array[i].len; j++)
			sum += lines_array[i].values[j];
		lines_array[i].average = (double)sum / lines_array[i].len;
	}

	qsort(lines_array, line_count, sizeof(line_type), cmp);
}

// 5
///////////////////////////////////////////////////////////

typedef struct {
	int r, c, v;
} triplet;

int read_sparse(triplet *triplet_array, int n_triplets) {
	for (int i = 0; i < n_triplets; i++) {
		scanf("%d %d %d", &triplet_array[i].r, &triplet_array[i].c, &triplet_array[i].v);
	}
	return n_triplets;
}

int cmp_triplets(const void *t1, const void *t2) {
	triplet *x = (triplet *)t1, *y = (triplet *)t2;

	if (x->r == y->r) {
		return x->c - y->c;
	}

	return x->r - y->r;
}

void make_CSR(triplet *triplet_array, int n_triplets, int rows, int *V, int *C, int *R) {
	qsort(triplet_array, n_triplets, sizeof(triplet), cmp_triplets);

	int lastRow = 0;
	R[0] = 0;

	for (int i = 0; i < n_triplets; i++) {
		V[i] = triplet_array[i].v;
		C[i] = triplet_array[i].c;

		if (lastRow != triplet_array[i].r) {
			for (int j = lastRow + 1; j <= triplet_array[i].r; j++) {
				R[j] = i;
			}

			lastRow = triplet_array[i].r;
		}
	}

	for (int j = lastRow + 1; j <= rows; j++) {
		R[j] = n_triplets;
	}
}

void multiply_by_vector(int rows, const int *V, const int *C, const int *R, const int *x, int *y) {
	for (int i = 0; i < rows; i++) {
		y[i] = 0;

		for (int j = R[i]; j < R[i + 1]; j++) {
			y[i] += V[j] * x[C[j]];
		}
	}
}

void read_vector(int *v, int n) {
	for (int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}
}

void write_vector(int *v, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}

	printf("\n");
}

// auxiliary
////////////////////////////////////////////////////////////

int read_int(void) {
	char c_buf[BUF_SIZE];
	fgets(c_buf, BUF_SIZE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
	int to_do = read_int();

	int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
	int n, lines_counter, rowsA, colsA, rowsB, colsB;
	int rows, cols, n_triplets;
	char* char_lines_array[TAB_SIZE] = { NULL };
	int continuous_array[TAB_SIZE];
	int* ptr_array[TAB_SIZE];
	triplet triplet_array[TAB_SIZE];
	int V[TAB_SIZE], C[TAB_SIZE], R[TAB_SIZE];
	int x[TAB_SIZE], y[TAB_SIZE];
	line_type int_lines_array[TAB_SIZE];

	switch (to_do) {
		case 1:
			scanf("%d %d", &rowsA, &colsA);
			read_mat(rowsA, colsA, A);
			scanf("%d %d", &rowsB, &colsB);
			read_mat(rowsB, colsB, B);
			prod_mat(rowsA, colsA, colsB, A, B, AB);
			print_mat(rowsA, colsB, AB);
			break;
		case 2:
			n = read_int() - 1; // we count from 1 :)
			ptr_array[0] = continuous_array;
			read_int_lines_cont(ptr_array);
			write_int_line_cont(ptr_array, n);
			break;
		case 3:
			n = read_int() - 1;
			read_char_lines(char_lines_array);
			write_char_line(char_lines_array, n);
			delete_lines(char_lines_array);
			break;
		case 4:
			n = read_int() - 1;
			lines_counter = read_int_lines(int_lines_array);
			sort_by_average(int_lines_array, lines_counter);
			write_int_line(int_lines_array, n);
			delete_int_lines(int_lines_array, lines_counter);
			break;
		case 5:
			scanf("%d %d %d", &rows, &cols, &n_triplets);
			n_triplets = read_sparse(triplet_array, n_triplets);
			read_vector(x, cols);
			make_CSR(triplet_array, n_triplets, rows, V, C, R);
			multiply_by_vector(rows, V, C, R, x, y);
			write_vector(V, n_triplets);
			write_vector(C, n_triplets);
			write_vector(R, rows + 1);
			write_vector(y, rows);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

