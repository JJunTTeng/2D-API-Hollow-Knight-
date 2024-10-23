#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_Matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::CollisionCheck(LAYER_TYPE _Left, LAYER_TYPE _Right)
{
	// 입력으로 들어온 레이어 번호중에서 더 작은값을 Matrix 의 행으로, 더 큰값을 열로 사용한다.
	UINT Row = (UINT)_Left;
	UINT Col = (UINT)_Right;

	if (Col < Row)
	{
		Row = (UINT)_Right;
		Col = (UINT)_Left;
	}

	// 이미 체크가 되어있으면
	if (m_Matrix[Row] & (1 << Col))
	{
		// 비트를 뺀다.
		m_Matrix[Row] &= ~(1 << Col);
	}

	// 체크가 안되어있으면
	else
	{
		// 체크한다.
		m_Matrix[Row] |= (1 << Col);
	}
}

void CCollisionMgr::Tick()
{
	for (UINT Row = 0; Row < (UINT)LAYER_TYPE::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)LAYER_TYPE::END; ++Col)
		{
			if (!(m_Matrix[Row] & (1 << Col)))
				continue;

			CollisionBtwLayer((LAYER_TYPE)Row, (LAYER_TYPE)Col);
		}
	}
}


void CCollisionMgr::CollisionBtwLayer(LAYER_TYPE _Left, LAYER_TYPE _Right)
{
	const vector<CCollider*>& vecLeft = CLevelMgr::GetInst()->GetCurrentLevel()->GetColliders(_Left);
	const vector<CCollider*>& vecRight = CLevelMgr::GetInst()->GetCurrentLevel()->GetColliders(_Right);

	// 서로 다른 레이어간의 충돌 검사
	if (_Left != _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				CollisionBtwCollider(vecLeft[i], vecRight[j]);
			}
		}
	}

	// 동일 레이어간의 충돌 검사
	else
	{
		// 중복 검사 or 자기자신과의 검사를 피하기 위해서 j 는 i + 1 부터 시작한다.
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = i + 1; j < vecRight.size(); ++j)
			{
				CollisionBtwCollider(vecLeft[i], vecRight[j]);
			}
		}
	}
}

void CCollisionMgr::CollisionBtwCollider(CCollider* _LeftCol, CCollider* _RightCol)
{
	COLLISION_ID ColID = {};
	ColID.Left = _LeftCol->GetID();
	ColID.Right = _RightCol->GetID();

	map<ULONGLONG, bool>::iterator iter = m_ColInfo.find(ColID.ID);

	// 두 충돌체 조합이 등록된 적이 없다.
	if (iter == m_ColInfo.end())
	{
		// 등록을 시킨다.
		m_ColInfo.insert(make_pair(ColID.ID, false));
		iter = m_ColInfo.find(ColID.ID);
	}
	
	// 두 충돌체 중 1개라도 삭제 예정 오브젝트라면
	bool IsDead = _LeftCol->GetOwner()->IsDead() || _RightCol->GetOwner()->IsDead();

	// 현재 겹쳐있다.
	if (!IsDead && IsCollision(_LeftCol, _RightCol))
	{
		// 이전에도 겹쳐있었다.
		if (iter->second)
		{
			_LeftCol->Overlap(_RightCol);
			_RightCol->Overlap(_LeftCol);
		}

		// 이전에는 겹쳐있지 않았다.
		else
		{
			_LeftCol->BeginOverlap(_RightCol);
			_RightCol->BeginOverlap(_LeftCol);
			iter->second = true; // 충돌정보 갱신
		} 
	}

	// 현재 떨어져 있다.
	else
	{
		// 이전에는 겹쳐있었다.
		if (iter->second)
		{
			_LeftCol->EndOverlap(_RightCol);
			_RightCol->EndOverlap(_LeftCol);
			iter->second = false;
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _LeftCol, CCollider* _RightCol)
{
	Vec2 LeftPos = _LeftCol->GetFinalPos();
	Vec2 RightPos = _RightCol->GetFinalPos();

	Vec2 LeftScale = _LeftCol->GetScale();
	Vec2 RightScale = _RightCol->GetScale();
	Vec2 vDiff = LeftPos - RightPos;

	if (fabs(vDiff.x) < (LeftScale.x + RightScale.x) / 2.f
		&& fabs(vDiff.y) < (LeftScale.y + RightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}