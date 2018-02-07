//
// Created by song on 17-5-12.
//

#include "ImgButton.h"

void ImgButton::show() {
    ltdc_draw_picture(this->x, this->y, this->width, this->height, this->backImg);
}

void ImgButton::solve(Point point) {
    Button::solve(point);
}

void ImgButton::handle() {
    if (this->toggled && (~(this->forestate))) {
        this->backImg = clickedImg;
        this->show();
        debug((uint8_t *) "down\n");
    } else if ((~(this->toggled)) && (this->forestate)) {
        this->backImg = normalImg;
        this->show();
        this->callBack(argv);
        debug((uint8_t *) "up\n");
    }
}

void ImgButton::setVal(uint16_t val) {

}

ImgButton::ImgButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                     uint8_t *normalImg, uint8_t *clickedImg)
        : Button(x, y, width, height), clickedImg(clickedImg), normalImg(normalImg) {
    this->backImg = normalImg;
}
