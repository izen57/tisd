/*
IO module.
*/
#include <stdio.h>
#include <string.h>
#include "../headers/data_structures.h"
#include "../headers/defines.h"
/*
Welcomming print with available features.
*/
void welcome(void)
{
	printf("\nДанная программа позволяет сравнить время, затраченное на сложение \n"
			"двух разреженных матриц, хранимых в стандартном виде и в разреженном \n"
			"столбцовом видах.\n\n");
	printf("Выберите действие из списка, введя соответствуюший номер:\n");
	printf("1. Ввести матрицы вручную.\n"
			"2. Сгенерировать матрицы случайно (по проценту заполненности).\n"
			"3. Сложить матрицы, используя стандартный способ хранения.\n"
			"4. Сложить матрицы, используя разреженный столбцовый вид хранения.\n"
			"5. Вывести исходные и результирующую матрицы в стандартном виде.\n"
			"6. Вывести исходные и результирующую матрицы в разреженном столбцовом виде.\n"
			"0. Выход из программы.\n\n");
}
/*
Clean input stream from trash.
*/
void clean_input_stream(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
/*
Input number in between.

Input data:
* int *const num - number of action to be done.
* const int left - left border of between.
* const int right - right border of between.

Output data:
* Return code - OK, INVALID_INT_INPUT_ERROR or IN_BETWEEN_ERROR.
*/
int input_interval(type_t *const num, const type_t left, const type_t right)
{
	if (scanf(type_spec, num) != GOT_ARG)
	{
		clean_input_stream();
		return INVALID_INT_INPUT_ERROR;
	}
	if (*num < left || *num > right)
	{
		clean_input_stream();
		return INVALID_INTERVAL_ERROR;
	}
	return OK;
}