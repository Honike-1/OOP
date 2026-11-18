#include <cstdlib>
#include "cube.h"

Cube::Cube() {
    Line::lineColor = RGB(0, 0, 160);
    Rect::lineColor = RGB(0, 0, 160);
    Rect::filled    = false;
}

void Cube::Show(HDC hdc) {
    const long x1 = xs, y1 = ys, x2 = xf, y2 = yf;
    const long dx = labs(x2 - x1);
    const long dy = labs(y2 - y1);
    const long ox = dx / 2;
    const long oy = dy / 2;

    Set(x1 + ox, y1 - oy, x2 + ox, y2 - oy);
    Rect::Show(hdc);

    Set(x1, y1, x2, y2);
    Rect::Show(hdc);

    for (int i = 0; i < 4; ++i) {
        const long cx = x1 + ((i & 1) ? dx : -dx);
        const long cy = y1 + ((i & 2) ? dy : -dy);
        Set(cx, cy, cx + ox, cy - oy);
        Line::Show(hdc);
    }

    Set(x1, y1, x2, y2);
}