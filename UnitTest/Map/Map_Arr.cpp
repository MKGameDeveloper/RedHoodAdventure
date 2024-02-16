#include "stdafx.h"
#include "Map_Arr.h"


Forest1::Forest1()
	:MapManager()
{
	MapSize = { WinMaxWidth * 2 , WinMaxHeight * 2 };

	map.push_back(new TextureRect({ WinMaxWidth,WinMaxHeight,0 }, { 1280  ,720, 1 }, 0, TexturePath + L"ForestNight1.png", DOWN_LEFT));
	map.push_back(new TextureRect({ WinMaxWidth,WinMaxHeight,0 }, { 1400  ,720, 1 }, 0, TexturePath + L"ForestNight2.png", DOWN_LEFT));
	map.push_back(new TextureRect({ WinMaxWidth,WinMaxHeight,0 }, { 1680  ,720 , 1 }, 0, TexturePath + L"ForestNight3.png", DOWN_LEFT));

	LoadMap(TilePath + "Forest1.txt");

	MusicName = "witch";

	Init();
}

void Forest1::Destroy()
{
	for (auto m : map)
	{
		SAFE_DELETE(m);
	}

	__super::Destroy();
}

void Forest1::Update()
{
	if (!_activeState[1])
		return;
	OnIsActive();

	__super::Update();
	BackGroundSight();
}

void Forest1::Render()
{
	if (!_activeState[1])
		return;

	for (auto m : map)
	{
		m->Render();
	}

	__super::Render();
}





Forest2::Forest2()
	:MapManager()
{
	MapSize = { WinMaxWidth * 2 , WinMaxHeight * 2 };

	map.push_back(new TextureRect({ WinMaxWidth,WinMaxHeight,0 }, { 1280  ,720, 1 }, 0, TexturePath + L"ForestNight1.png", DOWN_LEFT));
	map.push_back(new TextureRect({ WinMaxWidth,WinMaxHeight,0 }, { 1400  ,720, 1 }, 0, TexturePath + L"ForestNight2.png", DOWN_LEFT));
	map.push_back(new TextureRect({ WinMaxWidth,WinMaxHeight,0 }, { 1680  ,720 , 1 }, 0, TexturePath + L"ForestNight3.png", DOWN_LEFT));

	LoadMap(TilePath + "Forest2.txt");

	MusicName = "gosthouse";

	Init();
}

void Forest2::Destroy()
{
	for (auto m : map)
	{
		SAFE_DELETE(m);
	}

	__super::Destroy();
}

void Forest2::Update()
{
	if (!_activeState[1])
		return;
	OnIsActive();

	__super::Update();

}

void Forest2::Render()
{
	if (!_activeState[1])
		return;

	for (auto m : map)
	{
		m->Render();
	}

	__super::Render();
}


Town1::Town1()
	:MapManager()
{
	MapSize = { WinMaxWidth * 2 , WinMaxHeight * 2 };

	map.push_back(new TextureRect({ WinMaxWidth,WinMaxHeight,0 }, { 1280  ,720, 1 }, 0, TexturePath + L"ForestDay1.png", DOWN_LEFT));
	map.push_back(new TextureRect({ WinMaxWidth,WinMaxHeight,0 }, { 1400  ,720, 1 }, 0, TexturePath + L"ForestDay2.png", DOWN_LEFT));
	map.push_back(new TextureRect({ WinMaxWidth,WinMaxHeight,0 }, { 1680  ,720 , 1 }, 0, TexturePath + L"ForestDay3.png", DOWN_LEFT));

	istown = true; 
	LoadMap(TilePath + "Town1.txt");

	MusicName = "raintown";

	Init();
}

void Town1::Destroy()
{
	for (auto m : map)
	{
		SAFE_DELETE(m);
	}

	__super::Destroy();
}

void Town1::Update()
{
	if (!_activeState[1])
		return;
	OnIsActive();

	__super::Update();

}

void Town1::Render()
{
	if (!_activeState[1])
		return;

	for (auto m : map)
	{
		m->Render();
	}

	__super::Render();
}




