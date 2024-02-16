#include "Framework.h"
#include "Arrow.h"

Arrow::Arrow(Vector3 position, Vector3 size, float rotation, float dir)
	:GameObject(position ,size, rotation)
{

	arrow = new TextureRect(position, size, rotation, TexturePath + L"arrow.png");

	collision = new BoundingBox(BoundingBox::Weapon);
	collision->Init(Color(1, 0, 0, 0.3f), BoundingBox::MIDLE_CENTER);

	grav = Values::DownVec * 0.3f;

	Init(position, size, rotation, dir);
}

Arrow::~Arrow()
{
	SAFE_DELETE(collision);
	SAFE_DELETE(arrow);
}

void Arrow::Init(Vector3 position, Vector3 size, float rotation, float dir)
{
	this->dir = dir;
	this->position = position;
	this->size = size;


	if (this->dir == 1.f)
		dr = 180.f;
	else
		dr = 0.f;

	this->rotation = dr;

	collision->SetDamage(PlayerStatus::Get()->GetBowDamage());
	collision->SetDir(dir);
	collision->SetAtkType(KNOCKBACK);

	vx = accelSpeed;

	v1 = Vector3{ (this->dir * vx), 0, 0 };

	deltaTime = 0.f;

	SetIsActive(GameObject::ON);
	collision->SetActive(true);
	iscol = false;


}

void Arrow::Update()
{
	if (!(_activeState[1] == ON))
		return;

	//OnIsActive();

	delta = Time::Get()->WorldDelta();

	arrow->Update(position, size, rotation);
	collision->Update(position, size, rotation);


	if (iscol)
	{
		deltaTime += delta;

		if (deltaTime > 3.0f)
		{
			_activeState[1] = OFF;
		}
	}
	else
	{
		vector<BoundingBox*> floors = BoundingBox::GetTagCollision(BoundingBox::Floor);

		for (BoundingBox* f : floors)
		{
			if (f->GetType() == Pass || f->GetType() == UpPass)
				continue;

			if (BoundingBox::OBB(f, collision))
			{
				collision->SetActive(false);
				iscol = true;
			}

		}

		double s1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
		double s2 = sqrt(pow(dir, 2) + pow(0, 2));

		double inner = (v1.x * dir) + (v1.y * 0);
		double theta = (acos(inner / (s1 * s2)));

		if (dir == 1.f)
			rotation = (-theta * 180 / 3.141592f) + 180;
		else
			rotation = (theta * 180 / 3.141592f) + dr;


		position += v1;
		v1 += grav;
	}

	

	

	/*else
	{
		vx = 0.f;
		
	}*/



}

void Arrow::Render()
{
	if (!_activeState[1])
		return;

	arrow->Render();
	collision->Render();
}


void Arrow::OnIsActive()
{
	if (!(_activeState[0] == OFF) || !(_activeState[1] == ON))
		return;

	{
		// 활성화할 시 사용할 코드
		deltaTime = 0.f;
		vx = accelSpeed;

	}

	_activeState[1] = ON;
}

void Arrow::SetIsActive(Active isActive)
{
	_activeState[0] = _activeState[1];
	_activeState[1] = isActive;
}
