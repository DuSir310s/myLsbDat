#include "class_DAT.h"
// ʹ��ʾ��
int main() {
    DAT dat;

  

    // ����2����32λ�������� (С����)
    dat.setFooterFromUint32(0xCAFEBABE); // �洢Ϊ BE BA FE CA

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
        unsigned char byte;
        while (inFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
            printf("%02X ", byte);
        }
        std::cout << "\n";
    }

    return 0;
}