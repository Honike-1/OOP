#include "point.h"

void Point::Show(HDC hdc) {
    const int r = 2;

    for (int dx = -r; dx <= r; dx++) {
        for (int dy = -r; dy <= r; dy++) {
            SetPixel(hdc, xs + dx, ys + dy, RGB(0, 0, 0));
        }
    }
}