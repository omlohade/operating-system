#include <stdio.h>
#include <pthread.h>

#define N 3
int A[N][N], B[N][N], C[N][N];

void *add_matrix(void *args)
{
    int thread_id = (int)args;

    for (int i = thread_id; i < N; i = i + 2)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return NULL;
}

void *sub_matrix(void *args)
{
    int thread_id = (int)args;

    for (int i = thread_id; i < N; i = i + 2)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return NULL;
}

void *mul_matrix(void *args)
{
    int thread_id = (int)args;

    for (int i = thread_id; i < N; i = i + 2)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    return NULL;
}

void printMatrix(int C[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    // Setting the values of the array.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    // Print array A
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    // Print array B
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    pthread_t threads[2]; // We have used the same threads for all the operations.
    int thread_id[2] = {0, 1};

    // Addition
    for (int i = 0; i < N; i++)
    {
        pthread_create(&threads[i], NULL, add_matrix, &thread_id[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Matrix Addition: \n");
    printMatrix(C);

    // Subtraction
    for (int i = 0; i < N; i++)
    {
        pthread_create(&threads[i], NULL, sub_matrix, &thread_id[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Matrix Substraction: \n");
    printMatrix(C);

    // Multiplication

    for (int i = 0; i < N; i++)
    {
        pthread_create(&threads[i], NULL, mul_matrix, &thread_id[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Matrix Multiplication: \n");
    printMatrix(C);

    return 0;
}