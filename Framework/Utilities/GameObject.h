#pragma once

class GameObject
{
public:
	enum Active
	{
		OFF = 0,
		ON,
	};

	
public:

	GameObject(Vector3 position, Vector3 size, float rotation, Pivot p = DOWN_CENTER);
	~GameObject();

	void SetPivot(Pivot p);

	void Update();
	void Render();

	Vector3 GetPos() { return position; }
	float GetRot() { return rotation; }
	const Vector3 GetSize() { return size; }

	void SetPos(Vector3 position) { this->position = position; }
	void SetRot(float rotation) { this->rotation = rotation; }
	void SetSize(Vector3 size) { this->size = size; }


	void SetIsActive(Active isActive)
	{
		_activeState[0] = _activeState[1];
		_activeState[1] = isActive;
	}
	const bool IsActive() { return  _activeState[1] == ON; }

	


protected:
	Active _activeState[2] = { OFF, ON };

	Pivot pivot;

	Vector3 position;
	Vector3 size;
	float rotation;

	

};