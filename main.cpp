#include "class_DAT.h"
// 使用示例
int main() {
    DAT dat;

  

    // 方法2：从32位整数设置 (小端序)
    dat.setFooterFromUint32(0xCAFEBABE); // 存储为 BE BA FE CA

    // 打印验证
    std::cout << "DAT content before writing:\n";
    dat.print();

    // 写入.dat文件
    const char* filename = "output.dat";
    if (dat.writeToDatFile(filename)) {
        std::cout << "Successfully created " << filename << "\n";

        // 验证文件内容
        std::cout << "File content (hex): ";
        std::ifstream inFile(filename, std::ios::binary);
        unsigned char byte;
        while (inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
            printf("%02X ", byte);
        }
        std::cout << "\n";
    }

    return 0;
}