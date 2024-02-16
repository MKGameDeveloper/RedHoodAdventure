#pragma once

class TileMapDemo : public IObject
{
public:

	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	class TileMap* tm = nullptr;
};