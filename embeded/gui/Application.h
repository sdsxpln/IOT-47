//
// Created by song on 17-5-9.
//

#ifndef MOS_APPLICATION_H
#define MOS_APPLICATION_H

#include "List.h"
#include "Widget.h"
#include "TitleBar.h"
#include "ImgButton.h"
#include "Compatible.h"
#include "AppBar.h"

extern uint8_t currPos;

class Win;

class Application {
private:
    AppBar *appBar;
    uint16_t backColor;
    uint8_t task_id;
    uint8_t iterate;
public:
    static List<Win *> winList;

    Application(uint8_t task_id = 0, uint16_t backColor = 0xffff);

    void addWin(Win *win);

    void addBar();

    void show();

    void exec();

    uint16_t getBackColor() const;

    void setBackColor(uint16_t backColor);

};


#endif //MOS_APPLICATION_H
