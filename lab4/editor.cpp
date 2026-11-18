#include "editor.h"
#include "resource.h"
#include "shapes/point.h"
#include "shapes/line.h"
#include "shapes/rectangle.h"
#include "shapes/ellipse.h"
#include "shapes/dotsline.h"
#include "shapes/cube.h"

static Shape* CreateShape(int type) {
    switch (type) {
        case IDM_POINT:     return new Point();
        case IDM_LINE:      return new Line();
        case IDM_RECTANGLE: return new Rect();
        case IDM_ELLIPSE:   return new Ell();
        case IDM_DOTSLINE:    return new DotsLine();
        case IDM_CUBE:      return new Cube();
    }
    return nullptr;
}

MyEditor::MyEditor()
    : shapeCount(0), currentShape(nullptr),
      currentType(0), isDrawing(false), startX(0), startY(0) {
    for (int i = 0; i < N; ++i) {
        pcshape[i] = nullptr;
    }
}

MyEditor::~MyEditor() {
    for (int i = 0; i < shapeCount; ++i) {
        delete pcshape[i];
    }
    delete currentShape;
}

void MyEditor::Start(int type) {
    if (!isDrawing) currentType = type;
}

void MyEditor::OnLButtonDown(HWND hwnd, long x, long y) {
    if (!currentType || isDrawing || shapeCount >= N) return;

    currentShape = CreateShape(currentType);
    if (!currentShape) return;

    isDrawing = true;
    SetCapture(hwnd);
    startX = x;
    startY = y;
    currentShape->Set(x, y, x, y);

    HDC hdc = GetDC(hwnd);
    SetROP2(hdc, R2_NOTXORPEN);
    currentShape->Draw(hdc);
    ReleaseDC(hwnd, hdc);
}

void MyEditor::OnMouseMove(HWND hwnd, long x, long y) {
    if (!isDrawing || !currentShape) return;

    HDC hdc = GetDC(hwnd);
    SetROP2(hdc, R2_NOTXORPEN);

    currentShape->Draw(hdc);
    currentShape->Set(startX, startY, x, y);
    currentShape->Draw(hdc);

    ReleaseDC(hwnd, hdc);
}

void MyEditor::OnLButtonUp(HWND hwnd) {
    if (!isDrawing || !currentShape) return;

    isDrawing = false;
    ReleaseCapture();

    HDC hdc = GetDC(hwnd);
    SetROP2(hdc, R2_NOTXORPEN);
    currentShape->Draw(hdc);

    SetROP2(hdc, R2_COPYPEN);
    currentShape->Show(hdc);
    ReleaseDC(hwnd, hdc);

    pcshape[shapeCount++] = currentShape;
    currentShape = nullptr;
}

void MyEditor::OnPaint(HDC hdc) {
    for (int i = 0; i < shapeCount; ++i) {
        pcshape[i]->Show(hdc);
    }
}