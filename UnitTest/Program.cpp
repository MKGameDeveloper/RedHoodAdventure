#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/08_PlayerDemo.h"
#include "Demos/09_TileMapDemo.h"


void Program::Init()
{
	// Create Buffer
	{
		Camera::Create();
		States::Create();
		TileSet::Create();

		EditMode = false;

		Push(new PlayerDemo);
		Push(new TileMapDemo);

	}
}

void Program::Destroy()
{
	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
	Camera::Delete();
}

void Program::Update()
{

	Camera::Get()->Update();

	if (Keyboard::Get()->Down(VK_F9))
	{
		if (EditMode)
			EditMode = false;
		else
			EditMode = true;
	}

	//for (IObject* obj : objs)
	//	obj->Update();

	if(EditMode)
		objs[1]->Update();
	else
		objs[0]->Update();

}

void Program::Render()
{

	Camera::Get()->Render();

	//for (IObject* obj : objs)
	//	obj->Render();
	
	if (EditMode)
		objs[1]->Render();
	else
		objs[0]->Render();

}

void Program::PostRender()
{
	//for (IObject* obj : objs)
	//	obj->PostRender();

	if (EditMode)
		objs[1]->PostRender();
	else
		objs[0]->PostRender();
}

void Program::GUI()
{
	//for (IObject* obj : objs)
	//{
	//	obj->GUI();
	//}

	if (EditMode)
		objs[1]->GUI();
	else
		objs[0]->GUI();
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"Adventure Of RedHood ";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
