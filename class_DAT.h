#include "inclu.h"

class DAT {
private:
    // 4字节包头 (小端序)
    unsigned char header[4];
    // 4字节包尾 (小端序)
    unsigned char footer[4];
    // 4字节包尾 (小端序)
	unsigned char crc[4]; // CRC校验码 (可选)

public:
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

    // 从.dat文件读取包头和包尾，并输出到屏幕
    bool readFromDatFileAndPrint(const char* filename);
};