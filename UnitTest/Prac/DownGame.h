#pragma once

class DownGame : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

	bool IsRender() { return isrender; }
	void SetRender();

	void ChangeTheme();

private:
	class Player1* character;

	vector<class Floor*> rs;

	class ShadedTexture* stv = nullptr;
	class ShadedTexture* stm = nullptr;

	class ShadedTexture* GAMEOVER = nullptr;

	class RenderTexture* view = nullptr;
	class RenderTexture* minimap = nullptr;

	class TextureRect* sky = nullptr;

	bool isrender = true;

	int i = 0;
	int Gap = 300;

	int score = 0;

	bool Start = true;
	bool isminimap = false;

	int difficult = 4;

	float downSpeed = 0.7f;

};