#pragma once

class Camera : public SingletonBase<Camera>
{
public:
	friend class SingletonBase<Camera>;

	void Update();
	void Render();

	void Move(Vector2 size, Vector3 position);
	void UpdateView();

	void UnProjection(Vector3* out, Vector3 source, Matrix world);

	void SetCameraSize(Vector2 size);
	Vector2 GetCameraSize() { return size; }

	const Vector3 GetPosition() { return position; }

	void SetPosition(Vector3 Targetposition);

private:
	Camera();
	~Camera();

private:
	VPBuffer* vpb = nullptr;
	Matrix view, proj;

	Vector3 position = Values::ZeroVec3;
	Vector2 size;
	float cameraSpeed = 100.0f;


};