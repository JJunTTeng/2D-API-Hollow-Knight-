#include "pch.h"
#include "CMonsPattern.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CEngine.h"
#include "CCamera.h"

CMonsPattern::CMonsPattern()
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

void CMonsPattern::Play(bool Chase)
{
	m_Point = GetOwner()->GetPos();

	if (m_FmovePoint.x == NULL && m_FmovePoint.y == NULL)
		m_FmovePoint = m_Point;

	if (m_EmovePoint.x == NULL && m_EmovePoint.y == NULL)
		m_EmovePoint = m_Point;

	m_chase = Chase;
}

void CMonsPattern::FinalTick()
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
			if (mPos.x > m_FmovePoint.x)
				GetOwner()->SetPos(mPos + Vec2(-100.0f, 0.0f) * DT);
			else
				m_dir = Dir::RIGHT;
		}

		else
		{
			if (mPos.x < m_EmovePoint.x)
				GetOwner()->SetPos(mPos + Vec2(100.0f, 0.0f) * DT);
			else
				m_dir = Dir::LEFT;
		}
	}


}

void CMonsPattern::Render()
{
	HDC dc = CEngine::GetInst()->GetSecondDC();

	Vec2 mPos = CCamera::GetInst()->GetRenderPos(m_Point);


	Vec2 mDePos = CCamera::GetInst()->GetRenderPos(m_FmovePoint);
	Vec2 mDePos2 = CCamera::GetInst()->GetRenderPos(m_EmovePoint);


	if (GetOwner()->GetComponent<CRigidBody>())
	{
		MoveToEx(dc, mPos.x, mPos.y, nullptr);
		LineTo(dc, mDePos.x, mPos.y);

		MoveToEx(dc, mPos.x, mPos.y, nullptr);
		LineTo(dc, mDePos2.x, mPos.y);

		return;
	}

	MoveToEx(dc, mPos.x, mPos.y, nullptr);
	LineTo(dc, mDePos.x, mDePos.y);

	MoveToEx(dc, mPos.x, mPos.y, nullptr);
	LineTo(dc, mDePos2.x, mDePos2.y);
}
