//
// Created by song on 17-5-8.
//

#ifndef MOS_POINT_H
#define MOS_POINT_H


#include "stdint.h"

class Point {
private:

    uint16_t x;
    uint16_t y;

public:

    Point(uint16_t x = 0, uint16_t y = 0);

    uint16_t getX() const;

    void setX(uint16_t x);

    uint16_t getY() const;

    void setY(uint16_t y);
};


#endif //MOS_POINT_H
