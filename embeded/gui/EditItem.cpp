//
// Created by song on 17-6-3.
//

#include "EditItem.h"
#include "SliderBar.h"

uint16_t EditItem::getVal() const {
    return val;
}

void EditItem::setVal(uint16_t val) {
    EditItem::val = val;
    int2str(val, this->s);
//    this->content->setText(s);
//    *(this->saveData) = (uint8_t) val;
    this->show();
}

EditStyle EditItem::getEditStyle() const {
    return editStyle;
}

void EditItem::setEditStyle(EditStyle editStyle) {
    EditItem::editStyle = editStyle;
}

EditItem::EditItem(uint16_t x, uint16_t y, uint16_t w, uint16_t h) : Widget(x, y, w, h) {
    val = 0;
    focuse = false;
    editStyle = edit_modern;
    strmap(s, 0, 4);
//    s = (uint8_t *) mapply(4);
//    saveData = nullptr;
//    setVal(110);

//    content = new TextLabel(x, (uint16_t) (y + 16), (uint8_t *) "0", f24, this->forecolor, this->backcolor);
//    content->setWidth(this->width);

}

//EditItem::EditItem(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t forecolor, uint32_t backcolor)
//        : Widget(x, y, width, height, forecolor, backcolor) {
//    val = 0;
//    editStyle = edit_modern;
//
//}

void EditItem::show() {

    ltdc_fill(x, (uint16_t) (y + 16), this->width, (uint16_t) (height - 16), R888T565(this->backcolor));

    ltdc_draw_string((uint16_t) (x + (this->width - strlen(s) * 24) / 2), (uint16_t) (y + 16), s, 24,
                     R888T565(this->forecolor), R888T565(this->backcolor));

    debug(s);


    ltdc_draw_line(x, (uint16_t) (y + 16), x, (uint16_t) (y + 40), R888T565(forecolor));

    ltdc_draw_line((uint16_t) (x + this->width), (uint16_t) (y + 16), (uint16_t) (x + this->width), (uint16_t) (y + 40),
                   R888T565(forecolor));

//    content->show();

}

void EditItem::solve(Point point) {
    uint16_t x1 = point.getX();
    uint16_t y1 = point.getY();
    bool f = x1 > x && y1 > y && x1 < (x + width) && y1 < (y + height);
    this->setFocuse(f);
}

void EditItem::setFocuse(bool focuse) {

    uint16_t xp = (uint16_t) (x + width / 2);
    uint16_t yp = (uint16_t) (y + 6);
    if (this->focuse && (!focuse)) {
        ltdc_aa_fcircle(xp, yp, 5, backcolor, backcolor);
    }
    if (focuse && (!this->focuse)) {
        ltdc_aa_fcircle(xp, yp, 5, forecolor, backcolor);
        WidgetGroup::bar->setMin(min);
        WidgetGroup::bar->setMax(max);
        WidgetGroup::bar->setCurVaule(val);
    }

    this->focuse = focuse;
}

EditItem::~EditItem() {
//    mfree(s);
}

uint16_t EditItem::getMax() const {
    return max;
}

void EditItem::setMax(uint16_t max) {
    EditItem::max = max;
}

uint16_t EditItem::getMin() const {
    return min;
}

void EditItem::setMin(uint16_t min) {
    EditItem::min = min;
}

uint8_t *EditItem::getSaveData() const {
    return saveData;
}

void EditItem::setSaveData(uint8_t *saveData) {
    EditItem::saveData = saveData;
}

