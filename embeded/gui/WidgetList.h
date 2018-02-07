//
// Created by song on 17-5-9.
//

#ifndef MOS_WIDGETLIST_H
#define MOS_WIDGETLIST_H

#include "Widget.h"

class WidgetNode {
public:
    Widget *widget;
    WidgetNode *next;
};

class WidgetList {
private:
    uint16_t n;
    WidgetNode *head;
public:
    WidgetList(uint16_t n = 0);

    bool isEmpty() const;

    int size() const;

    bool insertw(int pos, Widget *element);

    bool deletew(int pos);

    bool update(int pos,  Widget *element);

    bool find(int pos, Widget *element) const;

    Widget* operator[](int pos);

    ~WidgetList();
};


#endif //MOS_WIDGETLIST_H
