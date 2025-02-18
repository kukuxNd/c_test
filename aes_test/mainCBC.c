#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"
#define BLOCK_SIZE 16       // AES 块大小
#define CHUNK_SIZE 512      // 每次处理的块大小（必须为 BLOCK_SIZE 的整数倍）
#define LUAC_HEADER_SIZE 12 // Lua 字节码头大小

// PKCS#7 填充函数
void add_padding(uint8_t* data, size_t* len) {
    uint8_t pad_value = BLOCK_SIZE - (*len % BLOCK_SIZE);
    memset(data + *len, pad_value, pad_value);
    *len += pad_value;
}

// 加密函数（保留头 + CBC模式）
int encrypt_luac_cbc(const char* input_path, const char* output_path, 
                    const uint8_t* key, const uint8_t* iv) {
    FILE* in = fopen(input_path, "rb");
    FILE* out = fopen(output_path, "wb");
    if (!in || !out) return -1;

    // 1. 保留未加密的Lua头
    uint8_t header[LUAC_HEADER_SIZE];
    fread(header, 1, LUAC_HEADER_SIZE, in);
    fwrite(header, 1, LUAC_HEADER_SIZE, out);

    // 2. 初始化AES-CBC上下文
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);
    fwrite(iv, 1, BLOCK_SIZE, out); // 将IV写入文件

    // 3. 分块读取、填充、加密
    uint8_t buffer[CHUNK_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, in)) > 0) {
        // 最后一个块需要填充
        if (feof(in) && (bytes_read % BLOCK_SIZE != 0)) {
            add_padding(buffer, &bytes_read);
        }
        AES_CBC_encrypt_buffer(&ctx, buffer, bytes_read);
        fwrite(buffer, 1, bytes_read, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}

// PKCS#7 移除填充
int remove_padding(uint8_t* data, size_t* len) {
    if (*len == 0) return -1;
    uint8_t pad_value = data[*len - 1];
    if (pad_value > BLOCK_SIZE) return -1;
    *len -= pad_value;
    return 0;
}

// 解密函数
int decrypt_luac_cbc(const char* input_path, const char* output_path, 
                    const uint8_t* key) {
    FILE* in = fopen(input_path, "rb");
    FILE* out = fopen(output_path, "wb");
    if (!in || !out) return -1;

    // 1. 读取未加密的Lua头
    uint8_t header[LUAC_HEADER_SIZE];
    fread(header, 1, LUAC_HEADER_SIZE, in);
    fwrite(header, 1, LUAC_HEADER_SIZE, out);

    // 2. 读取IV并初始化AES
    uint8_t iv[BLOCK_SIZE];
    fread(iv, 1, BLOCK_SIZE, in);
    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);

    // 3. 分块解密并处理填充
    uint8_t buffer[CHUNK_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, in)) > 0) {
        AES_CBC_decrypt_buffer(&ctx, buffer, bytes_read);
        //如果是最后一个块，移除填充
        if (feof(in)) {
            if (remove_padding(buffer, &bytes_read) != 0) {
                fclose(in);
                fclose(out);
                return -1;
            }
        }
        fwrite(buffer, 1, bytes_read, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}

int main() {
    // 示例密钥和 IV（必须与加解密一致）
    const uint8_t key[16] = { 
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c }; // AES-128 密钥
    uint8_t iv[16] = {0}; // 初始化向量（实际应随机生成并存储）

    // 加密示例
    if (encrypt_luac_cbc("input.luac", "encrypted.luac", key, iv) != 0) {
        fprintf(stderr, "加密失败\n");
        return 1;
    }

    // 解密示例（使用相同 IV）
    if (decrypt_luac_cbc("encrypted.luac", "decrypted.luac", key) != 0) {
        fprintf(stderr, "解密失败\n");
        return 1;
    }

    return 0;
}