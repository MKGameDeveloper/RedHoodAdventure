#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject(Vector3 position, Vector3 size, float rotation, Pivot p)
	: position(position), size(size), rotation(rotation), pivot(p)
{
}

GameObject::~GameObject()
{

}


void GameObject::Update()
{

}


void GameObject::Render()
{

}



