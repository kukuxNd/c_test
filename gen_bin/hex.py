# 生成二进制文件
def hex_to_bin(hex_file, bin_file):
    with open(hex_file, 'r') as hf:
        hex_data = hf.read().strip()
    
    bin_data = bytes.fromhex(hex_data)
    
    with open(bin_file, 'wb') as bf:
        bf.write(bin_data)

if __name__ == "__main__":
    hex_file = 'bytecode.hex'
    bin_file = 'bytecode.bin'
    hex_to_bin(hex_file, bin_file)
    print(f"Converted {hex_file} to {bin_file} in binary format.")