#pragma once

#include "Utilities/UI.h"

#include "GeoMatries/AnimationRect.h"
#include "Utilities/Animator.h"

class Button : public UI
{
public:
	Button();

	virtual void Init();
	virtual void OnActive();

	virtual void IsClick();

	bool IsPress();
	void SetNonPress();

	bool IsDetected();

protected:

	TextureRect* NonPress = nullptr;
	TextureRect* Press = nullptr;

	bool prepress = false;
	bool ispress = false;
	bool isOn = false;

	bool predetected = false;
	bool isdetected = false;

	Vector3 mPos;
	Vector3 position;
	Vector3 size;
};


class DaggerComboUpgrade : public Button
{
public:
	DaggerComboUpgrade();
	virtual ~DaggerComboUpgrade() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:

};


class DaggerComboButton : public Button
{
public:
	DaggerComboButton();
	virtual ~DaggerComboButton() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:
	TextureRect* dcb = nullptr;
	TextureRect* textBoard = nullptr;

	TextureRect* text = nullptr;
	TextureRect* mut = nullptr;

	DaggerComboUpgrade* dcu = nullptr;

};


class DaggerDamageUpgrade : public Button
{
public:
	DaggerDamageUpgrade();
	virtual ~DaggerDamageUpgrade() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:

};


class DaggerDamageButton : public Button
{
public:
	DaggerDamageButton();
	virtual ~DaggerDamageButton() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:
	TextureRect* ddb = nullptr;
	TextureRect* textBoard = nullptr;

	TextureRect* text = nullptr;
	TextureRect* mut = nullptr;

	DaggerDamageUpgrade* ddu = nullptr;

};


class DaggerButton : public Button
{
public:
	DaggerButton();
	virtual ~DaggerButton() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:
	DaggerComboButton* dcb = nullptr;
	DaggerDamageButton* ddb = nullptr;

};

class AxeComboUpgrade : public Button
{
public:
	AxeComboUpgrade();
	virtual ~AxeComboUpgrade() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:

};


class AxeComboButton : public Button
{
public:
	AxeComboButton();
	virtual ~AxeComboButton() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:
	TextureRect* acb = nullptr;
	TextureRect* textBoard = nullptr;

	TextureRect* text = nullptr;
	TextureRect* mut = nullptr;

	AxeComboUpgrade* acu = nullptr;

};


class AxeDamageUpgrade : public Button
{
public:
	AxeDamageUpgrade();
	virtual ~AxeDamageUpgrade() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:

};


class AxeDamageButton : public Button
{
public:
	AxeDamageButton();
	virtual ~AxeDamageButton() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:
	TextureRect* adb = nullptr;
	TextureRect* textBoard = nullptr;

	TextureRect* text = nullptr;
	TextureRect* mut = nullptr;

	AxeDamageUpgrade* adu = nullptr;

};


class AxeUnlockUpgrade : public Button
{
public:
	AxeUnlockUpgrade();
	virtual ~AxeUnlockUpgrade() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:

};


class AxeUnlockButton : public Button
{
public:
	AxeUnlockButton();
	virtual ~AxeUnlockButton() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:
	TextureRect* aub = nullptr;
	TextureRect* textBoard = nullptr;

	TextureRect* text = nullptr;
	TextureRect* mut = nullptr;

	AxeUnlockUpgrade* auu = nullptr;

};

class AxeButton : public Button
{
public:
	AxeButton();
	virtual ~AxeButton() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:
	AxeComboButton* acb = nullptr;
	AxeDamageButton* adb = nullptr;
	AxeUnlockButton* aub = nullptr;

};

class BowButton : public Button
{
public:
	BowButton();
	virtual ~BowButton() override;

	virtual void Init() override;
	virtual void OnActive() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void IsClick() override;


private:


};