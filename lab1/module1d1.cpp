#include <windows.h>
#include "module1d1.h"
#include "resource.h"

namespace {
    INT_PTR CALLBACK DialogProc1 (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_COMMAND: {
                WORD cID = LOWORD(wParam);

                if (cID == IDC_BTN_NEXT) {
                    EndDialog(hDlg, IDC_BTN_NEXT);
                    return TRUE;
                }

                if (cID == IDC_BTN_CANCEL || cID == IDCANCEL) {
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
                }
                break;
            }
        }

        return FALSE;
    }
}

INT_PTR ShowDialog1(HINSTANCE hInst, HWND hwnd) {
    return DialogBoxParamA(hInst, MAKEINTRESOURCEA(IDD_DIALOG1), hwnd, DialogProc1, 0);
}