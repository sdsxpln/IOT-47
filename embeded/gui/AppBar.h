//
// Created by song on 17-5-30.
//

#ifndef MOS_APPBAR_H
#define MOS_APPBAR_H

#include "Win.h"
#include "ImgButton.h"
class Application;
extern uint8_t currPos;

class AppBar : public Win {
private:
    ImgButton *left;
    ImgButton *center;
    ImgButton *right;


public:
    AppBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

//    List<Win *> winList;

    void static left_toggle(void*);

    void static center_toggle(void*);

    void static right_toggle(void*);
};


#endif //MOS_APPBAR_H
