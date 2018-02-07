//
// Created by song on 17-6-3.
//

#ifndef MOS_CIRCLESLIDERBAR_H
#define MOS_CIRCLESLIDERBAR_H

#include "Widget.h"
#include "TextLabel.h"
#include "antialiasing.h"

class CircleSliderBar : public Widget {
private:
public:
    void setVal(uint16_t val) override;

private:
    TextLabel label;
    uint16_t r1;
    uint16_t r2;
    uint16_t max;
    uint16_t min;
    uint16_t curvalue;
    uint16_t xp;
    uint16_t yp;
public:

    CircleSliderBar(uint16_t x = 0, uint16_t y = 0, uint16_t w = 80, uint16_t h = 80, uint16_t r1 = 40,
                    uint16_t r2 = 40, uint16_t min = 0, uint16_t max = 100, uint16_t value = 20);

    uint16_t getR1() const;

    void setR1(uint16_t r1);

    uint16_t getR2() const;

    void setR2(uint16_t r2);

    uint16_t getMax() const;

    void setMax(uint16_t max);

    uint16_t getMin() const;

    void setMin(uint16_t min);

    uint16_t getCurvalue() const;

    void setCurvalue(uint16_t curvalue);

    void setDeg(uint16_t deg);

    void show() override;

    void solve(Point point) override;

    void setFocuse(bool focuse) override;
};


#endif //MOS_CIRCLESLIDERBAR_H
