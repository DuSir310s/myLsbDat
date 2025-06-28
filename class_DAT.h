#include "inclu.h"
#pragma once
bool readFromDatFileAndPrint(const char* filename);
class DAT {
private:
   

public:
    // 4�ֽڰ�ͷ (С����)
    unsigned char header[4];
    // 4�ֽڰ�β (С����)
    unsigned char footer[4];
    // 4�ֽڰ�β (С����)
    unsigned char crc[4]; // CRCУ���� (��ѡ)
    // Ĭ�Ϲ��캯������ʼ��Ϊȫ0
    DAT();

    // ��32λ�������ð�ͷ (С����)
    void setHeaderFromUint32(uint32_t value);
    // ��32λ�������ð�β (С����)
    void setFooterFromUint32(uint32_t value);
	//��32λ��������CRCУ���� (С����)
	void setCrcFromUint32(uint32_t value);

    // ��ȡ��ͷ (ͨ��ָ���������)
    void getHeader(unsigned char out[4]) const;
    // ��ȡ��β (ͨ��ָ���������)
    void getFooter(unsigned char out[4]) const;
	// ��ȡCRCУ���� (ͨ��ָ���������)
	void getCrc(unsigned char out[4]) const;

    bool writeToDatFile(const char* filename);

    // ��ӡ��ͷ��β (������)
    void print() const;

 
};