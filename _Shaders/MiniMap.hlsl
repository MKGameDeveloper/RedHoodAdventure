struct VertexInput
{
	float4 position : POSITION0;		// ���� ��ġ		"position"�̶�� ������ "POSITION0" ��Ʈ���� ��ġ�� ���� ������ �����Ѵ�
	float2 uv : TEXCOORD0;				// uv ��ǥ
};

struct PixelInput
{
	float4 position : SV_POSITION0;		// �ȼ� ��ġ		�ȼ��� ��ġ�� ��Ÿ���� �ý��� ���� �ǹ�
    float2 uv : TEXCOORD0;				// �ȼ� ����
};

// cbuffer : ��� ���� �������� (constant buffer)
// ��� ���� �������� b0�� �Ҵ�� ���� ����� �����ϴ� ��� ����
cbuffer WorldBuffer : register(b0)	// 0 ~ 127
{
	matrix _world;
}

// ��� ���� �������� b1�� �Ҵ�� ��, �������� ����� �����ϴ� ��� ����
cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _projection;
}

// ���� ���̴� �Լ�
// �Է����� VertexInput�� �ް� PixelInput ����ü�� ��ȯ
PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.position = mul(input.position, _world);			// ���� ��ġ�� ���� ����� ����
	output.position = mul(output.position, _view);			// ����� �� ����� ����
	output.position = mul(output.position, _projection);	// ����� �������� ����� ����

	output.uv = input.uv;
	return output;

}

Texture2D _sourceTex : register(t0);	// �ؽ�ó �����͸� ����
SamplerState _samp : register(s0);		// ���ø��ϴ� ����� ����

// �ȼ� ���̴� �Լ�
// �Է����� PixelInput ����ü�� �ް�, float4 ������ �ȼ� ������ ��ȯ
float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
	
	
	
    
	
    return color;
}

/*
Semantic : ����ƽ
	- HLSL ���̴����� �������� �ǹ̸� �����ϴµ� ���
	- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ����
	- ���� �̸� �ڿ� ':' ��ȣ�� �Բ� ����
	- �ý��� �� ����ƽ�� 'SV_' ���λ�� �����Ͽ� Direct3D���� ���ǵ� Ư���� �ǹ̸� ����
	- �ý��� �� ����ƽ ���̴� �������� ���� �����͸� �����ϴµ� ���

slot
	- GPU���� ����ϴ� ��� ����, �ؽ�ó, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
	- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��
	- register��� Ű���带 ����Ͽ� ����
	- �� �ڿ��� � ���Կ� �Ҵ�� ������ ��������� ������ �� ����
	- �ֿ� ����
		1) ��� ���� ����
			- ��� �����͸� �����ϴµ� ���, VS�� PS���� ������ �� �ִ�
			- ��� ���� ������ register(b#)�� ����Ͽ� ����

		2) �ؽ�ó ����
			- �̹��� �����͸� �����ϴµ� ���
			- �ؽ�ó ���� ������ register(t#)�� ����Ͽ� ����

		3) ���÷� ����
			- �ؽ�ó�� ���ø� �ϴµ� ���
			- ���÷� ������ register(s#)�� ����Ͽ� ����

cbuffer = Constance Buffer : ��� ����
	- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
	- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� ����
	- ��� ���� ���ο��� ���� ���� ������ ������ �� �ִ�.

Sampler : ���÷�
	- �ؽ�ó���� �ȼ� ���� �������� ����� �����ϴ� ��ü
	- �ؽ�ó ���ø��� �ؽ�ó �̹����� ���� �ؼ� ���� ����ϴ� �۾�
	  (�ؼ� : �ؽ�ó�� �ȼ� ��)

*/