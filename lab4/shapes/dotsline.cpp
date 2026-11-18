#include "dotsline.h"

namespace {
    const long R = 10;
}

DotsLine::DotsLine() : Shape(), Line(), Ell() {
    Line::lineColor = RGB(139, 0, 0);
    Ell::lineColor = RGB(139, 0, 0);
    Ell::filled = true;
    Ell::fillColor = RGB(255, 255, 0);
}

void DotsLine::Show(HDC hdc) {
    long x1 = xs, y1 = ys, x2 = xf, y2 = yf;

    Line::Show(hdc);

    Set(x1 - R, y1 - R, x1 + R, y1 + R);
    Ell::Show(hdc);

    Set(x2 - R, y2 - R, x2 + R, y2 + R);
    Ell::Show(hdc);

    Set(x1, y1, x2, y2);
}