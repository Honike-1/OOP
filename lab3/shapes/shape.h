#pragma once

#include <windows.h>

class Shape {
    protected:
        long xs, ys, xf, yf;

    public:
        Shape() : xs(0), ys(0), xf(0), yf(0) {};
        virtual ~Shape() {};

        void Set(long x1, long y1, long x2, long y2);
        virtual void Show(HDC hdc) = 0;
        virtual void Draw(HDC hdc);
};