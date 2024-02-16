#include "stdafx.h"
#include "09_TileMapDemo.h"

#include "Geomatries/Tile/TileMap.h"

void TileMapDemo::Init()
{

	uint spacing = 40;
	uint width = (MapWidth) / spacing;
	uint height = (MapHeight) / spacing;

	tm = new TileMap(width, height, spacing);
}

void TileMapDemo::Destroy()
{
	SAFE_DELETE(tm);
}

void TileMapDemo::Update()
{
	Camera::Get()->SetCameraSize({ MapWidth ,MapHeight });
	Camera::Get()->SetPosition({ MapWidth/2,MapHeight/2,0 });

	tm->Update();
}

void TileMapDemo::Render()
{
	tm->Render();
}

void TileMapDemo::PostRender()
{

}

void TileMapDemo::GUI()
{
	tm->GUI();
}
