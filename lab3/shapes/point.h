#pragma once
#include "shape.h"

class Point: public Shape {
    public:
        void Show(HDC hdc) override;
};