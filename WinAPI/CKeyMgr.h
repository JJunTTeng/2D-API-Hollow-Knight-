#pragma once

enum KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,
};

enum KEY
{
	Q,W,E,R,T,Y,
	A,S,D,F,G,H,
	Z,X,C,V,B,N,M,

	ENTER,
	ESC,
	LSHIFT,
	ALT,
	CTRL,
	SPACE,

	UP, DOWN, LEFT, RIGHT,

	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,

	LBTN,
	RBTN,

	KEY_END,
};

enum LeftOrRight
{
	LR_LEFT,
	LR_RIGHT,
	LR_NONE
};;

struct KeyInfo
{	
	KEY_STATE	State;			// 현재 상태
	bool		bPrevPressed;	// 이전 프레임에 눌렸는지
};

class CCamera;
class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<KeyInfo>		m_vecKeyInfo;
	Vec2				m_MousePos;
	Vec2				m_EditMousePos;
	Vec2				m_Render;
	
	float				m_LeftKeyTime;
	float				m_RightKeyTime;

	LeftOrRight			m_LeftOrRight;

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKeyInfo[_key].State; }
	Vec2 GetMousePos() { return m_MousePos; }	
	Vec2 GetEditMousePos() { return m_EditMousePos;}
	LeftOrRight GetLeftOrRight() { return m_LeftOrRight; }

	bool  GetNoneKey();

	bool IsMouseOffScreen();

	void LeftORRightKey();

public:
	void Init();
	void Tick();
};

