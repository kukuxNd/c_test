#include <stdio.h>
#include <stdlib.h>

#define WIDTH  256
#define HEIGHT 256
#define FRAMES 30

#pragma pack(push, 1)
typedef struct {
    unsigned char signature[3];
    unsigned char version[3];
} GifHeader;

typedef struct {
    unsigned short width;
    unsigned short height;
    unsigned char flags;
    unsigned char background_color_index;
    unsigned char aspect_ratio;
} LogicalScreenDescriptor;

typedef struct {
    unsigned char block_size;
    unsigned short delay_time;
    unsigned char transparent_color_index;
    unsigned char terminator;
} GraphicControlExtension;

typedef struct {
    unsigned char separator;
    unsigned short left;
    unsigned short top;
    unsigned short width;
    unsigned short height;
    unsigned char flags;
} ImageDescriptor;
#pragma pack(pop)

void create_gradient_frame(unsigned char *frame, int width, int height, int frame_num) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int offset = (y * width + x) * 3;
            frame[offset + 0] = (unsigned char)((x + frame_num) % 256); // R
            frame[offset + 1] = (unsigned char)((y + frame_num) % 256); // G
            frame[offset + 2] = (unsigned char)((x + y + frame_num) % 256); // B
        }
    }
}

void write_color_table(FILE *file) {
    for (int i = 0; i < 256; i++) {
        fputc(i, file); // R
        fputc(i, file); // G
        fputc(i, file); // B
    }
}

void write_image_data(FILE *file, unsigned char *image_data, int width, int height) {
    fputc(8, file); // LZW minimum code size
    for (int y = 0; y < height; y++) {
        fputc(width, file); // Block size
        for (int x = 0; x < width; x++) {
            int offset = (y * width + x) * 3;
            fputc(image_data[offset], file); // Write pixel data
        }
    }
    fputc(0, file); // Block terminator
}

int main() {
    FILE *file = fopen("gradient_output.gif", "wb");
    if (!file) {
        perror("File open error");
        return 1;
    }

    GifHeader header = { {'G', 'I', 'F'}, {'8', '9', 'a'} };
    fwrite(&header, sizeof(header), 1, file);

    LogicalScreenDescriptor screen_desc = { WIDTH, HEIGHT, 0xF7, 0, 0 };
    fwrite(&screen_desc, sizeof(screen_desc), 1, file);

    write_color_table(file);

    unsigned char *frame = (unsigned char *)malloc(WIDTH * HEIGHT * 3);
    if (!frame) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < FRAMES; i++) {
        create_gradient_frame(frame, WIDTH, HEIGHT, i);

        GraphicControlExtension gce = { 0x04, 10, 0, 0x00 };
        fwrite(&gce, sizeof(gce), 1, file);

        ImageDescriptor image_desc = { 0x2C, 0, 0, WIDTH, HEIGHT, 0x00 };
        fwrite(&image_desc, sizeof(image_desc), 1, file);

        write_image_data(file, frame, WIDTH, HEIGHT);
    }

    fputc(0x3B, file); // GIF file terminator

    free(frame);
    fclose(file);

    printf("GIF saved as gradient_output.gif\n");

    return 0;
}