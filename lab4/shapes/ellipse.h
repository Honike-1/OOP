#pragma once
#include "shape.h"

class Ell: public virtual Shape {
    protected:
        COLORREF lineColor;
        COLORREF fillColor;
        bool filled;
    public:
        Ell() : lineColor(RGB(0, 0, 0)), fillColor(RGB(255, 255, 255)), filled(false) {}
        void Show(HDC hdc) override;
};