#pragma once

enum
{
	x = 0,
	y
};

struct RectEdge
{
	Vector3 LT;
	Vector3 LB;
	Vector3 RT;
	Vector3 RB;
};

struct AxisData
{
	Vector3 centerPos;
	Vector3 axisDir[2];
	float axisLen[2];
};

class CollisionBuffer : public ShaderBuffer
{
public:
	CollisionBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		data.isOn = 1;
	}

	void SwitchRender() { data.isOn = !data.isOn; }
	void SwitchOn() { data.isOn = true; }
	void SwitchOff() { data.isOn = false; }

	struct Data
	{
		int isOn;
		Vector3 dummy;
	};

private:
	Data data;
};

class BoundingBox
{
public:
	enum CenterPos
	{
		MIDLE_CENTER = 0,
		MIDLE_LEFT,
		MIDLE_RIGHT,
		UP_CENTER,
		UP_LEFT,
		UP_RIGHT,
		DOWN_CENTER,
		DOWN_LEFT,
		DOWN_RIGHT
	};

	enum Tag
	{
		None,
		Player,
		Monster,
		Item,
		BackFloor,
		Floor,
		Object,
		Trigger,
		Weapon,
		MonsterWeapon,
		NPC,
	};


public:
	static unordered_map<Tag, vector<BoundingBox*>> cols;

public:
	BoundingBox(Tag tag = None, Type pass = Pass);
	~BoundingBox();

	void Init(Color color);
	void Init(Color color, CenterPos center);

	void Update(Vector3 position, Vector3 size, float rotation);
	void Update();
	void Render();

	void UpdateCollisionData();

	RectEdge* GetEdge() { return edge; }
	AxisData* GetData() { return data; }
	Type GetType() { return this->pass; }

	float GetFSpeed() { return FSpeed; }
	float GetFYSpeed() { return FYSpeed; }
	float GetDamage() { return Damage; }
	Attack GetAtkType() { return _attack; }
	float GetDir() { return dir; }

	Vector3 GetPosition() { return position; }
	Vector3 GetSize() { return size; }
	float GetRotation() { return rotation; }

	void SetActive(bool isActive);
	void SetColor(Color color);

	void SetFSpeed(float speed) { FSpeed = speed; }
	void SetFYSpeed(float speed) { FYSpeed = speed; }
	void SetDamage(float damage) { Damage = damage; }
	void SetAtkType(Attack atk) { _attack = atk; }
	void SetDir(float dir) { this->dir = dir; }

	bool GetIsActive() { return isActive; }

	static bool AABB(BoundingBox* a, BoundingBox* b);
	static bool OBB(BoundingBox* a, BoundingBox* b);

	// 충돌 검사할 충돌체 vector 모음
	void Push();
	static vector<BoundingBox*> GetTagCollision(Tag tag);

private:
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	Matrix world;
	WorldBuffer* wb = nullptr;

	Vector3 position;
	Vector3 size;
	float rotation;
	Color color;

	float FSpeed;
	float FYSpeed;
	float Damage;
	Attack _attack;
	float dir;

	CollisionBuffer* cb = nullptr;
	ID3D11BlendState* bs = nullptr;

	RectEdge* edge = nullptr;
	AxisData* data = nullptr;

private:
	Type pass;
	Tag tag;
	bool isActive = true;
};