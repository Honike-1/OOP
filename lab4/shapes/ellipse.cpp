#include "ellipse.h"

void Ell::Show(HDC hdc) {
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

    Ellipse(hdc, xs, ys, xf, yf);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    if (solid) DeleteObject(hBrush);
}