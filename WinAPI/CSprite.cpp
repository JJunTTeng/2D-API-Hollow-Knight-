#include "pch.h"
#include "CSprite.h"

#include "CAssetMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"

CSprite::CSprite()
	: CAsset(ASSET_TYPE::SPRITE)
	, m_Atlas(nullptr)
{
}

CSprite::~CSprite()
{
}

void CSprite::Create(CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice)
{
	m_Atlas = _Atlas;
	m_LeftTop = _LeftTop;
	m_Slice = _Slice;
}

int CSprite::Save(const wstring& _RelativePath)
{
	wstring RelativePath = _RelativePath;
	CheckExt(L".sprite", RelativePath);

	// 에셋이 자신이 어디에 저장되는지를 알게 함
	SetRelativePath(RelativePath);

	wstring strFilePath = CPathMgr::GetContentPath() + RelativePath;
	
	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"w");
	
	// 가리키던 Atlas 텍스쳐의 키, 경로를 저장한다.	
	fwprintf_s(File, L"[KEY]\n");
	fwprintf_s(File, L"%s\n\n", GetKey().c_str());

	fwprintf_s(File, L"[PATH]\n");
	fwprintf_s(File, L"%s\n\n", GetRelativePath().c_str());
		
	wstring strAtlasKey, strAtlasPath;
	if (m_Atlas)
	{
		strAtlasKey = m_Atlas->GetKey();
		strAtlasPath = m_Atlas->GetRelativePath();		
	}	
	fwprintf_s(File, L"[ATLAS_KEY]\n");
	fwprintf_s(File, L"%s\n", strAtlasKey.c_str());
	fwprintf_s(File, L"[ATLAS_PATH]\n");
	fwprintf_s(File, L"%s\n\n", strAtlasPath.c_str());


	fwprintf_s(File, L"[LEFT_TOP]\n");
	fwprintf_s(File, L"%d, %d\n\n", (int)m_LeftTop.x, (int)m_LeftTop.y);

	fwprintf_s(File, L"[SLICE]\n");
	fwprintf_s(File, L"%d, %d\n\n", (int)m_Slice.x, (int)m_Slice.y);

	fwprintf_s(File, L"[OFFSET]\n");
	fwprintf_s(File, L"%d, %d\n\n", (int)m_Offset.x, (int)m_Offset.y);
	

	fclose(File);

	return S_OK;
}

int CSprite::Load(const wstring& _RelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath() + _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"r");

	// 가리키던 Atlas 텍스쳐의 키, 경로를 저장한다.
	wstring AtlasKey, AtlasPath;

	while (true)
	{
		wchar_t szBuff[255] = {};
		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}

		if (!wcscmp(szBuff, L"[KEY]"))
		{
			fwscanf_s(File, L"%s", szBuff, 255);
			SetKey(szBuff);
		}

		else if (!wcscmp(szBuff, L"[PATH]"))
		{
			fwscanf_s(File, L"%s", szBuff, 255);
			SetRelativePath(szBuff);
		}

		else if (!wcscmp(szBuff, L"[ATLAS_KEY]"))
		{			
			fwscanf_s(File, L"%s", szBuff, 255);
			AtlasKey = szBuff;
		}

		else if (!wcscmp(szBuff, L"[ATLAS_PATH]"))
		{
			fwscanf_s(File, L"%s", szBuff, 255);
			AtlasPath = szBuff;
			m_Atlas = CAssetMgr::GetInst()->LoadTexture(AtlasKey, AtlasPath);
		}

		else if (!wcscmp(szBuff, L"[LEFT_TOP]"))
		{
			int x = 0, y = 0;
			fwscanf_s(File, L"%d, %d", &x, &y);
			m_LeftTop = Vec2(x, y);			
		}

		else if (!wcscmp(szBuff, L"[SLICE]"))
		{
			int x = 0, y = 0;
			fwscanf_s(File, L"%d, %d", &x, &y);
			m_Slice = Vec2(x, y);
		}

		else if (!wcscmp(szBuff, L"[OFFSET]"))
		{
			int x = 0, y = 0;
			fwscanf_s(File, L"%d, %d", &x, &y);
			m_Offset = Vec2(x, y);
		}
	}


	fclose(File);

	return S_OK;
}