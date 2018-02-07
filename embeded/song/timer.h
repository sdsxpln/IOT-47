//
// Created by song on 17-5-13.
//

#ifndef MOS_TIMER_H
#define MOS_TIMER_H

#include "sys.h"
#include "usart.h"

void timer3_init(uint16_t arr);

void TIM3_IRQHandler(void);

#endif //MOS_TIMER_H
