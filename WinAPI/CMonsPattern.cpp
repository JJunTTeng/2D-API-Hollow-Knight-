#include "pch.h"
#include "CMonsPattern.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CMonsPattern::CMonsPattern ()
	:CComponent(COMPONENT_TYPE::PATTERN),
	m_EmovePoint(Vec2()),
	m_FmovePoint(Vec2()),
	m_MoveSpeed(Vec2()),
	m_chase(NULL),
	m_dir(Dir::LEFT)
{
}

CMonsPattern::~CMonsPattern()
{
}

void CMonsPattern::CreatePattern(Vec2 _FMovePoint, Vec2 _EMovePoint, Vec2 _MoveSpeed, bool Chase)
{
	m_FmovePoint = _FMovePoint;
	m_EmovePoint = _EMovePoint;
	m_MoveSpeed = _MoveSpeed;
	m_Point = GetOwner()->GetPos();
	m_chase = Chase;
}

void CMonsPattern::Tick()
{
	Vec2 mPos = GetOwner()->GetPos();

	if (nullptr == GetOwner()->GetComponent<CRigidBody>())
	{

	}

	else
	{
		CRigidBody* mRigidbody = GetOwner()->GetComponent<CRigidBody>();
		if (m_dir == Dir::LEFT)
		{
			if (mPos.x < m_Point.x - m_FmovePoint.x)
				GetOwner()->SetPos(mPos - m_MoveSpeed * DT);
			else
				m_dir = Dir::RIGHT;
		}

		else
		{
			if (mPos.x > m_Point.x + m_FmovePoint.x)
				GetOwner()->SetPos(mPos - m_MoveSpeed * DT);
			else
				m_dir = Dir::LEFT;
		}
	}


}

void CMonsPattern::Render()
{
	HDC dc = CEngine::GetInst()->GetEditSecondDC();
	Vec2 mPos = GetOwner()->GetPos();

	if (m_dir == Dir::LEFT)
	{
		//SELECT_PEN(PEN_TYPE::RED)
		MoveToEx(dc, mPos.x, mPos.y, nullptr);
		LineTo(dc, m_FmovePoint.x, m_FmovePoint.y);
	}

	else
	{
		MoveToEx(dc, mPos.x, mPos.y, nullptr);
		LineTo(dc, m_EmovePoint.x, m_EmovePoint.y);
	}
}
