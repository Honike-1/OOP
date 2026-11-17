#include <cstdlib>
#include "rectangle.h"

void Rect::Show(HDC hdc) {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HBRUSH hBrush = CreateSolidBrush(RGB(144, 238, 144));

    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    long dx = labs(xf - xs);
    long dy = labs(yf - ys);
    Rectangle(hdc, xs - dx, ys - dy, xs + dx, ys + dy);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

void Rect::Draw(HDC hdc) {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    long dx = labs(xf - xs);
    long dy = labs(yf - ys);
    Rectangle(hdc, xs - dx, ys - dy, xs + dx, ys + dy);

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}