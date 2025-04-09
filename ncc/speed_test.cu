#include <iostream>
#include <cuda_runtime.h>
#include <chrono>

#define ARRAY_SIZE (1024 * 1024)

int main() {
    float *h_data = new float[ARRAY_SIZE];
    float *d_data;

    // 分配显存
    cudaMalloc((void**)&d_data, ARRAY_SIZE * sizeof(float));

    // 记录开始时间
    auto start = std::chrono::high_resolution_clock::now();

    // 从内存复制数据到显存
    cudaMemcpy(d_data, h_data, ARRAY_SIZE * sizeof(float), cudaMemcpyHostToDevice);

    // 记录结束时间
    auto end = std::chrono::high_resolution_clock::now();

    // 计算传输时间
    std::chrono::duration<double> elapsed = end - start;

    // 计算传输速度 (GB/s)
    double transferSize = (double)ARRAY_SIZE * sizeof(float) / (1024 * 1024 * 1024);
    double transferSpeed = transferSize / elapsed.count();

    std::cout << "Transfer speed: " << transferSpeed << " GB/s" << std::endl;

    // 释放显存和内存
    cudaFree(d_data);
    delete[] h_data;

    return 0;
}