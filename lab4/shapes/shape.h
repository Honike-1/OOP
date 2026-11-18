#pragma once

#include <windows.h>

class Shape {
    protected:
        long xs, ys, xf, yf;
        bool rubber;
        HPEN CreateShapePen(COLORREF color) const;

    public:
        Shape() : xs(0), ys(0), xf(0), yf(0), rubber(false) {};
        virtual ~Shape() {};

        void Set(long x1, long y1, long x2, long y2);
        virtual void Show(HDC hdc) = 0;
        void Draw(HDC hdc);
};