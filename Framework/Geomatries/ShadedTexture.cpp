#include "Framework.h"
#include "ShadedTexture.h"

ShadedTexture::ShadedTexture(Vector3 position, Vector3 size, float rotation, wstring path)
	: TextureRect(position, size, rotation, path)
{
	sb = new ShadedBuffer;
	sb->SetTextureSize({ size.x, size.y });

}

ShadedTexture::ShadedTexture(Vector3 position, Vector3 size, float rotation)
	: TextureRect(position, size, rotation)
{
	sb = new ShadedBuffer;
	sb->SetTextureSize({ size.x, size.y });
}

ShadedTexture::~ShadedTexture()
{
	SAFE_DELETE(sb);
}

void ShadedTexture::Rotate180()
{
	/*if (*(TextureRect::GetRot()) > 360.f)
		*(TextureRect::GetRot()) -= 360.f;

	*(TextureRect::GetRot()) += 180.f;*/
}

void ShadedTexture::RotateZero()
{

	//*(TextureRect::GetRot()) = 0.0f;
}

void ShadedTexture::Render()
{
	sb->SetPSBuffer(0);
	TextureRect::Render();
}

void ShadedTexture::GUI()
{
	ImGui::Begin("Shaded");
	{
		ImGui::RadioButton("Nomal", sb->GetSelectionPtr(), 1);
		ImGui::RadioButton("AM", sb->GetSelectionPtr(), 2);
		ImGui::RadioButton("Sepia", sb->GetSelectionPtr(), 3);
		ImGui::RadioButton("Negative", sb->GetSelectionPtr(), 4);
		ImGui::RadioButton("Posterize", sb->GetSelectionPtr(), 5);
		ImGui::SliderInt("BlurCount", sb->GetBlurCountPtr(), 1, 20);
	}
	ImGui::End();
}
