#pragma once

#include "Utilities/UI.h"

#include "Game/UI/Progressbar.h"
#include "GeoMatries/AnimationRect.h"
#include "Utilities/Animator.h"

class MainProfile : public UI
{
public:
	MainProfile();
	virtual ~MainProfile() override;

	virtual void Update() override;
	virtual void Render() override;

private:

	TextureRect* tr = nullptr;
	TextureRect* arrow = nullptr;

	AnimationRect* ar = nullptr;
	Animator* animator = nullptr;

	ProgressBar* fhp = nullptr;
	ProgressBar* bhp = nullptr;
	
	
	ProgressBar* fstamina = nullptr;
	ProgressBar* bstamina = nullptr;

	float deltaTime = 0;

	float HpDelay = 0;
	float StaminaDelay = 0;
};