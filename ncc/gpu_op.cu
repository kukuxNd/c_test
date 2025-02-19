#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <time.h>

#define N 1000000000  // 向量和矩阵的大小（可根据需要调整）

// 点积
__global__ void dot_product_gpu(double *a, double *b, double *result) {
    __shared__ double cache[256];
    int tid = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    double temp = 0.0;
    if (idx < N) {
        temp = a[idx] * b[idx];
    }

    int cacheIndex = tid;
    cache[cacheIndex] = temp;
    __syncthreads();

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            cache[cacheIndex] += cache[cacheIndex + stride];
        }
        __syncthreads();
    }

    if (tid == 0) {
        atomicAdd(result, cache[0]);
    }
}

// 叉积（仅适用于三维向量）
__global__ void cross_product_gpu(double *a, double *b, double *result) {
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

// 外积
__global__ void outer_product_gpu(double *a, double *b, double *result) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N * N) {
        int row = idx / N;
        int col = idx % N;
        result[idx] = a[row] * b[col];
    }
}

// 矩阵乘积
__global__ void matrix_multiply_gpu(double *A, double *B, double *C) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < N) {
        double sum = 0.0;
        for (int i = 0; i < N; i++) {
            sum += A[row * N + i] * B[i * N + col];
        }
        C[row * N + col] = sum;
    }
}

// Hadamard 积
__global__ void hadamard_product_gpu(double *A, double *B, double *C) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N * N) {
        C[idx] = A[idx] * B[idx];
    }
}

// Kronecker 积
__global__ void kronecker_product_gpu(double *A, double *B, double *C) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N * N * N * N) {
        int row = idx / (N * N);
        int col = idx % (N * N);
        int A_row = row / N;
        int A_col = col / N;
        int B_row = row % N;
        int B_col = col % N;
        C[idx] = A[A_row * N + A_col] * B[B_row * N + B_col];
    }
}

void measure_time(cudaEvent_t start, cudaEvent_t stop, float *elapsedTime) {
    cudaEventRecord(start);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(elapsedTime, start, stop);
}

int main() {
    // 初始化随机数种子
    srand(time(NULL));

    // 分配主机内存
    double *a = (double *)malloc(N * sizeof(double));
    double *b = (double *)malloc(N * sizeof(double));
    double *result = (double *)malloc(sizeof(double));
    double *A = (double *)malloc(N * N * sizeof(double));
    double *B = (double *)malloc(N * N * sizeof(double));
    double *C = (double *)malloc(N * N * sizeof(double));

    // 初始化数据
    for (int i = 0; i < N; i++) {
        a[i] = (double)(rand() % 100);
        b[i] = (double)(rand() % 100);
    }
    for (int i = 0; i < N * N; i++) {
        A[i] = (double)(rand() % 100);
        B[i] = (double)(rand() % 100);
    }

    // 分配设备内存
    double *d_a, *d_b, *d_result, *d_A, *d_B, *d_C;
    cudaMalloc(&d_a, N * sizeof(double));
    cudaMalloc(&d_b, N * sizeof(double));
    cudaMalloc(&d_result, sizeof(double));
    cudaMalloc(&d_A, N * N * sizeof(double));
    cudaMalloc(&d_B, N * N * sizeof(double));
    cudaMalloc(&d_C, N * N * sizeof(double));

    // 创建 CUDA 事件
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // 点积
    cudaMemcpy(d_a, a, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemset(d_result, 0, sizeof(double));

    cudaEventRecord(start);
    dot_product_gpu<<<(N + 255) / 256, 256>>>(d_a, d_b, d_result);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float dotTime;
    cudaEventElapsedTime(&dotTime, start, stop);

    cudaMemcpy(result, d_result, sizeof(double), cudaMemcpyDeviceToHost);
    printf("Dot Product Result: %f\n", result[0]);
    printf("Dot Product Time: %.3f ms\n", dotTime);

    // 叉积
    double c[3];
    double *d_c;
    cudaMalloc(&d_c, 3 * sizeof(double));

    cudaMemcpy(d_a, a, 3 * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, 3 * sizeof(double), cudaMemcpyHostToDevice);

    cudaEventRecord(start);
    cross_product_gpu<<<1, 1>>>(d_a, d_b, d_c);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float crossTime;
    cudaEventElapsedTime(&crossTime, start, stop);

    cudaMemcpy(c, d_c, 3 * sizeof(double), cudaMemcpyDeviceToHost);
    printf("Cross Product Result: (%f, %f, %f)\n", c[0], c[1], c[2]);
    printf("Cross Product Time: %.3f ms\n", crossTime);

    // 外积
    cudaMemcpy(d_a, a, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N * sizeof(double), cudaMemcpyHostToDevice);

    cudaEventRecord(start);
    outer_product_gpu<<<(N * N + 255) / 256, 256>>>(d_a, d_b, d_C);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float outerTime;
    cudaEventElapsedTime(&outerTime, start, stop);

    cudaMemcpy(C, d_C, N * N * sizeof(double), cudaMemcpyDeviceToHost);
    printf("Outer Product Time: %.3f ms\n", outerTime);

    // 矩阵乘积
    cudaMemcpy(d_A, A, N * N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, N * N * sizeof(double), cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    dim3 gridSize((N + blockSize.x - 1) / blockSize.x, (N + blockSize.y - 1) / blockSize.y);

    cudaEventRecord(start);
    matrix_multiply_gpu<<<gridSize, blockSize>>>(d_A, d_B, d_C);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float matrixTime;
    cudaEventElapsedTime(&matrixTime, start, stop);

    cudaMemcpy(C, d_C, N * N * sizeof(double), cudaMemcpyDeviceToHost);
    printf("Matrix Multiply Time: %.3f ms\n", matrixTime);

    // Hadamard 积
    cudaMemcpy(d_A, A, N * N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, N * N * sizeof(double), cudaMemcpyHostToDevice);

    cudaEventRecord(start);
    hadamard_product_gpu<<<(N * N + 255) / 256, 256>>>(d_A, d_B, d_C);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float hadamardTime;
    cudaEventElapsedTime(&hadamardTime, start, stop);

    cudaMemcpy(C, d_C, N * N * sizeof(double), cudaMemcpyDeviceToHost);
    printf("Hadamard Product Time: %.3f ms\n", hadamardTime);

    // Kronecker 积
    double *d_K;
    cudaMalloc(&d_K, N * N * N * N * sizeof(double));

    cudaEventRecord(start);
    kronecker_product_gpu<<<(N * N * N * N + 255) / 256, 256>>>(d_A, d_B, d_K);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float kroneckerTime;
    cudaEventElapsedTime(&kroneckerTime, start, stop);

    printf("Kronecker Product Time: %.3f ms\n", kroneckerTime);

    // 释放内存
    free(a);
    free(b);
    free(result);
    free(A);
    free(B);
    free(C);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_result);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    cudaFree(d_c);
    cudaFree(d_K);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    return 0;
}