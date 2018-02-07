//
// Created by song on 17-6-3.
//

#include "SliderBar.h"
#include "WidgetGroup.h"

SliderBar::SliderBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h) : Widget(x, y, w, h) {
    this->min = 0;
    this->max = 100;
    this->curVaule = 200;
    if (this->x == 0)
        this->xp = 1;
    else
        this->xp = this->x;
    this->style = slider_modern;
    this->linkGroup = nullptr;
}

uint16_t SliderBar::getMax() const {
    return max;
}

void SliderBar::setMax(uint16_t max) {
    SliderBar::max = max;
}

uint16_t SliderBar::getMin() const {
    return min;
}

void SliderBar::setMin(uint16_t min) {
    SliderBar::min = min;
}

uint16_t SliderBar::getCurVaule() const {
    return curVaule;
}

void SliderBar::setCurVaule(uint16_t curVaule) {

    slide(curVaule);
}


void SliderBar::show() {
    slide(curVaule);

}

void SliderBar::solve(Point point) {
    uint16_t x1 = point.getX();
    uint16_t y1 = point.getY();
    bool toggled = x1 > x && y1 > y && x1 < (x + width) && y1 < (y + height);
    if (toggled) {
        uint16_t a = (uint16_t) (((x1 - this->x) * 1.0 / (this->width)) * (max - min) + min);
        slide(a);
        for (int i = 0; i < linkGroup->itemList.num(); ++i) {
            if(linkGroup->itemList[i]->focuse){
                linkGroup->itemList[i]->setVal(a);
            }
        }
    }
}

void SliderBar::slide(uint16_t value) {
    uint16_t x2 = (uint16_t) (((value - min) * 1.0 / (max - min)) * this->width + this->x);
    uint16_t y2;
    if (style == slider_modern) {
        y2 = (uint16_t) (this->y + 10);
    } else {
        y2 = (uint16_t) (this->y);
    }
//    ltdc_aa_fcircle(xp, y2, 5, this->backcolor, this->backcolor);
    ltdc_fill((uint16_t) (xp - 6), (uint16_t) (y2 - 6), 12, 12, R888T565(this->backcolor));
    ltdc_draw_line(this->x, this->y, this->x + this->width, this->y, R888T565(this->forecolor));
    ltdc_aa_fcircle(x2, y2, 5, this->forecolor, this->backcolor);
    curVaule = value;
    xp = x2;
}

sliderStyle SliderBar::getStyle() const {
    return style;
}

void SliderBar::setStyle(sliderStyle style) {
    SliderBar::style = style;
}

void SliderBar::setFocuse(bool focuse) {

}

void SliderBar::setLinkGroup(WidgetGroup *linkGroup) {
    SliderBar::linkGroup = linkGroup;
}

void SliderBar::setVal(uint16_t val) {

}

