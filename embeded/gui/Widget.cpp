//
// Created by song on 17-5-8.
//

#include "Widget.h"

Widget::Widget(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t forecolor, uint32_t backcolor)
        : x(x), y(y),
          width(width),
          height(height),
          forecolor(forecolor),
          backcolor(
                  backcolor) {
    this->z_index = 1;
    this->visible = 1;
    this->task_id = 0;
}

//Widget::Widget() {
//    this->x = 0;
//    this->y = 0;
//    this->z_index = 0;
//    this->width = 0;
//    this->height = 0;
//    this->visible = 1;
//    this->backcolor = 0xffff;
//}

void Widget::operator++(int) {
    this->z_index++;
}

void Widget::operator--(int) {
    this->z_index--;
}

void Widget::setBackColor(uint32_t color) {
    this->backcolor = color;
}

void Widget::resize(uint16_t height, uint16_t width) {

    this->height = height;
    this->width = width;
    show();
}

Point Widget::getPos() {
    return Point(this->x, this->y);
}

void Widget::move(Point point) {
    this->x = point.getX();
    this->y = point.getY();
    show();
}

uint8_t Widget::getVisible() const {
    return visible;
}

void Widget::setVisible(uint8_t visible) {
    this->visible = visible;
    show();
}

uint16_t Widget::getZ_index() const {
    return z_index;
}

void Widget::setZ_index(uint16_t z_index) {
    this->z_index = z_index;
}

uint8_t Widget::getTask_id() const {
    return task_id;
}

void Widget::setTask_id(uint8_t task_id) {
    this->task_id = task_id;
}

void Widget::setForeColor(uint32_t color) {
    this->forecolor = color;
}

uint16_t Widget::getWidth() const {
    return width;
}

void Widget::setWidth(uint16_t width) {
    Widget::width = width;
}

uint16_t Widget::getHeight() const {
    return height;
}

void Widget::setHeight(uint16_t height) {
    Widget::height = height;
}
//
//void Widget::show() {
//    sprint("wig_show:point1");
//}
//
//void Widget::solve(Point) {
//
//}



