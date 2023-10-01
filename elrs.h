#include "stm32f4xx_hal.h"
#ifndef __ELRS_H
#define __ERLS_H 	   

//v1.0 developer:youverybads
//2023 10 01




/*usage:
1.����Ҫʹ�õĴ��ڣ����úò�����416000�����Ǹ����ڵ�global interupt������ʹ�ܸô���dma��rxͨ��
2.�����ɵĹ����ҵ��ô��ڳ�ʼ�����֣�ʹ��idle�жϣ������������ݵ�user content���棺

HAL_NVIC_EnableIRQ(UART4_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,2,4);
__HAL_UART_CLEAR_IDLEFLAG(&huart2);  				
__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);

3.��it�ļ��ｫRC_Handler(*huart�����ﻻ����Ĵ��ںţ�)






�����ʱ�佫��ͼ������๦��

2023.10.01 ��������ok


*/













//the define below are for migration

#define RC_UART_NAME USART2




//macro define

#define ticks_to_us(x) ((x - 992) * 5 / 8 + 1500)
#define RC_MAX 1792
#define RC_MIN 192





#define u16 uint16_t
#define u8 uint8_t






uint16_t CH[16];  // rc channel value
uint8_t  rc_ok = 0; 
uint8_t rc_thr_ok=0;
uint8_t cn[52];//rc buf
int rc_i;
int rc_count;
uint8_t rx_loss=0;
char rssi_buf_count=0;

uint8_t throttle_buff[18]={31};


uint8_t link_quality=0;



void Sbus_Data_Count(uint8_t *buf);
void Rssi_decode(uint8_t *buf);
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart);
#endif