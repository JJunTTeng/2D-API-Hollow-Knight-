#pragma once
#include "CComponent.h"

enum class Dir
{
	LEFT,
	RIGHT
};

class CMonsPattern : public CComponent
{

public:
	CMonsPattern();
	~CMonsPattern();

	Vec2 GetFmovePoint() { return m_FmovePoint; }
	Vec2 GetEmovePoint() { return m_EmovePoint; }


	void SetFmovePoint(Vec2 _Pos) { m_FmovePoint = _Pos; }
	void SetEmovePoint(Vec2 _Pos) { m_EmovePoint = _Pos; }
	void SetMoveSpeed(Vec2 _Speed) { m_MoveSpeed = _Speed; }



	void Play(bool Chase = false);
	virtual void FinalTick()override;
	void Render();


private:
	Vec2 m_FmovePoint;
	Vec2 m_EmovePoint;
	Vec2 m_MoveSpeed;
	Vec2 m_Point;
	bool m_chase;
	Dir m_dir;
};
