#pragma once


#include "Utilities/BoundingBox.h"

#include "Utilities/GameObject.h"

class FootHolder : public GameObject
{
public:
	FootHolder(Vector3 position, Vector3 size, float rotation);
	~FootHolder();


	BoundingBox* GetCollision() { return collision; }
	Vector3* GetMoveDir() { return &MoveDir; }

	virtual void Update();
	void UpdateCollisionType();

	virtual void Render();
	virtual void PostRender();

	BoundingBox::Tag GetTag() { return tag; }
	void SetTag(BoundingBox::Tag tag) { this->tag = tag; }

	Type GetType() { return type; }
	void SetType(Type type) { this->type = type; }

	float GetDir() { return dir; }
	bool GetIsMove() { return IsMove; }
	int GetMoveStack() { return MoveStack; }


	Vector2 GetStartUV() { return startUV; }
	Vector2 GetEndUV() { return endUV; }
	Color GetColor() { return color; }

	void SetDir(float dir) { this->dir = dir; }
	void SetIsMove(bool ismove) { IsMove = ismove; }
	void SetMoveStack(int stack) { MoveStack = stack; }

	void SetStartUV(Vector2 startUV) { this->startUV = startUV; }
	void SetEndUV(Vector2 endUV) { this->endUV = endUV; }
	void SetColor(Color color) { this->color = color; }

	virtual void Init();
	virtual void OnActive();


protected:
	Type type;
	BoundingBox::Tag tag = BoundingBox::Floor;
	BoundingBox* collision = nullptr;

	Vector3 MoveDir;

	Vector3 CPos;
	Vector3 CSize;
	float CRot;

	Color color = Values::Black;

	Vector2 startUV = Values::ZeroVec2;
	Vector2 endUV = Values::ZeroVec2;

	float dir;
	bool IsMove;

	int MoveStack;

	float MoveSpeed;

	Vector3 StartPos = {};

	bool isInit = false;

};
