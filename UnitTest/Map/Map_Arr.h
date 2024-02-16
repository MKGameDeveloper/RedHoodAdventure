#pragma once

class Forest1 : public MapManager
{
public:
	Forest1();

	virtual void Destroy() override;

	virtual void Update() override;

	virtual void Render() override;


};

class Forest2 : public MapManager
{
public:
	Forest2();

	virtual void Destroy() override;

	virtual void Update() override;

	virtual void Render() override;


};

class Town1 : public MapManager
{
public:
	Town1();

	virtual void Destroy() override;

	virtual void Update() override;

	virtual void Render() override;


};