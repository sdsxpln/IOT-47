//
// Created by song on 17-6-3.
//

#ifndef MOS_SLIDERBAR_H
#define MOS_SLIDERBAR_H

#include "Widget.h"

class WidgetGroup;
enum sliderStyle {
    slider_modern, slider_normal
};

class SliderBar : public Widget {
private:
    uint16_t max;
    uint16_t min;
    uint16_t curVaule;
    uint16_t xp;
    sliderStyle style;
    WidgetGroup *linkGroup;
public:
    void setLinkGroup(WidgetGroup *linkGroup);

    SliderBar(uint16_t x = 0, uint16_t y = 0, uint16_t w = 200, uint16_t h = 50);

    sliderStyle getStyle() const;

    void setStyle(sliderStyle style);

    uint16_t getMax() const;

    void setMax(uint16_t max);

    uint16_t getMin() const;

    void setMin(uint16_t min);

    uint16_t getCurVaule() const;

    void setCurVaule(uint16_t curVaule);

    void show() override;

    void solve(Point point) override;

    void slide(uint16_t value);

    void setFocuse(bool focuse) override;

    void setVal(uint16_t val) override;
};


#endif //MOS_SLIDERBAR_H
