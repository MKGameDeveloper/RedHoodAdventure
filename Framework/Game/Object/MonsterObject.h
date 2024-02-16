#pragma once

#include "Utilities/GameObject.h"
#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"

class BringerSpell : public GameObject
{
public:

public:
	BringerSpell(Vector3 position, float rotation, float damage, float dir);
	~BringerSpell();

	void Init(Vector3 position, float rotation, float damage, float dir);

	void Update();
	void Render();

	void OnIsActive();

	void SetIsActive(Active isActive)
	{
		_activeState[0] = _activeState[1];
		_activeState[1] = isActive;
	}

	bool GetIsActive() { return _activeState[1] == ON; }

private:
	Active _activeState[2] = { OFF, ON };

	AnimationRect* spell = nullptr;
	Animator* animator = nullptr;

	BoundingBox* collision = nullptr;
};



class ShadowMageSpell : public GameObject
{
public:

public:
	ShadowMageSpell(Vector3 position, float rotation, float damage, float dir);
	~ShadowMageSpell();

	void Init(Vector3 position, float rotation, float damage, float dir);

	void Update();
	void Render();

	void OnIsActive();

	void SetIsActive(Active isActive)
	{
		_activeState[0] = _activeState[1];
		_activeState[1] = isActive;
	}

	bool GetIsActive() { return _activeState[1] == ON; }

private:
	Active _activeState[2] = { OFF, ON };

	AnimationRect* spell = nullptr;
	Animator* animator = nullptr;

	BoundingBox* collision = nullptr;

	float dir;
};

class Soul : public GameObject
{
public:
	enum STATE
	{
		NORMAL,
		REVERSE,
		GET,
	};

public:
	Soul(Vector3 position, float point);
	~Soul();

	void Init(Vector3 position, float point);

	void Update();
	void Render();

	void OnIsActive(Vector3 position);

	void SetIsActive(Active isActive)
	{
		_activeState[0] = _activeState[1];
		_activeState[1] = isActive;
	}

	bool GetIsActive() { return _activeState[1] == ON; }

private:
	Active _activeState[2] = { OFF, ON };

	AnimationRect* soul = nullptr;
	Animator* animator = nullptr;

	BoundingBox* collision = nullptr;

	STATE _State = NORMAL;

	float point = 0.f;
	float Speed = 0.f;
};