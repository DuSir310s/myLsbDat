#include "inclu.h"

class DAT {
private:
    // 4�ֽڰ�ͷ (С����)
    unsigned char header[4];
    // 4�ֽڰ�β (С����)
    unsigned char footer[4];

public:
    // Ĭ�Ϲ��캯������ʼ��Ϊȫ0
    DAT() {
        memset(header, 0, sizeof(header));
        memset(footer, 0, sizeof(footer));
    }

    // ���ð�ͷ (����4�ֽ�����)
    void setHeader(const unsigned char hdr[4]) {
        memcpy(header, hdr, sizeof(header));
    }

    // ���ð�β (����4�ֽ�����)
    void setFooter(const unsigned char ftr[4]) {
        memcpy(footer, ftr, sizeof(footer));
    }

    // ��32λ�������ð�ͷ (С����)
    void setHeaderFromUint32(uint32_t value) {
        header[0] = value & 0xFF;         // ���λ�ֽ� (LSB)
        header[1] = (value >> 8) & 0xFF;
        header[2] = (value >> 16) & 0xFF;
        header[3] = (value >> 24) & 0xFF; // ���λ�ֽ� (MSB)
    }

    // ��32λ�������ð�β (С����)
    void setFooterFromUint32(uint32_t value) {
        footer[0] = value & 0xFF;         // ���λ�ֽ� (LSB)
        footer[1] = (value >> 8) & 0xFF;
        footer[2] = (value >> 16) & 0xFF;
        footer[3] = (value >> 24) & 0xFF; // ���λ�ֽ� (MSB)
    }

    // ��ȡ��ͷ (ͨ��ָ���������)
    void getHeader(unsigned char out[4]) const {
        memcpy(out, header, sizeof(header));
    }

    // ��ȡ��β (ͨ��ָ���������)
    void getFooter(unsigned char out[4]) const {
        memcpy(out, footer, sizeof(footer));
    }

    // ����ͷ��βд��.dat�ļ� (С����)
    bool writeToDatFile(const char* filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Failed to create file " << filename << "\n";
            return false;
        }

        // д���ͷ (4�ֽ�)
        file.write(reinterpret_cast<const char*>(header), sizeof(header));

        // д���β (4�ֽ�)
        file.write(reinterpret_cast<const char*>(footer), sizeof(footer));

        file.close();
        return true;
    }

    // ��ӡ��ͷ��β (������)
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