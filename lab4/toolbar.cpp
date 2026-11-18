#include "toolbar.h"
#include "resource.h"

#pragma comment(lib, "comctl32.lib")

namespace {
    const int ICON_SIZE = 24;

    struct ButtonInfo {
        int id;
        const wchar_t* tip;
    };

    const ButtonInfo kButtons[] = {
        { IDM_POINT, L"Крапка" },
        { IDM_LINE, L"Лінія" },
        { IDM_RECTANGLE, L"Прямокутник" },
        { IDM_ELLIPSE, L"Еліпс" },
        { IDM_DOTSLINE, L"Лінія з кружечками" },
        { IDM_CUBE, L"Каркас куба" },
    };
    const int kCount = sizeof(kButtons) / sizeof(kButtons[0]);

    void DrawIcons(HDC dc) {
        const int S = ICON_SIZE;
        HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        HBRUSH green = CreateSolidBrush(RGB(144, 238, 144));
        HBRUSH nullBr = (HBRUSH)GetStockObject(NULL_BRUSH);

        HPEN oldPen = (HPEN)SelectObject(dc, pen);
        HBRUSH oldBr = (HBRUSH)SelectObject(dc, nullBr);
        int x;

        x = 0 * S;
        SelectObject(dc, GetStockObject(BLACK_BRUSH));
        Ellipse(dc, x + 9, 9, x + 15, 15);
        SelectObject(dc, nullBr);

        x = 1 * S;
        MoveToEx(dc, x + 3, 20, NULL);
        LineTo(dc, x + 21, 4);

        x = 2 * S;
        SelectObject(dc, green);
        Rectangle(dc, x + 3, 6, x + 21, 18);
        SelectObject(dc, nullBr);

        x = 3 * S;
        Ellipse(dc, x + 3, 5, x + 21, 19);

        x = 4 * S;
        MoveToEx(dc, x + 6, 18, NULL);
        LineTo(dc, x + 18, 6);
        Ellipse(dc, x + 2, 14, x + 10, 22);
        Ellipse(dc, x + 14, 2, x + 22, 10);

        x = 5 * S;
        Rectangle(dc, x + 9, 3, x + 21, 15);
        Rectangle(dc, x + 3, 9, x + 15, 21);
        MoveToEx(dc, x + 3, 9, NULL);   LineTo(dc, x + 9, 3);
        MoveToEx(dc, x + 15, 9, NULL);  LineTo(dc, x + 21, 3);
        MoveToEx(dc, x + 3, 21, NULL);  LineTo(dc, x + 9, 15);
        MoveToEx(dc, x + 15, 21, NULL); LineTo(dc, x + 21, 15);

        SelectObject(dc, oldBr);
        SelectObject(dc, oldPen);
        DeleteObject(pen);
        DeleteObject(green);
    }
}

Toolbar::Toolbar() : hwndTb(nullptr), himl(nullptr) {}

Toolbar::~Toolbar() {
    if (himl) ImageList_Destroy(himl);
}

HIMAGELIST Toolbar::CreateImages() {
    const int S = ICON_SIZE;
    const COLORREF transparent = RGB(255, 0, 255);

    HDC screen = GetDC(NULL);
    HDC mem = CreateCompatibleDC(screen);
    HBITMAP bmp = CreateCompatibleBitmap(screen, S * kCount, S);
    HBITMAP oldBmp = (HBITMAP)SelectObject(mem, bmp);

    HBRUSH bg = CreateSolidBrush(transparent);
    RECT rc = { 0, 0, S * kCount, S };
    FillRect(mem, &rc, bg);
    DeleteObject(bg);

    DrawIcons(mem);

    SelectObject(mem, oldBmp);
    DeleteDC(mem);
    ReleaseDC(NULL, screen);

    HIMAGELIST list = ImageList_Create(S, S, ILC_COLOR24 | ILC_MASK, kCount, 0);
    ImageList_AddMasked(list, bmp, transparent);
    DeleteObject(bmp);
    return list;
}

bool Toolbar::Create(HWND parent) {
    INITCOMMONCONTROLSEX icc = { sizeof(icc), ICC_BAR_CLASSES };
    InitCommonControlsEx(&icc);

    HINSTANCE hInst = (HINSTANCE)GetWindowLongPtrW(parent, GWLP_HINSTANCE);

    hwndTb = CreateWindowExW(
        0, TOOLBARCLASSNAMEW, NULL,
        WS_CHILD | WS_VISIBLE | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT,
        0, 0, 0, 0,
        parent, (HMENU)(INT_PTR)IDC_TOOLBAR, hInst, NULL);
    if (!hwndTb) return false;

    SendMessageW(hwndTb, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
    SendMessageW(hwndTb, TB_SETUNICODEFORMAT, TRUE, 0);

    himl = CreateImages();
    SendMessageW(hwndTb, TB_SETIMAGELIST, 0, (LPARAM)himl);

    TBBUTTON btn[kCount] = {};
    for (int i = 0; i < kCount; ++i) {
        btn[i].iBitmap   = i;
        btn[i].idCommand = kButtons[i].id;
        btn[i].fsState   = TBSTATE_ENABLED;
        btn[i].fsStyle   = TBSTYLE_CHECKGROUP;
    }
    SendMessageW(hwndTb, TB_ADDBUTTONSW, kCount, (LPARAM)btn);
    SendMessageW(hwndTb, TB_AUTOSIZE, 0, 0);
    return true;
}

void Toolbar::OnSize() {
    if (hwndTb) SendMessageW(hwndTb, TB_AUTOSIZE, 0, 0);
}

int Toolbar::Height() const {
    if (!hwndTb) return 0;
    RECT rc;
    GetWindowRect(hwndTb, &rc);
    return rc.bottom - rc.top;
}

void Toolbar::Check(int id) {
    if (!hwndTb) return;
    for (int i = 0; i < kCount; ++i) {
        SendMessageW(hwndTb, TB_CHECKBUTTON, kButtons[i].id, MAKELPARAM(kButtons[i].id == id, 0));
    }
}

void Toolbar::OnNotify(LPARAM lParam) {
    NMHDR* nm = (NMHDR*)lParam;
    if (nm->code != (UINT)TTN_GETDISPINFOW) return;

    NMTTDISPINFOW* di = (NMTTDISPINFOW*)lParam;
    for (int i = 0; i < kCount; ++i) {
        if ((int)nm->idFrom == kButtons[i].id) {
            di->lpszText = const_cast<LPWSTR>(kButtons[i].tip);
            return;
        }
    }
}