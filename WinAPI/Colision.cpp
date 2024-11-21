#include "pch.h"
#include "Colision.h"
#include "CRigidBody.h"
#include "CCamera.h"
#include "CCollider.h"

Colision::Colision()
{
}

Colision::~Colision()
{
}

void Colision::Begin()
{
}

void Colision::Tick()
{
}

void Colision::Render()
{
	


}

//지금은 플레이어가 other임
void Colision::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
		pBody->SetGround(true);
		CCamera::GetInst()->Oscillation(0.15f, 5.f, 10.f);
	}
}

void Colision::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void Colision::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		if (_OtherCollider->GetName() == L"HitBox_01")
		{

		}

		if (_OtherCollider->GetName() == L"HeadBox")
		{

		}

		if (_OtherCollider->GetName() == L"FloorBox")
		{

			CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
			pBody->SetGround(false);
		}
	}
}


