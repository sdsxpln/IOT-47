//
// Created by song on 17-5-8.
//

#ifndef MOS_WIDGET_H
#define MOS_WIDGET_H

#include "Point.h"
#include "stdint.h"
#include "Compatible.h"

class Widget {
protected:
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint16_t z_index;
    uint32_t backcolor;
    uint32_t forecolor;
    uint8_t visible;
    uint8_t task_id;
    uint16_t val;

public:
    bool focuse;
    Widget(uint16_t x = 0, uint16_t y = 0, uint16_t width = 0, uint16_t height = 0, uint32_t forecolor = 0xffffff,
           uint32_t backcolor = 0x000000);


    void operator++(int);

    void operator--(int);

    void setBackColor(uint32_t color);

    void setForeColor(uint32_t color);

    void resize(uint16_t height, uint16_t width);

    uint16_t getWidth() const;

    void setWidth(uint16_t width);

    uint16_t getHeight() const;

    void setHeight(uint16_t height);

    Point getPos();

    void move(Point);

    uint8_t getVisible() const;

    void setVisible(uint8_t visible);

    uint16_t getZ_index() const;

    void setZ_index(uint16_t z_index);

    virtual void show() = 0;

    virtual void solve(Point) = 0;

    virtual void setFocuse(bool focuse) = 0;

//    virtual void getFocuse(bool focuse) = 0;

    virtual void setVal(uint16_t val) = 0;

    uint8_t getTask_id() const;

    void setTask_id(uint8_t task_id);


};


#endif //MOS_WIDGET_H
