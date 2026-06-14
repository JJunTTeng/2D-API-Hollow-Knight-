#include "pch.h"
#include "CLevel_FalseKnight.h"

#include "CEngine.h"
#include "CLevelLoader.h"

#include "CPlayer.h"
#include "CAttack_Eft.h"

#include "CMap.h"
#include "CBgMap.h"

#include "CCollisionMgr.h"

CLevel_FalseKnight::CLevel_FalseKnight()
{
}

CLevel_FalseKnight::~CLevel_FalseKnight()
{
}

void CLevel_FalseKnight::Begin()
{

	// 메뉴바가 추가되었콅E때문에, 윈도퓖E크기를 재조정한다.
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());


	//MonsterFlipbook::GetInst()->CreateFlipbook();
	//
	 //Player 생성
	CPlayer* mPlayer = new CPlayer;
	mPlayer->SetName(L"Player");
	mPlayer->SetPos(Vec2(851, 512));
	AddObject(mPlayer, LAYER_TYPE::PLAYER);


	CAttack_Eft* m_Play_Effact = new CAttack_Eft;
	m_Play_Effact->LoadPlayer(mPlayer);
	AddObject(m_Play_Effact, LAYER_TYPE::PLAYER_OBJECT);


	// 샘플퓖EMap 오틒E㎷?생성
	CMap* m_MapObj = new CMap;
	m_MapObj->SetName(L"Dirtmouth");
	AddObject(m_MapObj, LAYER_TYPE::BACKGROUND);

	CBgMap* mBgMap = new CBgMap;
	AddObject(mBgMap, LAYER_TYPE::FrontBg);





	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::COLLIDER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::CAMERABOUND);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ATTCK_TILE);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::ATTCK_TILE);

	wchar_t _path[255] = L"Dirtmouth";
	CLevelLoader::CameraBoundLoad(this, _path);
	CLevelLoader::LoadColider(this, _path);

	CLevel::Begin();
}

void CLevel_FalseKnight::Tick()
{
	CLevel::Tick();
}

void CLevel_FalseKnight::FinalTick()
{
	CLevel::FinalTick();
}

void CLevel_FalseKnight::Render()
{
	CLevel::Render();
}

void CLevel_FalseKnight::End()
{
	DeleteAllObject();
}
