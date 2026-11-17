#pragma once

#include <windows.h>
#include "shapes/shape.h"

class MainWnd {
    private:
        static const int N = 107;
        HWND hwnd;
        Shape* pcshape[N];
        int shapeCount;
        Shape* currentShape;
        int currentType;
        bool isDrawing;
        long startX, startY;

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

        void OnCreate();
        void OnCommand(WPARAM wParam);
        void OnLButtonDown(LPARAM lParam);
        void OnMouseMove(LPARAM lParam);
        void OnLButtonUp();
        void OnPaint();
        void OnDestroy();
        void UpdateTitle();
    public:
        MainWnd();
        ~MainWnd();

        bool Create(HINSTANCE hInstance, int nCmdShow);
        int Run();
};