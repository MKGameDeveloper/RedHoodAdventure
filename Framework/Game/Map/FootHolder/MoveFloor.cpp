#include "Framework.h"
#include "MoveFloor.h"

MoveFloor::MoveFloor(Vector3 position, float dir, bool TriggerMode)
	: FootHolder(position, { 100, 20, 0 }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"MoveFloor.png",DOWN_CENTER);

	this->dir = dir;

	MoveDir = {this->dir, 0, 0};
	IsMove = false;
	rigidbody = new RigidBody(*this);

	collision = new BoundingBox(BoundingBox::Floor, UpPass);
	collision->Init(Color(0, 0, 1, 0.3f), BoundingBox::DOWN_CENTER);

	FSpeed = 2.f;
	this->TriggerMode = TriggerMode;

}


MoveFloor::~MoveFloor()
{
	SAFE_DELETE(collision);
	SAFE_DELETE(rigidbody);
	SAFE_DELETE(tr);
}

void MoveFloor::Move()
{
	if (TriggerMode)
	{
		if (IsMove)
		{
			MoveSpeed = dir * FSpeed;
			MoveDir.x = MoveSpeed;
			
			rigidbody->Update();

			MoveSpeed = dir * FSpeed;
			collision->SetFSpeed(MoveSpeed);


			position += MoveDir;
		}
		else
		{
			MoveSpeed = 0.f;
			collision->SetFSpeed(MoveSpeed);
		}
	}
	else
	{
		MoveSpeed = dir * FSpeed;
		MoveDir.x = MoveSpeed;

		rigidbody->Update();

		MoveSpeed = dir * FSpeed;
		collision->SetFSpeed(MoveSpeed);

		position += MoveDir;
	}
	
}


void MoveFloor::Update()
{
	Move();
	tr->Update(position, size, rotation);
	collision->Update(position, {size.x, size.y - 5.f, size.z}, rotation);
}

void MoveFloor::Render()
{
	tr->Render();
	//collision->Render();
	//rigidbody->Render();
}



UpDownFloor::UpDownFloor(Vector3 position, bool TriggerMode)
	: FootHolder(position, { 100, 20, 0 }, 0.f)
{
	tr = new TextureRect(position, size, rotation, TexturePath + L"MoveFloor.png", DOWN_CENTER);

	this->dir = 1.f;

	MoveDir = { 0, this->dir, 0 };
	IsMove = false;
	rigidbody = new RigidBody(*this);

	collision = new BoundingBox(BoundingBox::Floor, UpPass);
	collision->Init(Color(0, 0, 1, 0.3f), BoundingBox::DOWN_CENTER);

	FSpeed = 0.5f;
	this->TriggerMode = TriggerMode;

}



UpDownFloor::~UpDownFloor()
{
	SAFE_DELETE(collision);
	SAFE_DELETE(rigidbody);
	SAFE_DELETE(tr);
}

void UpDownFloor::Move()
{
	if (TriggerMode)
	{
		if (IsMove)
		{
			MoveSpeed = dir * FSpeed;
			MoveDir.y = MoveSpeed;

			rigidbody->Update();

			MoveSpeed = dir * FSpeed;
			collision->SetFYSpeed(MoveSpeed);

			if (isFirst)
				isFirst = false;
			else
				position += MoveDir;
		}
		else
		{
			MoveSpeed = 0.f;
			collision->SetFYSpeed(MoveSpeed);
		}
	}
	else
	{
		MoveSpeed = dir * FSpeed;
		MoveDir.y = MoveSpeed;

		rigidbody->Update();

		MoveSpeed = dir * FSpeed;
		collision->SetFYSpeed(MoveSpeed);

		position += MoveDir;

	}

}


void UpDownFloor::Update()
{
	Move();
	tr->Update(position, size, rotation);
	collision->Update(position, { size.x, size.y - 5.f, size.z }, rotation);
}

void UpDownFloor::Render()
{
	tr->Render();
	//collision->Render();
	//rigidbody->Render();
}

