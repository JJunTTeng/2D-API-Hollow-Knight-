#include "pch.h"
#include "CCameraBound.h"
#include "CCollider.h"

#include "CCamera.h"
#include "CTimeMgr.h"
CCameraBound::CCameraBound()
	:LerpTime(0.0f),
	m_roomName(RoomName::None)
{
}

CCameraBound::~CCameraBound()
{
}

void CCameraBound::Begin()
{
	SetName(L"CameraBound");
}

void CCameraBound::Tick()
{
}

void CCameraBound::Render()
{
}

void CCameraBound::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CCameraBound::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (m_roomName == RoomName::YStopRoom)
	{
		
	}
	Vec2 mFinalPos = Vec2(CCamera::GetInst()->GetLookAt().x,GetPos().y + _Collider->GetScale().y - 200.0f);

	Vec2 GetLerp = Lerp(CCamera::GetInst()->GetLookAt(), mFinalPos, 0.1);

	if (GetLerp.y != mFinalPos.y)
		CCamera::GetInst()->SetLookAt(Vec2(CCamera::GetInst()->GetLookAt().x, GetLerp.y));

	else
		CCamera::GetInst()->SetLookAt(mFinalPos);
}

void CCameraBound::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	CCamera::GetInst()->SetOffset(Vec2(0, -100));
	LerpTime = 0.0f;

}

Vec2 CCameraBound::Lerp(Vec2 _Pos1, Vec2 _finalPos2, float _v)
{
	Vec2 LerpPos = _Pos1 + (_finalPos2 - _Pos1) * _v;

	return LerpPos;

}
