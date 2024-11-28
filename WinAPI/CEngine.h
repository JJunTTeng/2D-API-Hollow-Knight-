#pragma once

#include "CTexture.h"

// ���α׷��� �ֻ��� ������
class CEngine
{
	SINGLE(CEngine);
private:
	HINSTANCE	m_hInst;		// ���μ��� �ּ�
	HWND		m_hWnd;			// ���� ������ �ڵ�
	Vec2		m_Resolution;	// ���� ������ �ػ�
	HDC			m_hDC;			// Main DC(Device Context) �׸��� ���� ������, �׸��� ���� ����ü
	
	CTexture*	m_BackBuffer;	// ����� �뵵 �ؽ���


	//���� ������
	HINSTANCE	m_EhInst;		// ���μ��� �ּ�
	HWND		m_EhWnd;		// ������ �ڵ�
	Vec2		m_EResolution;	// ������ �ػ�
	HDC			m_EhDC;			// DC(Device Context) �׸��� ���� ������, �׸��� ���� ����ü

	CTexture*	m_EBackBuffer;	// ����� �뵵 �ؽ���



	HPEN		m_Pen[(UINT)PEN_TYPE::END];
	HBRUSH		m_Brush[(UINT)BRUSH_TYPE::END];

public:
	HWND GetMainWndHwnd() { return m_hWnd; }
	Vec2 GetResolution() { return m_Resolution; }
	HPEN GetPen(PEN_TYPE _Type) { return m_Pen[(UINT)_Type]; }
	HBRUSH GetBrush(BRUSH_TYPE _Type) { return m_Brush[(UINT)_Type]; }
	HDC GetMainDC() { return m_hDC; }
	HDC GetSecondDC() { return m_BackBuffer->GetDC(); }

	HWND GetEditWndHwnd() { return m_EhWnd; }
	Vec2 GetEditResolution() { return m_EResolution; }
	HDC GetEditDC() { return m_EhDC; }
	HDC GetEditSecondDC() { return m_EBackBuffer->GetDC(); }


	void ChangeWindowSize(Vec2 _vResolution);





public:
	int Init(HINSTANCE _Inst, POINT _Resolution);
	int EditWindow(HINSTANCE _Inst, POINT _Resolution);

	void Progress();

private:
	void CreateGDIObject();
	void CreateSecondBuffer();
};
