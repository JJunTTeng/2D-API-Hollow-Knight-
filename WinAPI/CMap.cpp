#include "pch.h"
#include "CMap.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CTileMap.h"
#include "CEngine.h"


CMap::CMap()
	:mTexture(nullptr)
{

}

CMap::~CMap()
{
}

void CMap::Tick()
{

}

void CMap::Render()
{
	wstring _name;
	if (GetName() == L"KingPass")
		_name = L"Texture\\Map\\Kings Pass.png";

	if (GetName() == L"Dirtmouth")
		_name = L"Texture\\Map\\Dirtmouth.png";

	if (GetName() == L"Forgotten")
		_name = L"Texture\\Map\\Forgotten Crossroads.png";

	if (GetName() == L"FalseKnight")
		_name = L"Texture\\Map\\False Knight.png";

	CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"Map", _name);
	HDC dc = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

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


}