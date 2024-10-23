#pragma once


enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class BRUSH_TYPE
{
	RED,
	GREEN,
	BLUE,
	GRAY,
	HOLLOW,
	END,
};

enum class LEVEL_TYPE
{
	START,
	STAGE_0,
	STAGE_1,
	STAGE_2,
	EDITOR,

	END,
};


enum class TASK_TYPE
{
	// Param0 : Object Address, Param1 : Layer Index
	CREATE_OBJECT,

	// Param0 : Object Address
	DELETE_OBJECT,

	// Param0 : Next Level
	CHANGE_LEVEL,
};

enum class LAYER_TYPE
{
	BACKGROUND,
	TILE,
	DEFAULT,
	PLAYER,
	PLAYER_OBJECT,
	MONSTER,
	MONSTER_OBJECT,

	// 7 ~ 30

	UI = 31,
	END = 32
};


enum class COMPONENT_TYPE
{
	COLLIDER,
	RIGIDBODY,
	FLIPBOOKPLAYER,
	FSM,
	TILEMAP,
};

enum class ASSET_TYPE
{
	TEXTURE,	// 이미지
	SOUND,		// 소리	
	SPRITE,		// 특정 텍스쳐의 특정 부위
	FLIPBOOK,	// Sprite 의 집합체
};


enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,
};