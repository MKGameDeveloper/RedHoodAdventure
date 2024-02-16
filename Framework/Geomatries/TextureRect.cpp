#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path, Pivot p)
	: position(position), size(size), rotation(rotation)
{
	originalposition = position;

	Init(position, size, rotation, p);

	// Shader Resource View
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			DEVICE,
			path.c_str(),
			nullptr,
			nullptr,
			&srv,
			nullptr
		);
		CHECK(hr);
		SRV::Get()->AddSRV(String::ToString(path), srv);
	}

	UpdateWorld();
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, Pivot p)
	: position(position), size(size), rotation(rotation)
{
	originalposition = position;

	Init(position, size, rotation, p);
	UpdateWorld();

}

TextureRect::~TextureRect()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(ib);
	SAFE_DELETE(vs);
	SAFE_DELETE(ps);
	SAFE_DELETE(il);
	SAFE_DELETE(wb);
	//SAFE_RELEASE(srv);
}

void TextureRect::Init(Vector3 position, Vector3 size, float rotation, Pivot p)
{
	// vertices
	{
		vertices.assign(4, VertexTexture());

	}

	// Vertex Buffer
	{
		vb = new VertexBuffer();
	}

	// Index Buffer
	{
		indices = { 0,1,2,0,3,1 };

		ib = new IndexBuffer();
	}

	SetPivot(p);

	// Vertex Shader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	// Pixel Shader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	// InputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	// World Buffer
	{
		wb = new WorldBuffer();
	}
}

void TextureRect::SetShader(wstring shaderpath)
{
	vs->Clear();
	ps->Clear();

	vs->Create(shaderpath, "VS");
	ps->Create(shaderpath, "PS");

}


void TextureRect::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TextureRect::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}

void TextureRect::Update(Vector3 position, Vector3 size, float rotation, Pivot p)
{
	this->size = size;
	this->rotation = rotation;
	this->position = position;

	UpdateWorld();
}

void TextureRect::UpdateWorld()
{
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));

	world = S * R * T;
	wb->SetWorld(world);
}

void TextureRect::UpdateUI()
{
	Vector3 cpos = Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);

	this->position = originalposition + cpos;

	UpdateWorld();
}

void TextureRect::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();
	wb->SetVSBuffer(0);

	DC->PSSetShaderResources(0, 1, &srv);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{

}

void TextureRect::SetPivot(Pivot p)
{
	switch (p)
	{
	case MIDLE_CENTER:

		vertices[0].position = Vector3(-0.5f, -0.5f, +0.0f);
		vertices[1].position = Vector3(+0.5f, +0.5f, +0.0f);
		vertices[2].position = Vector3(+0.5f, -0.5f, +0.0f);
		vertices[3].position = Vector3(-0.5f, +0.5f, +0.0f);

		break;

	case MIDLE_LEFT:

		vertices[0].position = Vector3(+0.0f, -0.5f, +0.0f);
		vertices[1].position = Vector3(+1.0f, +0.5f, +0.0f);
		vertices[2].position = Vector3(+1.0f, -0.5f, +0.0f);
		vertices[3].position = Vector3(+0.0f, +0.5f, +0.0f);

		break;

	case MIDLE_RIGHT:

		vertices[0].position = Vector3(-1.0f, -0.5f, +0.0f);
		vertices[1].position = Vector3(+0.0f, +0.5f, +0.0f);
		vertices[2].position = Vector3(+0.0f, -0.5f, +0.0f);
		vertices[3].position = Vector3(-1.0f, +0.5f, +0.0f);

		break;

	case UP_CENTER:

		vertices[0].position = Vector3(-0.5f, -1.0f, +0.0f);
		vertices[1].position = Vector3(+0.5f, +0.0f, +0.0f);
		vertices[2].position = Vector3(+0.5f, -1.0f, +0.0f);
		vertices[3].position = Vector3(-0.5f, +0.0f, +0.0f);

		break;

	case UP_LEFT:

		vertices[0].position = Vector3(+0.0f, -1.0f, +0.0f);
		vertices[1].position = Vector3(+1.0f, +0.0f, +0.0f);
		vertices[2].position = Vector3(+1.0f, -1.0f, +0.0f);
		vertices[3].position = Vector3(+0.0f, +0.0f, +0.0f);

		break;

	case UP_RIGHT:

		vertices[0].position = Vector3(-1.0f, -1.0f, +0.0f);
		vertices[1].position = Vector3(+0.0f, +0.0f, +0.0f);
		vertices[2].position = Vector3(+0.0f, -1.0f, +0.0f);
		vertices[3].position = Vector3(-1.0f, +0.0f, +0.0f);

		break;

	case DOWN_CENTER:

		vertices[0].position = Vector3(-0.5f, +0.0f, +0.0f);
		vertices[1].position = Vector3(+0.5f, +1.0f, +0.0f);
		vertices[2].position = Vector3(+0.5f, +0.0f, +0.0f);
		vertices[3].position = Vector3(-0.5f, +1.0f, +0.0f);

		break;

	case DOWN_LEFT:

		vertices[0].position = Vector3(+0.0f, +0.0f, +0.0f);
		vertices[1].position = Vector3(+1.0f, +1.0f, +0.0f);
		vertices[2].position = Vector3(+1.0f, +0.0f, +0.0f);
		vertices[3].position = Vector3(+0.0f, +1.0f, +0.0f);

		break;

	case DOWN_RIGHT:

		vertices[0].position = Vector3(-1.0f, +0.0f, +0.0f);
		vertices[1].position = Vector3(+0.0f, +1.0f, +0.0f);
		vertices[2].position = Vector3(+0.0f, +0.0f, +0.0f);
		vertices[3].position = Vector3(-1.0f, +1.0f, +0.0f);

		break;

	default:
		break;
	}
	vertices[0].uv = Vector2(0, 1);
	vertices[1].uv = Vector2(1, 0);
	vertices[2].uv = Vector2(1, 1);
	vertices[3].uv = Vector2(0, 0);


	vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

}
