//
// Created by song on 17-6-3.
//

#include "WidgetGroup.h"
#include "SliderBar.h"

WidgetGroup::WidgetGroup(uint16_t x, uint16_t y, uint16_t w, uint16_t h) : Widget(x, y, w, h) {

}

void WidgetGroup::setVal(uint16_t val) {

}

void WidgetGroup::addItem(Widget *item) {
    itemList.Insert(itemList.num(), item);
}

void WidgetGroup::show() {
    for (int i = 0; i < itemList.num(); ++i) {
        itemList[i]->show();
    }
}

void WidgetGroup::solve(Point point) {

    uint16_t xp = point.getX();
    uint16_t yp = point.getY();

    if ((xp > x && yp > y && xp < (x + width) && yp < (y + height))) {
        for (uint16_t i = 0; i < itemList.num(); ++i) {
            itemList[i]->setFocuse(false);
            itemList[i]->solve(point);
        }
    }
}

void WidgetGroup::setFocuse(bool focuse) {
    this->focuse = focuse;
}

void WidgetGroup::setBar(SliderBar *bar) {
    WidgetGroup::bar = bar;
}



SliderBar *WidgetGroup::bar;
