#include "shape.h"

void Shape::Set(long x1, long y1, long x2, long y2) {
    xs = x1;
    ys = y1;
    xf = x2;
    yf = y2;
}

HPEN Shape::CreateShapePen(COLORREF color) const {
    if (rubber) {
        return CreatePen(PS_DASH, 1, RGB(0, 0, 0));
    }
    return CreatePen(PS_SOLID, 1, color);
}

void Shape::Draw(HDC hdc) {
    rubber = true;
    Show(hdc);
    rubber = false;
}