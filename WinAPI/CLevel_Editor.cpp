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
	// ����� ����
	//CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"DM_Opening", L"Sound\\DM.wav");
	//if (nullptr != pSound)
	//{
	//	pSound->SetVolume(70.f);
	//	pSound->PlayToBGM(true);
	//}

	// �޴��� �ε� �� ���� �����쿡 ����
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINAPI));
	}	
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), m_hMenu);

	// �޴��ٰ� �߰��Ǿ��� ������, ������ ũ�⸦ �������Ѵ�.
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());

	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	
	CCamera::GetInst()->GetLookAt();
	
	// Player ����
	mPlayer = new CPlayer;
	mPlayer->SetName(L"Player");
	mPlayer->SetPos(CEngine::GetInst()->GetResolution());


	AddObject(mPlayer, LAYER_TYPE::PLAYER);

	// ���ÿ� Map ������Ʈ ����
	m_MapObj = new CMap;
	AddObject(m_MapObj, LAYER_TYPE::TILE);

	
	//CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDER);


	// ���� �Ҽ� ��� ������Ʈ�� Begin �� ȣ����� �� �ֵ��� �Ѵ�
	CLevel::Begin();
}

void CLevel_Editor::End()
{
	DeleteAllObject();

	// �޴��� ����
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), nullptr);

	// �޴��� ���ŵǾ����Ƿ�, �ٽ� ������ ũ�� ����
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());
}


void CLevel_Editor::Tick()
{
	CLevel::Tick();

	// Ư�� Ű�� ������ Start ������ ����
	if (KEY_TAP(KEY::M))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		ChangeLevel(LEVEL_TYPE::START);
	}

	// ���콺 Ŭ������ CMap ������Ʈ�� Ÿ�� �̹��� �ε��� ����
	// �Ϲ����� ������ : ���� ��ǥ -> Render ��ǥ ����
	// ���콺 ��ǥ : Render ��ǥ(���콺��ǥ) -> ���� ��ǥ�� ����
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

	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// ���������� �� ��θ� �޾Ƴ� ������
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		// �� ������Ʈ�� TileMap ������Ʈ ������ �����Ѵ�.
		//m_MapObj->GetTileMap()->SaveTileMap(szFilePath);
	}
}

void CLevel_Editor::LoadTileMap()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"TileMap";

	// ���� ��� ���ڿ�
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
// �����Լ�
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
		// CLevel_Editor �� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� �� ���� �������־�� ��
		// ���� ������ �˾Ƴ���. ��Ȳ�� ���� ������ �ݵ�� CLevel_Editor ���� �Ѵ�.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->SaveTileMap();
	}
		return true;
	case ID_TILEMAP_LOAD:
	{
		// CLevel_Editor �� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� �� ���� �������־�� ��
		// ���� ������ �˾Ƴ���. ��Ȳ�� ���� ������ �ݵ�� CLevel_Editor ���� �Ѵ�.
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
// Tile_Map_Info Dialog ���ν���
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
			// ����Ʈ ��Ʈ�ѿ� �Է��� ���ڸ� �˾Ƴ�����
			int Row = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);
			int Col = GetDlgItemInt(hDlg, IDC_COL, nullptr, true);

			// CLevel_Editor �� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� �� ���� �������־�� ��
			// ���� ������ �˾Ƴ���. ��Ȳ�� ���� ������ �ݵ�� CLevel_Editor ���� �Ѵ�.
			CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
			assert(pEditorLevel);

			// Editor ������ ������ ���� CMap ������Ʈ�� ������
			CMap* pMapObj = pEditorLevel->GetMapObject();

			// Ÿ�ϸ� ������Ʈ�� ��ġ�� ����Ʈ��Ʈ�ѿ� �Էµ� ���ڷ� ������
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