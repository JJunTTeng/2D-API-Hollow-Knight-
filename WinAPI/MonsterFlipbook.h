#pragma once

class CFlipbook;
class MonsterFlipbook
{
	SINGLE(MonsterFlipbook);
public:

	void CreateFlipbook();
private:
	CFlipbook* mFlipBook;
};

