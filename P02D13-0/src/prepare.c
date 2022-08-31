#include <stdio.h>
#include <stdlib.h>
#define SIZE 10000

// сортировка змейкой
int main(){
    int n, m;
    printf("Matrix:\n");

    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 1;
    }
    if (scanf("%d", &m) != 1) {
        printf("n/a");
        return 1;
    } 


    return 0;
}
// перемножение матриц
/*
int main() {
    int n, m, l, c;
    printf("Matrix:\n");

    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 1;
    }
    if (scanf("%d", &m) != 1) {
        printf("n/a");
        return 1;
    }
    if (scanf("%d", &l) != 1) {
        printf("n/a");
        return 1;
    }
    if (scanf("%d", &c) != 1) {
        printf("n/a");
        return 1;
    }
    int A[n][m];
    int B[l][c];
    int C[n][c];

    printf("Fill matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(scanf("%d", &A[i][j]) != 1){
                printf("n/a");
                return 1;
            }
        }
    }
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if(scanf("%d", &B[i][j]) != 1){
                printf("n/a");
                return 1;
            }
        }
    }

    if (m == l) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < c; j++) {
                C[i][j] = 0;
                for(int k = 0; k < m; k++)
                    C[i][j] += A[i][k] * B[k][j];
            }
        }
    } else {
        printf("n/a");
        return 1;
    }
    printf("Result  :\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d", C[i][j]);
            if (j != c - 1) {
                printf(" ");
            }
        }
        if (i != n - 1)
            printf("\n");
    }
    return 0;
}
*/

/*
//Вторая реализация перемножения матриц
int main() {
    int N;
    char term;
    if (scanf("%d%c", &N, &term) != 2 || term != '\n') {
        printf("n/a");
        return 1;
    }

    int A[N][N];
    int B[N][N];
    int C[N][N];
    //   int **A = (int **)malloc(N * sizeof(int *));
    //   int **B = (int **)malloc(N * sizeof(int *));
    //   int **C = (int **)malloc(N * sizeof(int *));
    //   for (int i = 0; i < N; i++) {
    //     A[i] = (int *)malloc(N * sizeof(int));
    //     B[i] = (int *)malloc(N * sizeof(int));
    //     C[i] = (int *)malloc(N * sizeof(int));
    //   }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (scanf("%d", &A[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (scanf("%d", &B[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j < N - 1) {
                printf("%d ", C[i][j]);
            } else {
                printf("%d", C[i][j]);
                printf("\n");
            }
        }
    }
}
*/
//последовательность на -1, является ли строка полиндромом
/*
int main(){
    char word[SIZE];
    char c = 0;
    int idx = 0;
    while((c = getchar()) != '\n'){
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' '){
            word[idx] = c;
            idx++;
        } else {
            printf("n/a\n");
            return 1;
        }
    }
    word[idx] = '\0';
    // printf("%s", word);
    int fail = 0;
    for(int i = 0; i < idx/2; i++){
        if(word[i] != word[idx - 1 - i]){
            fail = 1;
        }
    }
    if(fail){
        printf("\nNO");
    } else {
        printf("\nYES");
    }
    return 0;
}
*/
//своп максимальных и минимальных значений матрицы
/*
int main() {
    int n, m;
    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 1;
    }
    if (scanf("%d", &m) != 1) {
        printf("n/a");
        return 1;
    }
    int arr[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &arr[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    }
    int min = arr[0][0];
    int max = arr[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (min > arr[i][j])
                min = arr[i][j];
            if (max < arr[i][j])
                max = arr[i][j];
        }
    }
    int exit = 0;
    int wasmin = 0;
    int wasmax = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == min && wasmin == 0) {
                arr[i][j] = max;
                wasmin = 1;
                break;
            }
            if (arr[i][j] == max && wasmax == 0) {
                arr[i][j] = min;
                wasmax = 1;
                break;
            }
            if (wasmax && wasmin)
                exit = 1;
        }
        if (exit) {
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", arr[i][j]);
            if (j != m - 1) {
                printf(" ");
            }
        }
        if (i != n - 1)
            printf("\n");
    }
    return 0;
}
*/
// Убрать повторы в последовательности, которая заканчивается на -1
/*
int main() {
    int arr[SIZE] = {};
    int res = 0;
    int idx = 0;
    int val = 0;
    int exit = 1;
    while ((res = scanf("%d", &val)) && val != -1) {
        if (res == 1) {
            arr[idx++] = val;
        } else {
            printf("n/a");
            exit = 0;
            break;
        }
    }
    for (int i = 0; i < idx; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    int buff[SIZE] = {};
    if (exit) {
        for (int i = 0; i < idx - 1; i++) {
            for (int j = 1; j < idx; j++) {
                if (arr[i] == arr[j] && i != j) {
                    arr[j] = -1;
                }
            }
        }
    }
    int len = 0;
    for (int i = 0; i < idx; i++) {
        if (arr[i] != -1) {
            buff[len++] = arr[i];
        }
    }
    for (int i = 0; i < len; i++) {
        printf("%d", buff[i]);
        if (i != len - 1) {
            printf(" ");
        }
    }
    return 0;
}
*/