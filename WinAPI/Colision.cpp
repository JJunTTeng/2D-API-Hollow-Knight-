#include "pch.h"
#include "Colision.h"
#include "CRigidBody.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CPlayer.h"

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

	//if (GetName() == L"Ground")
	//{
	//	if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"FloorBox")
	//	{
	//		CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
	//		pBody->SetGround(true);
	//		//CCamera::GetInst()->Oscillation(0.15f, 5.f, 10.f);
	//	}

	//	if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"HeadBox")
	//	{
	//		CRigidBody* mRigidBody = _OtherObject->GetComponent<CRigidBody>();
	//	}

	//	if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"LeftBox")
	//	{
	//		_OtherObject->SetPos(Vec2(_OtherObject->GetPrevPos().x + 2, _OtherObject->GetPos().y));
	//	}

	//	if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"RightBox")
	//	{
	//		_OtherObject->SetPos(Vec2(_OtherObject->GetPrevPos().x - 2, _OtherObject->GetPos().y));
	//	}

	//	if (_OtherObject->GetName() == L"Crawlid")
	//	{
	//		CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
	//		pBody->SetGround(true);
	//	}
	//}



}

void Colision::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	//if (GetName() == L"Ground")
	//{
	//	if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"FloorBox")
	//	{
	//		CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
	//		if(pBody->IsGround() == true)
	//		{
	//			if (_OtherObject->GetPos().y != (GetPos().y + GetScale().y))
	//			{
	//				_OtherObject->SetPos(Vec2(_OtherObject->GetPos().x, GetPos().y + GetScale().y + 1.0f));
	//			}
	//		}
	//		//CCamera::GetInst()->Oscillation(0.15f, 5.f, 10.f);
	//	}

	//	if (_OtherObject->GetName() == L"Crawlid")
	//	{
	//		CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
	//		pBody->SetGround(true);
	//	}
	//}

	if (GetName() == L"Ground")
	{


		if (_OtherCollider->GetName() == L"FloorBox")
		{
			CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
			if (_OtherObject->GetComponent<CRigidBody>()->GetVelocity().y < 0.0f)
			{
				pBody->SetGround(false);

			}

			else
			{
				pBody->SetGround(true);

				if (GetComponent<CCollider>()->GetLeftTopPos().y + 1.0f < _OtherCollider->GetRightButtomPos().y)
					_OtherObject->SetPlusPos(Vec2(0.0f, -1.0f));
			}


			//CCamera::GetInst()->Oscillation(0.15f, 5.f, 10.f);
		}

		if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"HeadBox")
		{
			CRigidBody* mRigidBody = _OtherObject->GetComponent<CRigidBody>();
		}

		if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"LeftBox")
		{
			_OtherObject->SetPos(Vec2(_OtherObject->GetPrevPos().x + 2, _OtherObject->GetPos().y));
		}

		if (_OtherObject->GetName() == L"Player" && _OtherCollider->GetName() == L"RightBox")
		{
			_OtherObject->SetPos(Vec2(_OtherObject->GetPrevPos().x - 2, _OtherObject->GetPos().y));
		}

		if (_OtherObject->GetName() == L"Crawlid")
		{
			CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
			pBody->SetGround(true);
		}
	}



	if (GetName() == L"Hurt")
	{
		if (_OtherObject->GetName() == L"Player")
		{
			CPlayer* mPlayer = dynamic_cast<CPlayer*>(_OtherObject);
			CRigidBody* pBody = _OtherObject->GetComponent<CRigidBody>();
			if (mPlayer->OnHit() == true)
			{
				pBody->PApplyKnockback(Vec2(-220.f, -340.f));
			}
		}

	}
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


