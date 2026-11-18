#include <windows.h>
#include "mainwnd.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    MainWnd app;

    if (!app.Create(hInstance, nCmdShow)) return 0;
    return app.Run();
}