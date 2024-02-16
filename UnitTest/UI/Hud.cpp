#include "stdafx.h"
#include "Hud.h"

#include "Game/UI/Progressbar.h"
#include "Game/UI/MainProfile.h"
#include "Game/UI/UpgradeShop.h"

HUD::HUD()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	/*
	HPBar = new ProgressBar({ width, height, 0.0f }, { 200 , 30, 1 }, 0.0f, Color(1, 0, 0, 1), UI::LEFT_TO_RIGHT);
	*/

	profile = new MainProfile();
	ushop = new UpgradeShop();
}

HUD::~HUD()
{
	SAFE_DELETE(profile);
	SAFE_DELETE(ushop);
	//SAFE_DELETE(HPBar);
}

void HUD::Update()
{
	
	/*if (Keyboard::Get()->Down(VK_F3))
	{
		percent -= 0.1f;
		HPBar->UpdateProgressBar(percent);
	}
	if (Keyboard::Get()->Down(VK_F4))
	{
		percent += 0.1f;
		HPBar->UpdateProgressBar(percent);
	}
	HPBar->Update();*/
	
	profile->Update();
	ushop->Update();
}

void HUD::Render()
{
	profile->Render();
	//ushop->Render();
	//HPBar->Render();
}
