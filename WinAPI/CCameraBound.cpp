#include "pch.h"
#include "CCameraBound.h"
#include "CCollider.h"

#include "CCamera.h"
#include "CTimeMgr.h"
CCameraBound::CCameraBound()
	:LerpTime(0.0f)
{
}

CCameraBound::~CCameraBound()
{
}

void CCameraBound::Begin()
{
	m_Coliider = new CCollider;
	m_Coliider->SetScale(GetScale());

	AddComponent(m_Coliider);
}

void CCameraBound::Tick()
{
	//CObj::FinalTick();

}

void CCameraBound::Render()
{
}

void CCameraBound::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetLayerType() == LAYER_TYPE::PLAYER && GetName() == L"AllBoundBox")
	{
		CCamera::GetInst()->SetBoundTarget(this, BOUND_TYPE::ALL);
	}

	if (_OtherObject->GetLayerType() == LAYER_TYPE::PLAYER && GetName() == L"XBoundBox")
	{
		//
	}

	if (_OtherObject->GetLayerType() == LAYER_TYPE::PLAYER && GetName() == L"YBoundBox")
	{
		CCamera::GetInst()->SetBoundTarget(this, BOUND_TYPE::Ypos);
	}

	
}

void CCameraBound::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CCameraBound::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{

	CCamera::GetInst()->DeleteBoundTarget();
	CCamera::GetInst()->SetOffset(Vec2(0, -100));
	LerpTime = 0.0f;

}

