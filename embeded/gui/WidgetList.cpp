//
// Created by song on 17-5-9.
//

#include "WidgetList.h"

WidgetList::WidgetList(uint16_t n) {

}

bool WidgetList::isEmpty() const {
    return (this->n == 0);
}

int WidgetList::size() const {
    return this->n;
}

bool WidgetList::insertw(int pos, Widget *element) {
    if (pos < 0 || pos > this->n) {
        return false;
    }

    WidgetNode *tmp = head;
    for (int i = 0; i < pos; ++i) {
        tmp = tmp->next;
    }
    WidgetNode *p = tmp->next;
    WidgetNode *node = new WidgetNode;
    node->widget = element;
    tmp->next = node;
    node->next = p;
    this->n++;
    return true;
}

bool WidgetList::deletew(int pos) {
    if (pos < 0 || pos > this->n - 1) {
        return false;
    }

    WidgetNode *tmp = head;
    for (int i = 0; i < pos; ++i) {
        tmp = tmp->next;
    }

    WidgetNode *q = tmp->next;
    WidgetNode *p = q->next;
    tmp->next = p;
    delete q;
    this->n--;
    return true;
}

bool WidgetList::update(int pos, Widget *element) {
    if (pos < 0 || pos > this->n - 1) {
        return false;
    }
    WidgetNode *tmp = head;
    for (int i = 0; i < pos + 1; ++i) {
        tmp = tmp->next;
    }
    tmp->widget = element;
    return true;
}

bool WidgetList::find(int pos, Widget *element) const {
    if (pos < 0 || pos > this->n - 1) {
        return false;
    }
    WidgetNode *tmp = head;
    for (int i = 0; i < pos + 1; ++i) {
        tmp = tmp->next;
    }
    element = tmp->widget;
    return true;
}

Widget *WidgetList::operator[](int pos) {
    Widget *element;
    find(pos, element);
    return element;
}

WidgetList::~WidgetList() {
    for (int i = 0; i < this->n; i++) {
        deletew(this->n - i - 1);
    }

    delete head;
    this->n = 0;
}
