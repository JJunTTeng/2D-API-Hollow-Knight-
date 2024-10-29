#include "pch.h"
#include "CMap.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CTileMap.h"
#include "CEngine.h"
#include "CTexture.h"


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
	CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"Map", L"Texture\\Map\\Kings Pass.png");
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