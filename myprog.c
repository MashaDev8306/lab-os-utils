//work with arrays

#include <stdio.h>
#include <stdlib.h>

void Trans(int rows, int cols, double **W, double **U) {
    int i ,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            U[j][i] = W[i][j];
        }
    }
}

void Sum(int n, int m, double **W, double **U, double **S) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            S[i][j] = W[i][j] + U[i][j];
        }
    }
}

void MatrMult(int n, int m, double **W, double **U, double **S) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            S[i][j] = 0;
            for (k = 0; k < m; k++) {
                S[i][j] += W[i][k] * U[k][j];
            }
        }
    }
}

void MVMult(int n, double **W, double *U, double *S) {
    int i, j;
    for (i = 0; i < n; i++) {
        S[i] = 0;
        for (j = 0; j < n; j++) {
            S[i] += W[i][j] * U[j];
        }
    }
}

void PrintMatrix(int n, int m, double **matrix) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void PrintDebugMatrix(int n, int m, double **matrix, char *matricName) {
    int i, j;
    printf("%s %x\n", matricName, matrix);
    for (i = 0; i < n; i++) {
        printf("%d %x\n", i, &matrix[i]);
        for (j = 0; j < m; j++) {
            printf("%d %d %x %.2f ", i, j, &matrix[i][j], matrix[i][j]);
        }
        printf("\n");
    }
}

void PrintVector(int n, double *vector) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%.2f ", vector[i]);
    }
    printf("\n");
}

int main() {
    int N, M;
    int i, j;
    double **A, **B, **Bt, **C_temp, **C_final, *X, *result;

    do {
        printf("Input N (rows of matrix A, no more than 10): ");
        scanf("%d", &N);
    } while (N <= 0 || N > 10);

    do {
        printf("Input M (columns of matrix A, no more than 20): ");
        scanf("%d", &M);
    } while (M <= 0 || M > 20);

    // Dynamic arrays
    A = (double **)malloc(N * sizeof(double *));
    B = (double **)malloc(M * sizeof(double *));
    Bt = (double **)malloc(N * sizeof(double *));
    C_temp = (double **)malloc(N * sizeof(double *));
    C_final = (double **)malloc(N * sizeof(double *));
    X = (double *)malloc(N * sizeof(double));
    result = (double *)malloc(N * sizeof(double));

    for (i = 0; i < N; i++) A[i] = (double *)malloc(M * sizeof(double));
    for (i = 0; i < M; i++) B[i] = (double *)malloc(N * sizeof(double));
    for (i = 0; i < M; i++) Bt[i] = (double *)malloc(M * sizeof(double));
    for (i = 0; i < N; i++) C_temp[i] = (double *)malloc(M * sizeof(double));
    for (i = 0; i < N; i++) C_final[i] = (double *)malloc(N * sizeof(double));

    printf("Input elements of matrix A:\n");
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            scanf("%lf", &A[i][j]);

    printf("Input elements of matrix B:\n");
    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
            scanf("%lf", &B[i][j]);

    printf("Input elements of vector X:\n");
    for (i = 0; i < N; i++)
        scanf("%lf", &X[i]);

    PrintDebugMatrix(N, M, A, "MatrixA");
    PrintDebugMatrix(M, N, B, "MatrixB");
    PrintDebugMatrix(N, M, Bt, "MatrixBt");

    // transpon of matrix B
    Trans(M, N, B, Bt);
    PrintDebugMatrix(N, M, Bt, "MatrixBt");
    getch();

    // calcuate A + B^T
    Sum(N, M, A, Bt, C_temp);

    printf("Print of A + B^T:\n");
    PrintMatrix(N, M, C_temp);

    // Calculate (A + B^T) * B
    MatrMult(N, N, C_temp, B, C_final);

    // Print C_temp * B
    printf("Print of (A + B^T) * B:\n");
    PrintMatrix(N, N, C_final);

    // Calculate ((A + B^T) * B) * X
    MVMult(N, C_final, X, result);

    // Print final result
    printf("Print final vector C:\n");
    PrintVector(N, result);

    free(X);
    free(result);

    for (i = 0; i < N; i++) free(A[i]);
    free(A);

    for (i = 0; i < M; i++) free(B[i]);
    free(B);

    for (i = 0; i < M; i++) free(Bt[i]);
    free(Bt);

    for (i = 0; i < N; i++) free(C_temp[i]);
    free(C_temp);

    for (i = 0; i < N; i++) free(C_final[i]);
    free(C_final);

    getch();
    return 0;
}
