#include <stdio.h>
#include <math.h>
#include <time.h>

void benchmark_float_addition() {
    clock_t start, end;
    float result = 0.0f;
    start = clock();
    for (int i = 0; i < 100000000; i++) {
        result += i * 0.1f;
    }
    end = clock();
    printf("Float addition time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_float_subtraction() {
    clock_t start, end;
    float result = 100000000.0f;
    start = clock();
    for (int i = 0; i < 100000000; i++) {
        result -= i * 0.1f;
    }
    end = clock();
    printf("Float subtraction time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_float_multiplication() {
    clock_t start, end;
    float result = 1.0f;
    start = clock();
    for (int i = 1; i < 100000000; i++) {
        result *= (i % 10 + 0.1f); // Avoid overflow by limiting the multiplier
    }
    end = clock();
    printf("Float multiplication time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_float_division() {
    clock_t start, end;
    float result = 1.0f;
    start = clock();
    for (int i = 1; i < 100000000; i++) {
        result /= (i % 10 + 1.0f); // Avoid division by zero
    }
    end = clock();
    printf("Float division time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_square_root() {
    clock_t start, end;
    float result = 0.0f;
    start = clock();
    for (int i = 1; i < 100000000; i++) {
        result = sqrt(i);
    }
    end = clock();
    printf("Square root time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_exponentiation() {
    clock_t start, end;
    float result = 0.0f;
    start = clock();
    for (int i = 1; i < 100000000; i++) {
        result = pow(i, 0.5);
    }
    end = clock();
    printf("Exponentiation time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_logarithm() {
    clock_t start, end;
    float result = 0.0f;
    start = clock();
    for (int i = 1; i < 100000000; i++) {
        result = log(i);
    }
    end = clock();
    printf("Logarithm time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_trigonometric() {
    clock_t start, end;
    float result = 0.0f;
    start = clock();
    for (int i = 1; i < 100000000; i++) {
        result = sin(i);
    }
    end = clock();
    printf("Trigonometric (sin) time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_inverse_trigonometric() {
    clock_t start, end;
    float result = 0.0f;
    start = clock();
    for (int i = 1; i < 100000000; i++) {
        result = asin(i % 10 * 0.1f);
    }
    end = clock();
    printf("Inverse trigonometric (asin) time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_hyperbolic() {
    clock_t start, end;
    float result = 0.0f;
    start = clock();
    for (int i = 1; i < 100000000; i++) {
        result = sinh(i % 10 * 0.1f);
    }
    end = clock();
    printf("Hyperbolic (sinh) time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void benchmark_inverse_hyperbolic() {
    clock_t start, end;
    float result = 0.0f;
    start = clock();
    for (int i = 1; i < 100000000; i++) {
        result = asinh(i % 10 * 0.1f);
    }
    end = clock();
    printf("Inverse hyperbolic (asinh) time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    printf("Benchmarking various floating-point operations with 100,000,000 iterations each.\n");
    
    benchmark_float_addition();
    benchmark_float_subtraction();
    benchmark_float_multiplication();
    benchmark_float_division();
    benchmark_square_root();
    benchmark_exponentiation();
    benchmark_logarithm();
    benchmark_trigonometric();
    benchmark_inverse_trigonometric();
    benchmark_hyperbolic();
    benchmark_inverse_hyperbolic();
    
    return 0;
}