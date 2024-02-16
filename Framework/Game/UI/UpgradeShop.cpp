#include "Framework.h"
#include "UpgradeShop.h"

UpgradeShop::UpgradeShop()
{
	float width = -WinMaxWidth / 2 + 30;
	float height = WinMaxHeight / 2 - 30;

	// 152 112
	tr = new TextureRect({ 0, 0, 0.f }, { 760,560,1 }, 0.f, TexturePath + L"UI/UpgradeShopUI.png", MIDLE_CENTER);

	db = new DaggerButton();
	eb = new AxeButton();
	bb = new BowButton();


}
UpgradeShop::~UpgradeShop()
{

	SAFE_DELETE(bb);
	SAFE_DELETE(eb);
	SAFE_DELETE(db);
	SAFE_DELETE(tr);
}

void UpgradeShop::Update()
{
	deltaTime = Time::Get()->WorldDelta();

	tr->UpdateUI();
	db->Update();
	eb->Update();
	bb->Update();

	if (db->IsPress())
	{
		eb->Init();
		bb->Init();
	}
	else if (eb->IsPress())
	{
		db->Init();
		bb->Init();
	}
	else if (bb->IsPress())
	{
		db->Init();
		eb->Init();
	}
}

void UpgradeShop::Render()
{
	tr->Render();
	db->Render();
	eb->Render();
	bb->Render();



}

void UpgradeShop::Init()
{
	db->Init();
	eb->Init();
	bb->Init();

}
