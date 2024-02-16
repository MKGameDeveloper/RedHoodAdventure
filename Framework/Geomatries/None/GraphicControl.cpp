#include "Framework.h"
#include "GraphicControl.h"
//
//GraphicControl::GraphicControl(Vector3 position, Vector3 size, float rotation, wstring path, Pivot p)
//	:position(position), size(size), rotation(rotation)
//{
//	tr = new TextureRect(position, size, rotation, path, p);
//}
//
//GraphicControl::GraphicControl(Vector3 position, Vector3 size, float rotation, Anim banim, Pivot p)
//	: position(position), size(size), rotation(rotation), _kind(banim)
//{
//	switch (_kind)
//	{
//	case GraphicControl::TEXTURE:
//		tr = new TextureRect(position, size, rotation, p);
//		break;
//	case GraphicControl::ANIMATION:
//		ar = new AnimationRect(position, size, rotation, p);
//		break;
//	}
//}
//
//GraphicControl::~GraphicControl()
//{
//	switch (_kind)
//	{
//	case GraphicControl::TEXTURE:
//		SAFE_DELETE(tr);
//		break;
//	case GraphicControl::ANIMATION:
//		SAFE_DELETE(ar);
//		break;
//	}
//}
//
//Vector3* GraphicControl::GetPos()
//{
//	switch (_kind)
//	{
//	case GraphicControl::TEXTURE:
//		return tr->GetPos();
//	case GraphicControl::ANIMATION:
//		return ar->GetPos();
//	}
//}
//
//float* GraphicControl::GetRot()
//{
//	switch (_kind)
//	{
//	case GraphicControl::TEXTURE:
//		return tr->GetRot();
//	case GraphicControl::ANIMATION:
//		return ar->GetRot();
//	}
//}
//
//
//const Vector3 GraphicControl::GetSize()
//{
//	switch (_kind)
//	{
//	case GraphicControl::TEXTURE:
//		return tr->GetSize();
//	case GraphicControl::ANIMATION:
//		return ar->GetSize();
//	}
//}
//
//const float GraphicControl::GetRotation()
//{
//	switch (_kind)
//	{
//	case GraphicControl::TEXTURE:
//		return tr->GetRotation();
//	case GraphicControl::ANIMATION:
//		return ar->GetRotation();
//	}
//}
//
//void GraphicControl::SetPivot(Pivot p)
//{
//	switch (_kind)
//	{
//	case GraphicControl::TEXTURE:
//		tr->SetPivot(p);
//		break;
//	case GraphicControl::ANIMATION:
//		ar->SetPivot(p);
//		break;
//	}
//}
//
//
//void GraphicControl::Update()
//{
//	switch (_kind)
//	{
//	case GraphicControl::TEXTURE:
//		tr->Update();
//		break;
//	case GraphicControl::ANIMATION:
//		ar->Update();
//		break;
//	}
//}
//
//void GraphicControl::Render()
//{
//	switch (_kind)
//	{
//	case GraphicControl::TEXTURE:
//		tr->Render();
//		break;
//	case GraphicControl::ANIMATION:
//		ar->Render();
//		break;
//	}
//}
