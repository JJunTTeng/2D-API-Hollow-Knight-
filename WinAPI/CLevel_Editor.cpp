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

#include "CBgMap.h"

#include "CCollisionMgr.h"



CLevel_Editor::CLevel_Editor()
	: m_MapObj(nullptr)
	, m_hMenu(nullptr)
	, ColBeginPos(0,0)
	, ColEndPos(0,0)
	, MouseRenderPos(0,0)
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

	
	//CCamera::GetInst()->GetLookAt();
	//
	//// Player ����
	//mPlayer = new CPlayer;
	//mPlayer->SetName(L"Player");
	//mPlayer->SetPos(Vec2(1954,1348));


	//AddObject(mPlayer, LAYER_TYPE::PLAYER);

	//// ���ÿ� Map ������Ʈ ����
	//m_MapObj = new CMap;
	//AddObject(m_MapObj, LAYER_TYPE::TILE);

	//CBgMap* mBgMap = new CBgMap;
	//AddObject(mBgMap, LAYER_TYPE::FrontBg);

	//CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::COLLIDER);

	//wchar_t m_Path[255] = L"1-1";

	//LoadColider(m_Path);

	// ���� �Ҽ� ��� ������Ʈ�� Begin �� ȣ����� �� �ֵ��� �Ѵ�
	CLevel::Begin();
}

void CLevel_Editor::End()
{
	//DeleteAllObject();

	// �޴��� ����
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), nullptr);

	// �޴��� ���ŵǾ����Ƿ�, �ٽ� ������ ũ�� ����
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());
}


void CLevel_Editor::Tick()
{
	//CLevel::Tick();

	//// Ư�� Ű�� ������ Start ������ ����
	//if (KEY_TAP(KEY::M))
	//{
	//	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	//	ChangeLevel(LEVEL_TYPE::START);
	//}

	//// ���콺 Ŭ������ CMap ������Ʈ�� Ÿ�� �̹��� �ε��� ����
	//// �Ϲ����� ������ : ���� ��ǥ -> Render ��ǥ ����
	//// ���콺 ��ǥ : Render ��ǥ(���콺��ǥ) -> ���� ��ǥ�� ����
	//
	//MouseRenderPos = mPlayer->GetPos() + CKeyMgr::GetInst()->GetMousePos() - CEngine::GetInst()->GetResolution() / 2;
	//if (KEY_TAP(KEY::LBTN))
	//{		
	//	ColBeginPos = MouseRenderPos;
	//}

	//if (KEY_TAP(KEY::RBTN))
	//{
	//	
	//	list<Colision*>::iterator iter = mDrawCol.begin();

	//	for (; iter != mDrawCol.end(); iter++)
	//	{
	//		CCollider* mColider = (*iter)->GetComponent<CCollider>();
	//					
	//		if(fabs(mColider->GetFinalPos().x - MouseRenderPos.x) < mColider->GetScale().x /2 && 
	//			fabs(mColider->GetFinalPos().y - MouseRenderPos.y) < mColider->GetScale().y / 2)
	//		{
	//			(*iter)->SetDead();

	//			return;
	//		}
	//	}
	//}

	//if (KEY_PRESSED(KEY::LBTN))
	//{
	//	ColEndPos = MouseRenderPos;
	//}



	//if (KEY_RELEASED(KEY::LBTN))
	//{

	//	Vec2 pos = mPlayer->GetPos();

	//	ColEndPos = MouseRenderPos;
	//	CObj* mColision = new Colision;
	//	AddObject(mColision, LAYER_TYPE::COLLIDER);
	//	CCollider* mCollider = new CCollider;
	//	mColision->SetPos(ColBeginPos);
	//	mCollider->SetScale(ColEndPos - ColBeginPos);
	//	mCollider->SetOffset(mCollider->GetScale()/2);
	//	mCollider->SetName(L"Tile");
	//	mCollider = (CCollider*)mColision->AddComponent(mCollider);

	//	mDrawCol.push_back((Colision*)mColision);


	//	ColBeginPos = Vec2(0, 0);
	//	ColEndPos = Vec2(0, 0);
	//}



}

void CLevel_Editor::Render()
{
	CLevel::Render();

	SELECT_PEN(PEN_TYPE::GREEN);
	SELECT_BRUSH(BRUSH_TYPE::HOLLOW);

	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Editor Level", wcslen(L"Editor Level"));

	wchar_t word[50] = L"";
	swprintf_s(word, 50, L"%f, %f", CKeyMgr::GetInst()->GetMousePos().x, CKeyMgr::GetInst()->GetMousePos().y);
	int len = wcsnlen_s(word, 50);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 30, word, len);


	swprintf_s(word, 50, L"%f, %f", MouseRenderPos.x, MouseRenderPos.y);
	int len1 = wcsnlen_s(word, 50);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 50, word, len1);

	//wchar_t word1[50] = L"";
	//swprintf_s(word1, 50, L"%f, %f", mPlayer->GetPos().x, mPlayer->GetPos().y);
	//int len2 = wcsnlen_s(word1, 50);
	//TextOut(CEngine::GetInst()->GetSecondDC(), 10, 70, word1, len2);


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

		
	}	
}

void CLevel_Editor::SaveColider()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"Colider\\";

	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// ���������� �� ��θ� �޾Ƴ� ������
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
		//Colider�� ������Ʈ �� ����
		fwprintf_s(File, L"[Name]\n");
		fwprintf_s(File, L"%s\n\n", mCollider->GetName().c_str());

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

	// ���� ��� ���ڿ�
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
				mCollider->SetName(szBuff);
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
}

void CLevel_Editor::SaveImage()
{
}

void CLevel_Editor::SavePlibook()
{
}

void CLevel_Editor::LoadPlibook()
{
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

		pEditorLevel->LoadColider();
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

	case Col_Save:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->SaveColider();
	}
	return true;

	case Col_Load:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadColider();
	}
		return true;

	case ID_IM_OPEN:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadColider();
	}

	case ID_IM_SAVE:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadColider();
	}

	case ID_PL_SAVE:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadColider();
	}

	case ID_PL_LOAD:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadColider();
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

