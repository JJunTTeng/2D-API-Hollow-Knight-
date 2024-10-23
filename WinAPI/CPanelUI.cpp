#include "pch.h"
#include "CPanelUI.h"

#include "CKeyMgr.h"
#include "CEngine.h"
#include "CSelectGDI.h"

CPanelUI::CPanelUI()
{
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::Tick_UI()
{
	if (IsLBtnDown())
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vDiff = vMousePos - m_DownPos;

		Vec2 vPos = GetPos();
		vPos += vDiff;
		SetPos(vPos);

		m_DownPos = vMousePos;
	}
}

void CPanelUI::Render_UI()
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	SELECT_PEN(PEN_TYPE::GREEN);

	HBRUSH hBrush = CreateSolidBrush(RGB(143, 90, 145));
	HDC dc = CEngine::GetInst()->GetSecondDC();

	HBRUSH hPrevBrush = (HBRUSH)SelectObject(dc, hBrush);
	
	Rectangle(dc
		, (int)vPos.x, (int)vPos.y
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));

	SelectObject(dc, hPrevBrush);
	DeleteObject(hBrush);
}

void CPanelUI::MouseLBtnDown()
{
	m_DownPos = CKeyMgr::GetInst()->GetMousePos();
}

void CPanelUI::MouseLBtnClikced()
{
}
