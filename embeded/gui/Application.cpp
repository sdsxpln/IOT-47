//
// Created by song on 17-5-9.
//

#include "Application.h"
#include "Win.h"

uint8_t currPos = 0;
extern const unsigned char gImage_center[8000];
extern const unsigned char gImage_center1[8000];
extern const unsigned char gImage_right1[8000];
extern const unsigned char gImage_right[8000];
extern const unsigned char gImage_left1[8000];
extern const unsigned char gImage_left[8000];

//按照从小到大的顺序插入到列表中
void Application::addWin(Win *win) {
//    uint8_t i = 0;
//    for (i = 0; i < winList.num(); ++i) {
//        if (win->getZ_index() <= winList[i]->getZ_index()) {
//            break;
//        }
//    }
    win->setZ_index(iterate);
    win->setTask_id(this->task_id);
    winList.Insert(iterate, win);
    currPos = iterate;
    iterate++;
}

void Application::addBar() {

}


void Application::show() {
    ltdc_clear((uint16_t) this->backColor);
    appBar->show();
    winList[currPos]->show();
//    for (uint8_t i = 0; i < winList.num(); ++i) {
//        winList[i]->show();
//    }
}

void Application::exec() {
    while (1) {
        uint16_t x = semaphore_request(this->task_id);
        uint16_t y = semaphore_request(this->task_id);
        Point p(x, y);
        //只对对上层的触摸信号进行处理
        appBar->solve(p);
        winList[(currPos)]->solve(p);
//        for (uint8_t i = 0; i < winList.num(); ++i) {
//            winList[winList.num() - i - 1]->solve(p);
//        }
    }
}

uint16_t Application::getBackColor() const {
    return backColor;
}

void Application::setBackColor(uint16_t backColor) {
    this->backColor = backColor;
}

Application::Application(uint8_t task_id, uint16_t backColor) : task_id(task_id), backColor(backColor) {
    this->iterate = 0;
    appBar = new AppBar(0, 270, 240, 50);

}
List<Win*> Application::winList;
