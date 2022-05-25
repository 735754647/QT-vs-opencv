#ifndef _BSP_PROTOCOL_H
#define _BSP_PROTOCOL_H

#include <iostream>
#include <QString>

#define PROTOCOL_CMD_ID 0XA5    //���忪ʼ֡ͷ
#define OFFSET_BYTE 8           //�����ݶ��⣬����������ռ�ֽ���

typedef struct
{
    struct
    {
        uint8_t  sof = 0;
        uint16_t data_length = 0;
        uint8_t  crc_check = 0;     //֡ͷCRCУ��
    } header;                       //����֡ͷ
    uint16_t cmd_id = 0;	 		//����ID
    uint16_t frame_tail = 0; 		//֡βCRCУ��
} protocol;

typedef struct
{
    uint16_t cmd_id = 0;
    uint16_t flags_register = 0;
    float   *data;
    uint8_t  float_len = 0;//float��Ч���ݳ���
    uint8_t  *utf8_data;   //uint8_t��Ч���ݳ���
    uint16_t utf8_data_len = 0;
}protocol_info;


class SerialProtocol
{
public:
    SerialProtocol();

    protocol_info tx_info;
    protocol_info rx_info;
    protocol rx_pro;
    uint16_t rx_date_length;

    /*���·�������֡�������㷢������֡����*/
    void get_protocol_send_data
    (uint16_t send_id,	 	  //�ź�id
     uint16_t flags_register, //16λ�Ĵ���
     float    *tx_data,		  //�����͵�float����
     uint8_t  float_length,   //float�����ݳ���
     uint8_t  *tx_buf,		  //�����͵�����֡
     uint16_t *tx_buf_len);	  //�����͵�����֡����

     bool get_protocol_len
    (uint8_t  *rx_buf,			//���յ���ԭʼ����
     uint16_t *rx_pos,			//ԭʼ����ָ��
     uint16_t *thisdataLength);	//��Ҫ���յ������ܳ���

    /*�������ݴ���*/
    bool get_protocol_info
    (uint8_t  *rx_buf,			//���յ���ԭʼ����
     uint16_t *rx_pos,			//ԭʼ����ָ��
     uint16_t *flags_register,	//�������ݵ�16λ�Ĵ�����ַ
     float    *rx_data);		//���յ�float���ݴ洢��ַ
};

#endif
