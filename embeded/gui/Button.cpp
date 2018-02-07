//
// Created by song on 17-5-8.
//

#include "Button.h"

Button::Button(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
               uint32_t backcolor, uint32_t normalColor, uint32_t clickedColor) : Widget(
        x, y, width,
        height,
        backcolor), normalColor(normalColor), clickedColor(clickedColor) {
    this->callBack = (void (*)(void *)) defun;
    this->toggled = false;
    this->forestate = false;
    this->argv = nullptr;
}

void Button::show() {
    ltdc_fill(this->x, this->y, this->width, this->height, R888T565(this->backcolor));
}


//void Button::clicked() {
//
//    this->backcolor = clickedColor;
//    this->show();
//    this->backcolor = normalColor;
//    this->show();
//    this->callBack();
//
//}

void Button::solve(Point point) {
//    debug((const uint8_t *) "img button solve\n");
    this->forestate = this->toggled;
    uint16_t xp = point.getX();
    uint16_t yp = point.getY();
    this->toggled = xp > x && yp > y && xp < (x + width) && yp < (y + height);
    if ((xp == 0) && (yp == 0)) {
        this->toggled = false;
    }
    this->handle();
}

void Button::setCallBack(void (*fun)(void *), void *argv) {
    this->callBack = fun;
}

void Button::handle() {
    if (this->toggled && (~(this->forestate))) {
        this->backcolor = clickedColor;
        this->show();
    } else if ((~(this->toggled)) && (this->forestate)) {
        this->backcolor = normalColor;
        this->show();
        this->callBack(argv);
    }
//    if(this->toggled){
//        this->backcolor = clickedColor;
//        this->show();
//    }
//    else{
//        this->backcolor = normalColor;
//        this->show();
//        this->callBack();
//    }
}

void Button::defun() {

}

void Button::setFocuse(bool focuse) {

}





