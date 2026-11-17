#include "mainwnd.h"
#include <windowsx.h>
#include "resource.h"
#include "shapes/point.h"
#include "shapes/line.h"
#include "shapes/rectangle.h"
#include "shapes/ellipse.h"

static Shape* CreateShape(int type) {
    switch (type) {
        case IDM_POINT: return new Point();
        case IDM_LINE: return new Line();
        case IDM_RECTANGLE: return new Rect();
        case IDM_ELLIPSE: return new Ell();
    }
    return nullptr;
}

MainWnd::MainWnd()
    : hwnd(nullptr), shapeCount(0), currentShape(nullptr),
      currentType(0), isDrawing(false), startX(0), startY(0) {
    for (int i = 0; i < N; ++i) {
        pcshape[i] = nullptr;
    }
}

MainWnd::~MainWnd() {
    for (int i = 0; i < shapeCount; ++i) {
        delete pcshape[i];
    }
    delete currentShape;
}

bool MainWnd::Create(HINSTANCE hInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"App";

    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = MainWnd::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName = MAKEINTRESOURCEW(IDM_MENU);

    if (!RegisterClassW(&wc)) return false;

    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);

    hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Main menu",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        NULL, NULL, hInstance, this
    );

    if (!hwnd) return false;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return true;
}

int MainWnd::Run() {
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK MainWnd::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    MainWnd* self = nullptr;

    if (msg == WM_NCCREATE) {
        CREATESTRUCTW* cs = (CREATESTRUCTW*)lParam;
        self = (MainWnd*)cs->lpCreateParams;
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)self);
        self->hwnd = hwnd;
    } else {
        self = (MainWnd*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
    }

    if (self) {
        return self->HandleMessage(msg, wParam, lParam);
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT MainWnd::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: OnCreate(); return 0;
        case WM_COMMAND: OnCommand(wParam); return 0;
        case WM_LBUTTONDOWN: OnLButtonDown(lParam); return 0;
        case WM_MOUSEMOVE: OnMouseMove(lParam); return 0;
        case WM_LBUTTONUP: OnLButtonUp(); return 0;
        case WM_PAINT: OnPaint(); return 0;
        case WM_DESTROY: OnDestroy(); return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void MainWnd::OnCreate() {
    UpdateTitle();
}

void MainWnd::OnCommand(WPARAM wParam) {
    int id = LOWORD(wParam);
    if (id >= IDM_POINT && id <= IDM_ELLIPSE && !isDrawing) {
        currentType = id;
        UpdateTitle();
    }
}

void MainWnd::OnLButtonDown(LPARAM lParam) {
    if (currentType && !isDrawing && shapeCount < N) {
        currentShape = CreateShape(currentType);
        if (!currentShape) return;
        isDrawing = true;
        SetCapture(hwnd);
        startX = GET_X_LPARAM(lParam);
        startY = GET_Y_LPARAM(lParam);
        currentShape->Set(startX, startY, startX, startY);
    }
}

void MainWnd::OnMouseMove(LPARAM lParam) {
    if (isDrawing && currentShape) {
        HDC hdc = GetDC(hwnd);
        SetROP2(hdc, R2_NOTXORPEN);

        currentShape->Draw(hdc);
        currentShape->Set(startX, startY, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        currentShape->Draw(hdc);

        ReleaseDC(hwnd, hdc);
    }
}

void MainWnd::OnLButtonUp() {
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
}

void MainWnd::OnPaint() {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    for (int i = 0; i < shapeCount; ++i) {
        pcshape[i]->Show(hdc);
    }

    EndPaint(hwnd, &ps);
}

void MainWnd::OnDestroy() {
    PostQuitMessage(0);
}

void MainWnd::UpdateTitle() {
    const wchar_t* name = L"";
    switch (currentType) {
        case IDM_POINT: name = L" - Крапка"; break;
        case IDM_LINE: name = L" - Лінія"; break;
        case IDM_RECTANGLE: name = L" - Прямокутник"; break;
        case IDM_ELLIPSE: name = L" - Еліпс"; break;
    }

    wchar_t title[128];
    wsprintfW(title, L"Main menu%ls", name);
    SetWindowTextW(hwnd, title);
}