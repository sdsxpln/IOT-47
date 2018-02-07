//
// Created by song on 17-5-13.
//

#ifndef MOS_ESP8266_H
#define MOS_ESP8266_H

#include "usart.h"
#include "string.h"
#include "../main/mos.h"

extern uint8_t *AT;
extern uint8_t *RET;
extern uint8_t *VERSION;
extern uint8_t *STAMODE;
extern uint8_t *JOINAP;
extern uint8_t *LSAP;
extern uint8_t *QUITAP;
extern uint8_t *UNAUTOJAP;
extern uint8_t *DISCON;
extern uint8_t *ATE;

uint8_t espDetect();

uint8_t espReset();

uint8_t espInfo();

uint8_t espWifi(uint8_t *ssid, uint8_t *passwd);

uint8_t espLAP();

uint8_t espQAP();

uint8_t espCIP(uint8_t *IP, uint8_t *port);

uint8_t espUEcho();

uint8_t espQTran();

#endif //MOS_ESP8266_H
