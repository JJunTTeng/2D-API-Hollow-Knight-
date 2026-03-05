#pragma once

struct Vec2
{
public:
	float x;
	float y;

public:
	// 벡터의 길이
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	// 정규화
	void Normalize()
	{
		float Len = Length();
		x /= Len;
		y /= Len;
	}

	// 내적
	float Dot(Vec2 _Other)
	{
		return x * _Other.x + y * _Other.y;
	}



	Vec2 operator + (Vec2 _Other) { return Vec2(x + _Other.x, y + _Other.y); }
	Vec2 operator + (float _f) { return Vec2(x + _f, y + _f); }
	void operator += (Vec2 _Other) { x += _Other.x; y += _Other.y; }
	void operator += (float _f) { x += _f; y += _f; }

	Vec2 operator - (Vec2 _Other) { return Vec2(x - _Other.x, y - _Other.y); }
	Vec2 operator - (float _f) { return Vec2(x - _f, y - _f); }
	void operator -= (Vec2 _Other) { x -= _Other.x; y -= _Other.y; }
	void operator -= (float _f) { x -= _f; y -= _f; }

	Vec2 operator * (Vec2 _Other) { return Vec2(x * _Other.x, y * _Other.y); }
	Vec2 operator * (float _f) { return Vec2(x * _f, y * _f); }
	void operator *= (Vec2 _Other) { x *= _Other.x; y *= _Other.y; }
	void operator *= (float _f) { x *= _f; y *= _f; }

	Vec2 operator / (Vec2 _Other) { assert(_Other.x && _Other.y); return Vec2(x / _Other.x, y / _Other.y); }
	Vec2 operator / (float _f) {  assert(_f); return Vec2(x / _f, y / _f); } 
	void operator /= (Vec2 _Other) { assert(_Other.x && _Other.y); x /= _Other.x; y /= _Other.y; }
	void operator /= (float _f) { assert(_f); x /= _f; y /= _f; }

	bool operator == (Vec2 _Other) { if (x == _Other.x && y == _Other.y) return true; return false; }
	bool operator >= (Vec2 _Other) { if (x >= _Other.x && y >= _Other.y) return true; return false; }
	bool operator <= (Vec2 _Other) { if (x <= _Other.x && y <= _Other.y) return true; return false; }
	bool operator != (Vec2 _Other) { if (x != _Other.x && y != _Other.y) return false; return true; }


public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}


	~Vec2()
	{}


};

struct tTask
{
	TASK_TYPE	Type;
	DWORD_PTR	Param0;
	DWORD_PTR	Param1;
};


struct tDbgRenderInfo
{
	DEBUG_SHAPE		Type;
	Vec2			Position0;
	Vec2			Position1;
	Vec2			Scale;
	Vec2			OffSet;
	PEN_TYPE		Color;
	float			Duration;	// 표시 시간
	float			Time;		// 진행 시간
}; 


struct tTile
{
	int ImgIdx;
};


struct tMonInfo
{
	float MaxHP;
	float CurHP;

	float MaxMP;
	float CurMP;

	float Att;
	float Def;
	float Dex;

	float AttRange;
	float DetectRange;

	float Speed;
};