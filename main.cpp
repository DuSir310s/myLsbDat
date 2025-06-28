#include "class_DAT.h"
// ʹ��ʾ��
int main() {
    DAT dat;

  
	dat.setHeaderFromUint32(0x12345678); // �洢Ϊ 78 56 34 12);
    // ����2����32λ�������� (С����)
	dat.setFooterFromUint32(0xABCDEF1);   // �洢Ϊ 1F EF CD AB);
	dat.setCrcFromUint32(0xBCDEF123);  // �洢Ϊ 23 F1 DE BC);
    // ��ӡ��֤
    std::cout << "DAT content before writing:\n";
    dat.print();

    // д��.dat�ļ�
    const char* filename = "output.dat";
    if (dat.writeToDatFile(filename)) {
        std::cout << "Successfully created " << filename << "\n";

        // ��֤�ļ�����
        std::cout << "File content (hex): ";
        std::ifstream inFile(filename, std::ios::binary);
        unsigned char byte = 0;
        while (inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
            printf("%02X ", byte);
        }
        std::cout << "\n";
    }
	// ��ȡ����ӡ.dat�ļ�����
	std::cout << "Reading from file and printing content:\n";
    bool a = dat.readFromDatFileAndPrint("output.dat");
    return 0;
}