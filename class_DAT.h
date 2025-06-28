#include "inclu.h"

class DAT {
private:
    // 4字节包头 (小端序)
    unsigned char header[4];
    // 4字节包尾 (小端序)
    unsigned char footer[4];

public:
    // 默认构造函数：初始化为全0
    DAT() {
        memset(header, 0, sizeof(header));
        memset(footer, 0, sizeof(footer));
    }

    // 设置包头 (接受4字节数组)
    void setHeader(const unsigned char hdr[4]) {
        memcpy(header, hdr, sizeof(header));
    }

    // 设置包尾 (接受4字节数组)
    void setFooter(const unsigned char ftr[4]) {
        memcpy(footer, ftr, sizeof(footer));
    }

    // 从32位整数设置包头 (小端序)
    void setHeaderFromUint32(uint32_t value) {
        header[0] = value & 0xFF;         // 最低位字节 (LSB)
        header[1] = (value >> 8) & 0xFF;
        header[2] = (value >> 16) & 0xFF;
        header[3] = (value >> 24) & 0xFF; // 最高位字节 (MSB)
    }

    // 从32位整数设置包尾 (小端序)
    void setFooterFromUint32(uint32_t value) {
        footer[0] = value & 0xFF;         // 最低位字节 (LSB)
        footer[1] = (value >> 8) & 0xFF;
        footer[2] = (value >> 16) & 0xFF;
        footer[3] = (value >> 24) & 0xFF; // 最高位字节 (MSB)
    }

    // 获取包头 (通过指针参数返回)
    void getHeader(unsigned char out[4]) const {
        memcpy(out, header, sizeof(header));
    }

    // 获取包尾 (通过指针参数返回)
    void getFooter(unsigned char out[4]) const {
        memcpy(out, footer, sizeof(footer));
    }

    // 将包头包尾写入.dat文件 (小端序)
    bool writeToDatFile(const char* filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Failed to create file " << filename << "\n";
            return false;
        }

        // 写入包头 (4字节)
        file.write(reinterpret_cast<const char*>(header), sizeof(header));

        // 写入包尾 (4字节)
        file.write(reinterpret_cast<const char*>(footer), sizeof(footer));

        file.close();
        return true;
    }

    // 打印包头包尾 (调试用)
    void print() const {
        std::cout << "Header: ";
        for (int i = 0; i < 4; i++) {
            printf("%02X ", header[i]);
        }

        std::cout << "\nFooter: ";
        for (int i = 0; i < 4; i++) {
            printf("%02X ", footer[i]);
        }
        std::cout << "\n";
    }
};