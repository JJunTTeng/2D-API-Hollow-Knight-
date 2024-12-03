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

	void CreatePattern(Vec2 _FMovePoint , Vec2 _EMovePoint, Vec2 _MoveSpeed, bool Chase);
	void Tick();


private:
	Vec2 m_FmovePoint;
	Vec2 m_EmovePoint;
	Vec2 m_MoveSpeed;
	Vec2 m_Point;
	bool m_chase;
	Dir m_dir;
};
