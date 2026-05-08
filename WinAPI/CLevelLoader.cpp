#include "pch.h"
#include "CLevelLoader.h"

#include "CPathMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CTile.h"

#include "CCameraBound.h"

#include "Colision.h"
#include "CCollider.h"

#include "CMonster.h"
#include "Crawlid.h"
#include "Vengefly.h"


void CLevelLoader::LoadColider(CLevel* mlevel, wchar_t* Path)
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
		mlevel->AddObject(mColision, LAYER_TYPE::COLLIDER);

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
	}
	fclose(File);

}
void CLevelLoader::EnimeLoad(CLevel* mlevel, wchar_t* Path)
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
		int fx = 0, fy = 0, fx2 = 0, fy2 = 0;

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

			if (wcscmp(szBuff, L"Vengefly") == 0)
			{
				mMonstor = new Vengefly;
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
		mlevel->AddObject(mMonstor, LAYER_TYPE::MONSTER);
	}
	fclose(File);

}
void CLevelLoader::CameraBoundLoad(CLevel* mlevel, wchar_t* Path)
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
			fwscanf_s(File, L"%s", &szBuff, 255);
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
		mlevel->AddObject(mCameraBound, LAYER_TYPE::CAMERABOUND);
	}
	fclose(File);

}
void CLevelLoader::TileLoad(CLevel* mlevel, wchar_t* Path)
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
			fwscanf_s(File, L"%s", szBuff, 255);
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

		mlevel->AddObject(mtile, LAYER_TYPE::ATTCK_TILE);
	}
	fclose(File);

}