#include "Framework.h"
#include "States.h"

D3D11_RASTERIZER_DESC       States::rsDesc;
D3D11_DEPTH_STENCIL_DESC    States::dsDesc;
D3D11_SAMPLER_DESC          States::spDesc;
D3D11_BLEND_DESC            States::blDesc;

void States::Create()
{
	CreateRasterizerDesc();
	CreateDepthStencilDesc();
	CreateSamplerDesc();
	CreateBlendDesc();
}

void States::GetRasterizerDesc(D3D11_RASTERIZER_DESC* desc)
{
    memcpy(desc, &rsDesc, sizeof(rsDesc));
}

void States::GetDepthStencilDesc(D3D11_DEPTH_STENCIL_DESC* desc)
{
    memcpy(desc, &dsDesc, sizeof(dsDesc));
}

void States::GetSamplerDesc(D3D11_SAMPLER_DESC* desc)
{
    memcpy(desc, &spDesc, sizeof(spDesc));
}

void States::GetBlendDesc(D3D11_BLEND_DESC* desc)
{
    memcpy(desc, &blDesc, sizeof(blDesc));
}

void States::CreateRasterizer(D3D11_RASTERIZER_DESC* desc, ID3D11RasterizerState** state)
{
    HRESULT hr = DEVICE->CreateRasterizerState(desc, state);
    CHECK(hr);
}

void States::CreateDepthStencil(D3D11_DEPTH_STENCIL_DESC* desc, ID3D11DepthStencilState** state)
{
    HRESULT hr = DEVICE->CreateDepthStencilState(desc, state);
    CHECK(hr);
}

void States::CreateSampler(D3D11_SAMPLER_DESC* desc, ID3D11SamplerState** state)
{
    HRESULT hr = DEVICE->CreateSamplerState(desc, state);
    CHECK(hr);
}

void States::CreateBlend(D3D11_BLEND_DESC* desc, ID3D11BlendState** state)
{
    HRESULT hr = DEVICE->CreateBlendState(desc, state);
    CHECK(hr);
}

void States::CreateRasterizerDesc()
{
    Zero(rsDesc);
    rsDesc.FillMode = D3D11_FILL_SOLID;     // 다각형의 채우기 모드
    rsDesc.CullMode = D3D11_CULL_BACK;      // 후면 컬링 사용 설정
    rsDesc.FrontCounterClockwise = false;   // 전면 면의 방향을 시계 방향으로 설정
    rsDesc.DepthBias = 0;                   // 깊이 바이어스 값
    rsDesc.DepthBiasClamp = .0f;            // 깊이 바이어스 클램프 값
    rsDesc.SlopeScaledDepthBias = .0f;      // 검사도에 따른 깊이 바이어스 값
    rsDesc.ScissorEnable = false;           // 가위 테스트 사용 설정 (렌더링 대상의 특정 영역만 렌더링하는데 사용)
    rsDesc.MultisampleEnable = false;       // 멀티 샘플링 사용 설정 (픽셀 경계의 부드러움을 증가시켜서 이미지 품질을 향상)
    rsDesc.AntialiasedLineEnable = false;   // 선 안티엘리어싱 사용 설정 (선의 경계를 부드럽게)
}

void States::CreateDepthStencilDesc()
{
    Zero(dsDesc);
    dsDesc.DepthEnable              = true;                         // 깊이 테스트 사용설정
    dsDesc.DepthWriteMask           = D3D11_DEPTH_WRITE_MASK_ALL;   // 깊이 버퍼의 모든 비트에 대해
    dsDesc.DepthFunc                = D3D11_COMPARISON_LESS;        // 깊이 테스트 함수를 LESS로 설정
                                                                     
    dsDesc.StencilEnable            = true;                         // 스텐실 테스트 사용 설정
    dsDesc.StencilReadMask          = 0xff;                         // 스텐실 버퍼에서 읽을 수 있는 비트 마스크 설정 
    dsDesc.StencilWriteMask         = 0xff;                         // 스텐실 테스트를 사용하도록 설정
                                                                     
    dsDesc.FrontFace.StencilFailOp  = D3D11_STENCIL_OP_KEEP;        // 전면 면의 스텐실 실패 작업 설정
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;    // 전면 면의 스텐실 깊이 실패 작업 설정
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;         // 전면 면의 스텐실 패스 작업 설정
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;         // 전면 면의 스텐실 함수 설정
                                                                    
    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;          // 후면 면의 스텐실 실패 작업 설정
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;     // 후면 면의 스텐실 깊이 실패 작업 설정
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;          // 후면 면의 스텐실 패스 작업 설정
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;          // 후면 면의 스텐실 함수 설정
}

void States::CreateSamplerDesc()
{
    Zero(spDesc);                                       
    spDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;    // 선행 필터링을 사용하여 텍스터를 샘플링
    spDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;       // U 좌표에 대해 텍스처 좌표를 래핑
    spDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;       // V 좌표에 대해 텍스처 좌표를 래핑
    spDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;       // W 좌표에 대해 텍스처 좌표를 래핑
    spDesc.MaxAnisotropy = 1;                           // 아니소프트로피 필터링에서 사용 (사용안함)
    spDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;    // 비교 샘플링에서 사용 (사용안함)
    spDesc.MinLOD = FLT_MIN;                            // 텍스처의 최소 LOD 레벨 생성
    spDesc.MaxLOD = FLT_MAX;                            // 텍스처의 최소 LOD 레벨 생성
}

void States::CreateBlendDesc()
{
    Zero(blDesc);
    blDesc.AlphaToCoverageEnable;                                   // Alpha to Coverage 사용 여부
    blDesc.IndependentBlendEnable;                                  // 독립적인 블랜드 사용 여부
                                                                     
    blDesc.RenderTarget[0].BlendEnable = false;                     // 렌더 타겟에 대한 블렌딩 사용 여부
    blDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;        // 목적지 색상에 대한 블렌드 인수를 설정
    blDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;   // 소스 색상에 대한 블렌드 인수를 설정
    blDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;            // 색상에 대한 블렌드 연산을 설정
                                                                    
    blDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;        // 목적지 알파에 대한 블렌드 인수를 설정
    blDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;        // 소스 알파에 대한 블렌드 인수를 설정
    blDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;       // 알파에 대한 블렌드 연산을 설정
                                                                                    
    blDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;    // 모든 색상 채널이 렌더 타겟에 기록
}
