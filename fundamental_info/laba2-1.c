#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Введите размер матрицы N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Ошибка: размер матрицы должен быть положительным целым числом.\n");
        return 1;
    }

    // Проверяем, что размер матрицы в байтах помещается в size_t.
    if ((size_t)n > SIZE_MAX / sizeof(int) / n ||
        (size_t)n > SIZE_MAX / sizeof(int *)) {
        printf("Ошибка: матрица слишком велика.\n");
        return 1;
    }

    // Выделяем память для указателей на строки и для элементов матрицы.
    int **matrix = malloc(n * sizeof *matrix);
    int *data = malloc((size_t)n * n * sizeof *data);
    if (matrix == NULL || data == NULL) {
        free(data);
        free(matrix);
        printf("Ошибка: не удалось выделить память для матрицы.\n");
        return 1;
    }

    // Каждый указатель ведёт к началу своей строки.
    for (int i = 0; i < n; i++) {
        matrix[i] = data + (size_t)i * n;
    }

    // ввод элементов матрицы
    printf("Введите элементы матрицы %dx%d:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Ошибка: не удалось прочитать элемент матрицы.\n");
                free(data);
                free(matrix);
                return 1;
            }
        }
    }

    printf("\nРезультат обхода:\n");
    
    // Основная логика обхода по диагоналям
    // s - сумма индексов (номер диагонали)

    for (long long s = 0; s <= 2LL * (n - 1); s++) {

        int start_row;
        int end_row;

        if (s % 2 == 0) {
            // чётная диагональ: идём сверху вниз

            if (s < n) {
                // первая половина матрицы
                start_row = 0;
                end_row = s;
            } else {
                // вторая половина матрицы
                start_row = s - (n - 1);
                end_row = n - 1;
            }

            for (int i = start_row; i <= end_row; i++) {
                int j = s - i;
                printf("%d ", matrix[i][j]);
            }

        } else {
            // нечётная диагональ: идём снизу вверх

            if (s < n) {
                // первая половина матрицы
                start_row = s;
                end_row = 0;
            } else {
                // вторая половина матрицы
                start_row = n - 1;
                end_row = s - (n - 1);
            }

            for (int i = start_row; i >= end_row; i--) {
                int j = s - i;
                printf("%d ", matrix[i][j]);
            }
        }
    }

    printf("\n");


    free(data);
    free(matrix);
    return 0;
}
