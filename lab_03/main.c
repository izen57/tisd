#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include "headers/defines.h"
#include "headers/func_io.h"
#include "headers/ds_matrix.h"
#include "headers/ds_sparse.h"
#include "headers/func_matrix.h"
int main(void)
{
	setbuf(stdout, NULL);
	welcome();
	matrix_t matrix_a, matrix_b, matrix_res;
	sparse_t sparse_a, sparse_b, sparse_res;
	int dots_a, dots_b, dots_sum = 0;
	int percent_a, percent_b;
	int cur_command = -1;
	while (cur_command)
	{
		if (input_interval(&cur_command, 0, 6))
		{
			printf("Введена недопустимая команда! Повторите попытку.");
			welcome();
		}
		else
		{
			if (cur_command == 1)
			{
				printf("Введите количество строк матрицы А (от 1 до 1000): ");
				if (input_interval(&matrix_a.rows, 1, 1000))
				{
					printf("Введено недопустимое значение! Повторите попытку.");
					return OK;
				}
				printf("Введите количество столбцов матрицы А (от 1 до 1000): ");
				if (input_interval(&matrix_a.columns, 1, 1000))
				{
					printf("Введено недопустимое значение! Повторите попытку.");
					return OK;
				}
				printf("Введите количество ненулевых элементов матрицы А (от 1 до 1000): ");
				if (input_interval(&dots_a, 0, matrix_a.rows * matrix_a.columns))
				{
					printf("Введено недопустимое значение! Повторите попытку.");
					welcome();
				}
				printf("Введите элементы матрицы А в формате 'строка столбец значение' построчно: \n");
				create(&matrix_a);
				if (input(&matrix_a, dots_a))
				{
					printf("Введено недопустимое значение! Повторите попытку.");
					return OK;
				}
				matrix_b.rows = matrix_a.rows;
				matrix_b.columns = matrix_a.columns;
				printf("Введите количество ненулевых элементов матрицы В (от 1 до 1000): ");
				if (input_interval(&dots_b, 0, matrix_b.rows * matrix_b.columns))
				{
					printf("Введено недопустимое значение! Повторите попытку.");
					welcome();
				}
				printf("Введите элементы матрицы В в формате 'строка столбец значение' построчно: \n");
				create(&matrix_b);
				if (input(&matrix_b, dots_b))
				{
					printf("Введено недопустимое значение! Повторите попытку.");
					return OK;
				}
				matrix_res.rows = matrix_a.rows;
				matrix_res.columns = matrix_a.columns;
				create(&matrix_res);
				screate(&sparse_a, dots_a, matrix_a.columns);
				sinput(&sparse_a, matrix_a);
				fill_col_entry(&sparse_a, matrix_a);
				screate(&sparse_b, dots_b, matrix_a.columns);
				sinput(&sparse_b, matrix_b);
				fill_col_entry(&sparse_b, matrix_b);
				sdots(sparse_a, sparse_b, &dots_sum);
				screate(&sparse_res, dots_sum, matrix_a.columns);
				welcome();
			}
			if (cur_command == 2)
			{
				printf("Введите количество строк матриц (от 1 до 1000): ");
				if (input_interval(&matrix_a.rows, 1, 1000)) 
				{
					printf("Введено недопустимое значение! Повторите попытку.");
					return OK;
				}
				printf("Введите количество столбцов матриц (от 1 до 1000): ");
				if (input_interval(&matrix_a.columns, 1, 1000))
				{
					printf("Введено недопустимое значение! Повторите попытку. ");
					return OK;
				}
				printf("Введите процентное значение ненулевых элементов матрицы А (от 0 до 100): ");
				if (input_interval(&percent_a, 0, 100))
				{
					printf("Введено недопустимое значение! Повторите попытку.");
					return OK;
				}
				printf("Введите процентное значение ненулевых элементов матрицы В (от 0 до 100): ");
				if (input_interval(&percent_b, 0, 100))
				{
					printf("Введено недопустимое значение! Повторите попытку.");
					return OK;
				}
				matrix_b.rows = matrix_a.rows;
				matrix_b.columns = matrix_a.columns;
				create(&matrix_a);
				create(&matrix_b);
				int to_fill_a = floor(matrix_a.rows * matrix_a.columns * percent_a / 100.0);
				int a_create = to_fill_a;
				while (to_fill_a)
				{
					gorandom(&matrix_a, percent_a);
					to_fill_a--;
				}
				int to_fill_b = floor(matrix_a.rows * matrix_a.columns * percent_b / 100.0);
				int b_create = to_fill_b;
				while (to_fill_b)
				{
					gorandom(&matrix_b, percent_b);
					to_fill_b--;
				}
				matrix_res.rows = matrix_a.rows;
				matrix_res.columns = matrix_a.columns;
				create(&matrix_res);
				screate(&sparse_a, a_create, matrix_a.columns);
				sinput(&sparse_a, matrix_a);
				fill_col_entry(&sparse_a, matrix_a);
				screate(&sparse_b, b_create, matrix_a.columns);
				sinput(&sparse_b, matrix_b);
				fill_col_entry(&sparse_b, matrix_b);
				sdots(sparse_a, sparse_b, &dots_sum);
				screate(&sparse_res, dots_sum, matrix_a.columns);
				welcome();
			}
			if (cur_command == 3)
			{
				uint64_t ticks = 0;
				classic_sum(matrix_a, matrix_b, &matrix_res, &ticks);
				printf("Время сложения матриц, хранимых стандартным методом = %ju тактов\n", ticks);
				welcome();
			}
			if (cur_command == 4)
			{
				uint64_t ticks = 0;
				classic_sum(matrix_a, matrix_b, &matrix_res, &ticks);
				ticks = 0;
				fill_col_entry(&sparse_a, matrix_a);
				fill_col_entry(&sparse_b, matrix_b);
				sparse_sum(sparse_a, sparse_b, &sparse_res, &ticks);
				fill_col_entry(&sparse_res, matrix_res);
				printf("Время сложения матриц, хранимых разреженным столбцовым методом = %ju тактов\n", ticks);
				int mat_size = sizeof(type_t **) + sizeof(type_t *) * matrix_res.rows + sizeof(type_t) * matrix_res.rows * matrix_res.columns + 2 * sizeof(int);
				int sparse_size = sizeof(type_t *) * 3 + sizeof(type_t) * sparse_res.elems_amount * 2 + sizeof(type_t) * sparse_res.cols_amount + 2 * sizeof(int);
				printf("Размер структуры стандартной матрицы: %d\n", mat_size);
				printf("Размер структуры разреженной матрицы: %d\n", sparse_size);
				//printf("~%d~%d\n", sparse_size, mat_size);
				welcome();
			}
			if (cur_command == 5)
			{
				printf("Матрица А:\n");
				output(&matrix_a);
				printf("Матрица В:\n");
				output(&matrix_b);
				printf("Матрица RES:\n");
				output(&matrix_res);
				welcome();
			}
			if (cur_command == 6)
			{
				printf("Матрица А:\n");
				soutput(sparse_a);
				printf("Матрица В:\n");
				soutput(sparse_b);
				printf("Матрица RES:\n");
				soutput(sparse_res);
				welcome();
			}
		}
	}
	deletee(&matrix_a);
	sdelete(&sparse_a);
	deletee(&matrix_b);
	sdelete(&sparse_b);
	deletee(&matrix_res);
	sdelete(&sparse_res);
	return OK;
}