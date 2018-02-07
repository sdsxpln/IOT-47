//
// Created by song on 17-5-12.
//

#ifndef MOS_IMGBUTTON_H
#define MOS_IMGBUTTON_H

#include "Button.h"

extern unsigned char gImage_led[8192];
extern unsigned char gImage_led_60[8192];

class ImgButton : public Button {
private:
    uint8_t *clickedImg;
    uint8_t *normalImg;
    uint8_t *backImg;
public:
    ImgButton(uint16_t x = 0, uint16_t y = 0, uint16_t width = 64, uint16_t height = 64,
              uint8_t *normalImg = (uint8_t *) gImage_led, uint8_t *clickedImg = (uint8_t *) gImage_led_60);

    void show() override;

    void solve(Point point) override;

    void handle() override;

    void setVal(uint16_t val) override;
};


#endif //MOS_IMGBUTTON_H
