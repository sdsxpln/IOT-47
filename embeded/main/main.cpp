#include "stm32f429i_discovery_ioe.h"
#include "main.h"
#include "Application.h"
#include "TextLabel.h"
#include "CircleSliderBar.h"
#include "SliderBar.h"
#include "WidgetGroup.h"
#include "EditItem.h"


extern uint32_t criticalnesting;
uint8_t esptaskId = 2;
extern unsigned char gImage_grey[8192];

extern const unsigned char gImage_center[8000];
extern const unsigned char gImage_center1[8000];
extern const unsigned char gImage_chip[8192];
extern const unsigned char gImage_chip_s[8192];
extern const unsigned char gImage_game[8192];
extern const unsigned char gImage_game_s[8192];
extern const unsigned char gImage_weather_s[8192];
extern const unsigned char gImage_weather[8192];
extern const unsigned char gImage_right1[8000];
extern const unsigned char gImage_right[8000];
extern const unsigned char gImage_left1[8000];
extern const unsigned char gImage_left[8000];
extern const unsigned char gImage_line[8192];
extern const unsigned char gImage_line_s[8192];
extern const unsigned char gImage_player[8192];
extern const unsigned char gImage_player_s[8192];
extern const unsigned char gImage_led_s[8192];


void task0();

void task1();

void print_task();

void receive_task();

void tp_task();

void gui_task();


void esp8266_rev();

void scan_task();

extern uint32_t systick_count;

//extern uint8_t doula[153600];
uint8_t test_a, test_b;

extern uint8_t uBuffer[BUFLEN + 2];

static TP_STATE *TP_State;

void led_toggle(void *);

void info_toggle(void *);

void aa_demo(void *);

void edit_demo(void *);

uint8_t save_cmd[100];

void exui(void *);

Application a(1);


uint8_t led_state = 0;
uint16_t longitude_a = 0;
uint16_t longitude_b = 0;
uint16_t longitude_c = 0;

uint16_t latitude_a = 0;
uint16_t latitude_b = 0;
uint16_t latitude_c = 0;

uint8_t temperature = 0;

Win *edit = new Win(0, 0, 240, 270, R888T565(0x626262));

WidgetGroup *widgetGroup = new WidgetGroup(0, 0, 240, 200);
SliderBar *sliderBar1 = new SliderBar(20, 220, 200, 20);

EditItem *editItem1 = new EditItem(15, 35, 70, 40);
EditItem *editItem2 = new EditItem(85, 35, 70, 40);
EditItem *editItem3 = new EditItem(155, 35, 70, 40);

EditItem *editItem4 = new EditItem(15, 120, 70, 40);
EditItem *editItem5 = new EditItem(85, 120, 70, 40);
EditItem *editItem6 = new EditItem(155, 120, 70, 40);


CircleSliderBar *sliderBar = new CircleSliderBar(50, 30, 140, 140, 70, 60);


void LED_Init() {

    RCC->AHB1ENR |= 1 << 6;
    RCC->AHB1ENR |= 1 << 0;
    gpio_set(GPIOG, PIN13 | PIN14, GPIO_MODE_OUT, GPIO_OTYPE_PP, GPIO_SPEED_100M, GPIO_PUPD_PU);
    gpio_set(GPIOA, PIN0, GPIO_MODE_IN, 0, 0, GPIO_PUPD_PD);

};

int main() {
    enter_critical();
    clock_init(8, 360, 2, 4);
    systick_init(CLOCK);
    SCB->CCR |= SCB_CCR_STKALIGN_Msk;
    LED_Init();
    os_init();
    exti_init(GPIO_A, 0, RTIR);
//    nvic_init(2, 2, EXTI0_IRQn, 2);
    nvic_init(1, 0, EXTI0_IRQn, 4);

    ltdc_init();
    IOE_Config();
    sdram_init();
    pool_init();
    ltdc_clear(WHITE);
    usart_init(115200);
    usart5_init(115200);



//    ltdc_draw_picture(100, 100, 64, 64, gImage_alarm);
//    task_create((void *(*)(void *)) task0, 0, 0);
//    task_create((void *(*)(void *)) task1, 0, 1);
//    task_create((void *(*)(void *)) print_task, 0, 2);
//    task_create((void *(*)(void *)) receive_task, 0, 3);
    task_create((void *(*)(void *)) tp_task, 0, 0);
    task_create((void *(*)(void *)) gui_task, 0, 1);
    task_create((void *(*)(void *)) esp8266_rev, 0, esptaskId);
    task_create((void *(*)(void *)) scan_task, 0, 3);

    exit_critical();
    debug((const uint8_t *) "test%d,%c,%s\n", 313, 's', "HGHJH");
    os_start();
}


void tp_task() {
    uint8_t flag = 0;

    while (1) {
        TP_State = IOE_TP_GetState();
        if (TP_State->TouchDetected) {
            debug((const uint8_t *) "x: %d\n", TP_State->X);
            debug((const uint8_t *) "y: %d\n", TP_State->Y);
            uint16_t x = TP_State->X;
            uint16_t y = TP_State->Y;
            semaphore_post(1, x);
            semaphore_post(1, y);
            flag = 1;
        } else if (flag) {
            sprint((char *) "up emit");
            semaphore_post(1, 0);
            semaphore_post(1, 0);
            flag = 0;
        }
        task_sleep(0, 100);
    }
}

void gui_task() {

    enter_critical();
    Win *win = new Win(0, 0, 240, 270, R888T565(0x626262));
    ImgButton *chip = new ImgButton(36, 20, 64, 64, (uint8_t *) gImage_chip, (uint8_t *) gImage_chip_s);
    ImgButton *led = new ImgButton(140, 20, 64, 64, gImage_led, (uint8_t *) gImage_led_s);
    ImgButton *weather = new ImgButton(36, 103, 64, 64, (uint8_t *) gImage_weather, (uint8_t *) gImage_weather_s);
    ImgButton *line = new ImgButton(140, 103, 64, 64, (uint8_t *) gImage_line, (uint8_t *) gImage_line_s);
    ImgButton *game = new ImgButton(36, 186, 64, 64, (uint8_t *) gImage_game, (uint8_t *) gImage_game_s);
    ImgButton *player = new ImgButton(140, 186, 64, 64, (uint8_t *) gImage_player, (uint8_t *) gImage_player_s);
//    ImgButton imgButton(50, 50, 64, 64, (uint8_t *) gImage_game, (uint8_t *) gImage_game_s);
//    ImgButton exButton(50, 200, 64, 64, (uint8_t *) gImage_chip, (uint8_t *) gImage_chip_s);
    a.addWin(win);

    win->addChild(chip);
    win->addChild(led);
    win->addChild(weather);
    win->addChild(line);
    win->addChild(game);
    win->addChild(player);

    led->setCallBack(led_toggle);
    chip->setCallBack(info_toggle);
    line->setCallBack(edit_demo);
    weather->setCallBack(aa_demo);
//    exButton.setCallBack(exui);
    a.show();
//    ltdc_draw_circle(170, 170, 50, R888T565(0x7CFC00));
//    ltdc_draw_line(0, 320, 240, 300, R888T565(0x7CFC00));
//    ltdc_aa_line(0, 0, 100, 240, R888T565(0xffffff), R888T565(0x626262));
//    ltdc_draw_string(100, 100, (uint8_t *) "test", 8,R888T565(0xffffff),R888T565(0x626262));
//    ltdc_draw_font(200,200,'w',24);
    exit_critical();
    a.exec();
//    while (1) {
//        uint16_t x = semaphore_request(1);
//        uint16_t y = semaphore_request(1);
//        if (x > 5 && x < 235 && y > 5 && y < 315) {
//            ltdc_draw_point(TP_State->X, TP_State->Y, BLACK);
//        }
//    }
}

void esp8266_rev() {
    while (1) {

        while (!espDetect()) {
            espReset();
            debug((const uint8_t *) "detecting\n");
        }
        espUEcho();
        espQAP();
        espInfo();
//        espLAP();
        espWifi((uint8_t *) "doula", (uint8_t *) "123456789");
        task_sleep(esptaskId, 1000);
        espCIP((uint8_t *) "112.74.200.146", (uint8_t *) "3001");
        debug((const uint8_t *) "END\n");

        u5_print((const uint8_t *) "AT+CIPMODE=1\r\n");
        task_sleep(esptaskId, 1000);
        u5_print((const uint8_t *) "AT+CIPSEND\r\n");
        task_sleep(esptaskId, 1000);

        u5_print((const uint8_t *) "i send a message from stm32\r\n");
        semaphore_post(3, 1);
//        while (1) {
////            debug(USART5_RX_BUF);
////            u5_rec_reset();
//            u5_print((const uint8_t *) "from stm32\n");
//            task_sleep(esptaskId, 3000);
//        }

        task_suspend(esptaskId);
//        u5_print((const uint8_t *) "AT\r\n");
//        task_sleep(2, 1000);
//        if ((USART5_RX_STA) & (1 << 15)) {
//            debug((const uint8_t *) "receive\r\n");
////            sprint((char *) USART5_RX_BUF);
//            USART5_RX_STA = 0;
//        }
//
//        u5_print((const uint8_t *) "AT+CWLAP\r\n");
//        task_sleep(2, 3000);
//        if ((USART5_RX_STA) & (1 << 15)) {
//            debug((const uint8_t *) "find ap\r\n");
////            sprint((char *) USART5_RX_BUF);
//            USART5_RX_STA = 0;
//        }
//
//        u5_print((const uint8_t *) "AT+ CWJAP =\"doula\",\"1234567890\"\r\n");
//        task_sleep(2, 3000);
//        if ((USART5_RX_STA) & (1 << 15)) {
////            debug((const uint8_t *) "find ap\r\n");
////            sprint((char *) USART5_RX_BUF);
//            USART5_RX_STA = 0;
//            debug((const uint8_t *) "connected\r\n");
//            sprint((char *) USART5_RX_BUF);
//            task_suspend(2);
//        }
    }
}


void led_toggle(void *) {
    if (led_state == 1) {
        LED_RED = 0;
        led_state = 0;
    } else {
        LED_RED = 1;
        led_state = 1;
    }
//    LED_RED = ~LED_RED;

//    u5_print((const uint8_t *) "AT\r\n");

}

void exui(void *) {

    Win *wifi = new Win(0, 0, 240, 270, R888T565(0x606060));
    wifi->setZ_index(2);
    ImgButton *imgButton2 = new ImgButton(100, 100, 64, 64, gImage_grey, gImage_grey);
    imgButton2->setCallBack(led_toggle);
    a.addWin(wifi);
    wifi->addChild(imgButton2);
    a.show();

}

void task0() {

    uint8_t flag = 0;
    while (1) {
        test_a = 100;
        test_b = 200;
        PGout(13) = ~PGout(13);
        if (flag) {
            ltdc_fill(0, 0, 240, 150, RED);
            flag = 0;
        } else {
            ltdc_fill(0, 0, 240, 150, GREEN);
            flag = 1;
        }
        task_sleep(0, 500);

//        os_delay(10000);
        debug((uint8_t *) "task0: a+b = %d\n", test_a + test_b);
    }
}

void task1() {

    uint8_t flag = 0;

    while (1) {
        semaphore_post(3, 7);

        PGout(14) = ~PGout(14);
        test_a = 10;
        test_b = 20;
        if (flag) {
            ltdc_fill(0, 170, 240, 150, RED);
            flag = 0;
        } else {
            ltdc_fill(0, 170, 240, 150, GREEN);
            flag = 1;
        }
        task_sleep(1, 3000);
        debug((uint8_t *) "task1: a+b = %d\n", test_a + test_b);
    }
}


void print_task() {
    while (1) {
        debug((uint8_t *) "os running\n");
        task_sleep(2, 500);
    }
}

void receive_task() {
    while (1) {
//        task_suspend(3);
//        printf("still running\n");
        task_sleep(3, 200);
//        semaphore_request(3);
        uint16_t a = semaphore_request(3);
//        printf("you say: \n");
//        send(uBuffer);

        debug((uint8_t *) "received %d\n", a);
    }
}


void info_toggle(void *) {

    Win *info = new Win(0, 0, 240, 270, R888T565(0x626262));
    TextLabel *osLabel = new TextLabel(20, 20, (uint8_t *) "OS  : MOS", f20);
    TextLabel *guiLabel = new TextLabel(20, 60, (uint8_t *) "GUI : MUI", f20);
    TextLabel *bootLabel = new TextLabel(20, 100, (uint8_t *) "BOOT: NANOBOOT", f20);
    TextLabel *mcuLabel = new TextLabel(20, 140, (uint8_t *) "MCU : STM32F29", f20);
    TextLabel *ramLabel = new TextLabel(20, 180, (uint8_t *) "SDRAM: 64MBIT", f20);
    info->addChild(osLabel);
    info->addChild(guiLabel);
    info->addChild(mcuLabel);
    info->addChild(ramLabel);
    info->addChild(bootLabel);

    a.addWin(info);

    info->show();

}


void edit_demo(void *) {


    widgetGroup->setBackColor(0x626262);
    widgetGroup->setForeColor(0x626262);

    TextLabel *lo = new TextLabel(30, 10, (uint8_t *) "longitude", f24);
    TextLabel *la = new TextLabel(35, 110, (uint8_t *) "latitude", f24);


    sliderBar1->setMin(0);
    sliderBar1->setMax(100);
    sliderBar1->setCurVaule(20);
    sliderBar1->setBackColor(0x626262);
    sliderBar1->setForeColor(0xCDF0FF);
    sliderBar1->setStyle(slider_modern);
    edit->addChild(sliderBar1);


//    edit->addChild(lo);
//    edit->addChild(la);



    editItem1->setMin(0);
    editItem1->setMax(180);
//    editItem1->setSaveData(&longitude_a);

    editItem2->setMin(0);
    editItem2->setMax(60);
//    editItem2->setSaveData(&longitude_b);

    editItem3->setMin(0);
    editItem3->setMax(60);
//    editItem3->setSaveData(&longitude_c);

    editItem4->setMin(0);
    editItem4->setMax(90);
//    editItem4->setSaveData(&latitude_a);

    editItem5->setMin(0);
    editItem5->setMax(60);
//    editItem5->setSaveData(&latitude_b);

    editItem6->setMin(0);
    editItem6->setMax(60);
//    editItem6->setSaveData(&latitude_c);


    editItem1->setBackColor(0x626262);
    editItem1->setForeColor(0xCDF0FF);

    editItem2->setBackColor(0x626262);
    editItem2->setForeColor(0xCDF0FF);

    editItem3->setBackColor(0x626262);
    editItem3->setForeColor(0xCDF0FF);

    editItem4->setBackColor(0x626262);
    editItem4->setForeColor(0xCDF0FF);

    editItem5->setBackColor(0x626262);
    editItem5->setForeColor(0xCDF0FF);

    editItem6->setBackColor(0x626262);
    editItem6->setForeColor(0xCDF0FF);


    widgetGroup->addItem(editItem1);
    widgetGroup->addItem(editItem2);
    widgetGroup->addItem(editItem3);
    widgetGroup->addItem(editItem4);
    widgetGroup->addItem(editItem5);
    widgetGroup->addItem(editItem6);

    widgetGroup->setBar(sliderBar1);
    sliderBar1->setLinkGroup(widgetGroup);
    edit->addChild(widgetGroup);

    a.addWin(edit);
    edit->show();


    editItem1->setVal(118);
    editItem2->setVal(55);
    editItem3->setVal(41);
    editItem4->setVal(32);
    editItem5->setVal(7);
    editItem6->setVal(15);


}


void aa_demo(void *) {
    Win *win = new Win(0, 0, 240, 270, R888T565(0x626262));

//    SliderBar *sliderBar1 = new SliderBar(20, 220, 200, 20);
//    sliderBar1->setMin(0);
//    sliderBar1->setMax(100);
//    sliderBar1->setCurVaule(20);
//    sliderBar1->setBackColor(0x626262);
//    sliderBar1->setForeColor(0xCDF0FF);
//    sliderBar1->setStyle(slider_modern);
//    win->addChild(sliderBar1);

    sliderBar->setBackColor(0x626262);
    sliderBar->setForeColor(0xCDF0FF);
    sliderBar->setMax(50);
    sliderBar->setMin(0);
    win->addChild(sliderBar);

    a.addWin(win);
    win->show();

//    ltdc_aa_line(0, 0, 160, 40, (0x7CFC00), (0));
//    ltdc_aa_line(160, 50, 0, 0, (0x7CFC00), (0));
//    ltdc_aa_line(0, 0, 160, 60, (0x7CFC00), (0));
//    ltdc_aa_line(0, 0, 50, 300, (0x7CFC00), (0));
//    ltdc_aa_circle(120, 100, 99, (0x7CFC00), (0xffffff));
//    ltdc_aa_fcircle(120, 100, 5, (0x7CFC00), (0x626262));
//    ltdc_aa_arc(120, 120, 80, 0, 359, (0x7CFC00), 0);
//    ltdc_aa_arc(120, 120, 40, 0, 359, (0x7CFC00), 0);
//    ltdc_aa_farc(120, 120, 60, 130, 359, (0x7CFC00), 0);
//    ltdc_aa_ring(120, 120, 60, 50, 130, 359, (0x5CAA15), 0xffffff);
//    while (1) {
//        uint16_t r = 0;
//        while (r <= 100) {
//
//            ltdc_aa_fcircle(120, 120, r, (0x7CFC00), (0));
////            delay_ms(10);
////            ltdc_aa_fcircle(120, 120, r, (0), (0));
//            r++;
//        }
//        delay_ms(30);
//        ltdc_aa_fcircle(120, 120, 100, 0, (0));
//    }
//    ltdc_aa_circle(120, 120, 40, (0x7CFC00), (0));
//    ltdc_aa_circle(120, 120, 20, (0x7CFC00), (0));
//    ltdc_aa_circle(120, 120, 5, (0x7CFC00), (0));
//
//    ltdc_draw_point_a(50,300,0xffff);
}

void scan_task() {
    uint16_t resu = semaphore_request(3);
    if (resu == 1) {
        while (1) {
            task_sleep(3, 1000);
            longitude_a = editItem1->getVal();
            longitude_b = editItem2->getVal();
            longitude_c = editItem3->getVal();
            latitude_a = editItem4->getVal();
            latitude_b = editItem5->getVal();
            latitude_c = editItem6->getVal();
            temperature = (uint8_t) sliderBar->getCurvalue();
            uint32_t lo = (uint32_t) ((((longitude_b * 60.0 + longitude_c) / 3600) + longitude_a) * 10000);
            uint32_t la = (uint32_t) ((((latitude_b * 60.0 + latitude_c) / 3600) + latitude_a) * 10000);
            uint8_t *led_S;
            if (led_state == 1) {
                led_S = (uint8_t *) "on";
            } else {
                led_S = (uint8_t *) "off";
            }
            uint8_t los[8] = {0};
            uint8_t las[8] = {0};
            int2str(lo, los);
            int2str(la, las);
            uint8_t *send_data = (uint8_t *) mapply(100);

            printfs(send_data, (uint8_t *) "stm32f4_951_doula_127.0.0.1_12345_%d_%s_%s_%s\r\n", temperature, led_S, los,
                    las);
            if (!strcmp(save_cmd, send_data)) {

                debug(send_data);

                u5_print((const uint8_t *) "stm32f4_951_doula_127.0.0.1_12345_%d_%s_%s_%s\r\n", temperature, led_S, los,
                         las);

                printfs(save_cmd, (uint8_t *) "stm32f4_951_doula_127.0.0.1_12345_%d_%s_%s_%s\r\n", temperature, led_S,
                        los,
                        las);
            }
        }
    }
}