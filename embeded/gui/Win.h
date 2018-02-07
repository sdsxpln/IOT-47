//
// Created by song on 17-5-9.
//

#ifndef MOS_WIN_H
#define MOS_WIN_H

#include "Compatible.h"
#include "TitleBar.h"
#include "Widget.h"
#include "Button.h"
#include "List.h"

//#include "WidgetList.h"
class Win {
private:
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;

//    TitleBar *titleBar;
    uint8_t z_index;
    uint16_t backColor;
    List<Widget *> widgetList;
    uint8_t task_id;


public:
    Win(uint16_t x = 0, uint16_t y = 0, uint16_t w = 240, uint16_t h = 270,
        uint16_t backColor = 0xffff);

    uint16_t getBackColor() const;

    void setBackColor(uint16_t backColor);

    uint8_t getZ_index() const;

    void setZ_index(uint8_t z_index);

    void addChild(Widget *widget);

    void detect(Point point);

    void solve(Point point);

    Point getPos();

    void resize(uint16_t height, uint16_t width);

    virtual void show();


    uint8_t getTask_id() const;

    void setTask_id(uint8_t task_id);

    virtual ~Win();

    //增加一个update方法，这个方法只会对控件进行刷新，而不会整体刷新
};


#endif //MOS_WIN_H
