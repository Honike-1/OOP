#include <cstdlib>
#include "rectangle.h"

void Rect::Show(HDC hdc) {
    const bool solid = filled && !rubber;

    HPEN hPen = CreateShapePen(lineColor);
    HBRUSH hBrush;
    if (solid) {
        hBrush = CreateSolidBrush(fillColor);
    } else {
        hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
    }

    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    long dx = labs(xf - xs);
    long dy = labs(yf - ys);
    Rectangle(hdc, xs - dx, ys - dy, xs + dx, ys + dy);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    if (solid) DeleteObject(hBrush);
}