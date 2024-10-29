#include "pch.h"
#include "CLevel_Editor.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CMap.h"
#include "CTileMap.h"

#include "CLevelMgr.h"
#include "CCamera.h"

#include "CPathMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

#include "CAssetMgr.h"
#include "CSound.h"

#include "Colision.h"
#include "CCollider.h"

#include "CSelectGDI.h"
#include "CPlayer.h"

#include "CCollisionMgr.h"



CLevel_Editor::CLevel_Editor()
	: m_MapObj(nullptr)
	, m_hMenu(nullptr)
	, ColBeginPos(0,0)
	, ColEndPos(0,0)
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

	// 메뉴바 로드 및 메인 윈도우에 부착
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINAPI));
	}	
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), m_hMenu);

	// 메뉴바가 추가되었기 때문에, 윈도우 크기를 재조정한다.
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());

	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	
	CCamera::GetInst()->GetLookAt();
	
	// Player 생성
	mPlayer = new CPlayer;
	mPlayer->SetName(L"Player");
	mPlayer->SetPos(CEngine::GetInst()->GetResolution());


	AddObject(mPlayer, LAYER_TYPE::PLAYER);

	// 샘플용 Map 오브젝트 생성
	m_MapObj = new CMap;
	AddObject(m_MapObj, LAYER_TYPE::TILE);

	
	//CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDER);


	// 레벨 소속 모든 오브젝트가 Begin 을 호출받을 수 있도록 한다
	CLevel::Begin();
}

void CLevel_Editor::End()
{
	DeleteAllObject();

	// 메뉴바 제거
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), nullptr);

	// 메뉴가 제거되었으므로, 다시 윈도우 크기 조정
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());
}


void CLevel_Editor::Tick()
{
	CLevel::Tick();

	// 특정 키가 눌리면 Start 레벨로 변경
	if (KEY_TAP(KEY::M))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		ChangeLevel(LEVEL_TYPE::START);
	}

	// 마우스 클릭으로 CMap 오브젝트의 타일 이미지 인덱스 변경
	// 일반적인 렌더링 : 실제 좌표 -> Render 좌표 변경
	// 마우스 좌표 : Render 좌표(마우스좌표) -> 실제 좌표로 변경
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	if (KEY_TAP(KEY::LBTN))
	{		

		ColBeginPos = vMousePos;
	}

	if (KEY_PRESSED(KEY::LBTN))
	{
		ColEndPos = vMousePos;
	}



	if (KEY_RELEASED(KEY::LBTN))
	{

		Vec2 pos = mPlayer->GetPos();

		ColEndPos = vMousePos;
		CObj* mColision = new Colision;
		AddObject(mColision, LAYER_TYPE::COLLIDER);
		CCollider* mCollider = new CCollider;
		mColision->SetPos(mPlayer->GetPos() - CEngine::GetInst()->GetResolution() / 2  + ColBeginPos);
		mCollider->SetScale(ColEndPos - ColBeginPos);
		mCollider->SetOffset(mCollider->GetScale()/2);
		mCollider->SetName(L"Tile");
		mCollider = (CCollider*)mColision->AddComponent(mCollider);

		mDrawCol.push_back((Colision*)mColision);


		ColBeginPos = Vec2(0, 0);
		ColEndPos = Vec2(0, 0);
	}



}

void CLevel_Editor::Render()
{
	CLevel::Render();

	SELECT_PEN(PEN_TYPE::GREEN);
	SELECT_BRUSH(BRUSH_TYPE::HOLLOW);
	Rectangle(CEngine::GetInst()->GetSecondDC(), ColBeginPos.x , ColBeginPos.y, 
		ColEndPos.x , ColEndPos.y );



	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Editor Level", wcslen(L"Editor Level"));

	wchar_t word[50] = L"";
	swprintf_s(word, 50, L"%f, %f", CKeyMgr::GetInst()->GetMousePos().x, CKeyMgr::GetInst()->GetMousePos().y);
	int len = wcsnlen_s(word, 50);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 30, word, len);

	wchar_t word1[50] = L"";
	swprintf_s(word1, 50, L"%f, %f", mPlayer->GetPos().x, mPlayer->GetPos().y);
	int len1 = wcsnlen_s(word1, 50);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 50, word1, len1);


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
	Desc.lpstrFile = szFilePath;	// 최종적으로 고른 경로를 받아낼 목적지
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		// 맵 오브젝트의 TileMap 컴포넌트 정보를 저장한다.
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
		//m_MapObj->GetTileMap()->LoadTileMap(szFilePath);
	}	
}






// =======
// 전역함수
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
		// CLevel_Editor 에 있는 MapObject 의 타일맵 컴포넌트의 행 렬을 설정해주어야 함
		// 현재 레벨을 알아낸다. 정황상 현재 레벨은 반드시 CLevel_Editor 여야 한다.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->SaveTileMap();
	}
		return true;
	case ID_TILEMAP_LOAD:
	{
		// CLevel_Editor 에 있는 MapObject 의 타일맵 컴포넌트의 행 렬을 설정해주어야 함
		// 현재 레벨을 알아낸다. 정황상 현재 레벨은 반드시 CLevel_Editor 여야 한다.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadTileMap();
	}
		return true;
	};

	return false;
}

// ============================
// Tile_Map_Info Dialog 프로시저
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

			// CLevel_Editor 에 있는 MapObject 의 타일맵 컴포넌트의 행 렬을 설정해주어야 함
			// 현재 레벨을 알아낸다. 정황상 현재 레벨은 반드시 CLevel_Editor 여야 한다.
			CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
			assert(pEditorLevel);

			// Editor 레벨에 생성해 놓은 CMap 오브젝트를 가져옴
			CMap* pMapObj = pEditorLevel->GetMapObject();

			// 타일맵 컴포넌트의 수치를 에디트컨트롤에 입력된 숫자로 변경함
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