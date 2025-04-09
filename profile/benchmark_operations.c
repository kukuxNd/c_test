#include <stdio.h>
#include <time.h>

#define NUM_ITERATIONS 10000000

void benchmark_bitwise_operations() {
    clock_t start, end;
    unsigned int result = 0;
    start = clock();
    for (unsigned int i = 0; i < NUM_ITERATIONS; i++) {
        result ^= i;
    }
    end = clock();
    printf("Bitwise operations time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_integer_operations() {
    clock_t start, end;
    int result = 0;
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        result += i;
    }
    end = clock();
    printf("Integer operations time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_float_operations() {
    clock_t start, end;
    float result = 0.0f;
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        result += i * 0.1f;
    }
    end = clock();
    printf("Float operations time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    printf("Benchmarking bitwise, integer, and float operations with %d iterations each.\n", NUM_ITERATIONS);
    
    benchmark_bitwise_operations();
    benchmark_integer_operations();
    benchmark_float_operations();
    
    return 0;
}