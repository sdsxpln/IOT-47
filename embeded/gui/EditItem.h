//
// Created by song on 17-6-3.
//

#ifndef MOS_EDITITEM_H
#define MOS_EDITITEM_H

#include "Widget.h"
#include "WidgetGroup.h"
#include "TextLabel.h"
#include "WidgetGroup.h"

enum EditStyle {
    edit_normal, edit_modern
};

class EditItem : public Widget {
private:
    uint16_t val;
    uint8_t s[4];
    uint8_t * saveData;
//    TextLabel *content;
    EditStyle editStyle;
    uint16_t max;
    uint16_t min;
public:


    uint16_t getMax() const;

    void setMax(uint16_t max);

    uint16_t getMin() const;

    void setMin(uint16_t min);

    EditItem(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

    uint16_t getVal() const;

    void setVal(uint16_t content);


//    void setFocuse(bool focused);

    void setFocuse(bool focuse) override;

    EditStyle getEditStyle() const;

    void setEditStyle(EditStyle editStyle);


//    EditItem(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t forecolor, uint32_t backcolor);

    void show() override;

    void solve(Point point) override;

    virtual ~EditItem();

    uint8_t *getSaveData() const;

    void setSaveData(uint8_t *saveData);
};


#endif //MOS_EDITITEM_H
