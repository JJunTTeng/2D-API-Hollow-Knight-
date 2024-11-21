#include "pch.h"
#include "CBgMap.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CTileMap.h"
#include "CEngine.h"
#include "CTexture.h"


CBgMap::CBgMap()
	:mTexture(nullptr)
{

}

CBgMap::~CBgMap()
{
}

void CBgMap::Tick()
{

}

void CBgMap::Render()
{
	CTexture* mTexture = CAssetMgr::GetInst()->LoadTexture(L"BgMap", L"Texture\\Map\\BG Kings Pass.png");
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