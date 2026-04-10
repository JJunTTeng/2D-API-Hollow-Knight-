#pragma once

class CEffectManager
{
	SINGLE(CEffectManager)

private:

public:
	void SpawnTileHit(Vec2 _pos, float dir);
	float RandomRange(float min, float max);
};
