#include <windows.h>
#include "module1d2.h"
#include "resource.h"

namespace {
    INT_PTR CALLBACK DialogProc2 (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_COMMAND: {
                WORD cID = LOWORD(wParam);

                if (cID == IDC_BTN_BACK) {
                    EndDialog(hDlg, IDC_BTN_BACK);
                    return TRUE;
                }

                if (cID == IDC_BTN_YES || cID == IDOK) {
                    EndDialog(hDlg, IDOK);
                    return TRUE;
                }

                if (cID == IDC_BTN_CANCEL || cID == IDCANCEL) {
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
                }
            }
        }

        return FALSE;
    }
}

INT_PTR ShowDialog2(HINSTANCE hInst, HWND hwnd) {
    return DialogBoxParamA(hInst, MAKEINTRESOURCEA(IDD_DIALOG2), hwnd, DialogProc2, 0);
}