#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "shapes/shape.h"
#include "shapes/point.h"
#include "shapes/line.h"
#include "shapes/rectangle.h"
#include "shapes/ellipse.h"

const int maxShapes = 106;
Shape** pcshape = nullptr;
int shapeCount = 0;
Shape* currentShape = nullptr;
int currentType = 0;
bool isDrawing = false;
long startX, startY;

static Shape* CreateShape(int type) {
    switch (type) {
        case IDM_POINT: return new Point();
        case IDM_LINE: return new Line();
        case IDM_RECTANGLE: return new Rect();
        case IDM_ELLIPSE: return new Ell();
    }
    return nullptr;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            pcshape = new Shape*[maxShapes];
            for (int i = 0; i < maxShapes; ++i) {
                pcshape[i] = nullptr;
            }
            return 0;
        }

        case WM_COMMAND: {
            int id = LOWORD(wParam);
            if (id >= IDM_POINT && id <= IDM_ELLIPSE && !isDrawing) {
                currentType = id;
            }
            return 0;
        }

        case WM_LBUTTONDOWN: {
            if (currentType && !isDrawing && shapeCount < maxShapes) {
                currentShape = CreateShape(currentType);
                if (!currentShape) return 0;
                isDrawing = true;
                SetCapture(hwnd);
                startX = GET_X_LPARAM(lParam);
                startY = GET_Y_LPARAM(lParam);
                currentShape->Set(startX, startY, startX, startY);
            }
            return 0;
        }

        case WM_MOUSEMOVE: {
            if (isDrawing && currentShape) {
                HDC hdc = GetDC(hwnd);
                SetROP2(hdc, R2_NOTXORPEN);

                currentShape->Draw(hdc);
                currentShape->Set(startX, startY, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                currentShape->Draw(hdc);

                ReleaseDC(hwnd, hdc);
            }
            return 0;
        }

        case WM_LBUTTONUP: {
            if (isDrawing && currentShape) {
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
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            if (pcshape) {
                for (int i = 0; i < shapeCount; ++i) {
                    if (pcshape[i]) {
                        pcshape[i]->Show(hdc);
                    }
                }
            }

            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_INITMENUPOPUP: {
            HMENU hPopup = (HMENU)wParam;
            if (hPopup == GetSubMenu(GetMenu(hwnd), 1)) {
                for (int id = IDM_POINT; id <= IDM_ELLIPSE; ++id)
                    CheckMenuItem(hPopup, id,
                        MF_BYCOMMAND | (id == currentType ? MF_CHECKED : MF_UNCHECKED));
            }
            return 0;
        }

        case WM_DESTROY: {
            if (pcshape) {
                for (int i = 0; i < shapeCount; ++i) {
                    delete pcshape[i];
                }
                delete[] pcshape;
                pcshape = nullptr;
            }

            if (currentShape) {
                delete currentShape;
                currentShape = nullptr;
            }

            PostQuitMessage(0);
            return 0;
        }

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"App";

    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName = MAKEINTRESOURCEW(IDM_MENU);

    if (!RegisterClassW(&wc)) return 0;

    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Main menu",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}