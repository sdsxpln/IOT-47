//
// Created by song on 17-5-8.
//

#ifndef MOS_BUTTON_H
#define MOS_BUTTON_H

#include "Widget.h"


class Button : public Widget {

protected:
    void static defun();

    void (*callBack)(void *);

    void *argv;
    uint32_t clickedColor;
    uint32_t normalColor;
    uint8_t *clickedImg;
    uint8_t *normalImg;
    bool toggled;
    bool forestate;  //用来记录上一次的点击状态

public:
    Button(uint16_t x = 0, uint16_t y = 0, uint16_t width = 50, uint16_t height = 30,
           uint32_t backcolor = 0x0, uint32_t normalColor = 0xffffff,
           uint32_t clickedColor = 0xffffff);

    void show();

    void clicked();

    void solve(Point);

    virtual void handle();

    void setFocuse(bool focuse) override;

    void setCallBack(void (*fun)(void *), void *argv = nullptr);
};


#endif //MOS_BUTTON_H
