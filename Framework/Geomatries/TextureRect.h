#pragma once

#include "Utilities/GameObject.h"

class TextureRect
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation, wstring path, Pivot p = MIDLE_CENTER);
	TextureRect(Vector3 position, Vector3 size, float rotation, Pivot p = MIDLE_CENTER);
	~TextureRect();

	void Init(Vector3 position, Vector3 size, float rotation, Pivot p);

	void SetShader(wstring shaderpath);
	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }

	ID3D11ShaderResourceView* GetSrv() { return srv; }

	void MapVertexBuffer();
	void UnmapVertexBuffer();

	void Update();
	void Update(Vector3 position, Vector3 size, float rotation, Pivot p = DOWN_CENTER);
	virtual void UpdateUI();

	void UpdateWorld();

	void Render();
	void GUI();

	const Vector3* GetVerticesLocalPosition() { return verticesLocalPosition; }
	const Matrix GetWorld() { return world; }

	const Vector3 GetPosition() { return position; }
	const Vector3 GetSize() { return size; }
	const float GetRotation() { return rotation; }

	void SetPivot(Pivot p);

	//void UpdateColor();
	//void SetAlpha(Color color);

protected:
	vector<VertexTexture> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	Matrix world;
	Matrix S, R, T;

	WorldBuffer* wb = nullptr;

	Vector3 position;
	Vector3 originalposition;
	Vector3 size;
	float rotation;

	ID3D11ShaderResourceView* srv = nullptr;

	D3D11_MAPPED_SUBRESOURCE subResource;

	Vector3 verticesLocalPosition[4];
};