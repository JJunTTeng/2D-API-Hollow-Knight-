#include "pch.h"
#include "CKeyMgr.h"

#include "CEngine.h"
#include "CTimeMgr.h"

UINT KeyValue[KEY::KEY_END] =
{
	'Q', 'W', 'E', 'R', 'T', 'Y',
	'A', 'S', 'D', 'F', 'G', 'H',
	'Z', 'X', 'C',  'V',  'B',  'N', 'M',

	VK_RETURN,
	VK_ESCAPE,
	VK_LSHIFT,
	VK_MENU,
	VK_CONTROL,
	VK_SPACE,

	VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,	

	VK_LBUTTON,
	VK_RBUTTON,
};




CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
	for (size_t i = 0; i < KEY_END; ++i)
	{
		m_vecKeyInfo.push_back(KeyInfo{ KEY_STATE::NONE, false});
		m_LeftKeyTime = 0.f;
		m_RightKeyTime = 0.f;
		m_LeftOrRight = LeftOrRight::LR_NONE;
	}	
}

void CKeyMgr::Tick()
{
	// 게임 윈도우가 포커싱 중일 때
	if (GetFocus() == CEngine::GetInst()->GetMainWndHwnd() || GetFocus() == CEngine::GetInst()->GetEditWndHwnd())
	{
		for (size_t i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			// 현재 해당 키가 눌려있다.
			if (GetAsyncKeyState(KeyValue[i]) & 0x8001)
			{
				if (KeyValue[i] == KeyValue[KEY::LEFT])
				{
					m_LeftKeyTime += DT;
				}

				if (KeyValue[i] == KeyValue[KEY::RIGHT])
				{
					m_RightKeyTime += DT;

				}

				// 이전에도 눌려있었다.
				if (m_vecKeyInfo[i].bPrevPressed)
				{
					m_vecKeyInfo[i].State = KEY_STATE::PRESSED;

				}

				// 이전에 눌려있지 않았다.
				else
				{
					m_vecKeyInfo[i].State = KEY_STATE::TAP;
				}

				m_vecKeyInfo[i].bPrevPressed = true;
			}

			// 현재 해당키가 안눌려있다.
			else
			{
				// 이전에는 눌려있었다.
				if (m_vecKeyInfo[i].bPrevPressed)
				{
					m_vecKeyInfo[i].State = KEY_STATE::RELEASED;
				}

				else
				{
					m_vecKeyInfo[i].State = KEY_STATE::NONE;
				}

				if (KeyValue[i] == KeyValue[KEY::LEFT])
				{
					m_LeftKeyTime = 0.f;
				}

				if (KeyValue[i] == KeyValue[KEY::RIGHT])
				{
					m_RightKeyTime = 0.f;
				}

				m_vecKeyInfo[i].bPrevPressed = false;
			}
		}

		// 마우스 좌표 갱신
		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(CEngine::GetInst()->GetMainWndHwnd(), &ptPos);

		m_MousePos = ptPos;

		GetCursorPos(&ptPos);
		ScreenToClient(CEngine::GetInst()->GetEditWndHwnd(), &ptPos);

		m_EditMousePos = ptPos;
		LeftORRightKey();
	}

	// 게임 윈도우가 비활성화 되어 있을 때
	else
	{
		for (size_t i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			if (KEY_STATE::TAP == m_vecKeyInfo[i].State
				|| KEY_STATE::PRESSED == m_vecKeyInfo[i].State)
			{
				m_vecKeyInfo[i].State = KEY_STATE::RELEASED;
			}

			else if (KEY_STATE::RELEASED == m_vecKeyInfo[i].State)
			{
				m_vecKeyInfo[i].State = KEY_STATE::NONE;
			}

			m_vecKeyInfo[i].bPrevPressed = false;
		}

		// 마우스 좌표 갱신
		*((int*)&m_MousePos.x) = 0xffffffff;
		*((int*)&m_MousePos.y) = 0xffffffff;

		*((int*)&m_EditMousePos.x) = 0xffffffff;
		*((int*)&m_EditMousePos.y) = 0xffffffff;
	}
}

bool CKeyMgr::GetNoneKey()
{
	for (size_t i = 0; i < m_vecKeyInfo.size(); ++i)
	{
		if (!m_vecKeyInfo[i].State == KEY_STATE::NONE)
			return false;
	}

	return true;
}

bool CKeyMgr::IsMouseOffScreen()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	if (vResolution.x <= m_MousePos.x || vResolution.y <= m_MousePos.y
		|| m_MousePos.x < 0 || m_MousePos.y < 0)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

void CKeyMgr::LeftORRightKey()
{
	if (m_LeftKeyTime == 0.0f || m_RightKeyTime == 0.0f)
		m_LeftOrRight = LR_NONE;

	else if (m_LeftKeyTime < m_RightKeyTime)
		m_LeftOrRight = LeftOrRight::LR_LEFT;

	else
		m_LeftOrRight = LeftOrRight::LR_RIGHT;
}
