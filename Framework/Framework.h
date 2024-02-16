#pragma once

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

struct Status
{
	float currentAtk = 0;
	float Atk = 20;
	float plusAtk = 0;

	float currentDef = 0;
	float Def = 10;
	float plusDef = 0;

	float currentHp = 100;
	float MaxHp = 0;
	float Hp = 100;
	float plusHp = 0;

	float currentStamina = 100;
	float MaxStamina = 0;
	float Stamina = 100;
	float plusStamina = 0;

};

typedef enum Attack
{
	NORMAL = 0,
	KNOCKBACK,
	RISE_UP,
	GRAB,
	SUPER_KNOCKBACK,


}Attack;

// 사용할 열거형
enum Pivot
{
	MIDLE_CENTER = 0,
	MIDLE_LEFT,
	MIDLE_RIGHT,
	UP_CENTER,
	UP_LEFT,
	UP_RIGHT,
	DOWN_CENTER,
	DOWN_LEFT,
	DOWN_RIGHT
};

// 캐릭터 INPUT 상태
enum StateCheck
{
	None = 0,
	IsMove = 1 << 0,
	bInput = 1 << 1,
	IsGround = 1 << 2,
	IsWall = 1 << 3,
	bMove = 1 << 4,
	bAttack = 1 << 5,
	MaxState = 63,
};

enum Type
{
	NonePass,
	Pass,
	UpPass,

	LeftSide,
	LeftSideDown,
	LeftSideUp,

	RightSide,
	RightSideDown,
	RightSideUp,

	Left_45,
	Left_45_Half,
	Right_45,
	Right_45_Half,

	LeftUp_Half,
	RightUp_Half,

	Up_Half,
	Down_Half,
};

//enum behavior
//{
//	Attack,
//	Jump,
//	Run,
//
//};

//미리 컴파일된 헤더.
//pch pre compiled header

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <fstream>

using namespace std;

//DirectX
#include <DirectXTex/DirectXTex.h>
#pragma comment(lib, "DirectXTex/DirectXTex.lib")

#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")
//////////////////////////////////////////
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//////////////////////////////////////////
//ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#pragma comment(lib, "ImGui/ImGui.lib")

//////////////////////////////////////////
//FMOD
#include "FMOD/inc/fmod.hpp"

#ifdef _WIN64
#pragma comment(lib, "FMOD/lib/x64/fmod_vc.lib")
#else
#pragma comment(lib, "FMOD/lib/x86/fmod_vc.lib")
#endif


/////////////////////////////////////////
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXMATRIX  Matrix;
typedef D3DXCOLOR   Color;
typedef UINT		uint;


#include "Interfaces/IObject.h"

#include "Utilities/SingletonBase.h"

#include "Systems/Graphics.h"
#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"
#include "Systems/Time.h"
#include "Systems/Sounds.h"
#include "Systems/SRV.h"
#include "Systems/Text.h"
#include "Systems/PlayerStatus.h"

#include "Utilities/Gui.h"

#define DEVICE Graphics::Get()->GetDevice()
#define DC     Graphics::Get()->GetDC()

#define CHECK(p) assert(SUCCEEDED(p))
#define Zero(p) ZeroMemory(&p, sizeof(p))

#define SAFE_DELETE(p)		 { if(p) { delete(p);	   (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[](p);	   (p) = nullptr; } }
#define SAFE_RELEASE(p)		 { if(p) { (p)->Release(); (p) = nullptr; } }

#include "Utilities/DirectHelper.h"

#include "Renders/Resources/VertexType.h"
#include "Renders/Resources/ShaderBuffer.h"
#include "Renders/Resources/GlobalBuffer.h"

#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"

#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"

#include "Renders/Resources/Texture2D.h"

#include "Renders/States.h"

#include "Utilities/BoundingBox.h"
#include "Utilities/String.h"
#include "Utilities/Path.h"
#include "Utilities/GameObject.h"

#include "Game/Manager/MapManager.h"


#include "Systems/Camera.h"


#define WinMaxWidth 1280
#define WinMaxHeight 720

#define MapWidth 2560
#define MapHeight 1440

const wstring ShaderPath  =	L"../_Shaders/";
const wstring TexturePath = L"../_Resources/_Textures/";
const wstring SoundPath   =	L"../_Resources/_Sounds/";

const string TilePath     =	"../_Resources/_TileData/";
const string MapPath      =	"../_Resources/_MapData/";

extern HWND handle;
