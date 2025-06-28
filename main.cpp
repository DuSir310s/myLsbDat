#include "class_DAT.h"
// 使用示例
int main() {
    DAT dat;

  
	dat.setHeaderFromUint32(0x12345678); // 存储为 78 56 34 12);
	dat.setFooterFromUint32(0xABCDEF1E);   // 存储为 1E EF CD AB);
	dat.setCrcFromUint32(0xBCDEF123);  // 存储为 23 F1 DE BC);
   
    std::cout << "DAT content before writing:\n";
    dat.print();

    
    const char* filename = "output.dat";
    if (dat.writeToDatFile(filename)) {
        std::cout << "Successfully created " << filename << "\n";

        // 验证文件内容
        std::cout << "File content (hex): ";
        std::ifstream inFile(filename, std::ios::binary);
        unsigned char byte = 0;
        while (inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
            printf("%02X ", byte);
        }
        std::cout << "\n";
    }
	// 读取并打印.dat文件内容
	std::cout << "Reading from file and printing content:\n";
    bool a = readFromDatFileAndPrint("output.dat");
    return 0;
}
