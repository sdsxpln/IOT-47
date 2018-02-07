//
// Created by song on 17-6-1.
//

#include "TextLabel.h"

void TextLabel::show() {

    ltdc_fill(this->x, this->y, this->width, this->height, R888T565(this->backcolor));
    switch (this->textsize) {
        case f8:
            ltdc_draw_string(x, y, this->text, 8, R888T565(this->forecolor), R888T565(this->backcolor));
            break;
        case f12:
            ltdc_draw_string(x, y, this->text, 12, R888T565(this->forecolor), R888T565(this->backcolor));
            break;
        case f16:
            ltdc_draw_string(x, y, this->text, 16, R888T565(this->forecolor), R888T565(this->backcolor));
            break;
        case f20:
            ltdc_draw_string(x, y, this->text, 20, R888T565(this->forecolor), R888T565(this->backcolor));
            break;
        case f24:
            ltdc_draw_string(x, y, this->text, 24, R888T565(this->forecolor), R888T565(this->backcolor));
            break;
    }
}

void TextLabel::solve(Point point) {

}


void TextLabel::setAlign(Align align) {
    this->align = align;
}

Fsize TextLabel::getTextsize() const {
    return textsize;
}

void TextLabel::setTextsize(Fsize textsize) {
    TextLabel::textsize = textsize;
}

TextLabel::TextLabel(uint16_t x, uint16_t y, uint8_t *text, Fsize textsize, uint32_t forecolor, uint32_t backcolor)
        : text(text), textsize(textsize) {
    this->x = x;
    this->y = y;
    this->forecolor = forecolor;
    this->backcolor = backcolor;

    switch (textsize) {
        case f8:
            this->height = 8;
            this->width = (uint16_t) (strlen(text) * 5);
            break;
        case f12:
            this->height = 12;
            this->width = (uint16_t) (strlen(text) * 7);
            break;
        case f16:
            this->height = 16;
            this->width = (uint16_t) (strlen(text) * 11);
            break;
        case f20:
            this->height = 20;
            this->width = (uint16_t) (strlen(text) * 14);
            break;
        case f24:
            this->height = 14;
            this->width = (uint16_t) (strlen(text) * 17);
            break;
        default:
            this->height = 20;
            this->width = (uint16_t) (strlen(text) * 14);
            break;
    }

}

void TextLabel::setFocuse(bool focuse) {

}

void TextLabel::setText(uint8_t *text) {
    TextLabel::text = text;
}

void TextLabel::setVal(uint16_t val) {

}


