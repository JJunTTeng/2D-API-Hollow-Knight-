#include "pch.h"
#include "CFlipbookPlayer.h"

#include "CTimeMgr.h"
#include "CFlipbook.h"

#include "CEngine.h"
#include "CSprite.h"
#include "CTexture.h"

CFlipbookPlayer::CFlipbookPlayer()
	: CComponent(COMPONENT_TYPE::FLIPBOOKPLAYER)
	, m_CurFlipbook(nullptr)
	, m_SpriteIdx(0)
	, m_FPS(0.f)
	, m_Time(0.f)
	, m_Repeat(false)
	, m_Finish(false)
{
}

CFlipbookPlayer::~CFlipbookPlayer()
{
}

void CFlipbookPlayer::FinalTick()
{
	// 현재 재생중인 Flipbook 이 없으면 끝
	if (nullptr == m_CurFlipbook)
	{
		return;
	}

	if (m_Finish)
	{	
		// 반복 재생하기로 했으면 다시 0 번 스프라이트로 인덱스를 변경한다.
		if (m_Repeat)
			Reset();

		// 한번 재생이 끝났고(m_Finish), 반복 재생모드가 아니라면
		// 마지막 프레임을 유지하도록 한다.
		else
			return;
	}	

	// FPS 에 따른 시간체크
	m_Time += DT;
	if (1.f / m_FPS <= m_Time)
	{
		m_Time -= 1.f / m_FPS;
		++m_SpriteIdx;

		// 마지막 Sprite 에 도달했다면
		if (m_CurFlipbook->GetMaxSpriteCount() <= m_SpriteIdx)
		{
			// Finish 상태 On
			m_Finish = true;
			--m_SpriteIdx;
		}
	}
}

void CFlipbookPlayer::Render()
{
	if (nullptr == m_CurFlipbook)
		return;

	CSprite* Sprite = m_CurFlipbook->GetSprite(m_SpriteIdx);
	// Sprite 를 화면에 그린다.
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	Vec2 LeftTop = Vec2(vPos.x - (Sprite->GetSlice().x / 2) + Sprite->GetOffset().x,
						vPos.y - (Sprite->GetSlice().y / 2) + Sprite->GetOffset().y);

	HDC dc = CEngine::GetInst()->GetSecondDC();
	BLENDFUNCTION blend = {};


	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(dc
		, vPos.x - (Sprite->GetSlice().x / 2) + Sprite->GetOffset().x
		, vPos.y - (Sprite->GetSlice().y / 2) + Sprite->GetOffset().y
		, Sprite->GetSlice().x
		, Sprite->GetSlice().y
		, Sprite->GetAtlas()->GetDC()
		, Sprite->GetLeftTop().x
		, Sprite->GetLeftTop().y
		, Sprite->GetSlice().x
		, Sprite->GetSlice().y
		, blend);

	//TransparentBlt(hBackDC
	//	, vPos.x - (Sprite->GetSlice().x / 2) + Sprite->GetOffset().x
	//	, vPos.y - (Sprite->GetSlice().y / 2) + Sprite->GetOffset().y
	//	, Sprite->GetSlice().x
	//	, Sprite->GetSlice().y
	//	, Sprite->GetAtlas()->GetDC()
	//	, Sprite->GetLeftTop().x
	//	, Sprite->GetLeftTop().y
	//	, Sprite->GetSlice().x
	//	, Sprite->GetSlice().y
	//	, RGB(255, 0, 255));


	
}