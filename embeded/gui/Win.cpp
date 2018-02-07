//
// Created by song on 17-5-9.
//

#include "Win.h"


void Win::addChild(Widget *widget) {

    uint8_t i = 0;
    for (i = 0; i < widgetList.num(); ++i) {
        if (widget->getZ_index() <= widgetList[i]->getZ_index()) {
            break;
        }
    }
    widgetList.Insert(i, widget);

}

void Win::show() {

//    ltdc_clear(this->backColor);
//    sprint("win_show:point1");
    ltdc_fill(this->x, this->y, this->w, this->h, this->backColor);
//    sprint("win_show:point2");
//    this->titleBar->show();
    for (uint8_t i = 0; i < widgetList.num(); ++i) {
//        sprint("win_show:loop:point1");
        widgetList[i]->show();
//        sprint("win_show:loop:point2");
    }
//    sprint("win_show:point3");
}


uint8_t Win::getZ_index() const {
    return z_index;
}

void Win::setZ_index(uint8_t z_index) {
    this->z_index = z_index;
}

void Win::solve(Point point) {

    uint16_t xp = point.getX();
    uint16_t yp = point.getY();
    if ((xp > x && yp > y && xp < (x + w) && yp < (y + h)) || ((xp == 0) && (yp == 0))) {
//        widgetList[widgetList.num() - 1]->solve(point);
        for (uint8_t i = 0; i < widgetList.num(); ++i) {
            widgetList[widgetList.num() - i - 1]->solve(point);
        }
    }

}

void Win::detect(Point point) {


}

uint16_t Win::getBackColor() const {
    return backColor;
}

void Win::setBackColor(uint16_t backColor) {
    this->backColor = backColor;
}

Win::Win(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t backColor) : x(x), y(y), w(w), h(h),
                                                                               backColor(backColor) {
    z_index = 1;
    task_id = 0;
//    this->titleBar = new TitleBar;

}

Point Win::getPos() {
    return Point(this->x, this->y);
}

void Win::resize(uint16_t height, uint16_t width) {
    this->h = height;
    this->w = width;
}

uint8_t Win::getTask_id() const {
    return task_id;
}

void Win::setTask_id(uint8_t task_id) {
    this->task_id = task_id;
}

Win::~Win() {
//    delete titleBar;
}
