#pragma once
#include "shape.h"

class Ell: public Shape {
    public:
        void Show(HDC hdc) override;
        void Draw(HDC hdc) override;
};