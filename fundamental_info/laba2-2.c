#include <stdint.h>
#include <limits.h>
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

    // Храним по одной сумме для каждого элемента побочной диагонали.
    int *sums = malloc(n * sizeof *sums);
    if (sums == NULL) {
        printf("Ошибка: не удалось выделить память для сумм.\n");
        free(data);
        free(matrix);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int j = n - 1 - i;
        int diff = i - j;

        // Начинаем на верхней или левой границе и идём вниз-вправо.
        int r = 0;
        int c = 0;
        if (diff > 0) {
            r = diff;
        } else {
            c = -diff;
        }

        long long sum = 0;
        while (r < n && c < n) {
            sum += matrix[r][c];
            r++;
            c++;
        }

        if (sum < INT_MIN || sum > INT_MAX) {
            printf("Ошибка: сумма диагонали не помещается в тип int.\n");
            free(sums);
            free(data);
            free(matrix);
            return 1;
        }
        sums[i] = (int)sum;
    }

    // записываем суммы в элементы побочной диагонали
    for (int i = 0; i < n; i++) {
        int j = n - 1 - i;
        matrix[i][j] = sums[i];
    }

    free(sums);

    printf("\nРезультат:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }

    free(data);
    free(matrix);
    return 0;
}
