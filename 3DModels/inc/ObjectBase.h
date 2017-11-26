#pragma once

#include "Mesh.h"

class ObjectBase
{
public:
	virtual void draw() = 0;
	virtual void translate(float x, float y, float z) = 0;
	virtual BoundingBox getBoundingBox() = 0;
	virtual void processKeyboard(int key) = 0;
};

