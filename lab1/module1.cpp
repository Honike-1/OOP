#include <windows.h>
#include "module1.h"
#include "module1d1.h"
#include "module1d2.h"
#include "resource.h"

int Module1Dialog(HWND hwnd) {
    HINSTANCE hInst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
    int curStep = 1;
    
    while (curStep != 0) {
        if (curStep == 1) {
            INT_PTR res = ShowDialog1(hInst, hwnd);

            if (res == IDC_BTN_NEXT) {
                curStep = 2;
            } else {
                curStep = 0;
            }
        } else if (curStep == 2) {
            INT_PTR res = ShowDialog2(hInst, hwnd);

            if (res == IDC_BTN_BACK) {
                curStep = 1;
            } else {
                curStep = 0;
            }
        }
    }

    return 0;
}