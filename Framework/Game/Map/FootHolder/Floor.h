#pragma once


#include "Utilities/BoundingBox.h"

#include "FootHolder.h"

class Floor : public FootHolder
{
public:
	Floor(Vector3 position, Vector3 size, float rotation, Type type = UpPass);
	~Floor();

	virtual void Update() override;
	virtual void Render() override;

};
