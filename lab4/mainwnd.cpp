#include "mainwnd.h"
#include <windowsx.h>
#include <new>
#include "resource.h"

MainWnd::MainWnd() : hwnd(nullptr), editor(nullptr) {}

MainWnd::~MainWnd() {
    delete editor;
    editor = nullptr;
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

    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;

    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, style, TRUE);

    hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Main menu",
        style,
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
        case WM_CREATE: return OnCreate() ? 0 : -1;
        case WM_SIZE: OnSize(); return 0;
        case WM_COMMAND: OnCommand(wParam); return 0;
        case WM_NOTIFY: OnNotify(lParam); return 0;
        case WM_LBUTTONDOWN: OnLButtonDown(lParam); return 0;
        case WM_MOUSEMOVE: OnMouseMove(lParam); return 0;
        case WM_LBUTTONUP: OnLButtonUp(); return 0;
        case WM_PAINT: OnPaint(); return 0;
        case WM_DESTROY: OnDestroy(); return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

bool MainWnd::OnCreate() {
    editor = new (std::nothrow) MyEditor();
    if (!editor) return false;

    if (!toolbar.Create(hwnd)) {
        delete editor;
        editor = nullptr;
        return false;
    }

    UpdateTitle();
    return true;
}

void MainWnd::OnSize() {
    toolbar.OnSize();
}

void MainWnd::OnCommand(WPARAM wParam) {
    int id = LOWORD(wParam);
    if (editor && id >= IDM_POINT && id <= IDM_CUBE) {
        editor->Start(id);
        toolbar.Check(editor->GetType());
        UpdateTitle();
    }
}

void MainWnd::OnNotify(LPARAM lParam) {
    toolbar.OnNotify(lParam);
}

void MainWnd::OnLButtonDown(LPARAM lParam) {
    if (editor) editor->OnLButtonDown(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
}

void MainWnd::OnMouseMove(LPARAM lParam) {
    if (editor) editor->OnMouseMove(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
}

void MainWnd::OnLButtonUp() {
    if (editor) editor->OnLButtonUp(hwnd);
}

void MainWnd::OnPaint() {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    if (editor) editor->OnPaint(hdc);

    EndPaint(hwnd, &ps);
}

void MainWnd::OnDestroy() {
    delete editor;
    editor = nullptr;
    PostQuitMessage(0);
}

void MainWnd::UpdateTitle() {
    const wchar_t* name = L"";
    switch (editor ? editor->GetType() : 0) {
        case IDM_POINT: name = L" - Крапка"; break;
        case IDM_LINE: name = L" - Лінія"; break;
        case IDM_RECTANGLE: name = L" - Прямокутник"; break;
        case IDM_ELLIPSE: name = L" - Еліпс"; break;
        case IDM_DOTSLINE: name = L" - Лінія з кружечками"; break;
        case IDM_CUBE: name = L" - Каркас куба"; break;
    }

    wchar_t title[128];
    wsprintfW(title, L"Main menu%ls", name);
    SetWindowTextW(hwnd, title);
}