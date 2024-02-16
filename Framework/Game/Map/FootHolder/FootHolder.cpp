#include "Framework.h"
#include "FootHolder.h"

FootHolder::FootHolder(Vector3 position, Vector3 size, float rotation)
	:GameObject(position, size, rotation)
{
	StartPos = position;
	MoveSpeed = 0.f;
	MoveStack = 0;
}

FootHolder::~FootHolder()
{
}

void FootHolder::Update()
{
	
}

void FootHolder::UpdateCollisionType()
{
	switch (type)
	{
	case Pass:
	case NonePass:
	case UpPass:
	case LeftSide:
	case LeftSideDown:
	case LeftSideUp:
	case RightSide:
	case RightSideDown:
	case RightSideUp:
	{
		CPos = position;
		CSize = size;
		CRot = rotation;
		break;
	}
	case Left_45:
		CPos = { position.x, position.y + size.y, position.z };
		CSize = { sqrt(float(pow(size.x, 2) * 2)), (size.y / 4), 1.f };
		CRot = -45.f;
		break;
	case Left_45_Half:
		CPos = { position.x, position.y + (size.y / 2.f), position.z };
		CSize = { sqrt(float(pow(size.x, 2) * 2)) / 2.f, (size.y / 4), 1.f };
		CRot = -45.f;
		break;
	case Right_45:
		CPos = { position.x + size.x, position.y + size.y, position.z };
		CSize = { sqrt(float(pow(size.x, 2) * 2)), (size.y / 4), 1.f };
		CRot = 45.f;
		break;
	case Right_45_Half:
		CPos = { position.x + size.x, position.y + (size.y / 2.f), position.z };
		CSize = { sqrt(float(pow(size.x, 2) * 2)) / 2.f, (size.y / 4), 1.f };
		CRot = 45.f;
		break;
	case LeftUp_Half:
		CPos = { position.x, position.y + size.y, position.z };
		CSize = { size.x / 2.f, size.y / 4.f, 1.f };
		CRot = rotation;
		break;
	case RightUp_Half:
		CPos = { position.x + (size.x / 2.f), position.y + size.y, position.z };
		CSize = { size.x / 2.f, size.y / 4.f, 1.f };
		CRot = rotation;
		break;

	case Up_Half:
		CPos = { position.x, position.y + size.y, position.z };
		CSize = { size.x, size.y / 2.f, 1.f };
		CRot = rotation;
		break;
	case Down_Half:
		CPos = position;
		CSize = { size.x, size.y / 2.f, 1.f };
		CRot = rotation;
		break;
	default:
		break;
	}
}

void FootHolder::Render()
{
}

void FootHolder::PostRender()
{
}

void FootHolder::Init()
{
	if (collision == nullptr)
		return;
		
	isInit = true;
	collision->SetActive(false);

	position = StartPos;
}

void FootHolder::OnActive()
{
	if (collision == nullptr)
		return;
		
	isInit = false;
	collision->SetActive(true);
}
