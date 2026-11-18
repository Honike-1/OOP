#pragma once

#include <windows.h>
#include "editor.h"
#include "toolbar.h"

class MainWnd {
    private:
        HWND hwnd;
        MyEditor* editor;
        Toolbar toolbar;

        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

        bool OnCreate();
        void OnSize();
        void OnCommand(WPARAM wParam);
        void OnNotify(LPARAM lParam);
        void OnLButtonDown(LPARAM lParam);
        void OnMouseMove(LPARAM lParam);
        void OnLButtonUp();
        void OnPaint();
        void OnDestroy();
        void UpdateTitle();

    public:
        MainWnd();
        ~MainWnd();

        MainWnd(const MainWnd&) = delete;
        MainWnd& operator=(const MainWnd&) = delete;

        bool Create(HINSTANCE hInstance, int nCmdShow);
        int Run();
};