#include "Framework.h"
#include "BoundingBox.h"

unordered_map<BoundingBox::Tag, vector<BoundingBox*>> BoundingBox::cols;

BoundingBox::BoundingBox(Tag tag, Type pass)
	:tag(tag), pass(pass)
{
	edge = new RectEdge();
	data = new AxisData();
	Push();
}

BoundingBox::~BoundingBox()
{
	SAFE_DELETE(data);
	SAFE_DELETE(edge);
}

void BoundingBox::Init(Color color)
{
	vertices.assign(4, VertexColor());

	vertices[0].position = Vector3(-.5f, -.5f, +.0f);
	vertices[1].position = Vector3(+.5f, +.5f, +.0f);
	vertices[2].position = Vector3(+.5f, -.5f, +.0f);
	vertices[3].position = Vector3(-.5f, +.5f, +.0f);

	for (VertexColor& v : vertices)
		v.color = color;

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	indices = { 0, 1, 2, 0, 3, 1 };
	ib = new IndexBuffer();
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"CollisionShader.hlsl", "VS");

	ps = new PixelShader();
	ps->Create(ShaderPath + L"CollisionShader.hlsl", "PS");

	il = new InputLayout();
	il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());

	wb = new WorldBuffer();

	cb = new CollisionBuffer();

	D3D11_BLEND_DESC desc;
	States::GetBlendDesc(&desc);
	desc.RenderTarget[0].BlendEnable = true;
	States::CreateBlend(&desc, &bs);

	FSpeed = 0.f;
	FYSpeed = 0.f;
	Damage = 0.f;
	_attack = NORMAL;
	dir = 1.f;
}

void BoundingBox::Init(Color color, CenterPos center)
{

	vertices.assign(4, VertexColor());

	switch (center)
	{
	case BoundingBox::MIDLE_CENTER:

		vertices[0].position = Vector3(-0.5f, -0.5f, +0.0f);
		vertices[1].position = Vector3(+0.5f, +0.5f, +0.0f);
		vertices[2].position = Vector3(+0.5f, -0.5f, +0.0f);
		vertices[3].position = Vector3(-0.5f, +0.5f, +0.0f);

		break;

	case BoundingBox::MIDLE_LEFT:

		vertices[0].position = Vector3(+0.0f, -0.5f, +0.0f);
		vertices[1].position = Vector3(+1.0f, +0.5f, +0.0f);
		vertices[2].position = Vector3(+1.0f, -0.5f, +0.0f);
		vertices[3].position = Vector3(+0.0f, +0.5f, +0.0f);

		break;

	case BoundingBox::MIDLE_RIGHT:

		vertices[0].position = Vector3(-1.0f, -0.5f, +0.0f);
		vertices[1].position = Vector3(+0.0f, +0.5f, +0.0f);
		vertices[2].position = Vector3(+0.0f, -0.5f, +0.0f);
		vertices[3].position = Vector3(-1.0f, +0.5f, +0.0f);

		break;

	case BoundingBox::UP_CENTER:

		vertices[0].position = Vector3(-0.5f, -1.0f, +0.0f);
		vertices[1].position = Vector3(+0.5f, +0.0f, +0.0f);
		vertices[2].position = Vector3(+0.5f, -1.0f, +0.0f);
		vertices[3].position = Vector3(-0.5f, +0.0f, +0.0f);

		break;

	case BoundingBox::UP_LEFT:

		vertices[0].position = Vector3(+0.0f, -1.0f, +0.0f);
		vertices[1].position = Vector3(+1.0f, +0.0f, +0.0f);
		vertices[2].position = Vector3(+1.0f, -1.0f, +0.0f);
		vertices[3].position = Vector3(+0.0f, +0.0f, +0.0f);

		break;

	case BoundingBox::UP_RIGHT:

		vertices[0].position = Vector3(-1.0f, -1.0f, +0.0f);
		vertices[1].position = Vector3(+0.0f, +0.0f, +0.0f);
		vertices[2].position = Vector3(+0.0f, -1.0f, +0.0f);
		vertices[3].position = Vector3(-1.0f, +0.0f, +0.0f);

		break;

	case BoundingBox::DOWN_CENTER:

		vertices[0].position = Vector3(-0.5f, +0.0f, +0.0f);
		vertices[1].position = Vector3(+0.5f, +1.0f, +0.0f);
		vertices[2].position = Vector3(+0.5f, +0.0f, +0.0f);
		vertices[3].position = Vector3(-0.5f, +1.0f, +0.0f);

		break;

	case BoundingBox::DOWN_LEFT:

		vertices[0].position = Vector3(+0.0f, +0.0f, +0.0f);
		vertices[1].position = Vector3(+1.0f, +1.0f, +0.0f);
		vertices[2].position = Vector3(+1.0f, +0.0f, +0.0f);
		vertices[3].position = Vector3(+0.0f, +1.0f, +0.0f);

		break;

	case BoundingBox::DOWN_RIGHT:

		vertices[0].position = Vector3(-1.0f, +0.0f, +0.0f);
		vertices[1].position = Vector3(+0.0f, +1.0f, +0.0f);
		vertices[2].position = Vector3(+0.0f, +0.0f, +0.0f);
		vertices[3].position = Vector3(-1.0f, +1.0f, +0.0f);

		break;

	default:
		break;
	}

	for (VertexColor& v : vertices)
		v.color = color;

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	indices = { 0, 1, 2, 0, 3, 1 };
	ib = new IndexBuffer();
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"CollisionShader.hlsl", "VS");

	ps = new PixelShader();
	ps->Create(ShaderPath + L"CollisionShader.hlsl", "PS");

	il = new InputLayout();
	il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());

	wb = new WorldBuffer();

	cb = new CollisionBuffer();

	D3D11_BLEND_DESC desc;
	States::GetBlendDesc(&desc);
	desc.RenderTarget[0].BlendEnable = true;
	States::CreateBlend(&desc, &bs);
}


void BoundingBox::Update(Vector3 position, Vector3 size, float rotation)
{
	this->size = size;
	this->rotation = rotation;
	this->position = position;

	world =
		DXMath::Scaling(size) *
		DXMath::RotationInDegree(rotation) *
		DXMath::Translation(position);

	UpdateCollisionData();
	wb->SetWorld(world);

	if (Keyboard::Get()->Down(VK_F1))
		cb->SwitchRender();
	
}

void BoundingBox::Update()
{
	if (Keyboard::Get()->Down(VK_F1) && this)
		cb->SwitchRender();
}

void BoundingBox::Render()
{
	if (isActive == false)
		return;

	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	wb->SetVSBuffer(0);

	ps->SetShader();
	cb->SetPSBuffer(0);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
	DC->OMSetBlendState(bs, nullptr, 0xffffffff);
}


void BoundingBox::UpdateCollisionData()
{
	// AABB
	{
		D3DXVec3TransformCoord(&edge->LT, &vertices[3].position, &world);
		D3DXVec3TransformCoord(&edge->LB, &vertices[0].position, &world);
		D3DXVec3TransformCoord(&edge->RT, &vertices[1].position, &world);
		D3DXVec3TransformCoord(&edge->RB, &vertices[2].position, &world);
	}

	// OBB
	{
		// Center Position Vector Update
		{
			float x = (edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) / 4.f;
			float y = (edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) / 4.f;
			float z = 0;

			data->centerPos = Vector3(x, y, z);
		}

		// Axis Vector Update
		{
			D3DXVec3TransformNormal(&data->axisDir[x], &Values::RightVec, &world);
			D3DXVec3TransformNormal(&data->axisDir[y], &Values::UpVec, &world);

			D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
			D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
		}

		// Axis Length Update
		{
			Vector3 unitAxes[2] = { data->axisDir[x], data->axisDir[y] };

			Vector3 verticesPos[4] = { edge->LT, edge->LB, edge->RT, edge->RB };
			float minValues[2] = { INT_MAX, INT_MAX };
			float maxValues[2] = { INT_MIN, INT_MIN };

			for (int i = 0; i < 4; ++i)
			{
				Vector3 point = verticesPos[i];

				for (int j = 0; j < 2; ++j)
				{
					float projection = D3DXVec3Dot(&point, &unitAxes[j]);

					if (projection < minValues[j])
						minValues[j] = projection;

					if (projection > maxValues[j])
						maxValues[j] = projection;
				}
			}
			data->axisLen[x] = (maxValues[x] - minValues[x]) / 2;
			data->axisLen[y] = (maxValues[y] - minValues[y]) / 2;
		}
	}
}

void BoundingBox::SetActive(bool isActive)
{
	this->isActive = isActive;
	if (isActive)
	{
		cb->SwitchOn();
	}
	else
		cb->SwitchOff();

}

void BoundingBox::SetColor(Color color)
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		for (VertexColor& v : vertices)
			v.color = color;

		memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());
	}
	DC->Unmap(vb->GetResource(), 0);

}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
	if (!a || !b)
		return false;

	if (a->isActive && b->isActive)
	{
		RectEdge aEdge = *a->edge;
		RectEdge bEdge = *b->edge;

		if (aEdge.RB.x >= bEdge.LT.x &&
			aEdge.LT.x <= bEdge.RB.x &&
			aEdge.LT.y >= bEdge.RB.y &&
			aEdge.RB.y <= bEdge.LT.y)
			return true;

	}

	return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
	AxisData ad = *a->data;
	AxisData bd = *b->data;

	Vector3 centerDir, axis;
	float centerProjDist, r1, r2;

	centerDir = ad.centerPos - bd.centerPos;

	if (a->isActive && b->isActive)
	{
		// a Rect : X axis
		{
			axis = ad.axisDir[x];

			centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

			r1 = ad.axisLen[x];
			r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
				abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

			if (centerProjDist > r1 + r2)
				return false;
		}

		// a Rect : Y axis
		{
			axis = ad.axisDir[y];

			centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

			r1 = ad.axisLen[y];
			r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
				abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

			if (centerProjDist > r1 + r2)
				return false;
		}

		// b Rect : X axis
		{
			axis = bd.axisDir[x];

			centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

			r1 = bd.axisLen[x];
			r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
				abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

			if (centerProjDist > r1 + r2)
				return false;
		}

		// b Rect : Y axis	
		{
			axis = bd.axisDir[y];

			centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

			r1 = bd.axisLen[y];
			r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
				abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

			if (centerProjDist > r1 + r2)
				return false;
		}


		return true;
	}

	else
		return false;
	
}

void BoundingBox::Push()
{
	if (cols.count(tag))
		cols.find(tag)->second.push_back(this);
	else
	{
		cols.insert(make_pair(tag, vector<BoundingBox*>()));
		cols.find(tag)->second.push_back(this);
	}

}

vector<BoundingBox*> BoundingBox::GetTagCollision(Tag tag)
{
	if (cols.count(tag))
		return cols.find(tag)->second;
	else
		assert(false);
}
