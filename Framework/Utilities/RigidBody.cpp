#include "Framework.h"
#include "RigidBody.h"

RigidBody::RigidBody(Character& character)
	:character(&character)
{
	CheckDown = new BoundingBox();
	CheckDown->Init(Color(0, 0, 1, 0.3f), BoundingBox::UP_CENTER);

	CheckUp = new BoundingBox();
	CheckUp->Init(Color(0, 0, 1, 0.3f), BoundingBox::DOWN_CENTER);

	CheckLeft = new BoundingBox();
	CheckLeft->Init(Color(0, 0, 1, 0.3f), BoundingBox::MIDLE_RIGHT);

	CheckRight = new BoundingBox();
	CheckRight->Init(Color(0, 0, 1, 0.3f), BoundingBox::MIDLE_LEFT);
	// �Ʒ� �ٴ� ������ üũ

	CheckLeftDown = new BoundingBox();
	CheckLeftDown->Init(Color(0, 0, 1, 0.3f), BoundingBox::UP_RIGHT);

	CheckRightDown = new BoundingBox();
	CheckRightDown->Init(Color(0, 0, 1, 0.3f), BoundingBox::UP_LEFT);


	grav = Values::DownVec * 0.98f;
	FinalMove = { 0,0,0 };

	isground = false;
	iswall = false;
	IsCharacter = true;

	isup = false;
	isdown = false;
	isleft = false;
	isright = false;

	FSpeed = 0.f;
	FYSpeed = 0.f;
	count = 0;
}

RigidBody::RigidBody(FootHolder& floor)
	:floor(&floor)
{
	CheckDown = new BoundingBox();
	CheckDown->Init(Color(0, 0, 1, 0.3f), BoundingBox::UP_CENTER);

	CheckUp = new BoundingBox();
	CheckUp->Init(Color(0, 0, 1, 0.3f), BoundingBox::DOWN_CENTER);

	CheckLeft = new BoundingBox();
	CheckLeft->Init(Color(0, 0, 1, 0.3f), BoundingBox::MIDLE_RIGHT);

	CheckRight = new BoundingBox();
	CheckRight->Init(Color(0, 0, 1, 0.3f), BoundingBox::MIDLE_LEFT);

	grav = Values::DownVec * 0.98f;
	FinalMove = { 0,0,0 };

	isground = false;
	iswall = false;
	IsCharacter = false;

	count = 0;

}

RigidBody::~RigidBody()
{
	SAFE_DELETE(CheckRightDown);
	SAFE_DELETE(CheckLeftDown);

	SAFE_DELETE(CheckRight);
	SAFE_DELETE(CheckLeft);
	SAFE_DELETE(CheckUp);
	SAFE_DELETE(CheckDown);

}

void RigidBody::Update()
{
	if (IsCharacter)
		Movement();
	else
		FloorMovement();
}

void RigidBody::Render()
{
	CheckDown->Render();
	CheckUp->Render();
	CheckLeft->Render();
	CheckRight->Render();

}


void RigidBody::Movement()
{
	// ĳ���Ϳ��� �Էµ� ������
	FinalMove = *character->GetMoveDir();

	// �߷� ���ӵ��� ���� ���� �ӵ� ����
	FinalMove += grav;

	// 1�� �浹 üũ
	{
		// Collision Update
		UpdateCollision();

		// Collision Check & MoveDir ����
		CheckCollision();
	}
	
	count++;

	// �߰� ��� ����
	{
		FinalMove.x += FSpeed;
		FinalMove.y += FYSpeed;
	}
	// 2�� �浹 üũ
	{

		// Collision Update
		UpdateCollision();

		// Collision Check & MoveDir ����
		CheckCollision();

		// ��ü�� ���� ��ȭ
		ChangeCol();
	}
	

	// ���� ������ ����
	*character->GetMoveDir() = FinalMove;

	FSpeed = 0.f;
	FYSpeed = 0.f;
	count = 0;


}

void RigidBody::FloorMovement()
{
	// ĳ���Ϳ��� �Էµ� ������
	FinalMove = *floor->GetMoveDir();

	// Collision Update
	UpdateFloorCollision();

	// Collision Check & MoveDir ����
	CheckFloorCollision();

	if (isCollisionFloor)
		floor->SetDir((floor->GetDir() * -1.f));

}

void RigidBody::UpdateCollision()
{
	BoundingBox* charCol = character->GetCollision();

	// �� �Ʒ�
	if (FinalMove.y <= 0.f)
	{
		CheckUp->SetActive(false);

		CheckDown->Update({ character->GetPos().x, character->GetPos().y, 0.f }, { charCol->GetSize().x, (FinalMove.y + grav.y) * (-1.f), 1.0f }, 0.0f); // 4.5f
	}
	else
	{
		CheckUp->SetActive(true);

		CheckDown->Update({ character->GetPos().x, character->GetPos().y, 0.f }, { charCol->GetSize().x, (FinalMove.y + grav.y) * (-1.f), 1.0f }, 0.0f); // 4.5f
		CheckUp->Update({ character->GetPos().x, (character->GetPos().y + charCol->GetSize().y), 0.f }, { charCol->GetSize().x, (FinalMove).y, 1.0f }, 0.0f);
	}

	// �¿�
	if (FinalMove.x < -0.01f)
	{
		CheckLeft->SetActive(true);
		CheckRight->SetActive(false);

		CheckLeft->Update({ character->GetPos().x - (charCol->GetSize().x / 2.f), character->GetPos().y + (charCol->GetSize().y / 2.f), 0.f }, { abs(FinalMove.x), charCol->GetSize().y, 1.0f }, 0.0f); // 4.5f
	}
	else if (FinalMove.x > 0.01f)
	{
		CheckRight->SetActive(true);
		CheckLeft->SetActive(false);

		CheckRight->Update({ character->GetPos().x + (charCol->GetSize().x / 2.f), character->GetPos().y + (charCol->GetSize().y / 2.f), 0.f }, { abs(FinalMove.x), charCol->GetSize().y, 1.0f }, 0.0f);
	}
	else
	{
		CheckLeft->SetActive(false);
		CheckRight->SetActive(false);
	}

	CheckLeftDown->Update({ character->GetPos().x - (charCol->GetSize().x / 2.f), character->GetPos().y, 0.f }, { 30.f,30.f,1.f }, 0.f);
	CheckRightDown->Update({ character->GetPos().x + (charCol->GetSize().x / 2.f), character->GetPos().y, 0.f }, { 30.f,30.f,1.f }, 0.f);

}

void RigidBody::CheckCollision()
{
	CheckDownCol();
	CheckUpCol();
	CheckLeftRightCol();
}

void RigidBody::CheckUpCol()
{
	if (count == 0)
	{
		isup = false;
	}

	vector<BoundingBox*> floors = BoundingBox::GetTagCollision(BoundingBox::Floor);

	for (BoundingBox* f : floors)
	{
		// ����� �ٴ��Ͻ� �浹�˻� x
		if (f->GetType() == Pass || f->GetIsActive() == false)
			continue;

		// ���� �ݸ��� üũ
		if (f->GetType() == NonePass || f->GetType() == LeftSideDown || f->GetType() == RightSideDown)
		{

			// Up
			if ((f->GetEdge()->RB.x != CheckUp->GetEdge()->LT.x) && (f->GetEdge()->LB.x != CheckUp->GetEdge()->RT.x))
			{
				if (BoundingBox::OBB(f, CheckUp))
				{
					float distance = ((f->GetEdge()->LB.y) - (CheckUp->GetEdge()->LB.y));
					

					if (distance >= 0.f)
					{
						// ���� �÷��̾�� Floor ������ �Ÿ��� ���� �ӵ����� ª�ٸ�
						if (distance <= FinalMove.y)
						{
							FinalMove.y = distance;	// ���ϼӵ��� �Ÿ��� ���̷� ��ü�Ͽ� ����
						}
						if (distance == 0.f)
						{
							isup = true;
						}

					}// if3 end

				}// if2 end

			}// if1 end

		}// Up Check end


	}
}

void RigidBody::CheckDownCol()
{
	if (count == 0)
	{
		isdown = false;
		isground = false;
	}
	

	vector<BoundingBox*> floors = BoundingBox::GetTagCollision(BoundingBox::Floor);

	for (BoundingBox* f : floors)
	{
		// ����� �ٴ��Ͻ� �浹�˻� x
		if (f->GetType() == Pass || f->GetIsActive() == false)
			continue;




		// ����� �ٴڸ� �ƴ϶�� �Ʒ��� �浹�� ��� �˻�

			// Down
		if ((f->GetEdge()->RT.x != CheckDown->GetEdge()->LB.x) && (f->GetEdge()->LT.x != CheckDown->GetEdge()->RB.x))
		{
			if (BoundingBox::OBB(f, CheckDown))
			{
				float distance = ((f->GetEdge()->LT.y) - (CheckDown->GetEdge()->RT.y));

				// �÷��̾�� ������ Floor�� �� �� ������ �Ÿ��� ���
				if (distance <= 0.f)
				{
					if (f->GetFYSpeed() != 0.f)
					{
						// ���� �÷��̾�� Floor ������ �Ÿ��� ���� �ӵ����� ª�ٸ�
						if (distance + f->GetFYSpeed() >= FinalMove.y)
						{
							FinalMove.y = distance + f->GetFYSpeed();	// ���ϼӵ��� �Ÿ��� ���̷� ��ü�Ͽ� ����
						}
						if (distance == 0.f)
						{
							if (f->GetFSpeed() != 0.f)
							{
								FSpeed = f->GetFSpeed();
							}
							FYSpeed = f->GetFYSpeed() + grav.y;

							isground = true;
							isdown = true;
						}


					}
					else
					{
						// ���� �÷��̾�� Floor ������ �Ÿ��� ���� �ӵ����� ª�ٸ�
						if (distance >= FinalMove.y)
						{
							FinalMove.y = distance;	// ���ϼӵ��� �Ÿ��� ���̷� ��ü�Ͽ� ����
						}
						if (distance == 0.f)
						{
							if (f->GetFSpeed() != 0.f)
							{
								FSpeed = f->GetFSpeed();
							}


							isground = true;
							isdown = true;
						}
					}
					

				}
				

			}// if2 end

		}// if1 end

	}
}

void RigidBody::CheckLeftRightCol()
{
	if (count == 0)
	{
		iswall = false;
		isleft = false;
		isright = false;
		isside = false;

		isleftnull = true;
		isrightnull = true;

		count++;
	}
	

	vector<BoundingBox*> floors = BoundingBox::GetTagCollision(BoundingBox::Floor);

	for (BoundingBox* f : floors)
	{
		// ����� �ٴ��Ͻ� �浹�˻� x
		if (f->GetType() == Pass || f->GetIsActive() == false)
			continue;

		if (BoundingBox::OBB(f, CheckLeftDown))
		{
			isleftnull = false;
		}

		if (BoundingBox::OBB(f, CheckRightDown))
		{
			isrightnull = false;
		}

		// ���� �ݸ��� üũ
		if (f->GetType() == NonePass || f->GetType() == RightSide || f->GetType() == RightSideDown || f->GetType() == RightSideUp)
		{

			// Left
			if ((f->GetEdge()->RB.y != CheckLeft->GetEdge()->RT.y) && (f->GetEdge()->RT.y != CheckLeft->GetEdge()->RB.y))
			{
				if (BoundingBox::OBB(f, CheckLeft))
				{
					float distance = ((f->GetEdge()->RT.x) - (CheckLeft->GetEdge()->RT.x));

					if (distance >= 0.f)
					{
						// ���� �÷��̾�� Floor ������ �Ÿ��� ���� �ӵ����� ª�ٸ�
						if (distance > FinalMove.x)
						{
							FinalMove.x = distance;	// ���ϼӵ��� �Ÿ��� ���̷� ��ü�Ͽ� ����
						}
						if (distance == 0.f)
						{
							if (f->GetType() == RightSide || f->GetType() == RightSideDown || f->GetType() == RightSideUp)
							{
								if (!CheckState(IsWall))
								{
									character->SetDir(1.f);
								}
								iswall = true;
							}
							isside = true;
							isleft = true;
						}

					}// if3 end

				}// if2 end

			}// if1 end

		}// Left Check end

		// ������ �ݸ��� üũ
		if (f->GetType() == NonePass || f->GetType() == LeftSide || f->GetType() == LeftSideDown || f->GetType() == LeftSideUp)
		{

			// Right
			if ((f->GetEdge()->LB.y != CheckRight->GetEdge()->LT.y) && (f->GetEdge()->LT.y != CheckRight->GetEdge()->LB.y))
			{
				if (BoundingBox::OBB(f, CheckRight))
				{
					float distance = ((f->GetEdge()->LT.x) - (CheckRight->GetEdge()->LT.x));
					if (distance <= 0.f)
					{
						// ���� �÷��̾�� Floor ������ �Ÿ��� ���� �ӵ����� ª�ٸ�
						if (distance < FinalMove.x)
						{
							FinalMove.x = distance;	// ���ϼӵ��� �Ÿ��� ���̷� ��ü�Ͽ� ����
						}
						if (distance == 0.f)
						{
							if (f->GetType() == LeftSide || f->GetType() == LeftSideDown || f->GetType() == LeftSideUp)
							{
								if (!CheckState(IsWall))
								{
									character->SetDir(-1.f);
								}
								iswall = true;
							}
							isside = true;
							isright = true;
						}

					}// if3 end

				}// if2 end

			}// if1 end

		}// Right Check end


	}
}

void RigidBody::ChangeCol()
{
	if (isup)
	{
		FinalMove.y = 0.f;
	}
	else if (isleft || isright)
	{
		FinalMove.x = 0.f;
	}

	CheckBool();

}

void RigidBody::CheckBool()
{
	BYTE checkbool = ((IsGround & (MaxState * isground)) | (IsWall & (MaxState * iswall))) | ((MaxState ^ (IsGround | IsWall)) & character->GetCurrentState());
	
	character->SetInputState(checkbool);
}

void RigidBody::UpdateFloorCollision()
{
	BoundingBox* floorCol = floor->GetCollision();

	// �� �Ʒ�
	if (FinalMove.y <= 0.f)
	{
		CheckUp->SetActive(false);

		CheckDown->Update({ floor->GetPos().x, floor->GetPos().y, 0.f }, { floorCol->GetSize().x, (FinalMove.y) * (-1.f), 1.0f }, 0.0f); // 4.5f
	}
	else
	{
		CheckUp->SetActive(true);

		CheckDown->Update({ floor->GetPos().x, floor->GetPos().y, 0.f }, { floorCol->GetSize().x, (FinalMove.y) * (-1.f), 1.0f }, 0.0f); // 4.5f
		CheckUp->Update({ floor->GetPos().x, (floor->GetPos().y + floorCol->GetSize().y), 0.f }, { floorCol->GetSize().x, (FinalMove).y, 1.0f }, 0.0f);
	}

	// �¿�
	if (FinalMove.x < -0.1f)
	{
		CheckLeft->SetActive(true);
		CheckRight->SetActive(false);

		CheckLeft->Update({ floor->GetPos().x - (floorCol->GetSize().x / 2.f), floor->GetPos().y + (floorCol->GetSize().y / 2.f), 0.f }, { abs(FinalMove.x), floorCol->GetSize().y, 1.0f }, 0.0f); // 4.5f
	}
	else if (FinalMove.x > 0.1f)
	{
		CheckRight->SetActive(true);
		CheckLeft->SetActive(false);

		CheckRight->Update({ floor->GetPos().x + (floorCol->GetSize().x / 2.f), floor->GetPos().y + (floorCol->GetSize().y / 2.f), 0.f }, { abs(FinalMove.x), floorCol->GetSize().y, 1.0f }, 0.0f);
	}
	else
	{
		CheckLeft->SetActive(false);
		CheckRight->SetActive(false);
	}
}

void RigidBody::CheckFloorCollision()
{
	isCollisionFloor = false;
	vector<BoundingBox*> floors = BoundingBox::GetTagCollision(BoundingBox::Floor);

	for (BoundingBox* f : floors)
	{
		// ����� �ٴ��Ͻ� �浹�˻� x
		if (f->GetIsActive() == false)
			continue;

		if (f == floor->GetCollision())
			continue;

		// ����� �ٴڸ� �ƴ϶�� �Ʒ��� �浹�� ��� �˻�

		// Down
		if ((f->GetEdge()->RT.x != CheckDown->GetEdge()->LB.x) && (f->GetEdge()->LT.x != CheckDown->GetEdge()->RB.x))
		{
			if (BoundingBox::OBB(f, CheckDown))
			{
				
				// �÷��̾�� ������ Floor�� �� �� ������ �Ÿ��� ���
				float distance = ((f->GetEdge()->LT.y) - (CheckDown->GetEdge()->RT.y));


				if (distance <= 0.f)
				{
					// ���� �÷��̾�� Floor ������ �Ÿ��� ���� �ӵ����� ª�ٸ�
					if (distance >= FinalMove.y)
					{
						FinalMove.y = distance;	// ���ϼӵ��� �Ÿ��� ���̷� ��ü�Ͽ� ����
					}
					if (distance == 0.f)
					{
						isground = true;

						if (isCollisionFloor == false)
						{
							isCollisionFloor = true;
							floor->SetMoveStack(floor->GetMoveStack() + 1);
						}
						
					}

				}

			}// if2 end

		}// if1 end



		// ���� �ݸ��� üũ

		// Up
		if ((f->GetEdge()->RB.x != CheckUp->GetEdge()->LT.x) && (f->GetEdge()->LB.x != CheckUp->GetEdge()->RT.x))
		{
			if (BoundingBox::OBB(f, CheckUp))
			{
				float distance = ((f->GetEdge()->LB.y) - (CheckUp->GetEdge()->LB.y));

				if (distance >= 0.f)
				{
					// ���� �÷��̾�� Floor ������ �Ÿ��� ���� �ӵ����� ª�ٸ�
					if (distance <= FinalMove.y)
					{
						FinalMove.y = distance;	// ���ϼӵ��� �Ÿ��� ���̷� ��ü�Ͽ� ����
					}
					if (distance == 0.f)
					{
						FinalMove.y = 0.f;

						if (isCollisionFloor == false)
						{
							isCollisionFloor = true;
							floor->SetMoveStack(floor->GetMoveStack() + 1);
						}
					}

				}// if3 end

			}// if2 end

		}// if1 end



		// ���� �ݸ��� üũ

		// Left
		if ((f->GetEdge()->RB.y != CheckLeft->GetEdge()->RT.y) && (f->GetEdge()->RT.y != CheckLeft->GetEdge()->RB.y))
		{
			if (BoundingBox::OBB(f, CheckLeft))
			{
				float distance = ((f->GetEdge()->RT.x) - (CheckLeft->GetEdge()->RT.x));

				if (distance >= 0.f)
				{
					// ���� �÷��̾�� Floor ������ �Ÿ��� ���� �ӵ����� ª�ٸ�
					if (distance >= FinalMove.x)
					{
						FinalMove.x = distance;	// ���ϼӵ��� �Ÿ��� ���̷� ��ü�Ͽ� ����
						floor->GetCollision()->SetFSpeed(distance);
					}
					if (distance == 0.f)
					{
						if (isCollisionFloor == false)
						{
							isCollisionFloor = true;
							floor->SetMoveStack(floor->GetMoveStack() + 1);
						}
					}

				}// if3 end

			}// if2 end

		}// if1 end



		// ������ �ݸ��� üũ
		

		// Right
		if ((f->GetEdge()->LB.y != CheckRight->GetEdge()->LT.y) && (f->GetEdge()->LT.y != CheckRight->GetEdge()->LB.y))
		{
			if (BoundingBox::OBB(f, CheckRight))
			{
				float distance = ((f->GetEdge()->LT.x) - (CheckRight->GetEdge()->LT.x));
				if (distance <= 0.f)
				{
					// ���� �÷��̾�� Floor ������ �Ÿ��� ���� �ӵ����� ª�ٸ�
					if (distance <= FinalMove.x)
					{
						FinalMove.x = distance;	// ���ϼӵ��� �Ÿ��� ���̷� ��ü�Ͽ� ����
						floor->GetCollision()->SetFSpeed(distance);
					}
					if (distance == 0.f)
					{
						if (isCollisionFloor == false)
						{
							isCollisionFloor = true;
							floor->SetMoveStack(floor->GetMoveStack() + 1);
						}
					}
				}// if3 end

			}// if2 end

		}// if1 end



	}// Floor Collison �˻� end

}

void RigidBody::SetGrav(float gravPow)
{
	grav = Values::DownVec * gravPow;
}

bool RigidBody::CheckState(BYTE check)
{
	return character->CheckInputState(check);
}