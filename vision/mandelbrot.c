#include <stdio.h>
#include <stdlib.h>

#define WIDTH  800
#define HEIGHT 800
#define MAX_ITER 1000

// 生成Mandelbrot集合的分形图
void generate_mandelbrot(unsigned char image[HEIGHT][WIDTH][3]) {
    double min_re = -2.0;
    double max_re = 1.0;
    double min_im = -1.5;
    double max_im = min_im + (max_re - min_re) * HEIGHT / WIDTH;

    double re_factor = (max_re - min_re) / (WIDTH - 1);
    double im_factor = (max_im - min_im) / (HEIGHT - 1);

    for (int y = 0; y < HEIGHT; y++) {
        double c_im = max_im - y * im_factor;
        for (int x = 0; x < WIDTH; x++) {
            double c_re = min_re + x * re_factor;

            double Z_re = c_re, Z_im = c_im;
            int is_inside = 1;
            int n;
            for (n = 0; n < MAX_ITER; n++) {
                double Z_re2 = Z_re * Z_re, Z_im2 = Z_im * Z_im;
                if (Z_re2 + Z_im2 > 4) {
                    is_inside = 0;
                    break;
                }
                Z_im = 2 * Z_re * Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }

            if (is_inside) {
                image[y][x][0] = 0;
                image[y][x][1] = 0;
                image[y][x][2] = 0;
            } else {
                image[y][x][0] = (unsigned char)(255 * n / MAX_ITER);
                image[y][x][1] = (unsigned char)(255 * n / MAX_ITER);
                image[y][x][2] = (unsigned char)(255 * n / MAX_ITER);
            }
        }
    }
}

// 保存图像为PPM格式
void save_image(const char *filename, unsigned char image[HEIGHT][WIDTH][3]) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("File open error");
        exit(EXIT_FAILURE);
    }

    // 写入PPM文件头
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    // 写入像素数据
    fwrite(image, sizeof(unsigned char), WIDTH * HEIGHT * 3, fp);

    fclose(fp);
}

int main() {
    // 创建一个图像
    unsigned char image[HEIGHT][WIDTH][3];

    // 生成Mandelbrot集合的分形图
    generate_mandelbrot(image);

    // 保存图像
    save_image("mandelbrot.ppm", image);

    printf("Mandelbrot fractal image saved as mandelbrot.ppm\n");

    return 0;
}