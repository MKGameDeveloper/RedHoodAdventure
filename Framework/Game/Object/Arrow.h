#pragma once

#include "Utilities/GameObject.h"
#include "Geomatries/TextureRect.h"

class Arrow : public GameObject
{
public:

public:
	Arrow(Vector3 position, Vector3 size, float rotation, float dir);
	~Arrow();

	void Init(Vector3 position, Vector3 size, float rotation, float dir);

	void Update();
	void Render();

	void OnIsActive();

	void SetIsActive(Active isActive);

	bool GetIsActive() { return _activeState[1] == ON; }

	bool IsCollison() {  }

private:
	Active _activeState[2] = { OFF, ON };

	TextureRect* arrow = nullptr;

	float dir = 1.f;

	float vx = 0.0f;
	float accel = -0.5f;
	float accelSpeed = 30.f;

	Vector3 grav;
	float dr;
	Vector3 v1;

	float delta;
	float deltaTime = 0.0f;

	bool CheckDisapear = false;
	float CheckTime = 0.f;

	BoundingBox* collision = nullptr;
	bool iscol;
};