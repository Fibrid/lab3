#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    int N, M;
    if (fscanf(f, "%d %d", &N, &M) != 2) {
        fprintf(stderr, "Ошибка: в файле должен быть первый строкой два целых числа N M\n");
        fclose(f);
        return 1;
    }
    if (N <= 0 || M <= 0) {
        fprintf(stderr, "Ошибка: N и M должны быть положительными целыми числами\n");
        fclose(f);
        return 1;
    }

    // Выделим память под матрицу в виде одномерного массива (строчно)
    int *a = malloc(sizeof(int) * N * M);
    if (!a) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        fclose(f);
        return 1;
    }

    // Считываем N*M элементов (построчно или как идут)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (fscanf(f, "%d", &a[i * M + j]) != 1) {
                fprintf(stderr, "Ошибка: недостаточно элементов в файле (ожидалось %d чисел)\n", N * M);
                free(a);
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);

    // 1) Сумма отрицательных элементов на побочной диагонали.
    // Побочная диагональ: элементы с координатами (i, j) где j = M-1 - i, при этом 0 <= i < N и 0 <= j < M.
    long long sum_neg_secondary = 0;
    int found_secondary = 0;
    for (int i = 0; i < N; ++i) {
        int j = M - 1 - i;
        if (j >= 0 && j < M) {
            int val = a[i * M + j];
            if (val < 0) {
                sum_neg_secondary += val;
       }
    }
    if (!found_secondary) {
        // Теоретически не может случиться при N>0,M>0, но на всякий случай.
        printf("На побочной диагонали нет элементов (возможно некорректные N или M).\n");
    }
    
    // 2) Найти минимальный элемент в 3-ем столбце (т.е. колонка с индексом 2).
    if (M < 3) {
        printf("Ошибка: в матрице менее 3-х столбцов (M = %d). Невозможно выполнить пункт 2 и 3.\n", M);
        // Выведем сумму и напечатаем исходную матрицу, затем завершим.
        printf("Сумма отрицательных элементов на побочной диагонали = %lld\n", sum_neg_secondary);
        printf("Исходная матрица (%d x %d):\n", N, M);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                printf("%d ", a[i * M + j]);
            } 
            printf("\n");
        }
        free(a);
        return 0;
    }
    
    int min_val = INT_MAX;
    int min_row = -1;
    for (int i = 0; i < N; ++i) {  
        int val = a[i * M + 2]; // 3-й столбец -> индекс 2
        if (val < min_val) {
            min_val = val;
            min_row = i;
        }
    }
    
    printf("Сумма отрицательных элементов на побочной диагонали = %lld\n", sum_neg_secondary);
    if (min_row >= 0) {
        printf("Минимальный элемент в 3-м столбце: %d (строка %d, столбец 3)\n", min_val, min_row + 1);
    } else {
        printf("Не удалось найти минимальный элемент в 3-м столбце (непредвиденная ошибка).\n");
        free(a);
        return 1;
    }
        
    // 3) Поменять местами найденный минимальный элемент и значение 3-го элемента в 4-ой строке.
    // 4-я строка -> индекс 3; 3-й элемент -> столбец индекс 2.
    if (N < 4) {
        printf("Невозможно выполнить обмен: в матрице менее 4-х строк (N = %d).\n", N);
        printf("Матрица после (обмен не выполнен):\n");
    } else {
        int row4 = 3;
        int col3 = 2;
        int idx_min = min_row * M + col3;
        int idx_row4 = row4 * M + col3;
    
        // Выполняем обмен (может быть одна и та же позиция — в этом случае ничего не поменяется)
        int tmp = a[idx_min];
        a[idx_min] = a[idx_row4];  
        a[idx_row4] = tmp;
               
        printf("Обмен выполнен между элементом (%d, %d) и элементом (4, 3).\n", min_row + 1, 3);
        printf("Новая матрица (%d x %d):\n", N, M);
    }
     
    // Печать матрицы (после возможного обмена)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%d ", a[i * M + j]);
        }   
        printf("\n");
    }
        
    free(a);
    return 0;
}

