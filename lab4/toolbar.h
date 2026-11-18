#pragma once

#include <windows.h>
#include <commctrl.h>

class Toolbar {
    private:
        HWND hwndTb;
        HIMAGELIST himl;

        HIMAGELIST CreateImages();

    public:
        Toolbar();
        ~Toolbar();

        bool Create(HWND parent);
        void OnSize();
        void OnNotify(LPARAM lParam);
        void Check(int id);
        int  Height() const;
};