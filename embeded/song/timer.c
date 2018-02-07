//
// Created by song on 17-5-13.
//

#include "timer.h"

//最小延时1ms
void timer3_init(uint16_t arr) {
    RCC->APB1ENR |= 1 << 1;
    arr *= 10;
    TIM3->ARR = --arr;
    TIM3->PSC = 9000 - 1;  //这里不能设置的太大，因为PSC是16位的。不能设置为90000
    TIM3->DIER |= 0x01;
    TIM3->CR1 |= 0x01;
    nvic_init(2, 0, TIM3_IRQn, 4);
    TIM3->CR1 &= ~(1 << 0);
}

void TIM3_IRQHandler(void) {
//    if (TIM3->SR &= 0x01) {
//        LED_RED = !LED_RED;
//        LED_GREEN = !LED_GREEN;
//    }
//    TIM3->SR &= ~(1 << 0);
    if (TIM3->SR & 0X01)//是更新中断
    {
        USART5_RX_STA |= 1 << 15;    //标记接收完成
        TIM3->SR &= ~(1 << 0);        //清除中断标志位
        TIM3->CR1 &= ~(1 << 0);        //关闭定时器7
//        debug((const uint8_t *) "timer3 toggle\n");
    }
}
