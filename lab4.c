#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000; 
    }
}

void puzirek(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void vstavki(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void sliyanie(int *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void sliyanieRec(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        sliyanieRec(arr, l, m);
        sliyanieRec(arr, m + 1, r);
                sliyanie(arr, l, m, r);
            }
        }

    void copyArray(int *source, int *dest, int size) {
            for (int i = 0; i < size; i++) {
                dest[i] = source[i];
            }
        }
            
      
int main() {
            srand(time(NULL));
            
            int sizes[] = {10, 1000, 10000, 100000};
            int numSizes = sizeof(sizes) / sizeof(sizes[0]);
             
            printf("Размер массива | Пузырек (с) | Вставки (с) | Слияние (с)\n");
            printf("---------------------------------------------------------\n");

            for (int s = 0; s < numSizes; s++) {
                int size = sizes[s];
                int *arr = (int *)malloc(size * sizeof(int));
                int *arrCopy = (int *)malloc(size * sizeof(int));

                generateArray(arr, size);
                
              
                copyArray(arr, arrCopy, size);
                clock_t start = clock();
                puzirek(arrCopy, size);
                clock_t end = clock();
                double puzirekTime = (double)(end - start) / CLOCKS_PER_SEC;

              
                copyArray(arr, arrCopy, size);
                start = clock();
                vstavki(arrCopy, size);
                end = clock();
                double vstavkiTime = (double)(end - start) / CLOCKS_PER_SEC;

               
                copyArray(arr, arrCopy, size);
                start = clock();
                sliyanieRec(arrCopy, 0, size - 1);
                end = clock();
                double sliyanieTime = (double)(end - start) / CLOCKS_PER_SEC;
            
                printf("%12d | %11.6f | %11.6f | %11.6f\n", size, puzirekTime, vstavkiTime, sliyanieTime);

                free(arr);
                free(arrCopy);
        }
                
        return 0;
    }
