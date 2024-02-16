#pragma once

#include "FootHolder.h"
#include "Geomatries/AnimationRect.h"

#include "Game/UI/UpgradeShop.h"




class CrystalMoveFloor : public FootHolder
{
public:
	CrystalMoveFloor(Vector3 position, float dir);
	~CrystalMoveFloor();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

	void Trigger();

private:
	float dir;

private:
	AnimationRect* ar = nullptr;
	MoveFloor* mf = nullptr;

	class Animator* animator = nullptr;
};

class CrystalUpDownFloor : public FootHolder
{
public:
	CrystalUpDownFloor(Vector3 position, float dir);
	~CrystalUpDownFloor();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

	void Trigger();

private:
	float dir;

private:
	AnimationRect* ar = nullptr;
	UpDownFloor* udf = nullptr;

	class Animator* animator = nullptr;
};

class Portal : public FootHolder
{
public:
	enum State {
		ON_PORTAL,
		CONTINUE,
	};

public:
	Portal(Vector3 position, float dir);
	~Portal();

	void StateControll();

	virtual void Update() override;
	virtual void Render() override;

	void SetOn() { isOn = true; }

	virtual void Init() override;
	virtual void OnActive() override;

	bool IsNext() { return isnext; }

private:
	float dir;

	bool isOn = false;
	bool isDetect = false;
	bool isnext = false;

	State _state = ON_PORTAL;

private:
	AnimationRect* ar = nullptr;
	TextureRect* tr = nullptr;

	class Animator* animator = nullptr;
};

class BigTree1 : public FootHolder
{

public:
	BigTree1(Vector3 position);
	~BigTree1();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

private:
	TextureRect* tr = nullptr;
};

class BigTree2 : public FootHolder
{

public:
	BigTree2(Vector3 position);
	~BigTree2();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

private:
	TextureRect* tr = nullptr;
};

class BigTree3 : public FootHolder
{

public:
	BigTree3(Vector3 position);
	~BigTree3();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

private:
	TextureRect* tr = nullptr;
};

class SmallTree1 : public FootHolder
{

public:
	SmallTree1(Vector3 position);
	~SmallTree1();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

private:
	TextureRect* tr = nullptr;
};

class SmallTree2 : public FootHolder
{

public:
	SmallTree2(Vector3 position);
	~SmallTree2();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

private:
	TextureRect* tr = nullptr;
};

class SmallTree3 : public FootHolder
{

public:
	SmallTree3(Vector3 position);
	~SmallTree3();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

private:
	TextureRect* tr = nullptr;
};

class Root1 : public FootHolder
{

public:
	Root1(Vector3 position);
	~Root1();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

private:
	TextureRect* tr = nullptr;
};

class Root2 : public FootHolder
{

public:
	Root2(Vector3 position);
	~Root2();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

private:
	TextureRect* tr = nullptr;
};

class Root3 : public FootHolder
{

public:
	Root3(Vector3 position);
	~Root3();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

private:
	TextureRect* tr = nullptr;
};

class Shop : public FootHolder
{

public:
	Shop(Vector3 position);
	~Shop();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

	bool isDetect = false;
	bool isOn = false;

private:
	AnimationRect* ar = nullptr;
	Animator* animator = nullptr;

	TextureRect* tr = nullptr;

};


class UpgradeNPC : public FootHolder
{

public:
	UpgradeNPC(Vector3 position);
	~UpgradeNPC();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void Init() override;
	virtual void OnActive() override;

private:
	float dir;

	bool isDetect = false;
	bool isOn = false;

private:
	AnimationRect* ar = nullptr;
	Animator* animator = nullptr;

	TextureRect* tr = nullptr;

	UpgradeShop* us = nullptr;

};