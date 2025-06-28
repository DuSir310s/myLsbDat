#include "inclu.h"
#pragma once
bool readFromDatFileAndPrint(const char* filename);
class DAT {
private:
   

public:
    // 4字节包头 (小端序)
    unsigned char header[4];
    // 4字节包尾 (小端序)
    unsigned char footer[4];
    // 4字节包尾 (小端序)
    unsigned char crc[4]; // CRC校验码 (可选)
    // 默认构造函数：初始化为全0
    DAT();

    // 从32位整数设置包头 (小端序)
    void setHeaderFromUint32(uint32_t value);
    // 从32位整数设置包尾 (小端序)
    void setFooterFromUint32(uint32_t value);
	//从32位整数设置CRC校验码 (小端序)
	void setCrcFromUint32(uint32_t value);

    // 获取包头 (通过指针参数返回)
    void getHeader(unsigned char out[4]) const;
    // 获取包尾 (通过指针参数返回)
    void getFooter(unsigned char out[4]) const;
	// 获取CRC校验码 (通过指针参数返回)
	void getCrc(unsigned char out[4]) const;

    bool writeToDatFile(const char* filename);

    // 打印包头包尾 (调试用)
    void print() const;

 
};