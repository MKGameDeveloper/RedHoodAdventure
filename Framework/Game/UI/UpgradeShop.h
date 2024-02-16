#pragma once

#include "Utilities/UI.h"

#include "Game/UI/Button.h"
#include "GeoMatries/AnimationRect.h"
#include "Utilities/Animator.h"

class UpgradeShop : public UI
{
public:
	UpgradeShop();
	virtual ~UpgradeShop() override;

	virtual void Update() override;
	virtual void Render() override;
	void Init();

private:

	TextureRect* tr = nullptr;

	DaggerButton* db = nullptr;
	AxeButton* eb = nullptr;
	BowButton* bb = nullptr;

	float deltaTime = 0;

	float HpDelay = 0;
	float StaminaDelay = 0;
};