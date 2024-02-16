#pragma once

#include "Utilities/Animator.h"
#include "TextureRect.h"

class AnimationRect : public TextureRect
{
public:
	AnimationRect(Vector3 position, Vector3 size, float rotation, Pivot p = MIDLE_CENTER);
	~AnimationRect();

	void Update(Vector3 position, Vector3 size, float rotation, Pivot p = DOWN_CENTER);
	virtual void UpdateUI() override;

	void Render();

	void SetAnimator(Animator* animator) { this->animator = animator; }


protected:

	Animator* animator = nullptr;

	ID3D11SamplerState* point[2];
	ID3D11BlendState* bPoint[2];


};