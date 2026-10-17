#include <windows.h>
#include <string>
#include <fstream>
#include "module2.h"
#include "resource.h"

using namespace std;
namespace {
    char buffer[64] = "";

    INT_PTR CALLBACK DialogProcL(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_INITDIALOG: {
                ifstream file("list.txt");

                if (file.is_open()) {
                    string group;
                    while (getline(file, group)) {
                        if (!group.empty()) {
                            SendDlgItemMessageA(hDlg, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)group.c_str());
                        }
                    }
                    file.close();
                }
                return TRUE;
            }

            case WM_COMMAND: {
                WORD cID = LOWORD(wParam);

                if (cID == IDC_BTN_YES || cID == IDOK) {
                    int strIndex = (int)SendDlgItemMessageA(hDlg, IDC_LIST, LB_GETCURSEL, 0, 0);

                    if (strIndex != LB_ERR) {
                        SendDlgItemMessageA(hDlg, IDC_LIST, LB_GETTEXT, strIndex, (LPARAM)buffer);
                    }

                    EndDialog(hDlg, IDOK);
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

bool Module2Dialog(HWND hwnd, char* outBuffer, int bufferSize) {
    HINSTANCE hInst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    INT_PTR res = DialogBoxParamA(hInst, MAKEINTRESOURCEA(IDD_DIALOG3), hwnd, DialogProcL, 0);

    if (res == IDOK) {
        lstrcpynA(outBuffer, buffer, bufferSize);
        return true;
    }

    return false;
}