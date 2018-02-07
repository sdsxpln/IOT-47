//
// Created by song on 17-2-11.
//

#ifndef APP_USART_H
#define APP_USART_H

#include "sys.h"
#include "string.h"

#define BUFLEN 100

#define USART5_MAX_RECV_LEN        500                    //最大接收缓存字节数
#define USART5_MAX_SEND_LEN        300                    //最大发送缓存字节数
#define USART5_RX_EN            1                    //0,不接收;1,接收.

extern uint8_t USART5_RX_BUF[USART5_MAX_RECV_LEN];        //接收缓冲,最大USART3_MAX_RECV_LEN字节
extern uint8_t USART5_TX_BUF[USART5_MAX_SEND_LEN];        //发送缓冲,最大USART3_MAX_SEND_LEN字节
extern volatile uint16_t USART5_RX_STA;

void usart_init(uint32_t bound);

void usart5_init(uint32_t bound);

void sputc(uint8_t ch);

void rec_reset();

void u5_sputc(uint8_t ch);

void send(uint8_t *s);

void sprint(char *s);

void u5_sprint(char *s);

void debug(const uint8_t *s, ...);

void u5_print(const uint8_t *s, ...);

void u5_rec_reset();

void USART1_IRQHandler(void);

void UART5_IRQHandler(void);

#endif //APP_USART_H
