#pragma once
#include "shape.h"

class Rect: public virtual Shape {
    protected:
        COLORREF lineColor;
        COLORREF fillColor;
        bool filled;
    public:
        Rect() : lineColor(RGB(0, 0, 0)), fillColor(RGB(144, 238, 144)), filled(true) {};
        void Show(HDC hdc) override;
};