#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
	: filePath(filePath)
{
	Textures::Load(this);
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
	D3D11_TEXTURE2D_DESC srcDesc;	// 원본
	texture->GetDesc(&srcDesc);		// 원보에 데이터 복사

	D3D11_TEXTURE2D_DESC destDesc;	// 텍스처 정보의 복사본
	Zero(destDesc);

	// 복사할 텍스처 desc 설정
	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	destDesc.Width = srcDesc.Width;
	destDesc.Height = srcDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srcDesc.Format;
	destDesc.SampleDesc = srcDesc.SampleDesc;

	ID3D11Texture2D* destTex = nullptr;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &destTex); // 복사할 텍스처 생성
	CHECK(hr);
	// 원본 텍스처에서 복사할 텍스처로 데이터를 복사
	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

	// 픽셀 개수 계산
	int pixelNum = destDesc.Width * destDesc.Height;

	// 픽셀 데이터를 저장할 배열
	UINT* colors = new UINT[destDesc.Width * destDesc.Height];

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subResource);
	{
		// 데이터를 colors 배열에 복사
		memcpy(colors, subResource.pData, sizeof(UINT) * destDesc.Width * destDesc.Height);
	}
	DC->Unmap(destTex, 0);

	UINT* alpha = new UINT[pixelNum];
	UINT* red = new UINT[pixelNum];
	UINT* green = new UINT[pixelNum];
	UINT* blue = new UINT[pixelNum];

	for (int i = 0; i < pixelNum; i++)
	{
		red[i] = (colors[i] & 0xff000000);
		green[i] = (colors[i] & 0x00ff0000);
		blue[i] = (colors[i] & 0x0000ff00);
		alpha[i] = (colors[i] & 0x000000ff);

		red[i] = colors[i] >> 16;
		blue[i] = colors[i] << 16;

		colors[i] = alpha[i] | red[i] | green[i] | blue[i];
	}

	// pixels 벡터에 colors 배열의 데이터 전달
	pixels->assign(&colors[0], &colors[pixelNum - 1]);

	SAFE_DELETE_ARRAY(colors);
	SAFE_RELEASE(destTex);

}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_RELEASE(desc.srv);
}

void Textures::Load(Texture2D* texture)
{
	HRESULT hr;
	TexMetadata metaData;

	wstring ext = Path::GetExtension(texture->filePath);
	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}
	else
	{
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	UINT width = metaData.width;
	UINT height = metaData.height;

	TextureDesc desc;
	desc.filePath = texture->filePath;
	desc.width = width;
	desc.height = height;

	TextureDesc exist;
	bool bExist = false;
	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			bExist = true;
			exist = temp;

			break;
		}
	}

	if (bExist == true)
	{
		texture->srv = exist.srv;
		texture->metaData = metaData;
	}
	else
	{
		ScratchImage image;

		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}
		else
		{
			hr = LoadFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView* srv = nullptr;
		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), metaData, &srv);
		CHECK(hr);

		SRV::Get()->AddSRV(String::ToString(texture->filePath), srv);

		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;

		descs.push_back(desc);
	}
}
