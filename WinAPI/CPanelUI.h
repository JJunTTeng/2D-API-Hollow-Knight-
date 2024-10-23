#pragma once
#include "CUI.h"

class CPanelUI :
    public CUI
{
private:
    Vec2    m_DownPos; // 자신이 마우스 왼쪽 클릭 되었을 때 좌표 기록

public:    
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

    virtual void MouseLBtnDown() override;
    virtual void MouseLBtnClikced() override;

public:
    CPanelUI();
    ~CPanelUI();
};

