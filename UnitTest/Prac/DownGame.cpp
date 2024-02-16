#include "stdafx.h"
#include "Prac/DownGame.h"

#include "Game/Map/Floor.h"
#include "Geomatries/TextureRect.h"
#include "Geomatries/ShadedTexture.h"

#include "Utilities/RenderTexture.h"


void DownGame::Init()
{
	view = new RenderTexture();
	minimap = new RenderTexture();

	//character = new Player1({ 533, 512, 0 }, { 20,20,1 }, .0f);
	//rs.push_back(new Floor({ WinMaxWidth - (WinMaxWidth / 2),10,0 }, {1280,100,0}, .0f,2));

	rs.push_back(new Floor({ 533, 500, 0 }, { 200,30,1 }, .0f, 1));
	rs.push_back(new Floor({ 100, 700, 0 }, { 200,30,1 }, .0f, 2));
	rs.push_back(new Floor({ 550, 900, 0 }, { 200,30,1 }, .0f, 3));
	rs.push_back(new Floor({ 200, 1100, 0 }, { 200,30,1 }, .0f, 4));
	rs.push_back(new Floor({ 500, 1300, 0 }, { 200,30,1 }, .0f, 1));

	Vector3 trPos = Vector3(WinMaxWidth - (WinMaxWidth / 8)-15, WinMaxHeight - (WinMaxHeight / 8)-10, 0);
	Vector3 trSiz = Vector3(WinMaxWidth / 4, WinMaxHeight / 4, 0);
	float rot = 0;

	stm = new ShadedTexture(trPos, trSiz, rot);
	stm->SetShader(ShaderPath + L"MiniMap.hlsl");

	stv = new ShadedTexture({ WinMaxWidth - (WinMaxWidth / 2),WinMaxHeight - (WinMaxHeight / 2),0 }, { WinMaxWidth,WinMaxHeight,0 }, 0);
	stv->SetShader(ShaderPath + L"Origin.hlsl");

	GAMEOVER = new ShadedTexture({ WinMaxWidth - (WinMaxWidth / 2),WinMaxHeight - (WinMaxHeight / 2),0 }, { WinMaxWidth,WinMaxHeight,1 }, 0, TexturePath + L"go1.jpg");
	GAMEOVER->SetShader(ShaderPath + L"Origin.hlsl");
	*(GAMEOVER->GetSB()->GetBlurCountPtr()) = 100;

	sky = new TextureRect({ WinMaxWidth - (WinMaxWidth / 2),WinMaxHeight - (WinMaxHeight / 2),0 }, { WinMaxWidth,WinMaxHeight + 200,1 }, 0, TexturePath + L"sky.jpg");
	sky->SetShader(ShaderPath + L"Origin.hlsl");
}

void DownGame::Destroy()
{
	SAFE_DELETE(sky);
	SAFE_DELETE(GAMEOVER);
	SAFE_DELETE(stv);
	SAFE_DELETE(stm);

	for (Floor* a : rs)
		SAFE_DELETE(a);

	SAFE_DELETE(character);

	SAFE_DELETE(minimap);
	SAFE_DELETE(view);
}

void DownGame::Update()
{

	//character->Update();
	//character->SetDownSpeed(downSpeed);

	if (Keyboard::Get()->Press('T'))
		downSpeed = 0.0f;

	if (Keyboard::Get()->Press('Y'))
		downSpeed = 0.7f;


	if ((score / Gap) > 1)
	{
		score -= 2 * Gap;
		ChangeTheme();
	}

	//if (character->IsAlive() == false)
	//{
	//	Start = false;
	//}

	

	if (Start)
	{
		for (Floor* a : rs)
		{
			a->Update();


			if (a->CheckOutSide())
			{
				score += 100;
				float x = 0;
				x = rs.back()->GetPositionX() + (rand() % 1000 - 500);
				if ((x- (a->GetSize().x / 2) < 0))
					x += 500.f;
				if ((x + (a->GetSize().x / 2)) > WinMaxWidth)
					x -= 500.f;

				int ai, bi;
				ai = rand() % 123;
				bi = rand() % 456;

				float rot = (ai * bi) % 90 - 45.f;

				int num = (rand() % 12345 * 23) % difficult + 1;

				a->SetPosition(num, x, rs.back()->GetPositionY() + 200.f, rot);
				rotate(rs.begin(), rs.begin() + 1, rs.end());
			}

		}
	}
	else
	{
		// 게임오버시 게임오버 화면을 천천히 블러 해제하는 효과
		i++;
		if (i % 2 == 0)
		{
			if (*(GAMEOVER->GetSB()->GetBlurCountPtr()) > 1)
				*(GAMEOVER->GetSB()->GetBlurCountPtr()) -= 1;
		}
	}
	

	for (Floor* a : rs)
	{
		/*if (BoundingBox::AABB(character->GetCollision(), a->GetCollision()) == true || 
			BoundingBox::OBB(character->GetCollision(), a->GetCollision()) == true )
		{
			character->SetTarget(a);
  			break;
		}*/
	}

	GAMEOVER->Update();
	sky->Update();
	stv->Update();
	stm->Update();
		
}

void DownGame::Render()
{
	if (Start)
	{
		stv->SetSRV(view->GetSRV());
		stv->Render();
		if (isminimap)
		{
			stm->SetSRV(minimap->GetSRV());
			stm->Render();
		}
	}

	if (!Start)
		GAMEOVER->Render();
}

void DownGame::PostRender()
{
	Graphics::Get()->InitViewport();
	view->RenderToTexture();
	{
		sky->Render();
		if (IsRender())
		{
			for (Floor* a : rs)
				a->Render();
		}

		//character->Render();
	}

	
	minimap->RenderToTexture();
	{
		for (Floor* a : rs)
			a->Render();

		//character->Render();
	}
	
}

void DownGame::GUI()
{
}

void DownGame::SetRender()
{
	switch (isrender)
	{
	case true:
		isrender = false;
		break;
	case false:
		isrender = true;
		break;
	}
	
}

void DownGame::ChangeTheme()
{
	*(stv->GetSB()->GetSelectionPtr()) = 1;
	*(stv->GetSB()->GetBlurCountPtr()) = 1;
	stv->RotateZero();
	isminimap = false;
	int a = rand() % 7 + 1;

	switch (a)
	{
	case 1:
		stv->Rotate180();
		isminimap = true;
		break;
	case 2:
		*(stv->GetSB()->GetSelectionPtr()) = 2;
		break;
	case 3:
		*(stv->GetSB()->GetSelectionPtr()) = 3;
		break;
	case 4:
		*(stv->GetSB()->GetSelectionPtr()) = 4;
		break;
	case 5:
		*(stv->GetSB()->GetSelectionPtr()) = 5;
		*(stv->GetSB()->GetBlurCountPtr()) = 30;
		isminimap = true;
		break;
	case 6:
		*(stv->GetSB()->GetBlurCountPtr()) = 30;
		isminimap = true;
		break;
	case 7:
		*(stv->GetSB()->GetSelectionPtr()) = 1;
		break;
	}

}
