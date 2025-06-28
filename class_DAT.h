#include "inclu.h"

class DAT {
private:
    // 4�ֽڰ�ͷ (С����)
    unsigned char header[4];
    // 4�ֽڰ�β (С����)
    unsigned char footer[4];
	unsigned char crc[4]; // CRCУ���� (��ѡ)

public:
    // Ĭ�Ϲ��캯������ʼ��Ϊȫ0
    DAT() {
        memset(header, 0, sizeof(header));
        memset(footer, 0, sizeof(footer));
		memset(crc, 0, sizeof(crc)); // ��ʼ��CRCΪȫ0);
    }

    // ���ð�ͷ (����4�ֽ�����)
    void setHeader(const unsigned char hdr[4]) {
        memcpy(header, hdr, sizeof(header));
    }

    // ���ð�β (����4�ֽ�����)
    void setFooter(const unsigned char ftr[4]) {
        memcpy(footer, ftr, sizeof(footer));
    }

	//����CRCУ���� (����4�ֽ�����) 
	void setCrc(const unsigned char crcCode[4]) {
		memcpy(crc, crcCode, sizeof(crc));
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

	//��32λ��������CRCУ���� (С����)
	void setCrcFromUint32(uint32_t value) {
		crc[0] = value & 0xFF;         // ���λ�ֽ� (LSB)
		crc[1] = (value >> 8) & 0xFF;
		crc[2] = (value >> 16) & 0xFF;
		crc[3] = (value >> 24) & 0xFF; // ���λ�ֽ� (MSB)
	}

    // ��ȡ��ͷ (ͨ��ָ���������)
    void getHeader(unsigned char out[4]) const {
        memcpy(out, header, sizeof(header));
    }

    // ��ȡ��β (ͨ��ָ���������)
    void getFooter(unsigned char out[4]) const {
        memcpy(out, footer, sizeof(footer));
    }
	// ��ȡCRCУ���� (ͨ��ָ���������)
	void getCrc(unsigned char out[4]) const {
		memcpy(out, crc, sizeof(crc));
	}

 



    bool writeToDatFile(const char* filename)  
        {  
           FILE* file;  
           errno_t err = fopen_s(&file, filename, "wb");  // ʹ��fopen_s�Զ�����д��ģʽ���ļ�  

           if (err != 0 || !file) {  
               fprintf(stderr, "Error: Failed to create file %s\n", filename);  
               return false;  
           }  

           // д���ͷ (4�ֽ�)  
           if (fwrite(header, sizeof(unsigned int), 1, file) != 1) {  
               fprintf(stderr, "Error: Failed to write header\n");  
               fclose(file);  
               return false;  
           }  

           // д���β (4�ֽ�)  
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

		std::cout << "\nCRC: ";
		for (int i = 0; i < 4; i++) {
			printf("%02X ", crc[i]);
		}
        std::cout << "\n";
    }
    // ��.dat�ļ���ȡ��ͷ�Ͱ�β�����������Ļ
    bool readFromDatFileAndPrint(const char* filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Failed to open file " << filename << "\n";
            return false;
        }

        // ��ȡ��ͷ
        
        file.read((char*)header, sizeof(header));
        if (file.gcount() != sizeof(header)) {
            std::cerr << "Error: Failed to read header from file " << filename << "\n";
            file.close();
            return false;
        }

        // ��ȡ��β
        file.read((char*)(footer), sizeof(footer));
        if (file.gcount() != sizeof(footer)) {
            std::cerr << "Error: Failed to read footer from file " << filename << "\n";
            file.close();
            return false;
        }
		file.read((char*)(crc), sizeof(crc));
		if (file.gcount() != sizeof(crc)) {
			std::cerr << "Error: Failed to read CRC from file " << filename << "\n";
			file.close();
			return false;
		}
        file.close();

        // �������
        print();
        return true;
    }
};