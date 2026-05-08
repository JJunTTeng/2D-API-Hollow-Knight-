#pragma once
class CLevel;
class CLevelLoader
{
public:
	static void LoadColider(CLevel* mlevel, wchar_t* Path);
	static void EnimeLoad(CLevel* mlevel, wchar_t* Path);
	static void CameraBoundLoad(CLevel* mlevel, wchar_t* Path);
	static void TileLoad(CLevel* mlevel, wchar_t* Path);
};

