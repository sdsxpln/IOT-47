//
// Created by song on 17-5-20.
//

#include "TitleBar.h"

TitleBar::TitleBar(uint16_t height, uint16_t width, uint16_t focusColor, uint16_t unfocusColor)
        : height(height), width(width), focusColor(focusColor), unfocusColor(unfocusColor) {
    title = (uint8_t *) "MOS & MUI";
    backColor = focusColor;
}

TitleBar::~TitleBar() {

}

void TitleBar::show() {
    ltdc_fill(this->pos.getX(), this->pos.getY(), this->width, this->height, backColor);
    uint16_t cx = (uint16_t) ((this->width - strlen(title) * 16) / 2);
    uint16_t cy = (uint16_t) ((this->height - 20) / 2);
    ltdc_draw_string(cx, cy, this->title, 20, 0xffff, this->backColor);
}
