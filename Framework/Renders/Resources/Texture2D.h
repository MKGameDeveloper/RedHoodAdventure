#pragma once

struct TextureDesc
{
	wstring filePath = L"";
	UINT width = 0;
	UINT height = 0;
	ID3D11ShaderResourceView* srv = nullptr;

	bool operator == (const TextureDesc& other)
	{
		bool b = true;

		b &= filePath == other.filePath;
		b &= width == other.width;
		b &= height == other.height;

		return b;
	}
};

class Texture2D
{
public:
	Texture2D(wstring filePath);

	void ReadPixel(vector<Color>* pixels);
	static void ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels);

	ID3D11ShaderResourceView* GetSRV() { return srv; }
	float GetWidth() { return (float)metaData.width; }
	float GetHeight() { return (float)metaData.height; }
	wstring GetFilePath() { return filePath; }

private:
	friend class Textures;
	wstring filePath = L"";
	ID3D11ShaderResourceView* srv = nullptr;
	DirectX::TexMetadata metaData;

};

class Textures
{
public:
	static void Delete();

private:
	friend class Texture2D;

	static void Load(Texture2D* texture);

private:
	static vector<TextureDesc> descs;

};

/*
	DirectTex
		- 텍스처 처리 라이브러리
		- DDS 파일 읽기, 쓰기, 리사이징, 포맷 변환, 미핑맵 생성 등 여러 텍스처 콘텐츠 처리 작업을 수행

	MetaData
		- 너비, 높이, 깊이, 배열 크기, 미핑맵 수 및 형식과 같은 정보를 저장

*/