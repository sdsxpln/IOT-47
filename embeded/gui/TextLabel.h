//
// Created by song on 17-6-1.
//

#ifndef MOS_TEXTLABEL_H
#define MOS_TEXTLABEL_H

#include "Widget.h"
#include "color.h"

enum Align {
    f_left, f_center, f_right
};
enum Fsize {
    f8, f12, f16, f20, f24
};

class TextLabel : public Widget {
private:
    uint8_t *text;
    Fsize textsize;
    Align align;
public:
    TextLabel(uint16_t x = 0, uint16_t y = 0, uint8_t *text = (uint8_t *) "UNDEF", Fsize textsize = f16,
              uint32_t forecolor = 0xffffff, uint32_t backcolor = 0x626262);

    void setAlign(Align);

    void show() override;

    Fsize getTextsize() const;

    void setTextsize(Fsize textsize);

    void solve(Point point) override;

    void setFocuse(bool focuse) override;

    void setText(uint8_t *text);

    void setVal(uint16_t val) override;
};


#endif //MOS_TEXTLABEL_H
