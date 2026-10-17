#include <windows.h>
#include <string>
#include "module1.h"
#include "module2.h"
#include "resource.h"

using namespace std;

static char buffer[64] = "";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "App";

    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc    = WndProc;
    wc.hInstance      = hInstance;
    wc.lpszClassName  = CLASS_NAME;
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName   = MAKEINTRESOURCEA(IDM_MENU);

    if (!RegisterClassA(&wc)) {
        MessageBoxA(NULL, "Error", "Error", MB_ICONERROR);
        return 0;
    }

    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);

    HWND hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "Main menu",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { 0 };
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND: {
            WORD id = LOWORD(wParam);

            if (id == IDM_WORK1) {
                Module1Dialog(hwnd);
            }
            if (id == IDM_WORK2) {
                if (Module2Dialog(hwnd, buffer, sizeof(buffer))) {
                    InvalidateRect(hwnd, NULL, TRUE);
                }
            }
            break;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            string text = string(buffer);
            TextOutA(hdc, 20, 30, text.c_str(), (int)text.length());

            EndPaint(hwnd, &ps);
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }

        default: {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }

    return 0;
}