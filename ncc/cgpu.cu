#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <time.h>

#define N 10000000  // 向量大小，可以根据需要调整

// CPU版本的点积计算
double dot_product_cpu(double *a, double *b) {
    double result = 0.0;
    for (int i = 0; i < N; i++) {
        result += a[i] * b[i];
    }
    return result;
}

// GPU版本的点积计算
__global__ void dot_product_gpu(double *a, double *b, double *result) {
    __shared__ double cache[256];  // 使用共享内存进行归约
    int tid = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    double temp = 0.0;
    if (idx < N) {
        temp = a[idx] * b[idx];
    }

    int cacheIndex = tid;
    cache[cacheIndex] = temp;
    __syncthreads();

    int i = blockDim.x / 2;
    while (i != 0) {
        if (tid < i) {
            cache[cacheIndex] += cache[cacheIndex + i];
        }
        __syncthreads();
        i /= 2;
    }

    if (tid == 0) {
        atomicAdd(result, cache[0]);
    }
}

int main() {
    double *a, *b, result_cpu, result_gpu;
    double *d_a, *d_b, *d_result;

    // 初始化向量
    a = (double *)malloc(N * sizeof(double));
    b = (double *)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        a[i] = (double)(rand() % 100);
        b[i] = (double)(rand() % 100);
    }

    // CPU计算
    clock_t start_cpu = clock();
    result_cpu = dot_product_cpu(a, b);
    clock_t end_cpu = clock();
    double cpu_time = (double)(end_cpu - start_cpu) / CLOCKS_PER_SEC;

    // GPU计算
    cudaMalloc(&d_a, N * sizeof(double));
    cudaMalloc(&d_b, N * sizeof(double));
    cudaMalloc(&d_result, sizeof(double));
    cudaMemcpy(d_a, a, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemset(d_result, 0, sizeof(double));

    // 创建CUDA事件
    cudaEvent_t start, stop;
    float milliseconds;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // 记录开始事件
    cudaEventRecord(start);

    // 执行GPU内核
    int blockSize = 256;
    int numBlocks = (N + blockSize - 1) / blockSize;
    dot_product_gpu<<<numBlocks, blockSize>>>(d_a, d_b, d_result);

    // 记录结束事件
    cudaEventRecord(stop);

    // 等待内核完成
    cudaEventSynchronize(stop);

    // 获取GPU执行时间
    cudaEventElapsedTime(&milliseconds, start, stop);

    // 获取结果
    cudaMemcpy(&result_gpu, d_result, sizeof(double), cudaMemcpyDeviceToHost);

    // 输出结果和耗时
    printf("CPU Result: %f\n", result_cpu);
    printf("GPU Result: %f\n", result_gpu);
    printf("CPU Time: %f seconds\n", cpu_time);
    printf("GPU Time: %f ms\n", milliseconds);

    // 释放资源
    free(a);
    free(b);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_result);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    return 0;
}