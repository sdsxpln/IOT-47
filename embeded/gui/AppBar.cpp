//
// Created by song on 17-5-30.
//

#include "AppBar.h"
#include "Application.h"


extern const unsigned char gImage_center[8000];
extern const unsigned char gImage_center1[8000];

extern const unsigned char gImage_right1[8000];
extern const unsigned char gImage_right[8000];
extern const unsigned char gImage_left1[8000];
extern const unsigned char gImage_left[8000];

AppBar::AppBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height) :
        Win(x, y, width,
            height) {
    left = new ImgButton(0, 270, 80, 50, (uint8_t *) gImage_left1, (uint8_t *) gImage_left);
    center = new ImgButton(80, 270, 80, 50, (uint8_t *) gImage_center1, (uint8_t *) gImage_center);
    right = new ImgButton(160, 270, 80, 50, (uint8_t *) gImage_right1, (uint8_t *) gImage_right);
//    typedef void* (*FUNC)(void*);//定义FUNC类型是一个指向函数的指针，该函数参数为void*，返回值为void*
//    FUNC left_call = (FUNC)&AppBar::left_toggle;//强制转换func()的类型
//    FUNC center_call = (FUNC)&AppBar::center_toggle;
//    FUNC right_call = (FUNC)&AppBar::right_toggle;
    left->setCallBack(left_toggle);
    center->setCallBack(center_toggle);
    right->setCallBack(right_toggle);
    this->addChild(left);
    this->addChild(center);
    this->addChild(right);
    this->setZ_index(999);

}

void AppBar::left_toggle(void *a) {
    if (currPos > 0) {
        currPos--;
        Application::winList[currPos]->show();
    }
}

void AppBar::center_toggle(void *a) {
    if (currPos != 0) {
        currPos = 0;
        Application::winList[currPos]->show();
    }
//    curPos = 0;
//    winList[curPos]->show();
//    winList[curPos]->setZ_index(winList.num() + 1);
}

void AppBar::right_toggle(void *a) {
    if (currPos < Application::winList.num() - 1) {
        currPos++;
        Application::winList[currPos]->show();
    }
}


