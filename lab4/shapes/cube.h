#pragma once
#include "line.h"
#include "rectangle.h"

class Cube: public Line, public Rect {
    public:
        Cube();
        void Show(HDC hdc) override;
};