#pragma once

#include "FootHolder.h"

class BackFloor : public FootHolder
{
public:
	BackFloor(Vector3 position, Vector3 size, float rotation);
	~BackFloor();

	virtual void Update() override;
	virtual void Render() override;

};
