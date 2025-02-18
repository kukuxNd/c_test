#include <stdio.h>
#include <stdlib.h>

// 定义图像的宽度和高度
#define WIDTH  256
#define HEIGHT 256

// 定义RGB结构体来表示图像中的一个像素
typedef struct {
    unsigned char r, g, b;
} RGB;

// 生成一个简单的渐变图像
void generate_image(RGB image[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            image[i][j].r = (unsigned char)i;  // 红色分量
            image[i][j].g = (unsigned char)j;  // 绿色分量
            image[i][j].b = (unsigned char)((i + j) / 2);  // 蓝色分量
        }
    }
}

// 保存图像为PPM格式
void save_image(const char *filename, RGB image[HEIGHT][WIDTH]) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("File open error");
        exit(EXIT_FAILURE);
    }

    // 写入PPM文件头
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    // 写入像素数据
    fwrite(image, sizeof(RGB), WIDTH * HEIGHT, fp);

    fclose(fp);
}

int main() {
    // 创建一个图像
    RGB image[HEIGHT][WIDTH];

    // 生成图像
    generate_image(image);

    // 保存图像
    save_image("output.ppm", image);

    printf("Image saved as output.ppm\n");

    return 0;
}