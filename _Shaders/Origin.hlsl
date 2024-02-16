struct VertexInput
{
    float4 position : POSITION0;       // ���� ��ġ "position"�̶�� ������ "POSITION0" ��Ʈ���� ��ġ�� ���� ������ �����Ѵ�
    float2 uv : TEXCOORD0;             // uv ��ǥ
};

struct PixelInput
{
    float4 position : SV_POSITION0;    // �ȼ� ��ġ     �ȼ��� ��ġ�� ��Ÿ���� �ý��� ���� �ǹ�
    float2 uv : TEXCOORD0;             // �ȼ� ����
};

// cbuffer : ��� ���� ��������
// ��� ���� �������� b0�� �Ҵ�� ���� ����� �����ϴ� ��� ����
cbuffer WorldBuffer : register(b0)  // 0 ~ 127
{
    matrix _world;
}

// ��� ���� �������� b1�� �Ҵ�� ��, �������� ����� �����ϴ� ��� ����
cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
}

cbuffer ShadedBuffer : register(b0)
{
    float2 _imageSize;
    int Selection;
    int _blurCount;
}

// ���� ���̴� �Լ�
// �Է����� VertexInput�� �ް� PixelInput ����ü�� ��ȯ
PixelInput VS(VertexInput input)
{
    PixelInput output;

    output.position = mul(input.position, _world);          // ���� ��ġ�� ���� ����� ����
    output.position = mul(output.position, _view);          // ����� �� ����� ����
    output.position = mul(output.position, _projection);    // ����� �������� ����� ����

    output.uv = input.uv;
    return output;
}

Texture2D _sourceTex : register(t0);    // �ؽ�ó �����͸� ����
SamplerState _samp : register(s0);      // ���ø��ϴ� ����� ����

// �ȼ� ���̴� �Լ�
// �Է����� PixelInput ����ü�� �ް�, float4 ������ �ȼ� ������ ��ȯ
float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    float4 resultColor = 0;
    
    float2 arr[8] =
    {
        float2(-1, 1),  float2(0, 1),	float2(1, 1),
        float2(-1, 0), /* ���� ����*/	float2(1, 0),
        float2(-1, -1), float2(0, -1),  float2(1, -1)
    };

    // �� ī��Ʈ ��ŭ �ݺ�
    for (int blur = 1; blur < _blurCount; blur++)
    {
        // �ֺ� �ȼ��鿡 ���� �ݺ�
        for (int i = 0; i < 8; i++)
        {
            // �Է� �ؽ�ó���� ���ø��� �ֺ� �ȼ����� ������� ��ġ�� ���
            float x = arr[i].x * (float)blur / _imageSize.x;
            float y = arr[i].y * (float)blur / _imageSize.y;

            // ���ο� uv ��ǥ ���
            float2 uv = input.uv + float2(x, y);

            // �Է� �ؽ�ó�� ������ �߰��� ���ø��Ͽ� ����
            color += _sourceTex.Sample(_samp, uv);
        }

    }

    // �� �ݺ� Ƚ��
    int blurInerations = _blurCount - 1;
    // ������ ����
    int offsetCount = 8;
    // ��ü ���ø� ����
    int totalSamples = blurInerations * offsetCount + 1;

    color /= totalSamples;

   
    if (Selection == 1)
    {
        return color;
    }
    else if (Selection == 2)
    {
        // AM
        float3 temp;
        temp = dot(color.rgb, float3(0.299f, 0.587f, 0.114f));
        resultColor = float4(temp, color.a);
    }
    else if (Selection == 3)
    {
        // Sepia
        float3 gray = float3(0.393f, 0.769f, 0.189f);
        float3 temp = dot(color.rgb, gray);
        temp.r += 0.2f;
        temp.g += 0.1f;
        resultColor = float4(temp, color.a);
    }
    else if (Selection == 4)
    {
        // Negative
        float3 negative = 1 - abs(color.rgb);
        resultColor = float4(negative, color.a);
    }
    else if (Selection == 5)
    {
        // Posterize
        float3 value = float3(4.0f, 4.0f, 4.0f);
        float3 posterize = round(color.rgb * value) / value;
        resultColor = float4(posterize, color.a);
    }


    

    return resultColor;
}

/*
Semantic : ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴµ� ���
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ����
- ���� �̸� �ڿ� ':'��ȣ�� �Բ� ����
- �ý��� �� ����ƽ�� 'SV_'���λ�� �����ϸ� Direct3D���� ���ǵ� Ư���� �ǹ̸� ����
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���

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
    - �ؽ�ó�� ���ø� �ϴ� �� ���
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