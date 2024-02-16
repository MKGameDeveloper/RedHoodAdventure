#include "Framework.h"
#include "AnimationRect.h"


AnimationRect::AnimationRect(Vector3 position, Vector3 size, float rotation, Pivot p)
	: TextureRect(position, size, rotation, p)
{
	SetShader(ShaderPath + L"Animation.hlsl");

	// Sampler
	{
		// 선형 보간
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		// point sampling
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}


	// Blend
	{
		// 블렌드 비활성화
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);

		// 블렌드 활성화
		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);
	}

}

AnimationRect::~AnimationRect()
{
	
}


void AnimationRect::Update(Vector3 position, Vector3 size, float rotation, Pivot p)
{
	this->size = size;
	this->rotation = rotation;
	this->position = position;

	animator->Update();

	MapVertexBuffer();
	{
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;
	}
	UnmapVertexBuffer();

	UpdateWorld();

}

void AnimationRect::UpdateUI()
{
	Vector3 cpos = Camera::Get()->GetPosition() + Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0.0f);

	position = originalposition + cpos;

	animator->Update();

	MapVertexBuffer();
	{
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;
	}
	UnmapVertexBuffer();

	UpdateWorld();
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xffffffff);

	__super::Render();
}


