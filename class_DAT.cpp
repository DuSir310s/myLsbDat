#include "class_DAT.h"
 DAT::DAT() {
        memset(header, 0, sizeof(header));
        memset(footer, 0, sizeof(footer));
		memset(crc, 0, sizeof(crc)); // 初始化CRC为全0);
    }


 // 从32位整数设置包头 (小端序)
 void DAT::setHeaderFromUint32(uint32_t value) {
     header[0] = value & 0xFF;         // 最低位字节 (LSB)
     header[1] = (value >> 8) & 0xFF;
     header[2] = (value >> 16) & 0xFF;
     header[3] = (value >> 24) & 0xFF; // 最高位字节 (MSB)
 }

 // 从32位整数设置包尾 (小端序)
 void DAT::setFooterFromUint32(uint32_t value) {
     footer[0] = value & 0xFF;         // 最低位字节 (LSB)
     footer[1] = (value >> 8) & 0xFF;
     footer[2] = (value >> 16) & 0xFF;
     footer[3] = (value >> 24) & 0xFF; // 最高位字节 (MSB)
 }

 //从32位整数设置CRC校验码 (小端序)
 void DAT::setCrcFromUint32(uint32_t value) {
     crc[0] = value & 0xFF;         // 最低位字节 (LSB)
     crc[1] = (value >> 8) & 0xFF;
     crc[2] = (value >> 16) & 0xFF;
     crc[3] = (value >> 24) & 0xFF; // 最高位字节 (MSB)
 }

 // 获取包头 (通过指针参数返回)
 void DAT::getHeader(unsigned char out[4]) const {
     memcpy(out, header, sizeof(header));
 }
 // 获取包尾 (通过指针参数返回)
 void DAT::getFooter(unsigned char out[4]) const {
     memcpy(out, footer, sizeof(footer));
 }
 // 获取CRC校验码 (通过指针参数返回)
 void DAT::getCrc(unsigned char out[4]) const {
     memcpy(out, crc, sizeof(crc));
 }





 bool DAT::writeToDatFile(const char* filename)
 {
     FILE* file;
     errno_t err = fopen_s(&file, filename, "wb");  // 使用fopen_s以二进制写入模式打开文件  

     if (err != 0 || !file) {
         fprintf(stderr, "Error: Failed to create file %s\n", filename);
         return false;
     }

     // 写入包头 (4字节)  
     if (fwrite(header, sizeof(unsigned int), 1, file) != 1) {
         fprintf(stderr, "Error: Failed to write header\n");
         fclose(file);
         return false;
     }

     // 写入包尾 (4字节)  
     if (fwrite(footer, sizeof(unsigned int), 1, file) != 1) {
         fprintf(stderr, "Error: Failed to write footer\n");
         fclose(file);
         return false;
     }

     if (fwrite(crc, sizeof(unsigned int), 1, file) != 1) {
         fprintf(stderr, "Error: Failed to write CRC\n");
         fclose(file);
         return false;
     }
     fclose(file);
 }

 // 打印包头包尾 (调试用)
 void DAT::print() const {
     std::cout << "Header: ";
     for (int i = 0; i < 4; i++) {
         printf("%02X ", header[i]);
     }

     std::cout << "\nFooter: ";
     for (int i = 0; i < 4; i++) {
         printf("%02X ", footer[i]);
     }

     std::cout << "\nCRC: ";
     for (int i = 0; i < 4; i++) {
         printf("%02X ", crc[i]);
     }
     std::cout << "\n";
 }
 // 从.dat文件读取包头和包尾，并输出到屏幕


 bool readFromDatFileAndPrint(const char* filename) {
     DAT rdDat;
     std::ifstream file(filename, std::ios::binary);
     if (!file.is_open()) {
         std::cerr << "Error: Failed to open file " << filename << "\n";
         return false;
     }

     // 读取包头
     file.read((char*)rdDat.header, sizeof(rdDat.header));
     if (file.gcount() != sizeof(rdDat.header)) {
         std::cerr << "Error: Failed to read header from file " << filename << "\n";
         file.close();
         return false;
     }

     // 读取包尾
	  
     file.read((char*)(rdDat.footer), sizeof(rdDat.footer));
     if (file.gcount() != sizeof(rdDat.footer)) {
         std::cerr << "Error: Failed to read footer from file " << filename << "\n";
         file.close();
         return false;
     }

     //读取校验和
     file.read((char*)(rdDat.crc), sizeof(rdDat.crc));
     if (file.gcount() != sizeof(rdDat.crc)) {
         std::cerr << "Error: Failed to read CRC from file " << filename << "\n";
         file.close();
         return false;
     }
     file.close();

     // 输出内容
     rdDat.print();
     return true;
 }