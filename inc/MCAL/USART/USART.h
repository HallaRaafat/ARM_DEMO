/*
 * USART.h
 *
 *  Created on: Apr 14, 2024
 *      Author: Halla Raafat
 */

#ifndef USART_H_
#define USART_H_

#include "MCAL/USART/USART_Cfg.h"
#include "stdint.h"

/***********************************************/
/******         Defines           **************/
/***********************************************/

#define USART1 				 (void *)0x40011000
#define USART2 			     (void *)0x40004400
#define USART6 				 (void *)0x40011400

#define USART_WL_8BIT_DATA		0X00000000
#define USART_WL_9BIT_DATA		0X00001000

#define USART_PARITY_ENABLE		0X00000400
#define USART_PARITY_DISABLE	0X00000000

#define USART_EVEN_PARITY		0X00000000
#define USART_ODD_PARITY		0X00000200

#define USART_STOP_BIT_1		0X00000000
#define USART_STOP_BIT_2		0X00002000

#define USART_OVS_8			    0X00000008         	//0X00008000
#define USART_OVS_16			0X00000010          // 0X00000000

#define FCPU					16000000
#define	Done					1
#define	NOT_Done				0


typedef void (*CB_t)(void);

typedef struct
{
        void  * USART_ID;
		uint32_t 	BaudRate;
		uint32_t 	WordLength;
		uint32_t 	ParityControl;
		uint32_t 	ParityType;
		uint32_t 	StopBits;
		uint32_t 	OverSamplingMode;


}
USART_Cfg_t ;

typedef enum
{
	USART_OK,
	USART_NOK,
}USART_Error_t;


typedef struct
{
 USART_Names_t  	USART_Num; // only in configured names in USART_Cfg.h
 uint8_t *	        Ptr_Buffer;
 uint32_t             Length;
 CB_t               CallBack; // called after finishing Request
}User_Request_t;

USART_Error_t USART_Init (void);

USART_Error_t USART_SendByte(User_Request_t * Ptr_Request);
USART_Error_t USART_GetByte(User_Request_t * Ptr_Request);
USART_Error_t USART_SendBufferAsync(User_Request_t * Ptr_Request);
USART_Error_t USART_ReceiveBufferAsync(User_Request_t * Ptr_Request);









#endif /* USART_H_ */
