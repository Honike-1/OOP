#include "line.h"

void Line::Show(HDC hdc) {
    HPEN hPen = CreateShapePen(lineColor);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    MoveToEx(hdc, xs, ys, NULL);
    LineTo(hdc, xf, yf);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}