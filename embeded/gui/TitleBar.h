//
// Created by song on 17-5-20.
//

#ifndef MOS_TITLEBAR_H
#define MOS_TITLEBAR_H

#include "color.h"
#include "Point.h"
#include "Compatible.h"

class TitleBar {
private:
    uint16_t height;
    uint16_t width;
    uint16_t backColor;
    uint16_t focusColor;
    uint16_t unfocusColor;
    Point pos;
    uint8_t *title;
public:
    TitleBar(uint16_t height = 30, uint16_t width = 240, uint16_t focusColor = R888T565(0x41424E),
             uint16_t unfocusColor = R888T565(0xF5F6F7));

    void show();
    virtual ~TitleBar();
};


#endif //MOS_TITLEBAR_H
