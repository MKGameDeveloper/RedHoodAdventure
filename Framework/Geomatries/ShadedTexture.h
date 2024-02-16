#pragma once
#include "TextureRect.h"

class ShadedBuffer : public ShaderBuffer
{
public:
	ShadedBuffer()
		: ShaderBuffer(&data, sizeof(Data))
	{
		data.textureSize = Values::ZeroVec2;
		data.Selection = 1;
		data.BlurCount = 1;
	}

	void SetTextureSize(Vector2 size)
	{
		data.textureSize = size;
	}

	void SetSelection(int selection) { data.Selection = selection; }

	int* GetSelectionPtr() { return &data.Selection; }
	int* GetBlurCountPtr() { return &data.BlurCount; }

	struct Data
	{
		Vector2 textureSize;
		int Selection;
		int BlurCount;
	};

private:
	Data data;
};

class ShadedTexture : public TextureRect
{
public:
	ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path);
	ShadedTexture(Vector3 position, Vector3 size, float rotation);
	~ShadedTexture();

	ShadedBuffer* GetSB() { return sb; }
	void Rotate180();
	void RotateZero();

	void Render();
	void GUI();

private:
	ShadedBuffer* sb = nullptr;
};