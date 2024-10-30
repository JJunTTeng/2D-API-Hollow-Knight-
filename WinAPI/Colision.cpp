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

void Colision::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		if (_OtherCollider->GetLeftTopPos().y <= _Collider->GetLeftTopPos().y &&
			_OtherCollider->GetLeftTopPos().y >= _Collider->GetRightButtomPos().y &&
			_OtherCollider->GetRightButtomPos().x <= _Collider->GetLeftTopPos().x &&
			_OtherCollider->GetLeftTopPos().x >= _Collider->GetRightButtomPos().x)
		{
			_OtherObject->SetPos(Vec2(_OtherObject->GetPrevPos().x,_OtherObject->GetPos().y));
		}

		else
		{
			CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
			pBody->SetGround(true);
			CCamera::GetInst()->Oscillation(0.15f, 5.f, 10.f);
		}

	}
}

void Colision::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void Colision::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Player")
	{
		CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
		pBody->SetGround(false);
	}
}


