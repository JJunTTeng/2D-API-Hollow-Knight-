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
	if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"FloorBox")
	{
		CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
		pBody->SetGround(true);
		//CCamera::GetInst()->Oscillation(0.15f, 5.f, 10.f);
	}

	if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"HeadBox")
	{
		CRigidBody* mRigidBody = _OtherObject->GetComponent<CRigidBody>();
		Vec2 JumpSeepd = mRigidBody->GetJumpVelocity();

		mRigidBody->SetVelocity(Vec2(mRigidBody->GetJumpVelocity().x, 3000.0f));


	}

	if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"LeftBox")
	{
		_OtherObject->SetPos(Vec2(_OtherObject->GetPrevPos().x + 2, _OtherObject->GetPos().y));
	}

	if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"RightBox")
	{
		_OtherObject->SetPos(Vec2(_OtherObject->GetPrevPos().x - 2, _OtherObject->GetPos().y));
	}
}

void Colision::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	//if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"LeftBox")
	//{
	//	_OtherObject->SetPos(Vec2(_OtherObject->GetPrevPos().x, _OtherObject->GetPos().y));
	//}

	//if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"RightBox")
	//{
	//	_OtherObject->SetPos(Vec2(_OtherObject->GetPrevPos().x, _OtherObject->GetPos().y));
	//}
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


