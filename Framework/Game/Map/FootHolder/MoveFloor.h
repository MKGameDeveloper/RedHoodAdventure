#pragma once

#include "FootHolder.h"
#include "Utilities/RigidBody.h"
#include "Geomatries/TextureRect.h"

class MoveFloor : public FootHolder
{
public:
	MoveFloor(Vector3 position, float dir, bool TriggerMode = false);
	~MoveFloor();

	void SetTrigger(bool trigger) { IsMove = trigger; }

	int GetMoveStack() { return MoveStack; }
	void SetMoveStack(int stack) { this->MoveStack = stack; }

	void Move();

	virtual void Update() override;
	virtual void Render() override;

private:
	TextureRect* tr = nullptr;

	RigidBody* rigidbody = nullptr;

	float FSpeed;

	bool TriggerMode;


};

class UpDownFloor : public FootHolder
{
public:
	UpDownFloor(Vector3 position, bool TriggerMode = false);
	~UpDownFloor();

	void SetTrigger(bool trigger) { IsMove = trigger; }

	int GetMoveStack() { return MoveStack; }
	void SetMoveStack(int stack) { this->MoveStack = stack; }

	void SetFirst() { isFirst = true; }

	void Move();

	virtual void Update() override;
	virtual void Render() override;

private:
	TextureRect* tr = nullptr;

	RigidBody* rigidbody = nullptr;

	float FSpeed;

	bool TriggerMode;

	bool isFirst = true;


};
