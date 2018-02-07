//
// Created by song on 17-5-13.
//

#include "esp8266.h"

extern uint8_t esptaskId;

uint8_t *AT = (uint8_t *) "AT\r\n";
uint8_t *RET = (uint8_t *) "AT+RST\r\n";
uint8_t *VERSION = (uint8_t *) "AT+GMR\r\n";
uint8_t *STAMODE = (uint8_t *) "AT+CWMODE=1\r\n";
uint8_t *JOINAP = (uint8_t *) "AT+CWJAP=\"doula\",\"1234567890\"\r\n";
uint8_t *LSAP = (uint8_t *) "AT+CWLAP\r\n";
uint8_t *QUITAP = (uint8_t *) "AT+CWQAP\r\n";
uint8_t *UNAUTOJAP = (uint8_t *) "AT+CWAUTOCONN=0\r\n";
uint8_t *ATE = (uint8_t *) "ATE0\r\n";
uint8_t *DISCON = (uint8_t *) "AT+CIPCLOSE\r\n";


uint8_t espDetect() {
    espQTran();
    u5_print(AT);
    uint8_t flag = 0;
    task_sleep(esptaskId, 1000);
//    debug(USART5_RX_BUF);
    if ((USART5_RX_STA) & (1 << 15)) {
        if (strsub((uint8_t *) "OK", USART5_RX_BUF) != -1) {
            debug("detected module\n");
            flag = 1;
        };
        u5_rec_reset();
    }
    return flag;
}

uint8_t espReset() {
    u5_print(RET);
    task_sleep(esptaskId, 2000);
    u5_rec_reset();
    return 0;
}

uint8_t espInfo() {
    for (uint8_t i = 0; i < 3; ++i) {
        u5_print(VERSION);
        task_sleep(esptaskId, 1000);
        if ((USART5_RX_STA) & (1 << 15)) {
            if (strsub((uint8_t *) "OK", USART5_RX_BUF) != -1) {
                debug(USART5_RX_BUF);
                u5_rec_reset();
                return 1;
            } else
                espReset();
        }
    }
    u5_rec_reset();
    return 0;
}


uint8_t espWifi(uint8_t *ssid, uint8_t *passwd) {
    for (uint8_t i = 0; i < 3; ++i) {
        u5_print(STAMODE);
        task_sleep(esptaskId, 1000);
        if ((USART5_RX_STA) & (1 << 15)) {
            if (strsub((uint8_t *) "OK", USART5_RX_BUF) != -1) {
                debug("STAMODE ON\n");
                u5_rec_reset();
//                espReset();
//                task_sleep(esptaskId, 1000);
                u5_print((const uint8_t *) "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, passwd);
////                u5_print(JOINAP);
//                task_sleep(esptaskId, 1000);
////                debug(USART5_RX_BUF);
////                espReset();
//                u5_rec_reset();
                task_sleep(esptaskId, 5000);
                debug(USART5_RX_BUF);
                if ((USART5_RX_STA) & (1 << 15)) {
                    if (strsub((uint8_t *) "CONNECTED", USART5_RX_BUF) != -1) {
                        u5_rec_reset();
                        debug("wifi connected\n");
                        return 1;
                    } else {
                        debug("can not connect\n");
                        u5_rec_reset();
                    }
                }
            } else {
                u5_rec_reset();
            }
        }
    }
    u5_rec_reset();
    return 0;
}

uint8_t espLAP() {
    for (uint8_t i = 0; i < 3; ++i) {
        u5_print(LSAP);
        task_sleep(esptaskId, 7000);
        debug("point1\n");
        if ((USART5_RX_STA) & (1 << 15)) {
            debug("point2\n");
            debug(USART5_RX_BUF);
            if (strsub((uint8_t *) "OK", USART5_RX_BUF) != -1) {
                debug(USART5_RX_BUF);
                u5_rec_reset();
                return 1;
            } else {
                espReset();
                debug("point3\n");
            }
        }
    }
    return 0;
}

uint8_t espQAP() {
    u5_print(UNAUTOJAP);
    task_sleep(esptaskId, 1000);
    u5_rec_reset();
    u5_print(DISCON);
    task_sleep(esptaskId, 1000);
    u5_rec_reset();
    return 0;
}

uint8_t espCIP(uint8_t *IP, uint8_t *port) {
    for (uint8_t i = 0; i < 3; ++i) {
        u5_rec_reset();
        u5_print((const uint8_t *) "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", IP, port);
        task_sleep(esptaskId, 2000);
        debug(USART5_RX_BUF);
        if ((USART5_RX_STA) & (1 << 15)) {
            if ((strsub((uint8_t *) "OK", USART5_RX_BUF) != -1)) {
                debug((const uint8_t *) "connect server\n");
                u5_rec_reset();
                break;
            } else {
                debug((const uint8_t *) "cannot connect server\n");
                u5_rec_reset();
            }
        }
    }
    debug((const uint8_t *) "quit\n");
    u5_rec_reset();

//    u5_print((const uint8_t *) "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", IP, port);
//    debug((const uint8_t *) "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", IP, port);
//    task_sleep(esptaskId, 5000);
//
//    u5_print("AT+CIPMODE=1\r\n");
//
//    task_sleep(esptaskId, 1000);
//    u5_print("AT+CIPSEND\r\n");
//    task_sleep(esptaskId, 1000);
//
//    if ((USART5_RX_STA) & (1 << 15)) {
//        if (strsub((uint8_t *) "CONNECT", USART5_RX_BUF) != -1) {
//            debug("connect server\n");
//            u5_print("AT+CIPMODE=1\r\n");
//            task_sleep(esptaskId, 1000);
//            u5_print("AT+CIPSEND\r\n");
//            task_sleep(esptaskId, 1000);
//        };
//        u5_rec_reset();
//    }
    return 1;

}

uint8_t espUEcho() {

    for (uint8_t i = 0; i < 3; ++i) {
        u5_print(ATE);
        task_sleep(esptaskId, 500);
        if ((USART5_RX_STA) & (1 << 15)) {
            if (strsub((uint8_t *) "OK", USART5_RX_BUF) != -1) {
                debug(USART5_RX_BUF);
                u5_rec_reset();
                return 1;
            } else {
                u5_rec_reset();
                espReset();
            }
        }
    }
    debug((const uint8_t *) "close cho failed\n");
    return 0;
}

uint8_t espQTran() {
    u5_print((const uint8_t *) "+++");
    task_sleep(esptaskId, 500);
    u5_print((const uint8_t *) "+++");
    task_sleep(esptaskId, 500);
    u5_print((const uint8_t *) "+++");
    task_sleep(esptaskId, 500);
    u5_print((const uint8_t *) "AT+CIPMODE=0\r\n");
    task_sleep(esptaskId, 500);
    u5_rec_reset();
    return 1;
}

