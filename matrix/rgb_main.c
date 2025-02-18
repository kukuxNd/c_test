#include <stdio.h>
#include <stdlib.h>

// 定义图像的宽度和高度
#define WIDTH  5
#define HEIGHT 5

// 定义RGB结构体来表示彩色图像中的一个像素
typedef struct {
    unsigned char r, g, b;
} RGB;

// 定义灰度图像中的一个像素
typedef unsigned char Gray;

// 打印RGB图像
void print_rgb_image(RGB image[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("(%d, %d, %d) ", image[i][j].r, image[i][j].g, image[i][j].b);
        }
        printf("\n");
    }
}

// 打印灰度图像
void print_gray_image(Gray image[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
}

// 将RGB图像转换为灰度图像
void rgb_to_grayscale(RGB rgb_image[HEIGHT][WIDTH], Gray gray_image[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // 使用平均法将RGB转换为灰度值
            gray_image[i][j] = (rgb_image[i][j].r + rgb_image[i][j].g + rgb_image[i][j].b) / 3;
        }
    }
}

// 保存灰度图像为PPM格式
void save_gray_image(const char *filename, Gray image[HEIGHT][WIDTH]) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("File open error");
        exit(EXIT_FAILURE);
    }

    // 写入PPM文件头
    fprintf(fp, "P5\n%d %d\n255\n", WIDTH, HEIGHT);

    // 写入像素数据
    fwrite(image, sizeof(Gray), WIDTH * HEIGHT, fp);

    fclose(fp);
}

int main() {
    // 创建一个示例RGB图像
    RGB rgb_image[HEIGHT][WIDTH] = {
        {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}, {0, 255, 255}},
        {{255, 0, 255}, {192, 192, 192}, {128, 128, 128}, {64, 64, 64}, {0, 0, 0}},
        {{255, 165, 0}, {0, 128, 0}, {128, 0, 128}, {0, 0, 128}, {128, 128, 0}},
        {{255, 192, 203}, {75, 0, 130}, {240, 230, 140}, {0, 100, 0}, {255, 69, 0}},
        {{173, 216, 230}, {0, 255, 127}, {50, 205, 50}, {255, 20, 147}, {255, 215, 0}}
    };

    // 打印原始RGB图像
    printf("Original RGB Image:\n");
    print_rgb_image(rgb_image);
    printf("\n");

    // 创建一个灰度图像
    Gray gray_image[HEIGHT][WIDTH];

    // 将RGB图像转换为灰度图像
    rgb_to_grayscale(rgb_image, gray_image);

    // 打印转换后的灰度图像
    printf("Grayscale Image:\n");
    print_gray_image(gray_image);
    printf("\n");

    // 保存灰度图像
    save_gray_image("gray_output.ppm", gray_image);

    printf("Grayscale image saved as gray_output.ppm\n");

    return 0;
}