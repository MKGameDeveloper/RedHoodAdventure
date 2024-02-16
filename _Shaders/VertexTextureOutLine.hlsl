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
    float3 greyScale = 0;
	
	// Line
	{
		if(input.uv.x < .01f || input.uv.x > .99f || input.uv.y < .01f || input.uv.y > .99f)
            return float4(1, 1, 1, 1);
		
        if (input.uv.x < .51f && input.uv.x > .49f)
            return float4(1, 1, 1, 1);
		
		if (input.uv.y < .51f && input.uv.y > .49f)
            return float4(1, 1, 1, 1);
    }
	
	{
        if (input.uv.x < 0.5f && input.uv.y < 0.5f)
        {
			// AM
            color = _sourceTex.Sample(_samp, float2(input.uv.x * 2.0f, input.uv.y * 2.0f));
            greyScale = dot(color.rgb, float3(.299f, .587f, .114f));
			
            color = float4(greyScale, 1);
			

        }
        else if (input.uv.x >= 0.5f && input.uv.y < 0.5f)
        {
			// Sepia
            color = _sourceTex.Sample(_samp, float2((input.uv.x - .5f) * 2.0f, input.uv.y * 2.f));
            float r, g, b;
            r = dot(color.rgb, float3(0.393f, 0.769f, 0.189f));
            g = dot(color.rgb, float3(0.393f, 0.686f, 0.168f));
            b = dot(color.rgb, float3(0.272f, 0.534f, 0.131f));
			
            greyScale = float3(r,g,b);
            color = float4(greyScale, 1);
        }
        else if (input.uv.x < 0.5f && input.uv.y >= 0.5f)
        {
			// Negative
            //float3 negative = 1 - abs(color.rgb);
            //resultColor = float4(negative, color.a);
			
			// ȭ�鸸 ����
            color = _sourceTex.Sample(_samp, float2(input.uv.x * 2.0f, (input.uv.y - .5f) * 2.f));
            
        }
        else if (input.uv.x >= 0.5f && input.uv.y >= 0.5f)
        {
			// Posterize
            //float3 value = float3(4.0f, 4.0f, 4.0f);
            //float3 posterize = round(color.rgb * value) / value;
			
            //greyScale = dot(color.rgb, float3(.299f, .587f, .114f));
			
			// ���ϴ� �������� ���� ä���
            color = _sourceTex.Sample(_samp, float2((input.uv.x - .5f) * 2.0f, (input.uv.y - .5f) * 2.f));
            float3 RGB = float3(1.f, 0.5f, 0.5f);
            color = float4(RGB, 1);
        }
    }
	
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