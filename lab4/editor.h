#pragma once

#include <windows.h>
#include "shapes/shape.h"

class MyEditor {
    private:
        static const int N = 107;
        Shape* pcshape[N];
        int shapeCount;
        Shape* currentShape;
        int currentType;
        bool isDrawing;
        long startX, startY;

    public:
        MyEditor();
        ~MyEditor();

        MyEditor(const MyEditor&) = delete;
        MyEditor& operator=(const MyEditor&) = delete;

        void Start(int type);
        int  GetType() const { return currentType; }

        void OnLButtonDown(HWND hwnd, long x, long y);
        void OnMouseMove(HWND hwnd, long x, long y);
        void OnLButtonUp(HWND hwnd);
        void OnPaint(HDC hdc);
};