#include "stdafx.h"
#include "08_PlayerDemo.h"



void PlayerDemo::Init()
{
	// wall collision
	{
		leftwall = new BoundingBox(BoundingBox::Floor, NonePass);
		leftwall->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_LEFT);
		leftwall->SetActive(true);

		rightwall = new BoundingBox(BoundingBox::Floor, NonePass);
		rightwall->Init(Color(1, 0, 0, 0.3f), BoundingBox::DOWN_LEFT);
		rightwall->SetActive(true);

		leftwall->Update({ 0, 0, 0 }, { 40 , 1440, 1 }, 0.0f);
		rightwall->Update({ 2520, 0, 0 }, { 40 , 1440, 1 }, 0.0f);

	}

	// Sound
	{
		// Map
		Sounds::Get()->AddSound("witch", SoundPath + L"witch.mp3", true);
		Sounds::Get()->AddSound("gosthouse", SoundPath + L"gosthouse.mp3", true);
		Sounds::Get()->AddSound("raintown", SoundPath + L"raintown.mp3", true);


		// Player
		{
			Sounds::Get()->AddSound("e2", SoundPath + L"/effect/" + L"e2.mp3");
			Sounds::Get()->AddSound("e3", SoundPath + L"/effect/" + L"e3.wav");

			Sounds::Get()->AddSound("s3", SoundPath + L"/effect/" + L"s3.mp3");

			Sounds::Get()->AddSound("arrow", SoundPath + L"/effect/" + L"arrow.mp3");

			// damaged
			Sounds::Get()->AddSound("d1", SoundPath + L"/effect/" + L"playerD1.mp3");
			Sounds::Get()->AddSound("d3", SoundPath + L"/effect/" + L"playerD3.mp3");
		}
		


		// Monster
		Sounds::Get()->AddSound("m_damaged", SoundPath + L"/effect/" + L"MudGuardDamaged.wav");

		// Object
		Sounds::Get()->AddSound("warp", SoundPath + L"/effect/" + L"warp.wav");
		Sounds::Get()->AddSound("shop_enter", SoundPath + L"/effect/" + L"shop_enter.mp3");
		Sounds::Get()->AddSound("buyitem", SoundPath + L"/effect/" + L"buyitem.mp3");
		Sounds::Get()->AddSound("hunterScript", SoundPath + L"/effect/" + L"hunterScript.mp3");
		Sounds::Get()->AddSound("UpgradeSound", SoundPath + L"/effect/" + L"UpgradeSound.mp3");
		Sounds::Get()->AddSound("ButtonSound", SoundPath + L"/effect/" + L"ButtonSound.mp3");
		Sounds::Get()->AddSound("paper2", SoundPath + L"/effect/" + L"paper2.wav");
		Sounds::Get()->AddSound("Coin", SoundPath + L"/effect/" + L"Coin.mp3");


	}
	


	Map_Push(new Forest1);
	Map_Push(new Forest2);
	Map_Push(new Town1);


	player = new Player(maps[map_num]->GetFirstPoint(), { 150,100,1 }, 0.f);
	//s1 = new ShadowStalker({ 1900, 80, 0 }, 0.f);

	hud = new HUD();



	SetMap(0);
}

void PlayerDemo::Destroy()
{

	SAFE_DELETE(hud);

	//SAFE_DELETE(s1);

	for (auto m : maps)
		m->Destroy();

	SAFE_DELETE(player);

	SAFE_DELETE(rightwall);
	SAFE_DELETE(leftwall);
}

void PlayerDemo::Update()
{
	Camera::Get()->SetCameraSize({ WinMaxWidth / CameraSize ,WinMaxHeight / CameraSize });

	maps[map_num]->Update();

	ChangeMap();

	if (Keyboard::Get()->Down('K'))
		SetMap(map_num - 1);
	
	if (Keyboard::Get()->Down('L'))
		SetMap(map_num + 1);


	player->Update();
	//s1->Update();

	hud->Update();

	Camera::Get()->Move(maps[map_num]->GetMapSize(), player->GetPos());

	if (Keyboard::Get()->Down('Z'))
		player->SetPos(maps[map_num]->GetFirstPoint());
}

void PlayerDemo::Render()
{
	maps[map_num]->Render();

	player->Render();
	//s1->Render();

}

void PlayerDemo::PostRender()
{
	hud->Render();

	maps[map_num]->PostRender();

	/*Text::Get()->BeginDraw();
	{
		wstring str = L"TEXT ÅØ½ºÆ® ¡Ù¡×";
		float size = (float)Text::Get()->GetStringWidth(str, 20.f);
		Vector2 pos = Vector2(0, 0);
		Text::Get()->RenderText(str, pos, Color(1, 0, 1, 1), size, false);
	}
	Text::Get()->EndDraw();*/

}

void PlayerDemo::GUI()
{
	//player->GUI();
	/*ImGui::Begin("CameraSize");
	{
		ImGui::SliderFloat("size", &CameraSize, 0.1f, 3.f);
	}
	ImGui::End();*/
}

void PlayerDemo::Map_Push(MapManager* m)
{
	maps.push_back(m);
	m->Init();
}

void PlayerDemo::SetMap(int num)
{
	maps[map_num]->Init();

	maps[num]->MapOn();
	map_num = num;

	player->SetPos(maps[map_num]->GetFirstPoint());

	if (maps[map_num]->IsTown())
		lastTown = map_num;
}

void PlayerDemo::ChangeMap()
{
	if (!maps[map_num]->NextMap())
		return;
	
	SetMap(map_num + 1);

}
