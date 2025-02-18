#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"

// 默认 Lua 5.1 头部长度（根据实际情况调整）
#define LUAC_HEADER_SIZE 12
#define BUFFER_SIZE 4096  // 分块处理缓冲区大小

// 加密/解密函数（CTR模式对称）
int aes_ctr_crypt(const char* input_path, const char* output_path,const uint8_t* key, const uint8_t* iv) 
{
    FILE* in_file = fopen(input_path, "rb");
    if (!in_file) {
        perror("输入文件打开失败");
        return -1;
    }

    FILE* out_file = fopen(output_path, "wb");
    if (!out_file) {
        perror("输出文件打开失败");
        fclose(in_file);
        return -1;
    }

    // 初始化 AES-CTR 上下文
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);

    // 读取并保留文件头
    uint8_t header[LUAC_HEADER_SIZE];
    if (fread(header, 1, LUAC_HEADER_SIZE, in_file) != LUAC_HEADER_SIZE) {
        perror("文件头读取失败");
        fclose(in_file);
        fclose(out_file);
        return -1;
    }
    fwrite(header, 1, LUAC_HEADER_SIZE, out_file);

    // 分块加密/解密
    uint8_t buffer[BUFFER_SIZE];
    size_t bytes_read;
    while (bytes_read = fread(buffer, 1, BUFFER_SIZE, in_file)) 
    {
        AES_CTR_xcrypt_buffer(&ctx, buffer, bytes_read);
        fwrite(buffer, 1, bytes_read, out_file);
    }

    fclose(in_file);
    fclose(out_file);
    return 0;
}

int main() {
    // 示例密钥和 IV（必须与加解密一致）
    const uint8_t key[16] = { 
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c }; // AES-128 密钥
    uint8_t iv[16] = {0}; // 初始化向量（实际应随机生成并存储）

    // 加密示例
    if (aes_ctr_crypt("input.luac", "encrypted.luac", key, iv) != 0) {
        fprintf(stderr, "加密失败\n");
        return 1;
    }

    // 解密示例（使用相同 IV）
    if (aes_ctr_crypt("encrypted.luac", "decrypted.luac", key, iv) != 0) {
        fprintf(stderr, "解密失败\n");
        return 1;
    }

    return 0;
}