#pragma once
#include "shape.h"

class Line: public virtual Shape {
    protected:
        COLORREF lineColor;
    public:
        Line() : lineColor(RGB(0, 0, 0)) {};
        void Show(HDC hdc) override;
};