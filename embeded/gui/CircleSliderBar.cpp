//
// Created by song on 17-6-3.
//

#include <cmath>
#include "CircleSliderBar.h"

CircleSliderBar::CircleSliderBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r1, uint16_t r2, uint16_t min,
                                 uint16_t max, uint16_t value) : Widget(x, y, w, h), r1(r1), r2(r2), min(min), max(max),
                                                                 curvalue(value) {
    xp = 10;
    yp = 10;

}

uint16_t CircleSliderBar::getR1() const {
    return r1;
}

void CircleSliderBar::setR1(uint16_t r1) {
    CircleSliderBar::r1 = r1;
}

uint16_t CircleSliderBar::getR2() const {
    return r2;
}

void CircleSliderBar::setR2(uint16_t r2) {
    CircleSliderBar::r2 = r2;
}

uint16_t CircleSliderBar::getMax() const {
    return max;
}

void CircleSliderBar::setMax(uint16_t max) {
    CircleSliderBar::max = max;
}

uint16_t CircleSliderBar::getMin() const {
    return min;
}

void CircleSliderBar::setMin(uint16_t min) {
    CircleSliderBar::min = min;
}

uint16_t CircleSliderBar::getCurvalue() const {
    return curvalue;
}

void CircleSliderBar::setCurvalue(uint16_t curvalue) {
    CircleSliderBar::curvalue = curvalue;

}

void CircleSliderBar::show() {
//    ltdc_fill(this->x, this->y, this->width, this->height, R888T565(this->backcolor));
    ltdc_aa_circle((uint16_t) (this->x + (this->width / 2)), (uint16_t) (this->y + (this->height / 2)), r1,
                   this->forecolor, this->backcolor);
    float a = (float) (curvalue * 1.0 / (max - min));
    float d = 360 * a;
//    d = 270 - d;
//    debug((const uint8_t *) "%d\n", d);
    uint16_t x1 = (uint16_t) (sinf((float) (d * 3.1416 / 180)) * (r1 - 15) * (-1) + (this->x + (this->width / 2)));


    uint16_t y1 = (uint16_t) (cosf((float) (d * 3.1416 / 180)) * (r1 - 15) + (this->y + (this->height / 2)));

    xp = x1;
    yp = y1;

    ltdc_aa_fcircle(x1, y1, 5, this->forecolor, this->backcolor);


}

void CircleSliderBar::solve(Point point) {

    uint16_t x1 = point.getX();
    uint16_t y1 = point.getY();

    bool toggled = x1 > x && y1 > y && x1 < (x + width) && y1 < (y + height);
    if (toggled) {

        int16_t dx = (int16_t) ((this->x + (this->width / 2)) - x1);
        int16_t dy = (int16_t) (y1 - (this->y + (this->height / 2)));
        float d = (float) ((dy * 1.0) / sqrt(dx * dx + dy * dy));
        d = asinf(d);
        d = (float) (d * 180 / 3.1416);

        if (dx < 0) {
            d = (180 - d);
        }
        d = 90 - d;
        if (d < 0) {
            d += 360;
        }
        setDeg((uint16_t) d);
    }
}

void CircleSliderBar::setDeg(uint16_t deg) {

    ltdc_aa_fcircle(xp, yp, 5, this->backcolor, this->backcolor);

    uint16_t x1 = (uint16_t) (sinf((float) (deg * 3.1416 / 180)) * (r1 - 15) * (-1) + (this->x + (this->width / 2)));

    uint16_t y1 = (uint16_t) (cosf((float) (deg * 3.1416 / 180)) * (r1 - 15) + (this->y + (this->height / 2)));
    xp = x1;
    yp = y1;
    ltdc_aa_fcircle(x1, y1, 5, this->forecolor, this->backcolor);

    setCurvalue((uint16_t) (((deg * 1.0) / 360) * (max - min) + min));

}

void CircleSliderBar::setFocuse(bool focuse) {

}

void CircleSliderBar::setVal(uint16_t val) {

}
