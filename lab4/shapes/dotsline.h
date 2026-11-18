#pragma once
#include "line.h"
#include "ellipse.h"

class DotsLine : public virtual Line, public virtual Ell {
public:
    DotsLine();
    void Show(HDC hdc) override;
};