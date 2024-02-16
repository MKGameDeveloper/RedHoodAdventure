#pragma once

class Rect
{
public:
	Rect(Vector3 position, Vector3 size, float rotation);
	~Rect();

	void Update();
	void Render();

	void Move();

	void GUI();

	void UpdateColor();
	string MakeLabel(string perFix);

	void UpdateWorld();
	void SetColor(Color color);

	void Grav();

	BoundingBox* GetCollision() { return collision; }

	void SetGround(bool ig) { isGround = ig; }
	bool IsGround() { return isGround; }

private:
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	Matrix world;
	// scale rotation translation
	Matrix S, R, T;

	Vector3 position;
	Vector3 size;
	float rotation;

	Color color = Color(1, 0, 0, 1);

	WorldBuffer* wb = nullptr;

	bool bOpen = true;

	BoundingBox* collision = nullptr;

	Vector3 verticesPosition[4];

	bool isGround = false;

};