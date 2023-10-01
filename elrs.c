#include "elrs.h"

void Sbus_Data_Count(uint8_t *buf)
{
	
	CH[ 0] = ((int16_t)buf[ 2] >> 0 | ((int16_t)buf[ 3] << 8 )) & 0x07FF;
	CH[ 1] = ((int16_t)buf[ 3] >> 3 | ((int16_t)buf[ 4] << 5 )) & 0x07FF;
	CH[ 2] = ((int16_t)buf[ 4] >> 6 | ((int16_t)buf[ 5] << 2 )  | (int16_t)buf[ 6] << 10 ) & 0x07FF;
	CH[ 3] = ((int16_t)buf[ 6] >> 1 | ((int16_t)buf[ 7] << 7 )) & 0x07FF;
	CH[ 4] = ((int16_t)buf[ 7] >> 4 | ((int16_t)buf[ 8] << 4 )) & 0x07FF;
	CH[ 5] = ((int16_t)buf[ 8] >> 7 | ((int16_t)buf[ 9] << 1 )  | (int16_t)buf[10] <<  9 ) & 0x07FF;
	CH[ 6] = ((int16_t)buf[10] >> 2 | ((int16_t)buf[11] << 6 )) & 0x07FF;
	CH[ 7] = ((int16_t)buf[11] >> 5 | ((int16_t)buf[12] << 3 )) & 0x07FF;
	
	CH[ 8] = ((int16_t)buf[13] << 0 | ((int16_t)buf[14] << 8 )) & 0x07FF;
	CH[ 9] = ((int16_t)buf[14] >> 3 | ((int16_t)buf[15] << 5 )) & 0x07FF;
	CH[10] = ((int16_t)buf[15] >> 6 | ((int16_t)buf[16] << 2 )  | (int16_t)buf[17] << 10 ) & 0x07FF;
	CH[11] = ((int16_t)buf[17] >> 1 | ((int16_t)buf[18] << 7 )) & 0x07FF;
	CH[12] = ((int16_t)buf[18] >> 4 | ((int16_t)buf[19] << 4 )) & 0x07FF;
	CH[13] = ((int16_t)buf[19] >> 7 | ((int16_t)buf[20] << 1 )  | (int16_t)buf[21] <<  9 ) & 0x07FF;
	CH[14] = ((int16_t)buf[21] >> 2 | ((int16_t)buf[22] << 6 )) & 0x07FF;
	CH[15] = ((int16_t)buf[22] >> 5 | ((int16_t)buf[23] << 3 )) & 0x07FF;
	rc_ok=1;
	rssi_buf_count=0;
	rx_loss=0;
}
void Rssi_decode(uint8_t *buf)
{
	link_quality=buf[5];
	
	if(rssi_buf_count<10)
	{
	rssi_buf_count++;
	}
}
	int pointer=0;
void RC_Handler(UART_HandleTypeDef *huart)
{
	int count=0;
		pointer=0;
	int x=0,y=0;
	if(huart->Instance==RC_UART_NAME)
	{
    HAL_UART_DMAStop(huart);  
//    char cursur=0;
//	while(cn[cursur]!=0xC8&&cursur<26)cursur++;
//	if(cursur==26||cn[cursur+2]!=0x16)
//	{
//	rc_ok=0;
//	}else//	{
//	Sbus_Data_Count(cn+cursur+1);
//	}
//	HAL_UART_Transmit(&huart2, cn, 52, 2);
//  for(cursur=0;cursur<=51;cursur++)
//	{
//		//HAL_UART_Transmit(&huart2, cn[cursur], 1, 2);
//		cn[cursur]=0;
//	}
	if(cn[2]==0x16)
	{
	Sbus_Data_Count(cn+1);
	}else if(cn[2]==0x14)
	{
		
		Rssi_decode(cn);
	}
	
		if(rssi_buf_count>4)
		{
			rx_loss=1;
		}
		
    HAL_UART_Receive_DMA(huart, cn, 52);     
	}
}