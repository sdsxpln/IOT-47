//
// Created by song on 17-2-11.
//

#include <stm32f429xx.h>
#include "usart.h"
#include "stdarg.h"
#include "timer.h"

uint8_t uBuffer[BUFLEN + 2];

//接收数据状态

uint8_t USART5_TX_BUF[USART5_MAX_SEND_LEN];    //发送缓冲,最大USART3_MAX_SEND_LEN字节
//串口接收缓存区
uint8_t USART5_RX_BUF[USART5_MAX_RECV_LEN];                //接收缓冲,最大USART3_MAX_RECV_LEN个字节.


//通过判断接收连续2个字符之间的时间差不大于10ms来决定是不是一次连续的数据.
//如果2个字符接收间隔超过10ms,则认为不是1次连续数据.也就是超过10ms没有接收到
//任何数据,则表示此次接收完毕.
//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
volatile uint16_t USART5_RX_STA = 0;

//串口设置的步骤
/** 使能时钟
 * 设置IO复用
 * 设置CR寄存器，从而设置 奇偶，停止位，过采样等
 * 设置BRR寄存器，从而设置波特率
 * 设置CR 分别打开接受，发送，接收中断，串口的开关
 * 设置接受优先级
 *
 *
 * */
void usart_init(uint32_t bound) {
    float temp;
    uint16_t z;
    uint16_t f;
    RCC->AHB1ENR |= 1 << 0;//是能GPIOA，与m3不同。gpio在AHB总线上
    RCC->APB2ENR |= 1 << 4;//开启USART时钟
    temp = (float) (90 * 1000000) / (bound * 16);
    z = (uint16_t) temp;
    f = (uint16_t) ((temp - z) * 16);
    z <<= 4;
    z += f;
    gpio_set(GPIOA, PIN9 | PIN10, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU);
    gpio_af_set(GPIOA, 9, 7);
    gpio_af_set(GPIOA, 10, 7);
    //设置波特率
    USART1->BRR = z;
    //16倍过采样
    USART1->CR1 &= ~(1 << 15);
    //设置1位停止位
    USART1->CR2 &= ~(3 << 12);
    //禁止奇偶校验
    USART1->CR1 &= ~(1 << 10);
    //发送使能
    USART1->CR1 |= 1 << 3;
    //接收使能
    USART1->CR1 |= 1 << 2;    //串口接收使能
    //接收中断使能
    USART1->CR1 |= 1 << 5;        //接收缓冲区非空中断使能
    nvic_init(5, 0, USART1_IRQn, 4);//组2，最低优先级
    //uart开启
    USART1->CR1 |= 1 << 13;
}

void usart5_init(uint32_t bound) {

    float temp;
    uint16_t z;
    uint16_t f;
    RCC->AHB1ENR |= 1 << 2;
    RCC->AHB1ENR |= 1 << 3;
    RCC->APB1ENR |= 1 << 20;    //开启USART5时钟
    temp = (float) (45 * 1000000) / (bound * 16);
    z = (uint16_t) temp;
    f = (uint16_t) ((temp - z) * 16);
    z <<= 4;
    z += f;
    gpio_set(GPIOC, PIN12, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU);
    gpio_set(GPIOD, PIN2, GPIO_MODE_AF, GPIO_OTYPE_PP, GPIO_SPEED_50M, GPIO_PUPD_PU);

    gpio_af_set(GPIOC, 12, 8);
    gpio_af_set(GPIOD, 2, 8);
    //设置波特率
    UART5->BRR = z;
//    //16倍过采样
    UART5->CR1 &= ~(1 << 15);
    //设置1位停止位
    UART5->CR2 &= ~(3 << 12);
    //禁止奇偶校验
    UART5->CR1 &= ~(1 << 10);
    //发送使能
    UART5->CR1 |= 1 << 3;
    //接收使能
    UART5->CR1 |= 1 << 2;    //串口接收使能
    //接收中断使能
    UART5->CR1 |= 1 << 5;        //接收缓冲区非空中断使能
    nvic_init(3, 0, UART5_IRQn, 4);//组2，最低优先级
    //uart开启
    UART5->CR1 |= 1 << 13;

    timer3_init(300);  //500ms
    USART5_RX_STA = 0;
    TIM3->CR1 &= ~(1 << 0);

}


void sputc(uint8_t ch) {
    while ((USART1->SR & 0X40) == 0);
    USART1->DR = (uint8_t) ch;
}

void u5_sputc(uint8_t ch) {
    while ((UART5->SR & 0X40) == 0);
    UART5->DR = (uint8_t) ch;
}

void send(uint8_t *s) {
    for (int i = 0; i < s[BUFLEN]; ++i) {
        sputc(s[i]);
    }
    sputc('\n');
    uBuffer[BUFLEN + 1] = 0;
    uBuffer[BUFLEN] = 0;

}

void sprint(char *s) {
    for (int i = 0; i < strlen(s); ++i) {
        sputc(s[i]);
    }
    sputc('\n');
}


void u5_sprint(char *s) {
    for (int i = 0; i < strlen(s); ++i) {
        u5_sputc(s[i]);
    }
    u5_sputc('\n');
}

void debug(const uint8_t *s, ...) {

    va_list arg;
    va_start(arg, s);
    for (uint8_t i = 0; i < strlen(s); ++i) {
        switch (s[i]) {
            case '%': {
                switch (s[i + 1]) {
                    case 'd': {
                        uint32_t vag = va_arg(arg, uint32_t);
                        uint32_t tmp = vag;
                        uint8_t num = 0;
                        if (tmp == 0) {
                            num = 1;
                        }
                        while (tmp) {
                            num++;
                            tmp /= 10;
                        }

                        tmp = vag;
                        uint32_t tmp1 = 1;
                        for (int k = 0; k < num - 1; ++k) {
                            tmp1 *= 10;
                        }
                        for (int j = 0; j < num; ++j) {
                            uint8_t a = (uint8_t) (tmp / tmp1);
                            sputc(a + '0');
                            tmp = tmp % tmp1;
                            tmp1 /= 10;
                        }
                    };
                        break;
                    case 'c': {
                        uint8_t vag = va_arg(arg, uint32_t);
                        sputc(vag);
                    };
                        break;
                    case 's': {
                        uint8_t *p = va_arg(arg, uint8_t*);
                        for (uint16_t j = 0; j < strlen(p); ++j) {
                            sputc(p[j]);
                        }
                    };
                        break;
                    default:
                        break;
                }

            };
                i += 1;
                break;
            default:
                sputc(s[i]);
                break;
        }
    }
    va_end(arg);
}


void u5_print(const uint8_t *s, ...) {
    va_list arg;
    va_start(arg, s);
    for (uint8_t i = 0; i < strlen(s); ++i) {
        switch (s[i]) {
            case '%': {
                switch (s[i + 1]) {
                    case 'd': {
                        uint32_t vag = va_arg(arg, uint32_t);
                        uint32_t tmp = vag;
                        uint8_t num = 0;
                        if (tmp == 0) {
                            num = 1;
                        }
                        while (tmp) {
                            num++;
                            tmp /= 10;
                        }
                        tmp = vag;
                        uint32_t tmp1 = 1;
                        for (int k = 0; k < num - 1; ++k) {
                            tmp1 *= 10;
                        }
                        for (int j = 0; j < num; ++j) {
                            uint8_t a = (uint8_t) (tmp / tmp1);
                            u5_sputc(a + '0');
                            tmp = tmp % tmp1;
                            tmp1 /= 10;
                        }
                    };
                        break;
                    case 'c': {
                        uint8_t vag = va_arg(arg, uint32_t);
                        u5_sputc(vag);
                    };
                        break;
                    case 's': {
                        uint8_t *p = va_arg(arg, uint8_t*);
                        for (uint16_t j = 0; j < strlen(p); ++j) {
                            u5_sputc(p[j]);
                        }
                    };
                        break;
                    default:
                        break;
                }

            };
                i += 1;
                break;
            default:
                u5_sputc(s[i]);
                break;
        }
    }
    va_end(arg);
}


void USART1_IRQHandler(void) {
    uint8_t res;
    if (USART1->SR & (1 << 5)) {
        res = (uint8_t) USART1->DR;
        if (res == 0x0d) {
            uBuffer[BUFLEN + 1] = 1;
            LED_RED = !LED_RED;
            LED_GREEN = !LED_GREEN;
//            uBuffer[BUFLEN + 1] = 0;
//            uBuffer[uBuffer[BUFLEN]] = res;
//            uBuffer[BUFLEN]++;
        } else {
            uBuffer[BUFLEN + 1] = 0;
            uBuffer[uBuffer[BUFLEN]] = res;
            uBuffer[BUFLEN]++;

//            uBuffer[BUFLEN + 1] = 1;
//            uBuffer[BUFLEN] = 0;
//            LED_RED = !LED_RED;
//            LED_GREEN = !LED_GREEN;
        }
    }
}

void UART5_IRQHandler(void) {
    uint8_t res;
//    debug("point1\n");
    if (UART5->SR & (1 << 5))//接收到数据
    {
        res = UART5->DR;
//        sputc(res);
        if ((USART5_RX_STA & (1 << 15)) == 0)//接收完的一批数据,还没有被处理,则不再接收其他数据
        {
            if (USART5_RX_STA < USART5_MAX_RECV_LEN)    //还可以接收数据
            {
                TIM3->CNT = 0;                        //计数器清空
                if (USART5_RX_STA == 0)                //使能定时器7的中断
                {
                    TIM3->CR1 |= 1 << 0;                //使能定时器7
                }
                USART5_RX_BUF[USART5_RX_STA++] = res;    //记录接收到的值
            } else {
                USART5_RX_STA |= 1 << 15;                //强制标记接收完成
            }
        }
    }
}

void u5_rec_reset() {
//    strmap(USART5_RX_BUF, 0, (uint16_t) (USART5_RX_STA & (~(1 << 15))));
    strmap(USART5_RX_BUF, 0, USART5_MAX_RECV_LEN);
    USART5_RX_STA = 0;
}

void rec_reset() {

}
