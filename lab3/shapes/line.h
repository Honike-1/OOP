#pragma once
#include "shape.h"

class Line: public Shape {
    public:
        void Show(HDC hdc) override;
};