#include "line.h"

void Line::Show(HDC hdc) {
    MoveToEx(hdc, xs, ys, NULL);
    LineTo(hdc, xf, yf);
}