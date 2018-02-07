//
// Created by song on 17-6-3.
//

#ifndef MOS_WIDGHTGROUP_H
#define MOS_WIDGHTGROUP_H

#include "List.h"
#include "Widget.h"


class SliderBar;

class WidgetGroup : public Widget {
private:
    List<Widget *> itemList;
public:
    friend class SliderBar;

    static SliderBar *bar;

    static void setBar(SliderBar *bar);

    WidgetGroup(uint16_t x = 0, uint16_t y = 0, uint16_t w = 40, uint16_t h = 40);

    void addItem(Widget *item);

    void show() override;

    void solve(Point point) override;

    void setFocuse(bool focuse) override;

    void setVal(uint16_t val) override;

};


#endif //MOS_WIDGHTGROUP_H
