#include "Framework.h"
#include "Floor.h"

Floor::Floor(Vector3 position, Vector3 size, float rotation, Type type)
	: FootHolder(position, size, rotation)
{
	this->type = type;
	// Edge
	{
		collision = new BoundingBox(BoundingBox::Floor, type);
		
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
			case Down_Half:
			{
				collision->Init(Color(0, 0, 1, 0.3f), BoundingBox::DOWN_LEFT);
				break;
			}
			case Left_45:
			case Left_45_Half:
			case LeftUp_Half:
			case RightUp_Half:
			case Up_Half:
			{
				collision->Init(Color(0, 0, 1, 0.3f), BoundingBox::UP_LEFT);
				break;
			}
			case Right_45:
			case Right_45_Half:
			{
				collision->Init(Color(0, 0, 1, 0.3f), BoundingBox::UP_RIGHT);
				break;
			}
			default:
				break;
		}
		
	}
	UpdateCollisionType();
	collision->Update(CPos, CSize, CRot);

}


Floor::~Floor()
{
	SAFE_DELETE(collision);
}


void Floor::Update()
{
	
	//collision->Update();
}

void Floor::Render()
{
	//collision->Render();
}



