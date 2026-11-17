#include "shape.h"

void Shape::Set(long x1, long y1, long x2, long y2) {
    xs = x1;
    ys = y1;
    xf = x2;
    yf = y2;
}

void Shape::Draw(HDC hdc) {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Show(hdc);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}