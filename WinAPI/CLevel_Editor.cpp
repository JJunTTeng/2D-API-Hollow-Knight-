#include "pch.h"
#include "CLevel_Editor.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CMap.h"

#include "CLevelMgr.h"
#include "CCamera.h"

#include "CPathMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

#include "CAssetMgr.h"
#include "CSound.h"

#include "CCollider.h"
#include "CSelectGDI.h"
#include "CCollisionMgr.h"

//object
#include "CTileMap.h"
#include "CMonster.h"
#include "Crawlid.h"
#include "Colision.h"
#include "CCameraBound.h"
#include "CPlayer.h"
#include "CAttack_Eft.h"
#include "CBgMap.h"
#include "CEffect.h"
#include "CTile.h"

#include "MonsterFlipbook.h"






CLevel_Editor::CLevel_Editor()
	: m_MapObj(nullptr)
	, m_hMenu(nullptr)
	, ColBeginPos(-1, -1)
	, ColEndPos(-1, -1)
	, MouseRenderPos(0, 0)
	, mEditMode(EditMode::None)
	, mEnimeName(EnimesName::None)
	, mMonsPtnPos(Vec2())
	, _Size(1.0f)
	, m_TileName(L"")
{
}

CLevel_Editor::~CLevel_Editor()
{
}

void CLevel_Editor::Begin()
{
	// 배경음 지정
	//CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"DM_Opening", L"Sound\\DM.wav");
	//if (nullptr != pSound)
	//{
	//	pSound->SetVolume(70.f);
	//	pSound->PlayToBGM(true);
	//}

	// 메뉴바 로탛E및 메인 윈도퓖E?부혖E
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINAPI));
	}	
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), m_hMenu);

	// 메뉴바가 추가되었콅E때문에, 윈도퓖E크기를 재조정한다.
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());

	//MonsterFlipbook::GetInst()->CreateFlipbook();
	//
	 //Player 생성
	//mPlayer = new CPlayer;
	//mPlayer->SetName(L"Player");
	//mPlayer->SetPos(Vec2(1954,1348));
	//AddObject(mPlayer, LAYER_TYPE::PLAYER);

	//
	//m_Play_Effact = new CAttack_Eft;
	//m_Play_Effact->LoadPlayer(mPlayer);
	//AddObject(m_Play_Effact, LAYER_TYPE::PLAYER_OBJECT);


	// 샘플퓖EMap 오틒E㎷?생성
	m_MapObj = new CMap;
	AddObject(m_MapObj, LAYER_TYPE::TILE);

	CBgMap* mBgMap = new CBgMap;
	AddObject(mBgMap, LAYER_TYPE::FrontBg);

	



	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::COLLIDER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::CAMERABOUND);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ATTCK_TILE);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::ATTCK_TILE);






	wchar_t m_Path[255] = L"KingLoad";
	LoadColider(m_Path);

	wchar_t m_Path2[255] = L"1-1";
	EnimeLoad(m_Path2);

	wchar_t m_Path3[255] = L"KingLoad";
	CameraBoundLoad(m_Path3);

	wchar_t m_Path4[255] = L"KingLoad2";
	TileLoad(m_Path4);

	// 레벨 소속 모탛E오틒E㎷??Begin 을 호출받을 펯E있도록 한다
	CLevel::Begin();
}

void CLevel_Editor::End()
{
	//DeleteAllObject();

	// 메뉴바 제거
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), nullptr);

	// 메뉴가 제거되었으므로, 다시 윈도퓖E크콅E조정
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());
}


void CLevel_Editor::Tick()
{
	CLevel::Tick();

	MouseRenderPos = CCamera::GetInst()->GetDiff() + CKeyMgr::GetInst()->GetMousePos();
	EditRenderPos = CKeyMgr::GetInst()->GetEditMousePos();


	if (mPlayer == nullptr)
	{
		if (CKeyMgr::GetInst()->GetLeftOrRight() == LeftOrRight::LR_NONE)
		{
			if (KEY_PRESSED(KEY::LEFT))
			{
				CCamera::GetInst()->SetPlusCameraPos(Vec2(-10.0f, 0.0f));
			}

			if (KEY_PRESSED(KEY::RIGHT))
			{
				CCamera::GetInst()->SetPlusCameraPos(Vec2(10.0f, 0.0f));
			}

			if (KEY_PRESSED(KEY::UP))
			{
				CCamera::GetInst()->SetPlusCameraPos(Vec2(0.0, -10.0f));
			}

			if (KEY_PRESSED(KEY::DOWN))
			{
				CCamera::GetInst()->SetPlusCameraPos(Vec2(0.0f, 10.0f));


			}
		}
	}


	switch (mEditMode)
	{
	case EditMode::FilbookMode:
		break;
	case EditMode::ColliderMode:
		ColliderMode(m_ColliderName);
		break;
	case EditMode::EnimesMode:
		EnimeMode();
		break;
	case EditMode::PatternMode:
		EnimesPattern();
		break;
	case EditMode::CameraMode:
		CameraBound(m_BoundName);
		break;
	case EditMode::TileMode:
		InsertTile(m_TileName);
	case EditMode::None:
		break;

	default:
		break;
	}

	// 특정 키가 눌리툈EStart 레벨로 변컖E
	if (KEY_TAP(KEY::M))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		ChangeLevel(LEVEL_TYPE::START);
	}


}

void CLevel_Editor::Render()
{
	CLevel::Render();

	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Editor Level", wcslen(L"Editor Level"));

	wchar_t word[50] = L"";
	swprintf_s(word, 50, L"%f, %f", CKeyMgr::GetInst()->GetMousePos().x, CKeyMgr::GetInst()->GetMousePos().y);
	int len = wcsnlen_s(word, 50);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 30, word, len);


	swprintf_s(word, 50, L"%f, %f", MouseRenderPos.x, MouseRenderPos.y);
	int len1 = wcsnlen_s(word, 50);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 50, word, len1);

	swprintf_s(word, 50, L"%f, %f", EditRenderPos.x, EditRenderPos.y);
	int len2 = wcsnlen_s(word, 50);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 70, word, len2);

	swprintf_s(word, 50, L"%f, %f", CCamera::GetInst()->GetDiff().x, CCamera::GetInst()->GetDiff().y);
	int len3 = wcsnlen_s(word, 50);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 90, word, len3);
		

	if (mEditMode == EditMode::FilbookMode)
	{
		wstring strContentPath = CPathMgr::GetContentPath();
		strContentPath += L"Texture\\Enime\\Crawlid.png";

		mTexture = CAssetMgr::GetInst()->LoadTexture(L"Crawlid", strContentPath, true);
		HDC dc = CEngine::GetInst()->GetSecondDC();
		Vec2 vPos = Vec2(0, 0);
		Vec2 vScale = Vec2((int)mTexture->GetWidth(), (int)mTexture->GetHeight());

		BLENDFUNCTION blend = {};

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(dc
			, vPos.x //m_Tex->GetWidth() / 2.f
			, vPos.y //m_Tex->GetHeight() / 2.f
			, mTexture->GetWidth()
			, mTexture->GetHeight()
			, mTexture->GetDC()
			, 0, 0
			, mTexture->GetWidth()
			, mTexture->GetHeight()
			, blend);

		HDC subdc = CEngine::GetInst()->GetEditSecondDC();
		Vec2 subPos = CEngine::GetInst()->GetEditResolution() / 2;

		AlphaBlend(subdc
			, subPos.x - (ColEndPos.x - ColBeginPos.x)/2 //m_Tex->GetWidth() / 2.f*/
			, subPos.y - (ColEndPos.y - ColBeginPos.y)/2//m_Tex->GetHeight() / 2.f*/
			, ColEndPos.x - ColBeginPos.x
			, ColEndPos.y - ColBeginPos.y
			, mSubTexture->GetDC()
			, ColBeginPos.x, ColBeginPos.y
			, ColEndPos.x - ColBeginPos.x
			, ColEndPos.y - ColBeginPos.y
			, blend);


		SELECT_PEN(PEN_TYPE::GREEN);
		SELECT_BRUSH(BRUSH_TYPE::HOLLOW);

		Rectangle(dc, ColBeginPos.x, ColBeginPos.y, ColEndPos.x, ColEndPos.y);

		HDC m_EhDC = CEngine::GetInst()->GetEditDC();
		Vec2 m_EResolution = CEngine::GetInst()->GetEditResolution();

		MoveToEx(m_EhDC, m_EResolution.x / 2, 0, nullptr);
		LineTo(m_EhDC, m_EResolution.x / 2, m_EResolution.y);

		MoveToEx(m_EhDC, 0, m_EResolution.y / 2, nullptr);
		LineTo(m_EhDC, m_EResolution.x, m_EResolution.y / 2);


	}

	if (mEditMode == EditMode::EnimesMode)
	{		
		BLENDFUNCTION blend = {};

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;
		HDC subdc = CEngine::GetInst()->GetEditSecondDC();
		Vec2 subPos = CEngine::GetInst()->GetEditResolution() / 2;

		AlphaBlend(subdc
			, 0//m_Tex->GetWidth() / 2.f*/
			, 0 //m_Tex->GetHeight() / 2.f*/
			, mSubTexture->GetWidth()
			, mSubTexture->GetHeight()
			, mSubTexture->GetDC()
			, 0, 0
			, mSubTexture->GetWidth()
			, mSubTexture->GetHeight()
			, blend);


	}

	if (mEditMode == EditMode::PatternMode && SelectMons)
	{
		HDC dc = CEngine::GetInst()->GetSecondDC();
		Vec2 mPos = SelectMons->GetPos();
		Vec2 mScale = SelectMons->GetScale();
		mPos = CCamera::GetInst()->GetRenderPos(mPos);


		SELECT_PEN(PEN_TYPE::GREEN);
		SELECT_BRUSH(BRUSH_TYPE::HOLLOW);
		Rectangle(dc, mPos.x - mScale.x / 2, mPos.y - mScale.y / 2, mPos.x + mScale.x / 2, mPos.y + mScale.y / 2);

		
	}

	if (mEditMode == EditMode::TileMode)
	{
		BLENDFUNCTION blend = {};

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;
		HDC subdc = CEngine::GetInst()->GetEditSecondDC();
		Vec2 subPos = CEngine::GetInst()->GetEditResolution() / 2;
		HDC mdc = CEngine::GetInst()->GetSecondDC();

		AlphaBlend(subdc
			, 0//m_Tex->GetWidth() / 2.f*/
			, 0 //m_Tex->GetHeight() / 2.f*/
			, mSubTexture->GetWidth()
			, mSubTexture->GetHeight()
			, mSubTexture->GetDC()
			, 0, 0
			, mSubTexture->GetWidth()
			, mSubTexture->GetHeight()
			, blend);


		if (mTexture == nullptr)
			return;

		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;
		HDC dc = CEngine::GetInst()->GetMainDC();
		Vec2 mPos = Vec2(CKeyMgr::GetInst()->GetMousePos().x - mTexture->GetWidth() /4, CKeyMgr::GetInst()->GetMousePos().y - mTexture->GetHeight() /2);

		AlphaBlend(mdc
			, mPos.x
			, mPos.y
			, mTexture->GetWidth()  * _Size
			, mTexture->GetHeight() * _Size
			, mTexture->GetDC()
			, 0, 0
			, mTexture->GetWidth() 
			, mTexture->GetHeight()
			, blend);

	}


	//wchar_t word1[50] = L"";
	//swprintf_s(word1, 50, L"%f, %f", mPlayer->GetPos().x, mPlayer->GetPos().y);
	//int len2 = wcsnlen_s(word1, 50);
	//TextOut(CEngine::GetInst()->GetSecondDC(), 10, 70, word1, len2);


}

void CLevel_Editor::SaveTileMap()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"TileMap";

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 과滔 경로를 받아낼 목적햨E
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		// 맵 오틒E㎷??TileMap 컴포넌트 정보를 저장한다.
		//m_MapObj->GetTileMap()->SaveTileMap(szFilePath);
	}
}

void CLevel_Editor::LoadTileMap()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"TileMap";

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;

	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetOpenFileName(&Desc))
	{

		
	}	
}


void CLevel_Editor::ColliderMode(wstring _name)
{
	mEditMode = EditMode::ColliderMode;
	m_ColliderName = _name;

	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 vRenMousePos = CKeyMgr::GetInst()->GetEditMousePos();

	if (KEY_RELEASED(KEY::LBTN))
	{
		if (ColBeginPos > Vec2(-1, -1) && MouseRenderPos.x > 0 && MouseRenderPos.y > 0)
			ColEndPos = MouseRenderPos;
	}

	if (KEY_RELEASED(KEY::LBTN))
	{
		if (ColEndPos > Vec2(-1, -1) && MouseRenderPos.x > 0 && MouseRenderPos.y > 0)
			return;

		ColBeginPos = MouseRenderPos;
	}


	if (KEY_TAP(KEY::RBTN))
	{
		list<Colision*>::iterator iter = mDrawCol.begin();

		for (; iter != mDrawCol.end(); iter++)
		{
			CCollider* mColider = (*iter)->GetComponent<CCollider>();

			if (fabs(mColider->GetFinalPos().x - MouseRenderPos.x) < mColider->GetScale().x / 2 &&
				fabs(mColider->GetFinalPos().y - MouseRenderPos.y) < mColider->GetScale().y / 2)
			{
				(*iter)->SetDead();
				mDrawCol.erase(iter);
				return;
			}
		}
	}

	if (ColEndPos != Vec2(-1, -1))
	{

		//Vec2 pos = mPlayer->GetPos();

		//ColEndPos = MouseRenderPos;
		Colision* mColision = new Colision;
		AddObject(mColision, LAYER_TYPE::COLLIDER);
		CCollider* mCollider = new CCollider;
		mCollider->SetScale(ColEndPos - ColBeginPos);
		mColision->SetPos(ColBeginPos);
		mCollider->SetOffset(mCollider->GetScale() / 2);
		mColision->SetName(m_ColliderName);
		(CCollider*)mColision->AddComponent(mCollider);

		mDrawCol.push_back(mColision);

		ColBeginPos = Vec2(-1, -1);
		ColEndPos = Vec2(-1, -1);

	}

}

void CLevel_Editor::SaveColider()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"Colider\\";

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 과滔 경로를 받아낼 목적햨E
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Col\0*.col\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (false == GetSaveFileName(&Desc))
		return;

	FILE* File = nullptr;
	_wfopen_s(&File, szFilePath, L"w");

	for (Colision* mColision : mDrawCol)
	{
		CCollider* mCollider = mColision->GetComponent<CCollider>();
		//Colider의 스테이트 값 저픸E
		fwprintf_s(File, L"[Name]\n",255);
		fwprintf_s(File, L"%s\n\n", mColision->GetName().c_str());

		fwprintf_s(File, L"[Position]\n");
		fwprintf_s(File, L"%d, %d\n\n", (int)mCollider->GetOwner()->GetPos().x, (int)mCollider->GetOwner()->GetPos().y);

		fwprintf_s(File, L"[Scale]\n");
		fwprintf_s(File, L"%d, %d\n\n", (int)mCollider->GetScale().x, (int)mCollider->GetScale().y);

		fwprintf_s(File, L"[OFFset]\n");
		fwprintf_s(File, L"%d, %d\n\n", (int)mCollider->GetOffset().x, (int)mCollider->GetOffset().y);


	}
	fclose(File);
}


void CLevel_Editor::LoadColider(wchar_t* Path = nullptr)
{
	wstring strContentPath = CPathMgr::GetContentPath();
	
	strContentPath += L"Colider\\";
	strContentPath += Path;

	// 파일 경로 문자열
	const wchar_t* m_Path = strContentPath.c_str();
	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = Path;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Col\0*.col\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();


		FILE* File = nullptr;

		_wfopen_s(&File, m_Path, L"r");

		while (true)
		{
			wchar_t szBuff[255] = {};
			int fx = 0, fy = 0;

			if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
			{
				break;
			}
			Colision* mColision = new Colision;
			CCollider* mCollider = new CCollider;
			AddObject(mColision, LAYER_TYPE::COLLIDER);

			if (!wcscmp(szBuff, L"[Name]"))
			{
				fwscanf_s(File, L"%s", szBuff, 255);
				mColision->SetName(szBuff);
			}

			if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
			{
				break;
			}

			if (!wcscmp(szBuff, L"[Position]"))
			{
				fwscanf_s(File, L"%d, %d", &fx, &fy);
				mColision->SetPos(Vec2(fx, fy));
			}

			if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
			{
				break;
			}

			if (!wcscmp(szBuff, L"[Scale]"))
			{
				fwscanf_s(File, L"%d, %d", &fx, &fy);
				mCollider->SetScale(Vec2(fx, fy));
			}

			if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
			{
				break;
			}

			if (!wcscmp(szBuff, L"[OFFset]"))
			{
				fwscanf_s(File, L"%d, %d", &fx, &fy);
				mCollider->SetOffset(Vec2(fx, fy));
			}


			mCollider = (CCollider*)mColision->AddComponent(mCollider);
			mDrawCol.push_back(mColision);
		}
		fclose(File);
	
}

void CLevel_Editor::OpenImage()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"Texture\\Enime\\";
	wstring _Path;

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Png\0*.png\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();
	//strContentPath = Desc.lpstrFile - strContentPath;
	if (GetOpenFileName(&Desc))
	{
		mTexture = CAssetMgr::GetInst()->LoadTexture(L"Crawlid", Desc.lpstrFile , true);
		mSubTexture = CAssetMgr::GetInst()->LoadTexture(L"SubCrawlid", Desc.lpstrFile, CEngine::GetInst()->GetEditDC(), true);

	}

	mEditMode = EditMode::FilbookMode;


}

void CLevel_Editor::SaveImage()
{
	//CSprite* mSprite = new CSprite;

	
}

void CLevel_Editor::SavePlibook()
{
}

void CLevel_Editor::LoadPlibook()
{
}

void CLevel_Editor::Enime()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"Texture\\Enime\\";
	wstring _Path;

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Png\0*.png\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();
	//strContentPath = Desc.lpstrFile - strContentPath;
	if (GetOpenFileName(&Desc))
	{
		//mTexture = CAssetMgr::GetInst()->LoadTexture(L"Enimes", Desc.lpstrFile, true);
		mSubTexture = CAssetMgr::GetInst()->LoadTexture(L"EditEnimes01", Desc.lpstrFile, CEngine::GetInst()->GetEditDC(), true);

	}

	mEditMode = EditMode::EnimesMode;
}

void CLevel_Editor::EnimeSave()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"Enimes\\";

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 과滔 경로를 받아낼 목적햨E
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Enimes\0*.enimes\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (false == GetSaveFileName(&Desc))
		return;

	FILE* File = nullptr;
	_wfopen_s(&File, szFilePath, L"w");

	for(CMonster* mMonstor : mMonsters)
	{
		//Monstor의 스테이트 값 저픸E
		fwprintf_s(File, L"[Name]\n",255);
		fwprintf_s(File, L"%s\n\n", mMonstor->GetName().c_str());

		fwprintf_s(File, L"[InitPosition]\n");
		fwprintf_s(File, L"%d, %d \n\n", (int)mMonstor->GetInitPos().x, (int)mMonstor->GetInitPos().y);
	}
	fclose(File);

}

void CLevel_Editor::EnimeLoad(wchar_t* Path = nullptr)
{
	wstring strContentPath = CPathMgr::GetContentPath();

	strContentPath += L"Enimes\\";
	strContentPath += Path;

	 //파일 경로 문자열
	const wchar_t* m_Path = strContentPath.c_str();
	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = Path;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Enimes\0*.enimes\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();


	FILE* File = nullptr;

	_wfopen_s(&File, m_Path, L"r");

	while (true)
	{
		wchar_t szBuff[255] = {};
		int fx = 0, fy = 0 ,fx2 = 0, fy2 = 0;

		CMonster* mMonstor = nullptr;
		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}

		if (!wcscmp(szBuff, L"[Name]"))
		{
			fwscanf_s(File, L"%s", szBuff, 255);

			//몬스터 분리
			if (wcscmp(szBuff, L"Crawlid") == 0)
			{
				mMonstor = new Crawlid;
			}

		}

		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}


		if (!wcscmp(szBuff, L"[InitPosition]"))
		{
			fwscanf_s(File, L"%d, %d", &fx, &fy);
			mMonstor->SetInitPos(Vec2(fx, fy));
		}

		mMonstor->SetPos(mMonstor->GetInitPos());
		AddObject(mMonstor, LAYER_TYPE::MONSTER);
		mMonsters.push_back(mMonstor);
	}
	fclose(File);

}

void CLevel_Editor::EnimeMode()
{
	Vec2 MinTileSize(0, 0);
	Vec2 TileSize = Vec2(100, 100);


	if (mSubTexture->GetKey() == L"EditEnimes01" && KEY_TAP(LBTN) && MinTileSize <= EditRenderPos)
	{
		if (EditRenderPos <= TileSize)
		{
			mEnimeName = EnimesName::Crawlid;
		}
	}
	

	if (KEY_TAP(LBTN) && CKeyMgr::GetInst()->IsMouseOffScreen() == false)
	{
		EnimeRenderer();
	}

}

void CLevel_Editor::EnimeRenderer()
{
	switch (mEnimeName)
	{
	case EnimesName::Crawlid:
	{
		CMonster* mMonstor = new Crawlid;
		mMonstor->SetInitPos(MouseRenderPos);
		mMonstor->SetPos(MouseRenderPos);
		AddObject(mMonstor, LAYER_TYPE::MONSTER);
		mMonsters.push_back(mMonstor);
	}
		break;
	case EnimesName::None:
		break;
	default:
		break;
	}

}

void CLevel_Editor::EnimesPattern()
{
	mEditMode = EditMode::PatternMode;
	
	for (CMonster* mMonstor : mMonsters)
	{
		if (MouseRenderPos >= (mMonstor->GetPos() - mMonstor->GetScale() / 2) && MouseRenderPos <= (mMonstor->GetPos() + mMonstor->GetScale() / 2))
			if (KEY_TAP(LBTN) && SelectMons != mMonstor)
			{
				SelectMons = mMonstor;
				return;
			}
	}

}

void CLevel_Editor::CameraBound(wstring _name)
{
	mEditMode = EditMode::CameraMode;
	m_BoundName = _name;





	if (KEY_RELEASED(KEY::LBTN))
	{
		if (ColBeginPos > Vec2(-1, -1) && MouseRenderPos.x > 0 && MouseRenderPos.y > 0)
			ColEndPos = MouseRenderPos;
	}

	if (KEY_RELEASED(KEY::LBTN))
	{
		if (ColEndPos > Vec2(-1, -1) && MouseRenderPos.x > 0 && MouseRenderPos.y > 0)
			return;

		ColBeginPos = MouseRenderPos;
	}

	if (KEY_TAP(KEY::RBTN))
	{
		for (auto iter = mCameraBounds.begin(); iter != mCameraBounds.end();)
		{
			CCameraBound* mCameraBound = *iter;

			if (fabs(mCameraBound->GetPos().x - MouseRenderPos.x)  < mCameraBound->GetScale().x / 2 
				&& fabs(mCameraBound->GetPos().y - MouseRenderPos.y) < mCameraBound->GetScale().y / 2)
			{
				iter = mCameraBounds.erase(iter);
				mCameraBound->SetDead();
			}

			else
			{
				++iter;
			}
		}
	}



	if (ColEndPos != Vec2(-1, -1))
	{
		CCameraBound* mCameraBound = new CCameraBound;
		AddObject(mCameraBound, LAYER_TYPE::CAMERABOUND);
		CCollider* mCollider = new CCollider;
		mCameraBound->SetName(m_BoundName);
		mCameraBound->SetScale(ColEndPos - ColBeginPos);
		mCameraBound->SetPos(ColBeginPos + mCameraBound->GetScale()/2);
		mCollider->SetScale(mCameraBound->GetScale());
		mCameraBound->AddComponent(mCollider);

		mCameraBounds.push_back(mCameraBound);

		ColBeginPos = Vec2(-1, -1);
		ColEndPos = Vec2(-1, -1);
	}

}

void CLevel_Editor::CameraBoundSave()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"Bound\\";

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 과滔 경로를 받아낼 목적햨E
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Bounds\0*.bounds\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (false == GetSaveFileName(&Desc))
		return;

	FILE* File = nullptr;
	_wfopen_s(&File, szFilePath, L"w");

	for (CCameraBound* mCameraBound : mCameraBounds)
	{
		fwprintf_s(File, L"[Name]\n");
		fwprintf_s(File, L"%s \n\n", mCameraBound->GetName().c_str(), 255);

		fwprintf_s(File, L"[Position]\n");
		fwprintf_s(File, L"%d, %d \n\n", (int)mCameraBound->GetPos().x, (int)mCameraBound->GetPos().y);

		fwprintf_s(File, L"[Scale]\n");
		fwprintf_s(File, L"%d, %d \n\n", (int)mCameraBound->GetComponent<CCollider>()->GetScale().x, (int)mCameraBound->GetComponent<CCollider>()->GetScale().y);
	}
	fclose(File);


}

void CLevel_Editor::CameraBoundLoad(wchar_t* Path = nullptr)
{

	wstring strContentPath = CPathMgr::GetContentPath();

	strContentPath += L"Bound\\";
	strContentPath += Path;

	//파일 경로 문자열
	const wchar_t* m_Path = strContentPath.c_str();
	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = Path;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Bounds\0*.bounds\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();


	FILE* File = nullptr;

	_wfopen_s(&File, m_Path, L"r");

	while (true)
	{
		wchar_t szBuff[255] = {};
		int fx = 0, fy = 0;

		CCameraBound* mCameraBound = new CCameraBound;

		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}

		if (!wcscmp(szBuff, L"[Name]"))
		{
			fwscanf_s(File, L"%s", &szBuff,255);
			mCameraBound->SetName(szBuff);
		}

		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}

		if (!wcscmp(szBuff, L"[Position]"))
		{
			fwscanf_s(File, L"%d, %d", &fx, &fy);
			mCameraBound->SetPos(Vec2(fx, fy));
		}

		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}

		if (!wcscmp(szBuff, L"[Scale]"))
		{
			fwscanf_s(File, L"%d, %d", &fx, &fy);
			mCameraBound->SetScale(Vec2(fx, fy));
		}
;
		AddObject(mCameraBound, LAYER_TYPE::CAMERABOUND);
		mCameraBounds.push_back(mCameraBound);
	}
	fclose(File);
}

void CLevel_Editor::InsertTile(wstring _name)
{
	mEditMode = EditMode::TileMode;
	m_TileName = _name;
	if (m_TileName == L"KingLoad")
	{
		mSubTexture = CAssetMgr::GetInst()->LoadTexture(L"EditTile", L"Texture\\Map\\King Load Tile.png", CEngine::GetInst()->GetEditSecondDC());

		if (fabs(125.0f - EditRenderPos.x) < 125.0f && fabs(125.0f - EditRenderPos.y) < 125.0f)
		{
			if (KEY_TAP(KEY::LBTN))
			{
				mTexture = CAssetMgr::GetInst()->LoadTexture(L"KingLoad", L"Texture\\Map\\Tile1.png", CEngine::GetInst()->GetSecondDC());
			}
		}

		else if (fabs(375.0f - EditRenderPos.x) < 125.0f && fabs(125.0f - EditRenderPos.y) < 125.0f)
		{
			if (KEY_TAP(KEY::LBTN))
			{
				mTexture = CAssetMgr::GetInst()->LoadTexture(L"KingLoad2", L"Texture\\Map\\Tile2.png", CEngine::GetInst()->GetSecondDC());
			}
		}

		else if (fabs(125.0f - EditRenderPos.x) < 125.0f && fabs(375.0f - EditRenderPos.y) < 125.0f)
		{
			if (KEY_TAP(KEY::LBTN))
			{
				mTexture = CAssetMgr::GetInst()->LoadTexture(L"KingLoad3", L"Texture\\Map\\Tile3.png", CEngine::GetInst()->GetSecondDC());
			}
		}

		else if (fabs(375.0f - EditRenderPos.x) < 125.0f && fabs(375.0f - EditRenderPos.y) < 125.0f)
		{
			if (KEY_TAP(KEY::LBTN))
			{
				mTexture = CAssetMgr::GetInst()->LoadTexture(L"KingLoad4", L"Texture\\Map\\Tile4.png", CEngine::GetInst()->GetSecondDC());
			}
		}


		if (CKeyMgr::GetInst()->GetMouseheel() > 0)
			_Size += 0.01;
		else if (CKeyMgr::GetInst()->GetMouseheel() < 0)
			_Size -= 0.01;

		if (KEY_TAP(KEY::LBTN) && CEngine::GetInst()->GetResolution().x >= CKeyMgr::GetInst()->GetMousePos().x && CEngine::GetInst()->GetResolution().y >= CKeyMgr::GetInst()->GetMousePos().y)
		{
			if (mTexture == nullptr)
				return;

			CTile* mtile = new CTile;
			mtile->SetName(mTexture->GetKey());
			mtile->SetPos(Vec2(MouseRenderPos.x - mTexture->GetWidth() / 4, MouseRenderPos.y - mTexture->GetHeight() / 2));
			mtile->SetScale(Vec2(mTexture->GetWidth() * _Size, mTexture->GetHeight() * _Size));
			mtile->Begin();
			//mtile->SetSize(_Size);

			AddObject(mtile, LAYER_TYPE::ATTCK_TILE);

			mTiles.push_back(mtile);
		}

		
	}
	
}

void CLevel_Editor::TileSave()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"Tile\\";

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// 최종적으로 과滔 경로를 받아낼 목적햨E
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tiles\0*.tiles\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (false == GetSaveFileName(&Desc))
		return;

	FILE* File = nullptr;
	_wfopen_s(&File, szFilePath, L"w");

	for (CTile* mTile : mTiles)
	{
		fwprintf_s(File, L"[Name]\n");
		fwprintf_s(File, L"%s\n\n", mTile->GetName().c_str());

		fwprintf_s(File, L"[Position]\n");
		fwprintf_s(File, L"%d, %d \n\n", (int)mTile->GetPos().x, (int)mTile->GetPos().y);

		fwprintf_s(File, L"[Scale]\n");
		fwprintf_s(File, L"%d, %d \n\n", (int)mTile->GetScale().x, (int)mTile->GetScale().y);

	}
	fclose(File);


}

void CLevel_Editor::TileLoad(wchar_t* Path)
{
	wstring strContentPath = CPathMgr::GetContentPath();

	strContentPath += L"Tile\\";
	strContentPath += Path;

	//파일 경로 문자열
	const wchar_t* m_Path = strContentPath.c_str();
	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = Path;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tiles\0*.tiles\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();


	FILE* File = nullptr;

	_wfopen_s(&File, m_Path, L"r");

	while (true)
	{
		wchar_t szBuff[255] = {};
		int fx = 0, fy = 0;

		CTile* mtile = new CTile;

		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}

		if (!wcscmp(szBuff, L"[Name]"))
		{
			fwscanf_s(File, L"%s", szBuff,255);
			mtile->SetName(szBuff);

		}

		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}

		if (!wcscmp(szBuff, L"[Position]"))
		{
			fwscanf_s(File, L"%d, %d", &fx, &fy);
			mtile->SetPos(Vec2(fx, fy));
		}

		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}

		if (!wcscmp(szBuff, L"[Scale]"))
		{
			fwscanf_s(File, L"%d, %d", &fx, &fy);
			mtile->SetScale(Vec2(fx, fy));
		}

		AddObject(mtile, LAYER_TYPE::ATTCK_TILE);
		mTiles.push_back(mtile);
	}
	fclose(File);

}


// =======
// 픸Eで獨갋
// =======
INT_PTR CALLBACK    TileMapInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void SaveTileMap()
{
	DialogBox(nullptr, MAKEINTRESOURCE(DLG_TILEMAP_INFO), CEngine::GetInst()->GetMainWndHwnd(), &TileMapInfoProc);

	/*CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
	if (nullptr == pEditorLevel)
		return;

	pEditorLevel->SaveTileMap();*/
}


void LoadTileMap()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
	if (nullptr == pEditorLevel)
		return;

	pEditorLevel->LoadTileMap();
}

void SaveColider()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
	if (nullptr == pEditorLevel)
		return;

	pEditorLevel->SaveColider();
}

	void LoadColider()
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
		if (nullptr == pEditorLevel)
			return;

		pEditorLevel->LoadColider();
	}

	void ImageOpen()
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
		if (nullptr == pEditorLevel)
			return;

		pEditorLevel->OpenImage();
	}

	void ImageSave()
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
		if (nullptr == pEditorLevel)
			return;

		pEditorLevel->SaveImage();
	}

	void PlibookSave()
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
		if (nullptr == pEditorLevel)
			return;

		pEditorLevel->SavePlibook();
	}

	void PlibookLoad()
	{
		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
		if (nullptr == pEditorLevel)
			return;

		pEditorLevel->LoadPlibook();
	}




bool EditorMenu(HINSTANCE _inst, HWND _wnd, int wParam)
{
	switch (wParam)
	{
	case ID_TILE_INFO:
	{
		DialogBox(_inst, MAKEINTRESOURCE(DLG_TILEMAP_INFO), _wnd, &TileMapInfoProc);

		/* if(nullptr == g_hDlg)
			g_hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(DLG_TILEMAP_INFO), hWnd, &TileMapInfoProc);

		ShowWindow(g_hDlg, true);*/
		return true;
	}
	case ID_TILEMAP_SAVE:
	{
		// CLevel_Editor 에 있는 MapObject 의 타일맵 컴포넌트의 ?E렬을 설정해주엉雹 함
		// 현픸E레벨을 알아낸다. 정황퍊E현픸E레벨은 반드시 CLevel_Editor 여야 한다.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->SaveTileMap();
		return true;

	}
	case ID_TILEMAP_LOAD:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadTileMap();
		return true;
	}
		

	case ID_COLLIDERS_GROUND:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->ColliderMode(L"Ground");
		return true;

		/*	ID_COLLIDERS_GROUND
		ID_COLLIDERS_HURT
		ID_COLLIDERS_FIRE
		ID_COLLIDERS_POISON*/
	}

	case ID_COLLIDERS_HURT:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->ColliderMode(L"Hurt");
		return true;
	}



	case Col_Save:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->SaveColider();
		return true;

	}
	
	case Col_Load:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadColider();
		return true;
	}
		

	case ID_IM_OPEN:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->OpenImage();
		return true;
	}

	case ID_IM_SAVE:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->SaveImage();
		return true;
	}

	case ID_PL_SAVE:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->SavePlibook();
		return true;
	}

	case ID_PL_LOAD:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadPlibook();
		return true;
	}
	

	case ID_ENIMES:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->Enime();
		return true;
	}

	case ID_Enimes_SAVE:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->EnimeSave();
		return true;
	}
	case ID_Enimes_LOAD:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->EnimeLoad();
		return true;
	}

	case ID_ENIMES_PATTERN:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->EnimesPattern();
		return true;
	}

	case ID_BOUND_ALL:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->CameraBound(L"AllBoundBox");
		return true;
	}
	case ID_BOUND_XBOUND:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->CameraBound(L"XBoundBox");
		return true;
	}

	case ID_BOUND_YBOUND:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->CameraBound(L"YBoundBox");
		return true;
	}


	case ID_CAMERA_SAVE:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->CameraBoundSave();
		return true;
	}

	case ID_CAMERA_LOAD:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->CameraBoundLoad();
		return true;
	}

	case ID_INSERT_KINGLOAD:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->InsertTile(L"KingLoad");

		return true;
	}

	case ID_TILE_SAVE:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->TileSave();

		return true;
	}

	};



	return false;
}

// ============================
// Tile_Map_Info Dialog 프로시픸E
// ============================
INT_PTR CALLBACK TileMapInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// 에디트 컨트롤에 입력한 숫자를 알아내야함
			int Row = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);
			int Col = GetDlgItemInt(hDlg, IDC_COL, nullptr, true);

			// CLevel_Editor 에 있는 MapObject 의 타일맵 컴포넌트의 ?E렬을 설정해주엉雹 함
			// 현픸E레벨을 알아낸다. 정황퍊E현픸E레벨은 반드시 CLevel_Editor 여야 한다.
			CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
			assert(pEditorLevel);

			// Editor 레벨에 생성해 놓은 CMap 오틒E㎷??가져옴
			CMap* pMapObj = pEditorLevel->GetMapObject();

			// 타일맵 컴포넌트의 수치를 에디트컨트롤에 입력된 숫자로 변컖E
			CTileMap* pTileMap = pMapObj->GetComponent<CTileMap>();
			pTileMap->SetRowCol(Row, Col);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
		}


		break;
	}
	return (INT_PTR)FALSE;
}

