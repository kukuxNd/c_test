
# AES加密解密算法 针对Lua脚本和字节码的加密解密
---
## 涉及两种算法：
1. CBC是固定长度 会末尾添加填充 适合字符串文本
2. CTR不固定长，不会末尾填充，适合针对字节码等容易结构被破坏的文件

- 编译运行
```
gcc -O2 -Wall aes.c mainCBC.c -o cbc_crypt

或者 
gcc -O2 -Wall aes.c mainCTR.c -o cbc_crypt
```

* 这里还有一个有意思的地方，就是使用随机iv向量 并保存到加密文件种