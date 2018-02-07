//
// Created by song on 17-5-8.
//

#include "Point.h"


uint16_t Point::getX() const {
    return x;
}

void Point::setX(uint16_t x) {
    Point::x = x;
}

uint16_t Point::getY() const {
    return y;
}

void Point::setY(uint16_t y) {
    Point::y = y;
}

Point::Point(uint16_t x, uint16_t y) : x(x), y(y) {}
