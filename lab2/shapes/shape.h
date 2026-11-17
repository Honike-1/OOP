#pragma once

#include <windows.h>

class Shape {
    protected:
        long xs, ys, xf, yf;

    public:
        virtual ~Shape() {};

        void Set(long x1, long y1, long x2, long y2);
        virtual void Show(HDC hdc) = 0;
        virtual void Draw(HDC hdc);
};