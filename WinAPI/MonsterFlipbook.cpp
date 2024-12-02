#include "pch.h"
#include "MonsterFlipbook.h"
#include "CFlipbook.h"
#include "CTexture.h"
#include "CAssetMgr.h"

MonsterFlipbook::MonsterFlipbook()
{
}

MonsterFlipbook::~MonsterFlipbook()
{
}

void MonsterFlipbook::CreateFlipbook()

{
	CTexture* mTexture;
	{
		//Crawlid
 		mTexture = CAssetMgr::GetInst()->LoadTexture(L"Crawlid", L"Texture\\Enime\\Crawlid\\Crawlid.png");
		mFlipBook->CreateFlipbook(L"Crawlid_Walk", mTexture, Vec2(3, 22), Vec2(116, 85), 3, 4);
		mFlipBook->CreateFlipbook(L"Crawlid_turn", mTexture, Vec2(3, 129), Vec2(96, 83), 3, 2);
		mFlipBook->CreateFlipbook(L"Crawlid_death", mTexture, Vec2(3, 234), Vec2(117, 120), 3, 3);

		//R
		mTexture = CAssetMgr::GetInst()->LoadTexture(L"Crawlid", L"Texture\\Enime\\Crawlid\\R_Crawlid.png");
		mFlipBook->CreateFlipbook(L"R_Crawlid_Walk", mTexture, Vec2(360, 22), Vec2(116, 85), 3, 4);
		mFlipBook->CreateFlipbook(L"R_Crawlid_turn", mTexture, Vec2(380, 129), Vec2(96, 83), 3, 2);
		mFlipBook->CreateFlipbook(L"R_Crawlid_death", mTexture, Vec2(359, 234), Vec2(117, 120), 3, 3);

	}

}
